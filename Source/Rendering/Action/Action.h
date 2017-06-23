#pragma once
#include <Frontier.h>

NS_FT_BEGIN

struct UpdateEvent;
class Node;

class Action {
public:
    // Called before the first call to onUpdate
    //
    // if setCompleted() is called within onStart the node will not be destroyed
    // until the next update event
    // Should fully reset the node in order for repeats to work correctly
    virtual void onStart(Node* node) {
        is_completed_ = false;
    }

    // Called every time an UpdateEvent is fired.
    // This will never be called on an Action marked as completed
    virtual void onUpdate(Node* node, const UpdateEvent& event) {
        
    }

    virtual ~Action() {

    }

    void setPaused(bool is_paused) {
        is_paused_ = is_paused;
    }

    bool getIsPaused() const {
        return is_paused_;
    }

    void setCompleted() {
        is_completed_ = true;
    }

    bool getCompleted() const {
        return is_completed_;
    }

protected:
    Action() : is_paused_(false), is_completed_(false) {

    }

private:
    bool is_paused_;
    bool is_completed_;
};

NS_FT_END
