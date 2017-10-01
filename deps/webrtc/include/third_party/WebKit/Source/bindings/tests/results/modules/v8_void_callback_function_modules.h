// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/callback_function.h.tmpl

// clang-format off

#ifndef V8VoidCallbackFunctionModules_h
#define V8VoidCallbackFunctionModules_h

#include "bindings/core/v8/NativeValueTraits.h"
#include "modules/ModulesExport.h"
#include "platform/bindings/ScriptWrappable.h"
#include "platform/bindings/TraceWrapperV8Reference.h"
#include "platform/heap/Handle.h"
#include "platform/wtf/text/WTFString.h"

namespace blink {

class ScriptState;

class MODULES_EXPORT V8VoidCallbackFunctionModules final : public GarbageCollectedFinalized<V8VoidCallbackFunctionModules>, public TraceWrapperBase {
 public:
  static V8VoidCallbackFunctionModules* Create(ScriptState*, v8::Local<v8::Value> callback);

  ~V8VoidCallbackFunctionModules() = default;

  DEFINE_INLINE_TRACE() {}
  DECLARE_TRACE_WRAPPERS();

  bool call(ScriptWrappable* scriptWrappable);

  v8::Local<v8::Function> v8Value(v8::Isolate* isolate) {
    return callback_.NewLocal(isolate);
  }

 private:
  V8VoidCallbackFunctionModules(ScriptState*, v8::Local<v8::Function>);

  RefPtr<ScriptState> script_state_;
  TraceWrapperV8Reference<v8::Function> callback_;
};

template <>
struct NativeValueTraits<V8VoidCallbackFunctionModules> : public NativeValueTraitsBase<V8VoidCallbackFunctionModules> {
  MODULES_EXPORT static V8VoidCallbackFunctionModules* NativeValue(v8::Isolate*, v8::Local<v8::Value>, ExceptionState&);
};

}  // namespace blink

#endif  // V8VoidCallbackFunctionModules_h