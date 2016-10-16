#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <gmock/gmock.h>

class GlfwMock {

public:

    static GlfwMock* getMock();

    GlfwMock();
    
    virtual ~GlfwMock();

    // Input callbacks
    GLFWkeyfun key_callback_;
    GLFWcharfun char_callback_;
    GLFWcharmodsfun char_mods_callback_;
    GLFWmousebuttonfun mouse_button_callback_;
    GLFWcursorposfun mouse_pos_callback_;
    GLFWcursorenterfun mouse_enter_callback_;
    GLFWscrollfun mouse_scroll_callback_;
    GLFWdropfun drop_callback_;

    // Window callbacks
    GLFWwindowposfun window_pos_callback_;
    GLFWwindowsizefun window_size_callback_;
    GLFWwindowclosefun window_close_callback_;
    GLFWwindowrefreshfun window_refresh_callback_;
    GLFWwindowfocusfun window_focus_callback_;
    GLFWwindowiconifyfun window_iconify_callback_;
    GLFWframebuffersizefun window_set_frame_buffer_size_callback_;
};
