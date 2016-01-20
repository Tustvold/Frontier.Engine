﻿#pragma once
#include "FTLabel.h"

struct FTKeyRepeatEvent;
struct FTKeyPressedEvent;
struct FTCharInputEvent;

class FTInputLabel : public FTNode {
public:
    FTInputLabel(const std::wstring& placeholder, const std::wstring& text, const std::string& font, int fontsize);
    
    virtual ~FTInputLabel();

    void setFillColor(const glm::vec3& fill_color) {
        fill_color_ = fill_color;
        updateLabel();
    }

    void setPlaceholderFillColor(const glm::vec3& placeholder_fill_color) {
        placeholder_fill_color_ = placeholder_fill_color;
        updateLabel();
    }

    const std::wstring& getText() const {
        return input_text_;
    }

    void setText(const std::wstring& text) {
        input_text_ = text;
        updateLabel();
        cursor_pos_ = FTMIN(cursor_pos_, input_text_.size());
        updateCursorRendererPos();
    }

protected:
    bool is_active_;
    size_t cursor_pos_;
    std::wstring placeholder_;
    std::wstring input_text_;
    glm::vec3 fill_color_;
    glm::vec3 placeholder_fill_color_;
    std::shared_ptr<FTNode> cursor_renderer_;
    std::shared_ptr<FTLabel> label_;

    void updateLabel();
    void charInput(const FTCharInputEvent& event);
    void keyPressedEvent(const FTKeyPressedEvent& event);
    void keyRepeatEvent(const FTKeyRepeatEvent& event);
    void applyKey(int key);

    void setActive();
    void setInactive();
    void updateCursorRendererPos() const;

    void onPressed(FTButton* button, const FTMouseButtonPressedEvent& event);
    void onDeselect(FTButton* button);
};