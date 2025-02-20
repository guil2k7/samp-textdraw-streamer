// Taken from https://github.com/guil2k7/samp-plugin-sdk

// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include "Value.hpp"

PawnValue::~PawnValue() {
    switch (type) {
    case PawnValueType::Undefined:
        break;

    case PawnValueType::Int:
    case PawnValueType::Float:
    case PawnValueType::UInt:
        break;

    case PawnValueType::String:
        delete[] data.string.data;
        break;

    case PawnValueType::Array:
        delete[] data.array.data;
        break;
    }
}

cell PawnValue::push(AMX* amx) const {
    switch (type) {
    case PawnValueType::Int:
    case PawnValueType::Float:
    case PawnValueType::UInt:
        amx_Push(amx, data.i);
        return 0;

    case PawnValueType::String: {
        cell xAddr;
        amx_PushString(amx, &xAddr, nullptr, data.string.data, 0, 0);
        return xAddr;
    }

    case PawnValueType::Array: {
        cell xAddr;
        amx_PushArray(amx, &xAddr, nullptr, data.array.data, data.array.length);
        return xAddr;
    }

    default:
        return 0;
    }
}

PawnValue& PawnValue::operator =(PawnValue&& that) {
    type = that.type;

    switch (type) {
    case PawnValueType::Int:
    case PawnValueType::Float:
    case PawnValueType::UInt:
        data.i = that.data.i;
        break;

    case PawnValueType::String:
        data.string = that.data.string;
        break;

    case PawnValueType::Array:
        data.array = that.data.array;
        break;

    case PawnValueType::Undefined:
        break;
    }

    that.type = PawnValueType::Undefined;

    return *this;
}
