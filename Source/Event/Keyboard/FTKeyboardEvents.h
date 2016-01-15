#pragma once
#include <Event/FTEvent.h>

struct FTKeyPressedEvent : public FTEvent {
public:
    FTKeyPressedEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const FTKeyPressedEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct FTKeyReleasedEvent : public FTEvent {
public:
    FTKeyReleasedEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const FTKeyReleasedEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct FTKeyRepeatEvent : public FTEvent {
public:
    FTKeyRepeatEvent(int key, int scancode, int mods) : key_(key), scancode_(scancode), mods_(mods) {

    }

    int key_;
    int scancode_;
    int mods_;

    bool operator==(const FTKeyRepeatEvent& other) const {
        return key_ == other.key_ && scancode_ == other.scancode_ && mods_ == other.mods_;
    }
};

struct FTCharInputEvent : public FTEvent {
public:
    FTCharInputEvent(wchar_t character, int mods) : character_(character), mods_(mods) {
        
    }

    wchar_t character_;
    int mods_;

    bool operator==(const FTCharInputEvent& other) const {
        return character_ == other.character_ && mods_ == other.mods_;
    }
};