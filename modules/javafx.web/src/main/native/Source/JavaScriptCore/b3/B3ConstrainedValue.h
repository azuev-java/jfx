/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(B3_JIT)

#include "B3ValueRep.h"
#include "B3Width.h"
#include "WasmCallingConvention.h"

namespace JSC { namespace B3 {

class Value;

#if ENABLE(WEBASSEMBLY)
struct ArgumentLocation {
    ArgumentLocation(Wasm::ValueLocation loc, Width width)
        : location(loc)
        , width(width)
    {
    }

    ArgumentLocation() { }

    Wasm::ValueLocation location;
    Width width;
};
#endif

class ConstrainedValue {
public:
    ConstrainedValue()
    {
    }

    ConstrainedValue(Value* value)
        : m_value(value)
        , m_rep(ValueRep::WarmAny)
    {
    }

    ConstrainedValue(Value* value, const ValueRep& rep)
        : m_value(value)
        , m_rep(rep)
    {
    }

#if ENABLE(WEBASSEMBLY)
#if USE(JSVALUE32_64)
    ConstrainedValue(Value* value, const Wasm::ArgumentLocation& loc)
        : m_value(value)
    {
        if (loc.location.isGPR() && loc.usedWidth == Width32)
            m_rep = B3::ValueRep(loc.location.jsr().payloadGPR());
        else
            m_rep = B3::ValueRep(loc.location);
    }
#else
    ConstrainedValue(Value* value, const Wasm::ArgumentLocation& loc)
        : m_value(value)
        , m_rep(loc.location)
    {
    }
#endif // USE(JSVALUE32_64)
#endif // ENABLE(WEBASSEMBLY)

    explicit operator bool() const { return m_value || m_rep; }

    Value* value() const { return m_value; }
    const ValueRep& rep() const { return m_rep; }

    void dump(PrintStream& out) const;

private:
    Value* m_value;
    ValueRep m_rep;
};

} } // namespace JSC::B3

#endif // ENABLE(B3_JIT)
