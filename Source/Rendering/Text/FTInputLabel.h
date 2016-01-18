#pragma once
#include "FTLabel.h"

struct FTKeyRepeatEvent;
struct FTKeyPressedEvent;
struct FTCharInputEvent;

class FTInputLabel : public FTLabel {
public:
    FTInputLabel(const std::wstring& placeholder, const std::wstring& text, const std::string& font, int fontsize);
    
    virtual ~FTInputLabel();

protected:
    bool is_active_;
    size_t cursor_pos_;
    std::wstring placeholder_;
    std::wstring input_text_;
    std::shared_ptr<FTNode> cursor_renderer_;

    void updateLabel();
    void charInput(const FTCharInputEvent& event);
    void keyPressedEvent(const FTKeyPressedEvent& event);
    void keyRepeatEvent(const FTKeyRepeatEvent& event);
    void applyKey(int key);

    void setActive();
    void setInactive();
    void updateCursorRendererPos() const;

    bool onPressed(FTButton* button, const FTMouseButtonPressedEvent& event);
    void onDeselect(FTButton* button);
};
