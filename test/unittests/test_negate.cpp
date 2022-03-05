#include "algorithms/simulation/simple_simulation.hpp"
#include "core/circuit.hpp"
#include "core/syrec/parser.hpp"
#include "core/syrec/program.hpp"
#include "core/test_functions.hpp"

#include "gtest/gtest.h"
#include <algorithms/synthesis/syrec_synthesis.hpp>
#include <core/properties.hpp>
#include <core/utils/costs.hpp>
#include <string>

namespace syrec {
    class syrec_test_negate: public ::testing::Test {
    protected:
        // any objects needed by all tests
        circuit                            circ;
        applications::program              prog;
        std::string                        error_string;
        cost_t                             qc;
        cost_t                             tc;
        std::vector<std::vector<unsigned>> cl;
        std::vector<std::vector<unsigned>> tl;
        std::vector<gate>                  gates_vec;
        properties::ptr                    settings;
        properties::ptr                    statistics;
        bool                               okay1;

        void SetUp() override {
            // setup all the individual objects before each test
            error_string = my_read_program(prog, "./circuits/negate_8.src");
            okay1        = syrec::syrec_synthesis(circ, prog);
            qc           = syrec::final_quantum_cost(circ, circ.lines());
            tc           = syrec::final_transistor_cost(circ, circ.lines());
            gates_vec    = ct_gates(circ);
            for (gate i: gates_vec) {
                cl.push_back(control_lines_check(i));
                tl.push_back(target_lines_check(i));
            }
        }
    };

    TEST_F(syrec_test_negate, GenericTest_negate1) {
        EXPECT_EQ(48, circ.num_gates());
    }

    TEST_F(syrec_test_negate, GenericTest_negate2) {
        EXPECT_EQ(8, circ.lines());
    }

    TEST_F(syrec_test_negate, GenericTest_negate3) {
        EXPECT_EQ(1740, qc);
    }

    TEST_F(syrec_test_negate, GenericTest_negate4) {
        EXPECT_EQ(896, tc);
    }

} // namespace syrec
