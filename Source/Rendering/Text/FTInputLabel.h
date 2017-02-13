#pragma once
#include "FTLabel.h"
#include <Event/Input/FTKeyboardDelegate.h>

struct FTKeyRepeatEvent;
struct FTKeyPressedEvent;
struct FTCharInputEvent;

class FTInputLabel : public FTNode, public FTKeyboardDelegate {
public:
    FTInputLabel(const std::wstring& placeholder, const std::wstring& text, int fontsize);
    
    virtual ~FTInputLabel();

    const std::wstring& getText() const {
        return input_text_;
    }

    std::string getUTF8Text() const;

    void setText(const std::wstring& text) {
        input_text_ = text;
        updateLabel();
        cursor_pos_ = FTMIN(cursor_pos_, input_text_.size());
        updateCursorRendererPos();
    }


    bool onKeyPressed(const FTKeyPressedEvent& event) override;

    void onKeyRepeat(const FTKeyRepeatEvent& event) override;

    bool getKeyboardDelegateEnabled() const override {
        return is_active_ && this->getIsActive();
    }
protected:
    bool is_active_;
    size_t cursor_pos_;
    std::wstring placeholder_;
    std::wstring input_text_;
    std::shared_ptr<FTNode> cursor_renderer_;
    std::shared_ptr<FTLabel> label_;

    void updateLabel();
    void charInput(const FTCharInputEvent& event);
    bool applyKey(int key);

    void setInputLabelActive();
    void setInputLabelInactive();
    void updateCursorRendererPos() const;

    void onPressed(FTButton* button, const FTMouseButtonPressedEvent& event);
    void onSelect(FTButton* button);
    void onDeselect(FTButton* button);
};
