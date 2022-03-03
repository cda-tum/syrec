#include "core/circuit.hpp"
#include "core/syrec/parser.hpp"
#include "core/syrec/program.hpp"
#include "algorithms/simulation/simple_simulation.hpp"
#include "functions.hpp"
#include <core/utils/costs.hpp>
#include <algorithms/synthesis/syrec_synthesis.hpp>
#include <core/properties.hpp>
#include <string>

#include "gtest/gtest.h"

namespace syrec {
    class syrec_test_bitwise_or: public ::testing::Test {
    protected:
        // any objects needed by all tests
        circuit 	circ;
        applications::	program prog;
        std::string	error_string;
        cost_t      qc;
        cost_t      tc;
        properties::ptr settings;
        properties::ptr statistics;
        bool 		okay1;

        void SetUp() override {
            // setup all the individual objects before each test
            error_string = my_read_program(prog, "./circuits/bitwise_or_2.src");
            okay1 = syrec::syrec_synthesis(circ, prog);
            qc = syrec::final_quantum_cost(circ, circ.lines());
            tc = syrec::final_transistor_cost(circ, circ.lines());

        }
    };

    TEST_F(syrec_test_bitwise_or, GenericTest_bitwise_or1) {
        EXPECT_EQ(12, circ.num_gates());
    }

    TEST_F(syrec_test_bitwise_or, GenericTest_bitwise_or2) {
        EXPECT_EQ(8, circ.lines());
    }

    TEST_F(syrec_test_bitwise_or, GenericTest_bitwise_or3) {
        EXPECT_EQ(28, qc);
    }

    TEST_F(syrec_test_bitwise_or, GenericTest_bitwise_or4) {
        EXPECT_EQ(128, tc);
    }


} // namespace syrec
