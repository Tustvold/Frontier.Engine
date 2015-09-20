#include "glfwmock.h"

GlfwMock::GlfwMock() {

}

GlfwMock::~GlfwMock() {

}

GlfwMock* GlfwMock::getMock() {
    return (GlfwMock*)GlewMock::getMock();
}


int glfwInit(void) {
    return GlfwMock::getMock()->glfwInit();
}

void glfwTerminate(void) {
    GlfwMock::getMock()->glfwTerminate();
}

void glfwGetVersion(int* major, int* minor, int* rev) {
    GlfwMock::getMock()->glfwGetVersion(major, minor, rev);
}

const char* glfwGetVersionString(void) {
    return GlfwMock::getMock()->glfwGetVersionString();
}

GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun) {
    return GlfwMock::getMock()->glfwSetErrorCallback(cbfun);
}

GLFWmonitor** glfwGetMonitors(int* count) {
    return GlfwMock::getMock()->glfwGetMonitors(count);
}

GLFWmonitor* glfwGetPrimaryMonitor(void) {
    return GlfwMock::getMock()->glfwGetPrimaryMonitor();
}

void glfwGetMonitorPos(GLFWmonitor* monitor, int* xpos, int* ypos) {
    GlfwMock::getMock()->glfwGetMonitorPos(monitor, xpos, ypos);
}

void glfwGetMonitorPhysicalSize(GLFWmonitor* monitor, int* widthMM, int* heightMM) {
    GlfwMock::getMock()->glfwGetMonitorPhysicalSize(monitor, widthMM, heightMM);
}

const char* glfwGetMonitorName(GLFWmonitor* monitor) {
    return GlfwMock::getMock()->glfwGetMonitorName(monitor);
}

GLFWmonitorfun glfwSetMonitorCallback(GLFWmonitorfun cbfun) {
    return GlfwMock::getMock()->glfwSetMonitorCallback(cbfun);
}

const GLFWvidmode* glfwGetVideoModes(GLFWmonitor* monitor, int* count) {
    return GlfwMock::getMock()->glfwGetVideoModes(monitor, count);
}

const GLFWvidmode* glfwGetVideoMode(GLFWmonitor* monitor) {
    return GlfwMock::getMock()->glfwGetVideoMode(monitor);
}

void glfwSetGamma(GLFWmonitor* monitor, float gamma) {
    GlfwMock::getMock()->glfwSetGamma(monitor, gamma);
}

const GLFWgammaramp* glfwGetGammaRamp(GLFWmonitor* monitor) {
    return GlfwMock::getMock()->glfwGetGammaRamp(monitor);
}

void glfwSetGammaRamp(GLFWmonitor* monitor, const GLFWgammaramp* ramp) {
    GlfwMock::getMock()->glfwSetGammaRamp(monitor, ramp);
}

void glfwDefaultWindowHints(void) {
    GlfwMock::getMock()->glfwDefaultWindowHints();
}

void glfwWindowHint(int target, int hint) {
    GlfwMock::getMock()->glfwWindowHint(target, hint);
}

GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
    return GlfwMock::getMock()->glfwCreateWindow(width, height, title, monitor, share);
}

void glfwDestroyWindow(GLFWwindow* window) {
    GlfwMock::getMock()->glfwDestroyWindow(window);
}

int glfwWindowShouldClose(GLFWwindow* window) {
    return GlfwMock::getMock()->glfwWindowShouldClose(window);
}

void glfwSetWindowShouldClose(GLFWwindow* window, int value) {
    GlfwMock::getMock()->glfwSetWindowShouldClose(window, value);
}

void glfwSetWindowTitle(GLFWwindow* window, const char* title) {
    GlfwMock::getMock()->glfwSetWindowTitle(window, title);
}

void glfwGetWindowPos(GLFWwindow* window, int* xpos, int* ypos) {
    GlfwMock::getMock()->glfwGetWindowPos(window, xpos, ypos);
}

void glfwSetWindowPos(GLFWwindow* window, int xpos, int ypos) {
    GlfwMock::getMock()->glfwSetWindowPos(window, xpos, ypos);
}

void glfwGetWindowSize(GLFWwindow* window, int* width, int* height) {
    GlfwMock::getMock()->glfwGetWindowSize(window, width, height);
}

void glfwSetWindowSize(GLFWwindow* window, int width, int height) {
    GlfwMock::getMock()->glfwSetWindowSize(window, width, height);
}

void glfwGetFramebufferSize(GLFWwindow* window, int* width, int* height) {
    GlfwMock::getMock()->glfwGetFramebufferSize(window, width, height);
}

void glfwGetWindowFrameSize(GLFWwindow* window, int* left, int* top, int* right, int* bottom) {
    GlfwMock::getMock()->glfwGetWindowFrameSize(window, left, top, right, bottom);
}

void glfwIconifyWindow(GLFWwindow* window) {
    GlfwMock::getMock()->glfwIconifyWindow(window);
}

void glfwRestoreWindow(GLFWwindow* window) {
    GlfwMock::getMock()->glfwRestoreWindow(window);
}

void glfwShowWindow(GLFWwindow* window) {
    GlfwMock::getMock()->glfwShowWindow(window);
}

void glfwHideWindow(GLFWwindow* window) {
    GlfwMock::getMock()->glfwHideWindow(window);
}

GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* window) {
    return GlfwMock::getMock()->glfwGetWindowMonitor(window);
}

int glfwGetWindowAttrib(GLFWwindow* window, int attrib) {
    return GlfwMock::getMock()->glfwGetWindowAttrib(window, attrib);
}

void glfwSetWindowUserPointer(GLFWwindow* window, void* pointer) {
    GlfwMock::getMock()->glfwSetWindowUserPointer(window, pointer);
}

