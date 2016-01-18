#include "FTInputLabel.h"
#include <Rendering/Primitives/FTPlane.h>
#include <Rendering/Action/FTCallFuncAction.h>
#include <Rendering/Action/FTActionSequence.h>
#include <Rendering/Action/FTMoveToAction.h>
#include <Rendering/Action/FTRepeatAction.h>
#include <Event/FTEventManager.h>
#include <Event/Keyboard/FTKeyboardEventDispatcher.h>

FTInputLabel::FTInputLabel(const std::wstring& placeholder, const std::wstring& text, const std::string& font, int fontsize)
    : FTLabel(font,text,fontsize, true), cursor_pos_(0), placeholder_(placeholder), input_text_(text) {
    updateLabel();
    cursor_renderer_ = std::make_shared<FTPlane>(glm::vec2(0.07f, 1.0f)*(float)fontsize, glm::vec3());
    addChild(cursor_renderer_);

    
        
    auto setHidden = std::make_unique<FTCallFuncAction>([](FTNode* node)
    {
        node->setHidden(true);
    });

    auto setVisible = std::make_unique<FTCallFuncAction>([](FTNode* node)
    {
        node->setHidden(false);
    });

    auto sequence = std::make_unique<FTActionSequence>();
    sequence->addAction(std::move(setVisible));
    sequence->addAction(std::make_unique<FTDelayAction>(0.5f));
    sequence->addAction(std::move(setHidden));
    sequence->addAction(std::make_unique<FTDelayAction>(0.5f));
    
    cursor_renderer_->runAction(std::make_unique<FTRepeatAction>(std::move(sequence), -1));

    setInactive();
    updateCursorRendererPos();

    this->getButton()->bindMousePressedDelegate(this, &FTInputLabel::onPressed);
    this->getButton()->bindOnDeselectDelegate(this, &FTInputLabel::onDeselect);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::keyPressedEvent);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::keyRepeatEvent);
    FTEngine::getEventManager()->registerDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::charInput);

}

FTInputLabel::~FTInputLabel() {
    FTEngine::getEventManager()->unregisterDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::keyPressedEvent);
    FTEngine::getEventManager()->unregisterDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::keyRepeatEvent);
    FTEngine::getEventManager()->unregisterDelegate<FTKeyboardEventDispatcher>(this, &FTInputLabel::charInput);
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

void FTInputLabel::applyKey(int key) {
    if (!is_active_)
        return;
    if (key == GLFW_KEY_LEFT) {
        if (cursor_pos_ > 0) {
            cursor_pos_--;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
        }
    }
    else if (key == GLFW_KEY_RIGHT) {
        if (cursor_pos_ < input_text_.size()) {
            cursor_pos_++;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
        }
    } else if (key == GLFW_KEY_BACKSPACE) {
        if (cursor_pos_ != 0) {
            input_text_.erase(cursor_pos_ - 1, 1);
            updateLabel();
            cursor_pos_--;
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
        }
    } else if (key == GLFW_KEY_DELETE) {
        if (cursor_pos_ != input_text_.size()) {
            input_text_.erase(cursor_pos_, 1);
            updateLabel();
            cursor_renderer_->resetAllActions();
            updateCursorRendererPos();
        }
    }
}

void FTInputLabel::keyPressedEvent(const FTKeyPressedEvent& event) {
    applyKey(event.key_);
}

void FTInputLabel::keyRepeatEvent(const FTKeyRepeatEvent& event) {
    applyKey(event.key_);
}

void FTInputLabel::setActive() {
    is_active_ = true;
    cursor_renderer_->setHidden(false);
    cursor_renderer_->resumeAllActions();
    updateLabel();
}

void FTInputLabel::setInactive() {
    is_active_ = false;
    cursor_renderer_->pauseAllActions();
    cursor_renderer_->setHidden(true);
    updateLabel();
}

void FTInputLabel::updateCursorRendererPos() const {
    if (cursor_pos_ == 0) {
        cursor_renderer_->setPosition(glm::vec2(0, -0.1f * font_size_));
        return;
    }
    if (cursor_pos_ != input_text_.size()) {
        auto glyph_bounds = mesh_data_->getGlyphBounds(cursor_pos_);
        cursor_renderer_->setPosition(glm::vec2(glyph_bounds.first, -0.1f * font_size_));
        return;
    }
    auto glyph_bounds = mesh_data_->getGlyphBounds(cursor_pos_-1);
    cursor_renderer_->setPosition(glm::vec2(glyph_bounds.second, -0.1f * font_size_));
}

bool FTInputLabel::onPressed(FTButton* button, const FTMouseButtonPressedEvent& event) {
    setActive();
    auto pos = convertMouseToLocalCoordinates(event.cursor_pos_);
    for (int i = 0; i < input_text_.size(); i++) {
        auto glyph = mesh_data_->getGlyphBounds(i);
        auto delta1 = pos.x - glyph.first;
        auto delta2 = glyph.second - pos.x;
        if (delta1 < 0) {
            cursor_pos_ = i;
            updateCursorRendererPos();
            return true;
        } 
        if (delta2 >= 0) {
            if (delta1 > delta2) {
                cursor_pos_ = i + 1;
            } else {
                cursor_pos_ = i;
            }
            updateCursorRendererPos();
            return true;
        }
    }
    cursor_pos_ = input_text_.size();
    updateCursorRendererPos();
    return true;
}

void FTInputLabel::onDeselect(FTButton* button) {
    setInactive();
}

void FTInputLabel::updateLabel() {
    if (input_text_.size() == 0 && !is_active_)
        setString(placeholder_);
    else
        setString(input_text_);
}
