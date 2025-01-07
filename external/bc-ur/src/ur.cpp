//
//  ur.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "ur.hpp"

#include <iostream>

using namespace std;

namespace ur {

UR::UR(std::string type, ByteVector cbor)
    : type_(std::move(type)), cbor_(std::move(cbor))
{
    if (!is_ur_type(type)) {
        throw invalid_type();
    }
}

bool operator==(const UR& lhs, const UR& rhs) {
    return lhs.type() == rhs.type() && lhs.cbor() == rhs.cbor();
}

} // namespace ur
