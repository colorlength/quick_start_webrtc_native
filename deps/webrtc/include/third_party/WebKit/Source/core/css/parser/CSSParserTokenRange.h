// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CSSParserTokenRange_h
#define CSSParserTokenRange_h

#include "core/CoreExport.h"
#include "core/css/parser/CSSParserToken.h"
#include "platform/wtf/Allocator.h"
#include "platform/wtf/Vector.h"

namespace blink {

CORE_EXPORT extern const CSSParserToken& g_static_eof_token;

// A CSSParserTokenRange is an iterator over a subrange of a vector of
// CSSParserTokens. Accessing outside of the range will return an endless stream
// of EOF tokens. This class refers to half-open intervals [first, last).
class CORE_EXPORT CSSParserTokenRange {
  DISALLOW_NEW();

 public:
  template <size_t InlineBuffer>
  CSSParserTokenRange(const Vector<CSSParserToken, InlineBuffer>& vector)
      : first_(vector.begin()), last_(vector.end()) {}

  // This should be called on a range with tokens returned by that range.
  CSSParserTokenRange MakeSubRange(const CSSParserToken* first,
                                   const CSSParserToken* last) const;

  bool AtEnd() const { return first_ == last_; }
  const CSSParserToken* end() const { return last_; }

  const CSSParserToken& Peek(unsigned offset = 0) const {
    if (first_ + offset >= last_)
      return g_static_eof_token;
    return *(first_ + offset);
  }

  const CSSParserToken& Consume() {
    if (first_ == last_)
      return g_static_eof_token;
    return *first_++;
  }

  const CSSParserToken& ConsumeIncludingWhitespace() {
    const CSSParserToken& result = Consume();
    ConsumeWhitespace();
    return result;
  }

  // The returned range doesn't include the brackets
  CSSParserTokenRange ConsumeBlock();

  void ConsumeComponentValue();

  void ConsumeWhitespace() {
    while (Peek().GetType() == kWhitespaceToken)
      ++first_;
  }

  String Serialize() const;

  const CSSParserToken* begin() const { return first_; }

  static void InitStaticEOFToken();

 private:
  CSSParserTokenRange(const CSSParserToken* first, const CSSParserToken* last)
      : first_(first), last_(last) {}

  const CSSParserToken* first_;
  const CSSParserToken* last_;
};

}  // namespace blink

#endif  // CSSParserTokenRange_h
