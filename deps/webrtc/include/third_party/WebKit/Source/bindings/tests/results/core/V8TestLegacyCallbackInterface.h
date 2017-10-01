// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/legacy_callback_interface.h.tmpl

// clang-format off
#ifndef V8TestLegacyCallbackInterface_h
#define V8TestLegacyCallbackInterface_h

#include "bindings/tests/idls/core/TestLegacyCallbackInterface.h"
#include "core/CoreExport.h"
#include "platform/bindings/DOMWrapperWorld.h"
#include "platform/bindings/ScopedPersistent.h"

namespace blink {

class V8TestLegacyCallbackInterface final {
  STATIC_ONLY(V8TestLegacyCallbackInterface);
 public:
  static v8::Local<v8::FunctionTemplate> DomTemplate(v8::Isolate*, const DOMWrapperWorld&);
  CORE_EXPORT  static const WrapperTypeInfo wrapperTypeInfo;
  CORE_EXPORT  static void TypeErrorConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>&);
};
}
#endif  // V8TestLegacyCallbackInterface_h
