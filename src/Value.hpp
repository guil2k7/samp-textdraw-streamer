// Taken from https://github.com/guil2k7/samp-plugin-sdk

// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include "amx.h"

enum PawnValueType {
    Undefined,
    UInt,
    Int,
    Float,
    String,
    Array,
};

class PawnValue {
public:
    PawnValue() : type(PawnValueType::Undefined) {}
    
    inline PawnValue(PawnValue&& that) {
        *this = std::move(that);
    }

    PawnValue(PawnValue const& that) = delete;

    ~PawnValue();

    cell push(AMX* amx) const;

    PawnValue& operator =(PawnValue const& that) = delete;
    PawnValue& operator =(PawnValue&& that);

    PawnValueType type;

    union {
        uint32_t u;
        int32_t i;
        float f;

        struct {
            char* data;
            size_t length;
        } string;

        struct {
            cell* data;
            size_t length;
        } array;
    } data;
};
