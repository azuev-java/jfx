/*
 * Copyright (C) 2012, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "AccessibilityObject.h"
#include "LayoutRect.h"
#include <wtf/Forward.h>

namespace WebCore {

class AXObjectCache;
class Element;
class HTMLLabelElement;
class Node;

enum MouseButtonListenerResultFilter {
    ExcludeBodyElement = 1,
    IncludeBodyElement,
};

class AccessibilityNodeObject : public AccessibilityObject {
public:
    static Ref<AccessibilityNodeObject> create(Node&);
    virtual ~AccessibilityNodeObject();

    void init() override;

    bool canvasHasFallbackContent() const override;

    bool isBusy() const override;
    bool isControl() const override;
    bool isRadioInput() const override;
    bool isFieldset() const override;
    bool isHovered() const override;
    bool isInputImage() const override;
    bool isLink() const override;
    bool isMultiSelectable() const override;
    bool isNativeImage() const;
    bool isNativeTextControl() const override;
    bool isSecureField() const override;
    bool isSearchField() const override;

    bool isChecked() const override;
    bool isEnabled() const override;
    bool isIndeterminate() const override;
    bool isPressed() const final;
    bool isRequired() const override;
    bool supportsARIAOwns() const final;
    bool supportsRequiredAttribute() const override;

    bool supportsDropping() const override;
    bool supportsDragging() const override;
    bool isGrabbed() override;
    Vector<String> determineDropEffects() const override;

    bool canSetSelectedAttribute() const override;

    Node* node() const override { return m_node.get(); }
    Document* document() const override;
    LocalFrameView* documentFrameView() const override;

    void setFocused(bool) override;
    bool isFocused() const override;
    bool canSetFocusAttribute() const override;
    unsigned headingLevel() const override;

    bool canSetValueAttribute() const override;

    String valueDescription() const override;
    float valueForRange() const override;
    float maxValueForRange() const override;
    float minValueForRange() const override;
    float stepValueForRange() const override;

    AccessibilityOrientation orientation() const override;

    AccessibilityButtonState checkboxOrRadioValue() const override;

    URL url() const override;
    unsigned hierarchicalLevel() const override;
    String textUnderElement(TextUnderElementMode = TextUnderElementMode()) const override;
    String accessibilityDescriptionForChildren() const;
    String description() const override;
    String helpText() const override;
    String title() const override;
    String text() const override;
    void alternativeText(Vector<AccessibilityText>&) const;
    void helpText(Vector<AccessibilityText>&) const;
    String stringValue() const override;
    WallTime dateTimeValue() const final;
    SRGBA<uint8_t> colorValue() const override;
    String ariaLabeledByAttribute() const override;
    bool hasAccNameAttribute() const;
    bool hasAttributesRequiredForInclusion() const final;
    void setIsExpanded(bool) override;

    Element* actionElement() const override;
    Element* mouseButtonListener(MouseButtonListenerResultFilter = ExcludeBodyElement) const;
    Element* anchorElement() const override;
    RefPtr<Element> popoverTargetElement() const final;
    AXCoreObject* internalLinkElement() const final;
    AccessibilityChildrenVector radioButtonGroup() const final;
    AccessibilityObject* menuForMenuButton() const;

    virtual void changeValueByPercent(float percentChange);

    AccessibilityObject* firstChild() const override;
    AccessibilityObject* lastChild() const override;
    AccessibilityObject* previousSibling() const override;
    AccessibilityObject* nextSibling() const override;
    AccessibilityObject* parentObject() const override;
    AccessibilityObject* parentObjectIfExists() const override;

    bool matchesTextAreaRole() const;

    void increment() override;
    void decrement() override;
    bool toggleDetailsAncestor() final;

    LayoutRect elementRect() const override;

#if ENABLE(AX_THREAD_TEXT_APIS)
    bool shouldEmitNewlinesBeforeAndAfterNode() const final;
#endif

protected:
    explicit AccessibilityNodeObject(Node*);
    void detachRemoteParts(AccessibilityDetachmentType) override;

    AccessibilityRole m_ariaRole { AccessibilityRole::Unknown };
#ifndef NDEBUG
    bool m_initialized { false };
#endif

    bool isDetached() const override { return !m_node; }

    AccessibilityRole determineAccessibilityRole() override;
    enum class TreatStyleFormatGroupAsInline : bool { No, Yes };
    AccessibilityRole determineAccessibilityRoleFromNode(TreatStyleFormatGroupAsInline = TreatStyleFormatGroupAsInline::No) const;
    AccessibilityRole roleFromInputElement(const HTMLInputElement&) const;
    AccessibilityRole ariaRoleAttribute() const override { return m_ariaRole; }
    virtual AccessibilityRole determineAriaRoleAttribute() const;
    AccessibilityRole remapAriaRoleDueToParent(AccessibilityRole) const;

    bool computeAccessibilityIsIgnored() const override;
    void addChildren() override;
    void clearChildren() override;
    void updateChildrenIfNecessary() override;
    bool canHaveChildren() const override;
    AccessibilityChildrenVector visibleChildren() override;
    bool isDescendantOfBarrenParent() const override;
    void updateOwnedChildren();
    AccessibilityObject* ownerParentObject() const;

    enum class StepAction : bool { Decrement, Increment };
    void alterRangeValue(StepAction);
    void changeValueByStep(StepAction);
    // This returns true if it's focusable but it's not content editable and it's not a control or ARIA control.
    bool isGenericFocusableElement() const;

    VisiblePositionRange visiblePositionRange() const final;
    VisiblePositionRange selectedVisiblePositionRange() const final;
    VisiblePositionRange visiblePositionRangeForLine(unsigned) const final;
    VisiblePosition visiblePositionForIndex(int) const override;
    int indexForVisiblePosition(const VisiblePosition&) const override;

    bool elementAttributeValue(const QualifiedName&) const;

    const String liveRegionStatus() const override;
    const String liveRegionRelevant() const override;
    bool liveRegionAtomic() const override;

    String accessKey() const final;
    bool isLabelable() const;
    AccessibilityObject* controlForLabelElement() const final;
    String textAsLabelFor(const AccessibilityObject&) const;
    String textForLabelElements(Vector<Ref<HTMLElement>>&&) const;
    HTMLLabelElement* labelElementContainer() const;

    String ariaAccessibilityDescription() const;
    Vector<Ref<Element>> ariaLabeledByElements() const;
    String descriptionForElements(const Vector<Ref<Element>>&) const;
    LayoutRect boundingBoxRect() const override;
    String ariaDescribedByAttribute() const override;

    Element* menuElementForMenuButton() const;
    Element* menuItemElementForMenu() const;
    AccessibilityObject* menuButtonForMenu() const;
    AccessibilityObject* captionForFigure() const;
    virtual void labelText(Vector<AccessibilityText>&) const;
private:
    bool isAccessibilityNodeObject() const final { return true; }
    void accessibilityText(Vector<AccessibilityText>&) const override;
    void visibleText(Vector<AccessibilityText>&) const;
    String alternativeTextForWebArea() const;
    void ariaLabeledByText(Vector<AccessibilityText>&) const;
    bool usesAltTagForTextComputation() const;
    bool roleIgnoresTitle() const;
    bool postKeyboardKeysForValueChange(StepAction);
    void setNodeValue(StepAction, float);
    bool performDismissAction() final;
    bool hasTextAlternative() const;
    LayoutRect checkboxOrRadioRect() const;

    void setNeedsToUpdateChildren() override { m_childrenDirty = true; }
    bool needsToUpdateChildren() const override { return m_childrenDirty; }
    void setNeedsToUpdateSubtree() override { m_subtreeDirty = true; }

    bool isDescendantOfElementType(const HashSet<QualifiedName>&) const;
protected:
    WeakPtr<Node, WeakPtrImplWithEventTargetData> m_node;
};

namespace Accessibility {

RefPtr<HTMLElement> controlForLabelElement(const HTMLLabelElement&);
Vector<Ref<HTMLElement>> labelsForElement(Element*);

} // namespace Accessibility

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_BEGIN(WebCore::AccessibilityNodeObject) \
    static bool isType(const WebCore::AccessibilityObject& object) { return object.isAccessibilityNodeObject(); } \
SPECIALIZE_TYPE_TRAITS_END()
