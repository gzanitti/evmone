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
    using uint = UintT;

    const uint mod;  ///< The modulus.

private:
    const uint m_r_squared;    ///< R² % mod.
    const uint64_t m_mod_inv;  ///< The modulus inversion.

public:
    explicit ModArith(const UintT& modulus) noexcept;

    /// Converts a value to Montgomery form.
    uint to_mont(const uint& x) const noexcept;

    /// Converts a value in Montgomery form back to normal value.
    uint from_mont(const uint& x) const noexcept;

    /// Performs a Montgomery modular multiplication. Inputs must be in Montgomery form.
    uint mul(const uint& x, const uint& y) const noexcept;

    /// Performs a modular addition.
    uint add(const uint& x, const uint& y) const noexcept;

    /// Performs a modular subtraction.
    uint sub(const uint& x, const uint& y) const noexcept;
};
}  // namespace evmmax
