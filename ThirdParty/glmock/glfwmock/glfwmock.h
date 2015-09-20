#pragma once

#include <gmock/gmock.h>
#include <glewmock.hpp>
#include <GLFW/glfw3.h>


class GlfwMock : public GlewMock {

public:

    static GlfwMock* getMock();

    GlfwMock();
    
    virtual ~GlfwMock();

    MOCK_METHOD0(glfwInit, int(void));

    MOCK_METHOD0(glfwTerminate, void(void));

    MOCK_METHOD3(glfwGetVersion, void(int* major, int* minor, int* rev));

    MOCK_METHOD0(glfwGetVersionString, const char*(void));

    MOCK_METHOD1(glfwSetErrorCallback, GLFWerrorfun(GLFWerrorfun cbfun));

    MOCK_METHOD1(glfwGetMonitors, GLFWmonitor**(int* count));

    MOCK_METHOD0(glfwGetPrimaryMonitor, GLFWmonitor*(void));

    MOCK_METHOD3(glfwGetMonitorPos, void(GLFWmonitor* monitor, int* xpos, int* ypos));

    MOCK_METHOD3(glfwGetMonitorPhysicalSize, void(GLFWmonitor* monitor, int* widthMM, int* heightMM));

    MOCK_METHOD1(glfwGetMonitorName, const char*(GLFWmonitor* monitor));

    MOCK_METHOD1(glfwSetMonitorCallback, GLFWmonitorfun(GLFWmonitorfun cbfun));

    MOCK_METHOD2(glfwGetVideoModes, const GLFWvidmode*(GLFWmonitor* monitor, int* count));

    MOCK_METHOD1(glfwGetVideoMode, const GLFWvidmode*(GLFWmonitor* monitor));

    MOCK_METHOD2(glfwSetGamma, void(GLFWmonitor* monitor, float gamma));

    MOCK_METHOD1(glfwGetGammaRamp, const GLFWgammaramp*(GLFWmonitor* monitor));

    MOCK_METHOD2(glfwSetGammaRamp, void(GLFWmonitor* monitor, const GLFWgammaramp* ramp));

    MOCK_METHOD0(glfwDefaultWindowHints, void(void));

    MOCK_METHOD2(glfwWindowHint, void(int target, int hint));

    MOCK_METHOD5(glfwCreateWindow, GLFWwindow*(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share));

    MOCK_METHOD1(glfwDestroyWindow, void(GLFWwindow* window));

    MOCK_METHOD1(glfwWindowShouldClose, int(GLFWwindow* window));

    MOCK_METHOD2(glfwSetWindowShouldClose, void(GLFWwindow* window, int value));

    MOCK_METHOD2(glfwSetWindowTitle, void(GLFWwindow* window, const char* title));

    MOCK_METHOD3(glfwGetWindowPos, void(GLFWwindow* window, int* xpos, int* ypos));

    MOCK_METHOD3(glfwSetWindowPos, void(GLFWwindow* window, int xpos, int ypos));

    MOCK_METHOD3(glfwGetWindowSize, void(GLFWwindow* window, int* width, int* height));

    MOCK_METHOD3(glfwSetWindowSize, void(GLFWwindow* window, int width, int height));

    MOCK_METHOD3(glfwGetFramebufferSize, void(GLFWwindow* window, int* width, int* height));

    MOCK_METHOD5(glfwGetWindowFrameSize, void(GLFWwindow* window, int* left, int* top, int* right, int* bottom));

    MOCK_METHOD1(glfwIconifyWindow, void(GLFWwindow* window));

    MOCK_METHOD1(glfwRestoreWindow, void(GLFWwindow* window));

    MOCK_METHOD1(glfwShowWindow, void(GLFWwindow* window));

    MOCK_METHOD1(glfwHideWindow, void(GLFWwindow* window));

    MOCK_METHOD1(glfwGetWindowMonitor, GLFWmonitor*(GLFWwindow* window));

    MOCK_METHOD2(glfwGetWindowAttrib, int(GLFWwindow* window, int attrib));

    MOCK_METHOD2(glfwSetWindowUserPointer, void(GLFWwindow* window, void* pointer));

    MOCK_METHOD1(glfwGetWindowUserPointer, void*(GLFWwindow* window));

    MOCK_METHOD0(glfwPollEvents, void(void));

    MOCK_METHOD0(glfwWaitEvents, void(void));

    MOCK_METHOD0(glfwPostEmptyEvent, void(void));

    MOCK_METHOD2(glfwGetInputMode, int(GLFWwindow* window, int mode));

    MOCK_METHOD3(glfwSetInputMode, void(GLFWwindow* window, int mode, int value));

    MOCK_METHOD2(glfwGetKey, int(GLFWwindow* window, int key));

    MOCK_METHOD2(glfwGetMouseButton, int(GLFWwindow* window, int button));

    MOCK_METHOD3(glfwGetCursorPos, void(GLFWwindow* window, double* xpos, double* ypos));

    MOCK_METHOD3(glfwSetCursorPos, void(GLFWwindow* window, double xpos, double ypos));

    MOCK_METHOD3(glfwCreateCursor, GLFWcursor*(const GLFWimage* image, int xhot, int yhot));

    MOCK_METHOD1(glfwCreateStandardCursor, GLFWcursor*(int shape));

    MOCK_METHOD1(glfwDestroyCursor, void(GLFWcursor* cursor));

    MOCK_METHOD2(glfwSetCursor, void(GLFWwindow* window, GLFWcursor* cursor));

    MOCK_METHOD1(glfwJoystickPresent, int(int joy));

    MOCK_METHOD2(glfwGetJoystickAxes, const float*(int joy, int* count));

    MOCK_METHOD2(glfwGetJoystickButtons, const unsigned char*(int joy, int* count));

    MOCK_METHOD1(glfwGetJoystickName, const char*(int joy));

    MOCK_METHOD2(glfwSetClipboardString, void(GLFWwindow* window, const char* string));

    MOCK_METHOD1(glfwGetClipboardString, const char*(GLFWwindow* window));

    MOCK_METHOD0(glfwGetTime, double(void));

    MOCK_METHOD1(glfwSetTime, void(double time));

    MOCK_METHOD1(glfwMakeContextCurrent, void(GLFWwindow* window));

    MOCK_METHOD0(glfwGetCurrentContext, GLFWwindow*(void));

    MOCK_METHOD1(glfwSwapBuffers, void(GLFWwindow* window));

    MOCK_METHOD1(glfwSwapInterval, void(int interval));

    MOCK_METHOD1(glfwExtensionSupported, int(const char* extension));

    MOCK_METHOD1(glfwGetProcAddress, GLFWglproc(const char* procname));

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
