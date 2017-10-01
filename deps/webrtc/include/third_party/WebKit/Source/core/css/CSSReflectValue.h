/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
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
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CSSReflectValue_h
#define CSSReflectValue_h

#include "core/css/CSSValue.h"
#include "platform/wtf/RefPtr.h"

namespace blink {

class CSSIdentifierValue;
class CSSPrimitiveValue;

class CSSReflectValue : public CSSValue {
 public:
  static CSSReflectValue* Create(CSSIdentifierValue* direction,
                                 CSSPrimitiveValue* offset,
                                 CSSValue* mask) {
    return new CSSReflectValue(direction, offset, mask);
  }

  CSSIdentifierValue* Direction() const { return direction_.Get(); }
  CSSPrimitiveValue* Offset() const { return offset_.Get(); }
  CSSValue* Mask() const { return mask_.Get(); }

  String CustomCSSText() const;

  bool Equals(const CSSReflectValue&) const;

  DECLARE_TRACE_AFTER_DISPATCH();

 private:
  CSSReflectValue(CSSIdentifierValue* direction,
                  CSSPrimitiveValue* offset,
                  CSSValue* mask)
      : CSSValue(kReflectClass),
        direction_(direction),
        offset_(offset),
        mask_(mask) {}

  Member<CSSIdentifierValue> direction_;
  Member<CSSPrimitiveValue> offset_;
  Member<CSSValue> mask_;
};

DEFINE_CSS_VALUE_TYPE_CASTS(CSSReflectValue, IsReflectValue());

}  // namespace blink

#endif  // CSSReflectValue_h