void* glfwGetWindowUserPointer(GLFWwindow* window) {
    return GlfwMock::getMock()->glfwGetWindowUserPointer(window);
}

GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun cbfun) {
    return GlfwMock::getMock()->window_pos_callback_ = cbfun;
}

GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun cbfun) {
    return GlfwMock::getMock()->window_size_callback_ = cbfun;
}

GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun cbfun) {
    return GlfwMock::getMock()->window_close_callback_ = cbfun;
}

GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* window, GLFWwindowrefreshfun cbfun) {
    return GlfwMock::getMock()->window_refresh_callback_ = cbfun;
}

GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun cbfun) {
    return GlfwMock::getMock()->window_focus_callback_ = cbfun;
}

GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* window, GLFWwindowiconifyfun cbfun) {
    return GlfwMock::getMock()->window_iconify_callback_ = cbfun;
}

GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun cbfun) {
    return GlfwMock::getMock()->window_set_frame_buffer_size_callback_ = cbfun;
}

void glfwPollEvents(void) {
    GlfwMock::getMock()->glfwPollEvents();
}

void glfwWaitEvents(void) {
    GlfwMock::getMock()->glfwWaitEvents();
}

void glfwPostEmptyEvent(void) {
    GlfwMock::getMock()->glfwPostEmptyEvent();
}

int glfwGetInputMode(GLFWwindow* window, int mode) {
    return GlfwMock::getMock()->glfwGetInputMode(window, mode);
}

void glfwSetInputMode(GLFWwindow* window, int mode, int value) {
    GlfwMock::getMock()->glfwSetInputMode(window, mode, value);
}

int glfwGetKey(GLFWwindow* window, int key) {
    return GlfwMock::getMock()->glfwGetKey(window, key);
}

int glfwGetMouseButton(GLFWwindow* window, int button) {
    return GlfwMock::getMock()->glfwGetMouseButton(window, button);
}

void glfwGetCursorPos(GLFWwindow* window, double* xpos, double* ypos) {
    GlfwMock::getMock()->glfwGetCursorPos(window, xpos, ypos);
}

void glfwSetCursorPos(GLFWwindow* window, double xpos, double ypos) {
    GlfwMock::getMock()->glfwSetCursorPos(window, xpos, ypos);
}

GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot) {
    return GlfwMock::getMock()->glfwCreateCursor(image, xhot, yhot);
}

GLFWcursor* glfwCreateStandardCursor(int shape) {
    return GlfwMock::getMock()->glfwCreateStandardCursor(shape);
}

void glfwDestroyCursor(GLFWcursor* cursor) {
    GlfwMock::getMock()->glfwDestroyCursor(cursor);
}

void glfwSetCursor(GLFWwindow* window, GLFWcursor* cursor) {
    GlfwMock::getMock()->glfwSetCursor(window, cursor);
}

GLFWkeyfun glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun cbfun) {
    return GlfwMock::getMock()->key_callback_ = cbfun;
}

GLFWcharfun glfwSetCharCallback(GLFWwindow* window, GLFWcharfun cbfun) {
    return GlfwMock::getMock()->char_callback_ = cbfun;
}

GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow* window, GLFWcharmodsfun cbfun) {
    return GlfwMock::getMock()->char_mods_callback_ = cbfun;
}

GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun cbfun) {
    return GlfwMock::getMock()->mouse_button_callback_ = cbfun;
}

GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun cbfun) {
    return GlfwMock::getMock()->mouse_pos_callback_ = cbfun;
}

GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun cbfun) {
    return GlfwMock::getMock()->mouse_enter_callback_ = cbfun;
}

GLFWscrollfun glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun cbfun) {
    return GlfwMock::getMock()->mouse_scroll_callback_ = cbfun;
}

GLFWdropfun glfwSetDropCallback(GLFWwindow* window, GLFWdropfun cbfun) {
    return GlfwMock::getMock()->drop_callback_ = cbfun;
}

int glfwJoystickPresent(int joy) {
    return GlfwMock::getMock()->glfwJoystickPresent(joy);
}

const float* glfwGetJoystickAxes(int joy, int* count) {
    return GlfwMock::getMock()->glfwGetJoystickAxes(joy, count);
}

const unsigned char* glfwGetJoystickButtons(int joy, int* count) {
    return GlfwMock::getMock()->glfwGetJoystickButtons(joy, count);
}

const char* glfwGetJoystickName(int joy) {
    return GlfwMock::getMock()->glfwGetJoystickName(joy);
}

void glfwSetClipboardString(GLFWwindow* window, const char* string) {
    GlfwMock::getMock()->glfwSetClipboardString(window, string);
}

const char* glfwGetClipboardString(GLFWwindow* window) {
    return GlfwMock::getMock()->glfwGetClipboardString(window);
}

double glfwGetTime(void) {
    return GlfwMock::getMock()->glfwGetTime();
}

void glfwSetTime(double time) {
    GlfwMock::getMock()->glfwSetTime(time);
}

void glfwMakeContextCurrent(GLFWwindow* window) {
    GlfwMock::getMock()->glfwMakeContextCurrent(window);
}

GLFWwindow* glfwGetCurrentContext(void) {
    return GlfwMock::getMock()->glfwGetCurrentContext();
}

void glfwSwapBuffers(GLFWwindow* window) {
    GlfwMock::getMock()->glfwSwapBuffers(window);
}

void glfwSwapInterval(int interval) {
    GlfwMock::getMock()->glfwSwapInterval(interval);
}

int glfwExtensionSupported(const char* extension) {
    return GlfwMock::getMock()->glfwExtensionSupported(extension);
}

GLFWglproc glfwGetProcAddress(const char* procname) {
    return GlfwMock::getMock()->glfwGetProcAddress(procname);
}