// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2022 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include "../state/mpt_hash.hpp"
#include "../state/rlp.hpp"
#include "statetest.hpp"
#include <gtest/gtest.h>

namespace evmone::test
{
void run_state_test(
    const StateTransitionTest& test, evmc::VM& vm, bool ignore_state_root, bool ignore_logs)
{
    for (const auto& [rev, cases] : test.cases)
    {
        for (size_t case_index = 0; case_index != cases.size(); ++case_index)
        {
            SCOPED_TRACE(std::string{evmc::to_string(rev)} + '/' + std::to_string(case_index));
            // if (rev != EVMC_FRONTIER)
            //     continue;
            // if (case_index != 3)
            //     continue;

            const auto& expected = cases[case_index];
            const auto tx = test.multi_tx.get(expected.indexes);
            auto state = test.pre_state;

            validate_deployed_code(state, rev);

            const auto res = state::transition(state, test.block, tx, rev, vm);

            // Finalize block with reward 0.
            state::finalize(state, rev, test.block.coinbase, 0, {});

            if (holds_alternative<state::TransactionReceipt>(res))
                if (!ignore_logs)
                    EXPECT_EQ(
                        logs_hash(get<state::TransactionReceipt>(res).logs), expected.logs_hash);
                else
                    EXPECT_TRUE(true);
            else
                EXPECT_TRUE(expected.exception);

            if (!ignore_state_root)
                EXPECT_EQ(state::mpt_hash(state.get_accounts()), expected.state_hash);
            else
            {
                std::cerr << "{";
                std::cerr << R"("stateRoot": ")" << state::mpt_hash(state.get_accounts()) << "\"";
                std::cerr << "}\n";
                EXPECT_TRUE(true);
            }
        }
    }
}
}  // namespace evmone::test
