// evmone: Fast Ethereum Virtual Machine implementation
// Copyright 2023 The evmone Authors.
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <intx/intx.hpp>

namespace evmmax
{

/// The modular arithmetic operations for EVMMAX (EVM Modular Arithmetic Extensions).
template <typename UintT>
class ModArith
{
public:
    const UintT mod;  ///< The modulus.

private:
    const UintT m_r_squared;   ///< R² % mod.
    const uint64_t m_mod_inv;  ///< The modulus inversion.

public:
    explicit ModArith(const UintT& modulus) noexcept;

    /// Converts a value to Montgomery form.
    UintT to_mont(const UintT& x) const noexcept;

    /// Converts a value in Montgomery form back to normal value.
    UintT from_mont(const UintT& x) const noexcept;

    /// Performs a Montgomery modular multiplication. Inputs must be in Montgomery form.
    UintT mul(const UintT& x, const UintT& y) const noexcept;

    /// Performs a modular addition.
    UintT add(const UintT& x, const UintT& y) const noexcept;

    /// Performs a modular subtraction.
    UintT sub(const UintT& x, const UintT& y) const noexcept;
};
}  // namespace evmmax
