#pragma once
#include "Label.h"
#include <Event/Input/KeyboardDelegate.h>

NS_FT_BEGIN

struct KeyRepeatEvent;
struct KeyPressedEvent;
struct CharInputEvent;

class InputLabel : public Node, public KeyboardDelegate {
public:
    InputLabel(const std::wstring& placeholder, const std::wstring& text, int fontsize);
    
    virtual ~InputLabel();

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


    bool onKeyPressed(const KeyPressedEvent& event) override;

    void onKeyRepeat(const KeyRepeatEvent& event) override;

    bool getKeyboardDelegateEnabled() const override {
        return is_active_ && this->getIsActive();
    }
protected:
    bool is_active_;
    size_t cursor_pos_;
    std::wstring placeholder_;
    std::wstring input_text_;
    std::shared_ptr<Node> cursor_renderer_;
    std::shared_ptr<Label> label_;

    void updateLabel();
    void charInput(const CharInputEvent& event);
    bool applyKey(int key);

    void setInputLabelActive();
    void setInputLabelInactive();
    void updateCursorRendererPos() const;

    void onPressed(Button* button, const MouseButtonPressedEvent& event);
    void onSelect(Button* button);
    void onDeselect(Button* button);
};

NS_FT_END
