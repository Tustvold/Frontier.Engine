#include <Event/Mouse/FTMouseEventDispatcher.h>

// A targeted delegate to facilitate UI 
class FTMouseDelegate {
public:
    FTMouseDelegate() : priority_(0), is_enabled_(0) {

    }

    virtual ~FTMouseDelegate() {
    }

    virtual bool onMouseDown(const FTMouseButtonPressedEvent& event) = 0;
    virtual void onMouseMove(const FTMouseMoveEvent&, int mouse_button) = 0;
    virtual void onMouseRelease(const FTMouseButtonReleasedEvent& event) = 0;

    void setPriority(int priority) {
        priority_ = priority;
    }

    int getPriority() const {
        return priority_;
    }

    void setEnabled(bool enabled) {
        is_enabled_ = enabled;
    }

    bool getIsEnabled() const {
        return is_enabled_;
    }

private:
    int priority_;
    bool is_enabled_;
};
