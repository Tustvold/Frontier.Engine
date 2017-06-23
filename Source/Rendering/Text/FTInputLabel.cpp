#include "FTInputLabel.h"
#include <Rendering/Primitives/FTPlane.h>
#include <Rendering/Action/FTCallFuncAction.h>
#include <Rendering/Action/FTActionSequence.h>
#include <Rendering/Action/FTMoveToAction.h>
#include <Rendering/Action/FTRepeatAction.h>
#include <Event/FTEventManager.h>
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>
#include <Rendering/BoundingShape/FTBoundingShapeWrapper.h>
#include <Event/Input/FTInputManager.h>
#include <Util/FTStringUtils.h>

NS_FT_BEGIN

FTInputLabel::FTInputLabel(const std::wstring& placeholder, const std::wstring& text, int fontsize)
    : cursor_pos_(0), placeholder_(placeholder), input_text_(text)  {

    label_ = std::make_shared<FTLabel>(text, fontsize, true);
    addChild(label_);

    updateLabel();
    
    this->setBoundingShape(std::make_unique<FTBoundingShapeWrapper>(label_));

    cursor_renderer_ = std::make_shared<FTPlane>(glm::vec2(0.07f, 1.0f) * (float)fontsize, glm::vec3());
    addChild(cursor_renderer_);


    auto setHidden = std::make_unique<FTCallFuncAction>([](FTNode* node) {
        node->setHidden(true);
    });

    auto setVisible = std::make_unique<FTCallFuncAction>([](FTNode* node) {
        node->setHidden(false);
    });

    auto sequence = std::make_unique<FTActionSequence>();
    sequence->addAction(std::move(setVisible));
    sequence->addAction(std::make_unique<FTDelayAction>(0.5f));
    sequence->addAction(std::move(setHidden));
    sequence->addAction(std::make_unique<FTDelayAction>(0.5f));

    cursor_renderer_->runAction(std::make_unique<FTRepeatAction>(std::move(sequence), -1));

    setInputLabelInactive();
    updateCursorRendererPos();

    this->getButton()->bindMousePressedDelegate(this, &FTInputLabel::onPressed);
    this->getButton()->bindOnDeselectDelegate(this, &FTInputLabel::onDeselect);
    this->getButton()->bindOnSelectDelegate(this, &FTInputLabel::onSelect);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::charInput);

    this->setKeyboardDelegatePriority(DEFAULT_KEYBOARD_INPUT_PRIORITY + 5);
    FTEngine::getInputManager()->addKeyboardDelegate(this);

}

FTInputLabel::~FTInputLabel() {
    FTEngine::getEventManager()->unregisterDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::charInput);
    FTEngine::getInputManager()->removeKeyboardDelegate(this);
}

bool FTInputLabel::onKeyPressed(const FTKeyPressedEvent& event) {
    // If active we swallow keyboard input corresponding to ASCII characters
    // This method will only be called if active and therefore don't need to check again
    return applyKey(event.key_) || event.key_ < GLFW_KEY_ESCAPE;
}

void FTInputLabel::onKeyRepeat(const FTKeyRepeatEvent& event) {
    applyKey(event.key_);
}

void FTInputLabel::charInput(const FTCharInputEvent& event) {
    if (!is_active_)
        return;
    input_text_.insert(cursor_pos_, 1, event.character_);
    updateLabel();

    cursor_pos_++;
    cursor_renderer_->resetAllActions();
    updateCursorRendererPos();
}

bool FTInputLabel::applyKey(int key) {
    if (!is_active_)
        return false;
    if (key == GLFW_KEY_LEFT) {
        if (cursor_pos_ > 0) {
            cursor_pos_--;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
            return true;
        }
    } else if (key == GLFW_KEY_RIGHT) {
        if (cursor_pos_ < input_text_.size()) {
            cursor_pos_++;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
            return true;
        }
    } else if (key == GLFW_KEY_BACKSPACE) {
        if (cursor_pos_ != 0) {
            input_text_.erase(cursor_pos_ - 1, 1);
            updateLabel();
            cursor_pos_--;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
            return true;
        }
    } else if (key == GLFW_KEY_DELETE) {
        if (cursor_pos_ != input_text_.size()) {
            input_text_.erase(cursor_pos_, 1);
            updateLabel();
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
            return true;
        }
    }
    return false;
}

void FTInputLabel::setInputLabelActive() {
    is_active_ = true;
    cursor_renderer_->setHidden(false);
    cursor_renderer_->resumeAllActions();
    updateLabel();
}

void FTInputLabel::setInputLabelInactive() {
    is_active_ = false;
    cursor_renderer_->pauseAllActions();
    cursor_renderer_->setHidden(true);
    updateLabel();
}

void FTInputLabel::updateCursorRendererPos() const {
    if (cursor_pos_ == 0) {
        cursor_renderer_->setPosition(glm::vec2(0, -0.1f * label_->getFontSize()));
        return;
    }
    if (cursor_pos_ != input_text_.size()) {
        auto glyph_bounds = label_->getMeshData()->getGlyphBounds(cursor_pos_);
        cursor_renderer_->setPosition(glm::vec2(glyph_bounds.first, -0.1f * label_->getFontSize()));
        return;
    }
    auto glyph_bounds = label_->getMeshData()->getGlyphBounds(cursor_pos_ - 1);
    cursor_renderer_->setPosition(glm::vec2(glyph_bounds.second, -0.1f * label_->getFontSize()));
}

void FTInputLabel::onPressed(FTButton* button, const FTMouseButtonPressedEvent& event) {
    auto pos = convertMouseToLocalCoordinates(event.cursor_pos_);
    for (size_t i = 0; i < input_text_.size(); i++) {
        auto glyph = label_->getMeshData()->getGlyphBounds(i);
        auto delta1 = pos.x - glyph.first;
        auto delta2 = glyph.second - pos.x;
        if (delta1 < 0) {
            cursor_pos_ = i;
            updateCursorRendererPos();
            return;
        }
        if (delta2 >= 0) {
            if (delta1 > delta2) {
                cursor_pos_ = i + 1;
            } else {
                cursor_pos_ = i;
            }
            updateCursorRendererPos();
            return;
        }
    }
    cursor_pos_ = input_text_.size();
    updateCursorRendererPos();
}

void FTInputLabel::onSelect(FTButton* button) {
    setInputLabelActive();
}

void FTInputLabel::onDeselect(FTButton* button) {
    setInputLabelInactive();
}

void FTInputLabel::updateLabel() {
    if (input_text_.size() == 0 && !is_active_) {
        label_->setString(placeholder_);
        label_->setStyle("DefaultTextPlaceholder");
    }
    else {
        label_->setString(input_text_);
        label_->setStyle("DefaultText");
    }
}

std::string FTInputLabel::getUTF8Text() const {
    return FTCharUtil::convertString(input_text_);
}

NS_FT_END