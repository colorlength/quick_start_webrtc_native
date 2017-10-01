/*
 * Copyright (C) 1999 Lars Knoll (knoll@kde.org)
 *           (C) 1999 Antti Koivisto (koivisto@kde.org)
 *           (C) 2001 Dirk Mueller (mueller@kde.org)
 *           (C) 2006 Alexey Proskuryakov (ap@webkit.org)
 * Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2012 Apple Inc. All
 * rights reserved.
 * Copyright (C) 2008, 2009 Torch Mobile Inc. All rights reserved.
 * (http://www.torchmobile.com/)
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef TreeScopeStyleSheetCollection_h
#define TreeScopeStyleSheetCollection_h

#include "core/CoreExport.h"
#include "core/css/StyleSheetCollection.h"
#include "core/dom/TreeOrderedList.h"
#include "core/dom/TreeScope.h"

namespace blink {

class Document;
class Node;

class CORE_EXPORT TreeScopeStyleSheetCollection : public StyleSheetCollection {
 public:
  void AddStyleSheetCandidateNode(Node&);
  void RemoveStyleSheetCandidateNode(Node& node) {
    style_sheet_candidate_nodes_.Remove(&node);
  }
  bool HasStyleSheetCandidateNodes() const {
    return !style_sheet_candidate_nodes_.IsEmpty();
  }
  bool HasStyleSheets() const;

  bool MediaQueryAffectingValueChanged();

  virtual bool IsShadowTreeStyleSheetCollection() const { return false; }
  void UpdateStyleSheetList();

  DECLARE_VIRTUAL_TRACE();

 protected:
  explicit TreeScopeStyleSheetCollection(TreeScope&);

  Document& GetDocument() const { return GetTreeScope().GetDocument(); }
  TreeScope& GetTreeScope() const { return *tree_scope_; }

  void ApplyActiveStyleSheetChanges(StyleSheetCollection&);

  Member<TreeScope> tree_scope_;
  TreeOrderedList style_sheet_candidate_nodes_;

 private:
  friend class TreeScopeStyleSheetCollectionTest;
};

}  // namespace blink

#endif
