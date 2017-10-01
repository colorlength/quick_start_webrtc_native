/*
 *  Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2013 Apple Inc.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 *
 */

#ifndef WTF_RefPtr_h
#define WTF_RefPtr_h

#include "platform/wtf/Allocator.h"
#include "platform/wtf/HashTableDeletedValueType.h"
#include "platform/wtf/allocator/PartitionAllocator.h"
#include <algorithm>
#include <utility>

namespace WTF {

template <typename T>
class RefPtrValuePeeker;
template <typename T>
class RefPtr;

template <typename T>
RefPtr<T> AdoptRef(T*);

// requireAdoption() is not overloaded for WTF::RefCounted, which has a built-in
// assumption that adoption is required. requireAdoption() is for bootstrapping
// alternate reference count classes that are compatible with RefPtr
// but cannot have adoption checks enabled by default, such as skia's
// SkRefCnt. The purpose of requireAdoption() is to enable adoption checks only
// once it is known that the object will be used with RefPtr.
inline void RequireAdoption(const void*) {}

template <typename T>
ALWAYS_INLINE void RefIfNotNull(T* ptr) {
  if (LIKELY(ptr != 0)) {
    RequireAdoption(ptr);
    ptr->Ref();
  }
}

template <typename T>
ALWAYS_INLINE void DerefIfNotNull(T* ptr) {
  if (LIKELY(ptr != 0))
    ptr->Deref();
}

inline void Adopted(const void*) {}

template <typename T>
class RefPtr {
  USING_FAST_MALLOC(RefPtr);

 public:
  ALWAYS_INLINE RefPtr() : ptr_(nullptr) {}
  ALWAYS_INLINE RefPtr(std::nullptr_t) : ptr_(nullptr) {}
  ALWAYS_INLINE RefPtr(T* ptr) : ptr_(ptr) { RefIfNotNull(ptr); }
  ALWAYS_INLINE RefPtr(const RefPtr& o) : ptr_(o.ptr_) { RefIfNotNull(ptr_); }
  template <typename U>
  RefPtr(const RefPtr<U>& o, EnsurePtrConvertibleArgDecl(U, T))
      : ptr_(o.get()) {
    RefIfNotNull(ptr_);
  }
  RefPtr(RefPtr&& o) : ptr_(o.ptr_) { o.ptr_ = nullptr; }
  template <typename U>
  RefPtr(RefPtr<U>&& o, EnsurePtrConvertibleArgDecl(U, T))
      : ptr_(o.LeakRef()) {}

  ALWAYS_INLINE ~RefPtr() { DerefIfNotNull(ptr_); }

  ALWAYS_INLINE T* get() const { return ptr_; }
  T* LeakRef() WARN_UNUSED_RESULT;

  T& operator*() const { return *ptr_; }
  ALWAYS_INLINE T* operator->() const { return ptr_; }

  bool operator!() const { return !ptr_; }
  explicit operator bool() const { return ptr_ != nullptr; }

  RefPtr& operator=(RefPtr o) {
    swap(o);
    return *this;
  }
  RefPtr& operator=(std::nullptr_t) {
    T* ptr = ptr_;
    ptr_ = nullptr;
    DerefIfNotNull(ptr);
    return *this;
  }
  // This is required by HashMap<RefPtr>>.
  template <typename U>
  RefPtr& operator=(RefPtrValuePeeker<U>);

  void swap(RefPtr&);

 private:
  friend RefPtr AdoptRef<T>(T*);

  enum AdoptRefTag { kAdoptRef };
  RefPtr(T* ptr, AdoptRefTag) : ptr_(ptr) {}

  T* ptr_;
};

template <typename T>
inline T* RefPtr<T>::LeakRef() {
  T* ptr = ptr_;
  ptr_ = nullptr;
  return ptr;
}

template <typename T>
template <typename U>
inline RefPtr<T>& RefPtr<T>::operator=(RefPtrValuePeeker<U> optr) {
  RefPtr ptr = static_cast<U*>(optr);
  swap(ptr);
  return *this;
}

template <class T>
inline void RefPtr<T>::swap(RefPtr& o) {
  std::swap(ptr_, o.ptr_);
}

template <class T>
inline void swap(RefPtr<T>& a, RefPtr<T>& b) {
  a.swap(b);
}

template <typename T, typename U>
inline bool operator==(const RefPtr<T>& a, const RefPtr<U>& b) {
  return a.get() == b.get();
}

template <typename T, typename U>
inline bool operator==(const RefPtr<T>& a, U* b) {
  return a.get() == b;
}

template <typename T, typename U>
inline bool operator==(T* a, const RefPtr<U>& b) {
  return a == b.get();
}

template <typename T>
inline bool operator==(const RefPtr<T>& a, std::nullptr_t) {
  return !a.get();
}

template <typename T>
inline bool operator==(std::nullptr_t, const RefPtr<T>& b) {
  return !b.get();
}

template <typename T, typename U>
inline bool operator!=(const RefPtr<T>& a, const RefPtr<U>& b) {
  return a.get() != b.get();
}

template <typename T, typename U>
inline bool operator!=(const RefPtr<T>& a, U* b) {
  return a.get() != b;
}

template <typename T, typename U>
inline bool operator!=(T* a, const RefPtr<U>& b) {
  return a != b.get();
}

template <typename T>
inline bool operator!=(const RefPtr<T>& a, std::nullptr_t) {
  return a.get();
}

template <typename T>
inline bool operator!=(std::nullptr_t, const RefPtr<T>& b) {
  return b.get();
}

template <typename T>
inline T* GetPtr(const RefPtr<T>& p) {
  return p.get();
}

template <typename T>
class RefPtrValuePeeker {
  DISALLOW_NEW();

 public:
  ALWAYS_INLINE RefPtrValuePeeker(T* p) : ptr_(p) {}
  ALWAYS_INLINE RefPtrValuePeeker(std::nullptr_t) : ptr_(nullptr) {}
  template <typename U>
  RefPtrValuePeeker(const RefPtr<U>& p) : ptr_(p.get()) {}

  ALWAYS_INLINE operator T*() const { return ptr_; }

 private:
  T* ptr_;
};

template <typename T>
RefPtr<T> AdoptRef(T* p) {
  Adopted(p);
  return RefPtr<T>(p, RefPtr<T>::kAdoptRef);
}

template <typename T>
RefPtr<T> WrapRefPtr(T* ptr) {
  return RefPtr<T>(ptr);
}

}  // namespace WTF

using WTF::RefPtr;

#endif  // WTF_RefPtr_h
