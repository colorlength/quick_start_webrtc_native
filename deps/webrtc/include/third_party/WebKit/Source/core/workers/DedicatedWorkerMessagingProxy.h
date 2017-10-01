// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DedicatedWorkerMessagingProxy_h
#define DedicatedWorkerMessagingProxy_h

#include <memory>
#include "core/CoreExport.h"
#include "core/dom/MessagePort.h"
#include "core/workers/ThreadedMessagingProxyBase.h"
#include "core/workers/WorkerBackingThreadStartupData.h"
#include "platform/heap/Handle.h"
#include "platform/wtf/Noncopyable.h"
#include "platform/wtf/Optional.h"
#include "platform/wtf/RefPtr.h"

namespace blink {

class InProcessWorkerBase;
class InProcessWorkerObjectProxy;
class SerializedScriptValue;
class WorkerClients;

// TODO(nhiroki): Add the class-level comment once
// InProcessWorker->DedicatedWorker move is done (https://crbug.com/688116).
class CORE_EXPORT DedicatedWorkerMessagingProxy
    : public ThreadedMessagingProxyBase {
  WTF_MAKE_NONCOPYABLE(DedicatedWorkerMessagingProxy);

 public:
  DedicatedWorkerMessagingProxy(ExecutionContext*,
                                InProcessWorkerBase*,
                                WorkerClients*);
  ~DedicatedWorkerMessagingProxy() override;

  // These methods should only be used on the parent context thread.
  void StartWorkerGlobalScope(const KURL& script_url,
                              const String& user_agent,
                              const String& source_code,
                              const String& referrer_policy);
  void PostMessageToWorkerGlobalScope(RefPtr<SerializedScriptValue>,
                                      Vector<MessagePortChannel>);

  // Implements ThreadedMessagingProxyBase.
  void WorkerThreadCreated() override;

  bool HasPendingActivity() const;

  // These methods come from worker context thread via
  // InProcessWorkerObjectProxy and are called on the parent context thread.
  void PostMessageToWorkerObject(RefPtr<SerializedScriptValue>,
                                 Vector<MessagePortChannel>);
  void DispatchErrorEvent(const String& error_message,
                          std::unique_ptr<SourceLocation>,
                          int exception_id);

  InProcessWorkerObjectProxy& WorkerObjectProxy() {
    return *worker_object_proxy_.get();
  }

  DECLARE_VIRTUAL_TRACE();

 private:
  friend class DedicatedWorkerMessagingProxyForTest;

  WTF::Optional<WorkerBackingThreadStartupData> CreateBackingThreadStartupData(
      v8::Isolate*);

  std::unique_ptr<WorkerThread> CreateWorkerThread() override;

  std::unique_ptr<InProcessWorkerObjectProxy> worker_object_proxy_;

  // This must be weak. The base class (i.e., ThreadedMessagingProxyBase) has a
  // strong persistent reference to itself via SelfKeepAlive (see class-level
  // comments on ThreadedMessagingProxyBase.h for details). To cut the
  // persistent reference, this worker object needs to call a cleanup function
  // in its dtor. If this is a strong reference, the dtor is never called
  // because the worker object is reachable from the persistent reference.
  WeakMember<InProcessWorkerBase> worker_object_;

  // Tasks are queued here until there's a thread object created.
  struct QueuedTask;
  Vector<QueuedTask> queued_early_tasks_;
};

}  // namespace blink

#endif  // DedicatedWorkerMessagingProxy_h
