#include "algorithms/simulation/simple_simulation.hpp"
#include "core/circuit.hpp"
#include "core/properties.hpp"
#include "core/syrec/program.hpp"
#include "core/test_functions.hpp"

#include "gtest/gtest.h"
#include <algorithm>
#include <boost/dynamic_bitset.hpp>
#include <boost/range/adaptors.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

using namespace syrec;

class SyrecSimulationTest: public testing::TestWithParam<std::string> {
protected:
    std::string             test_circuits_dir = "./circuits/";
    std::string             file_name;
    boost::dynamic_bitset<> input;
    boost::dynamic_bitset<> output;
    std::vector<int>        set_lines;
    std::string             expected_sim_out;
    std::string             output_string;

    void SetUp() override {
        std::string synthesis_param = GetParam();
        file_name                   = test_circuits_dir + GetParam() + ".src";
        std::ifstream i(test_circuits_dir + "circuits_simulation.json");
        json          j;
        i >> j;
        expected_sim_out = j[synthesis_param]["sim_out"];
        set_lines        = j[synthesis_param]["set_lines"].get<std::vector<int>>();
    }
};

INSTANTIATE_TEST_SUITE_P(SyrecSimulationTest, SyrecSimulationTest,
                         testing::Values(
                                 "alu_2",
                                 "swap_2",
                                 "shift_4"),
                         [](const testing::TestParamInfo<SyrecSimulationTest::ParamType>& info) {
                             auto s = info.param;
                             std::replace( s.begin(), s.end(), '-', '_');
                             return s; });

TEST_P(SyrecSimulationTest, GenericSimulationTest) {
    circuit               circ;
    applications::program prog;
    properties::ptr       settings;
    properties::ptr       statistics;
    std::string           error_string;

    error_string = my_read_program(prog, file_name);
    EXPECT_TRUE(error_string.empty());

    input.resize(circ.lines());

    for (int line: set_lines)
        input.set(line);

    output.resize(circ.lines());

    EXPECT_TRUE(simple_simulation(output, circ, input, settings, statistics));

    boost::to_string(output, output_string);

    EXPECT_EQ(expected_sim_out, boost::adaptors::reverse(output_string));
}