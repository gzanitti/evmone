// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2023 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0

#include "../utils/bytecode.hpp"
#include "state_transition.hpp"

using namespace evmc::literals;
using namespace evmone::test;

TEST_F(state_transition, transient_storage)
{
    rev = EVMC_CANCUN;
    const auto tbump = 0xb0_address;

    tx.to = To;
    pre.insert(tbump, {.code = tstore(0, add(tload(0), 1)) + sstore(0, tload(0))});
    pre.insert(*tx.to, {.code = call(tbump).gas(0xffff) + call(tbump).gas(0xffff)});

    expect.post[To].exists = true;
    expect.post[tbump].storage[0x00_bytes32] = 0x02_bytes32;
}

TEST_F(state_transition, transient_storage_revert)
{
    rev = EVMC_CANCUN;
    const auto tbump = 0xb0_address;

    tx.to = To;
    pre.insert(tbump, {.code = tstore(0, add(tload(0), 1)) + sstore(0, tload(0))});
    pre.insert(*tx.to,
        {.code = call(tbump).gas(0xffff) + call(tbump).gas(0x1ff) + call(tbump).gas(0xffff)});

    expect.post[To].exists = true;
    expect.post[tbump].storage[0x00_bytes32] = 0x02_bytes32;
}
