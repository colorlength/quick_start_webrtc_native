// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DevToolsHostFileSystem_h
#define DevToolsHostFileSystem_h

#include "platform/heap/Handle.h"
#include "platform/wtf/Allocator.h"
#include "platform/wtf/text/WTFString.h"

namespace blink {

class DOMFileSystem;
class DevToolsHost;

class DevToolsHostFileSystem {
  STATIC_ONLY(DevToolsHostFileSystem);

 public:
  static DOMFileSystem* isolatedFileSystem(DevToolsHost&,
                                           const String& file_system_name,
                                           const String& root_url);
  static void upgradeDraggedFileSystemPermissions(DevToolsHost&,
                                                  DOMFileSystem*);
};

}  // namespace blink

#endif  // !defined(DevToolsHostFileSystem_h)
