#pragma once
#include <Event/Event.h>

NS_FT_BEGIN

struct KeyPressedEvent : public Event {
public:
    KeyPressedEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const KeyPressedEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct KeyReleasedEvent : public Event {
public:
    KeyReleasedEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const KeyReleasedEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct KeyRepeatEvent : public Event {
public:
    KeyRepeatEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const KeyRepeatEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct CharInputEvent : public Event {
public:
    CharInputEvent(wchar_t character, int mods) : character_(character), mods_(mods) {
        
    }

    wchar_t character_;
    int mods_;

    bool operator==(const CharInputEvent& other) const {
        return character_ == other.character_ && mods_ == other.mods_;
    }
};

NS_FT_END