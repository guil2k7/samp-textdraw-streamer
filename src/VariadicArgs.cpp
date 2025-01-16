// Taken from https://github.com/guil2k7/samp-plugin-sdk

// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <cstring>
#include <string>
#include "service.hpp"

class Lexer {
public:
    Lexer(char const* chars, size_t length) :
        m_chars(chars), m_length(length), m_index(0) {}

    bool next();

    char kind;
    std::string attribute;

private:
    char getCurCharAndAdvance();

    char const* m_chars;
    size_t m_length;
    size_t m_index;
};

char Lexer::getCurCharAndAdvance() {
    if (m_index >= m_length)
        return '\0';

    return m_chars[m_index++];
}

bool Lexer::next() {
    char ch = getCurCharAndAdvance();

    if (ch == '\0')
        return false;

    kind = ch;

    // Clear the previous attribute.
    attribute.clear();

    if (m_index < m_length && m_chars[m_index] == '[') {
        getCurCharAndAdvance();
        ch = getCurCharAndAdvance();

        while (ch != ']' && ch != '\0') {
            attribute.push_back(ch);
            ch = getCurCharAndAdvance();
        }

        // Eat the right square bracket.
        getCurCharAndAdvance();
    }

    return true;
}

ErrorID service::parseVariadicArgs(AMX* amx, cell const* args, size_t formatIndex, size_t vargsIndex, std::vector<PawnValue>& output) {
    std::string format = getString(amx, args[formatIndex]);
    size_t argsCount = args[0] / sizeof (cell);

    Lexer lexer(format.c_str(), format.length());
    PawnValue pwnValue;
    size_t argIndex = vargsIndex;

    output.reserve(format.length());

    while (lexer.next()) {
        if (argIndex > argsCount)
            return ErrorID::SpecifierCountMismatchArgs;

        cell* source;
        amx_GetAddr(amx, args[argIndex++], &source);

        switch (lexer.kind) {
        case 'i':
            pwnValue.type = PawnValueType::Int;
            pwnValue.data.i = *source;
            output.push_back(std::move(pwnValue));
            break;

        case 'f':
            pwnValue.type = PawnValueType::Float;
            pwnValue.data.i = *source;
            output.push_back(std::move(pwnValue));
            break;

        case 'u':
            pwnValue.type = PawnValueType::UInt;
            pwnValue.data.i = *source;
            output.push_back(std::move(pwnValue));
            break;

        case 's': {
            cell length;
            amx_StrLen(source, &length);

            pwnValue.type = PawnValueType::String;
            pwnValue.data.string.data = new char[length + 1];
            pwnValue.data.string.length = length;

            amx_GetString(pwnValue.data.string.data, source, 0, length + 1);

            output.push_back(std::move(pwnValue));
            break;
        }

        case 'a': {
            cell length;

            if (lexer.attribute.empty()) {
                return ErrorID::InvalidSpecifierUse;
            }
            else if (lexer.attribute == "*") {
                if (argIndex >= argsCount)
                    return ErrorID::SpecifierCountMismatchArgs;

                length = argIndex++;
            }
            else {
                length = std::stoi(lexer.attribute);

                if (length <= 0)
                    return ErrorID::InvalidSpecifierUse;
            }

            pwnValue.type = PawnValueType::Array;
            pwnValue.data.array.data = new cell[length];
            pwnValue.data.array.length = length;

            memcpy(pwnValue.data.array.data, source, length * sizeof (cell));

            output.push_back(std::move(pwnValue));
            break;
        }

        default:
            return ErrorID::UnknownSpecifier;
        }
    }

    return ErrorID::None;
}
