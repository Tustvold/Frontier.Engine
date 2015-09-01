
#ifdef _WIN32
#define GLAPI __declspec(dllexport)
#endif

#include "iglmock.hpp"
#include <thread>
#include <mutex>
#include <map>
#include <ostream>
#include <iostream>


static std::map<std::thread::id, IGLMock* > gMap;
static std::mutex gMutex;

IGLMock::IGLMock() {
	gMutex.lock();
	gMap.insert(std::pair<std::thread::id, IGLMock* >(std::this_thread::get_id(), this));
	gMutex.unlock();
}

IGLMock::~IGLMock() {
	gMutex.lock();
	auto it = gMap.find(std::this_thread::get_id());
	gMap.erase(std::this_thread::get_id());
	gMutex.unlock();
}

IGLMock* IGLMock::getMock() {
	gMutex.lock();
	auto it = gMap.find(std::this_thread::get_id());
	if (it == gMap.end()) {
		std::cerr << "Initialize IGLMock first" << std::endl;
		gMutex.unlock();
		std::abort();
	}
	gMutex.unlock();
	return it->second;
}

void glAccum(GLenum op, GLfloat value) {
	return IGLMock::getMock()->gl_Accum(op, value);
}

void glAlphaFunc(GLenum func, GLclampf ref) {
	return IGLMock::getMock()->gl_AlphaFunc(func, ref);
}

GLboolean glAreTexturesResident(GLsizei n, const GLuint* textures, GLboolean* residences) {
	return IGLMock::getMock()->gl_AreTexturesResident(n, textures, residences);
}

void glArrayElement(GLint i) {
	return IGLMock::getMock()->gl_ArrayElement(i);
}

void glBegin(GLenum mode) {
	return IGLMock::getMock()->gl_Begin(mode);
}

void glBindTexture(GLenum target, GLuint texture) {
	return IGLMock::getMock()->gl_BindTexture(target, texture);
}

void glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap) {
	return IGLMock::getMock()->gl_Bitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}

void glBlendFunc(GLenum sfactor, GLenum dfactor) {
	return IGLMock::getMock()->gl_BlendFunc(sfactor, dfactor);
}

void glCallList(GLuint list) {
	return IGLMock::getMock()->gl_CallList(list);
}

void glCallLists(GLsizei n, GLenum type, const void* lists) {
	return IGLMock::getMock()->gl_CallLists(n, type, lists);
}

void glClear(GLbitfield mask) {
	return IGLMock::getMock()->gl_Clear(mask);
}

void glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	return IGLMock::getMock()->gl_ClearAccum(red, green, blue, alpha);
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
	return IGLMock::getMock()->gl_ClearColor(red, green, blue, alpha);
}

void glClearDepth(GLclampd depth) {
	return IGLMock::getMock()->gl_ClearDepth(depth);
}

void glClearIndex(GLfloat c) {
	return IGLMock::getMock()->gl_ClearIndex(c);
}

void glClearStencil(GLint s) {
	return IGLMock::getMock()->gl_ClearStencil(s);
}

void glClipPlane(GLenum plane, const GLdouble* equation) {
	return IGLMock::getMock()->gl_ClipPlane(plane, equation);
}

void glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
	return IGLMock::getMock()->gl_Color3b(red, green, blue);
}

void glColor3bv(const GLbyte* v) {
	return IGLMock::getMock()->gl_Color3bv(v);
}

void glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
	return IGLMock::getMock()->gl_Color3d(red, green, blue);
}

void glColor3dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Color3dv(v);
}

void glColor3f(GLfloat red, GLfloat green, GLfloat blue) {
	return IGLMock::getMock()->gl_Color3f(red, green, blue);
}

void glColor3fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Color3fv(v);
}

void glColor3i(GLint red, GLint green, GLint blue) {
	return IGLMock::getMock()->gl_Color3i(red, green, blue);
}

void glColor3iv(const GLint* v) {
	return IGLMock::getMock()->gl_Color3iv(v);
}

void glColor3s(GLshort red, GLshort green, GLshort blue) {
	return IGLMock::getMock()->gl_Color3s(red, green, blue);
}

void glColor3sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Color3sv(v);
}

void glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
	return IGLMock::getMock()->gl_Color3ub(red, green, blue);
}

void glColor3ubv(const GLubyte* v) {
	return IGLMock::getMock()->gl_Color3ubv(v);
}

void glColor3ui(GLuint red, GLuint green, GLuint blue) {
	return IGLMock::getMock()->gl_Color3ui(red, green, blue);
}

void glColor3uiv(const GLuint* v) {
	return IGLMock::getMock()->gl_Color3uiv(v);
}

void glColor3us(GLushort red, GLushort green, GLushort blue) {
	return IGLMock::getMock()->gl_Color3us(red, green, blue);
}

void glColor3usv(const GLushort* v) {
	return IGLMock::getMock()->gl_Color3usv(v);
}

void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
	return IGLMock::getMock()->gl_Color4b(red, green, blue, alpha);
}

void glColor4bv(const GLbyte* v) {
	return IGLMock::getMock()->gl_Color4bv(v);
}

void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) {
	return IGLMock::getMock()->gl_Color4d(red, green, blue, alpha);
}

void glColor4dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Color4dv(v);
}

void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
	return IGLMock::getMock()->gl_Color4f(red, green, blue, alpha);
}

void glColor4fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Color4fv(v);
}

void glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
	return IGLMock::getMock()->gl_Color4i(red, green, blue, alpha);
}

void glColor4iv(const GLint* v) {
	return IGLMock::getMock()->gl_Color4iv(v);
}

void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) {
	return IGLMock::getMock()->gl_Color4s(red, green, blue, alpha);
}

void glColor4sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Color4sv(v);
}

void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
	return IGLMock::getMock()->gl_Color4ub(red, green, blue, alpha);
}

void glColor4ubv(const GLubyte* v) {
	return IGLMock::getMock()->gl_Color4ubv(v);
}

void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
	return IGLMock::getMock()->gl_Color4ui(red, green, blue, alpha);
}

void glColor4uiv(const GLuint* v) {
	return IGLMock::getMock()->gl_Color4uiv(v);
}

void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) {
	return IGLMock::getMock()->gl_Color4us(red, green, blue, alpha);
}

void glColor4usv(const GLushort* v) {
	return IGLMock::getMock()->gl_Color4usv(v);
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
	return IGLMock::getMock()->gl_ColorMask(red, green, blue, alpha);
}

void glColorMaterial(GLenum face, GLenum mode) {
	return IGLMock::getMock()->gl_ColorMaterial(face, mode);
}

void glColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_ColorPointer(size, type, stride, pointer);
}

void glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) {
	return IGLMock::getMock()->gl_CopyPixels(x, y, width, height, type);
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border) {
	return IGLMock::getMock()->gl_CopyTexImage1D(target, level, internalFormat, x, y, width, border);
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
	return IGLMock::getMock()->gl_CopyTexImage2D(target, level, internalFormat, x, y, width, height, border);
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
	return IGLMock::getMock()->gl_CopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
	return IGLMock::getMock()->gl_CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void glCullFace(GLenum mode) {
	return IGLMock::getMock()->gl_CullFace(mode);
}

void glDeleteLists(GLuint list, GLsizei range) {
	return IGLMock::getMock()->gl_DeleteLists(list, range);
}

void glDeleteTextures(GLsizei n, const GLuint* textures) {
	return IGLMock::getMock()->gl_DeleteTextures(n, textures);
}

void glDepthFunc(GLenum func) {
	return IGLMock::getMock()->gl_DepthFunc(func);
}

void glDepthMask(GLboolean flag) {
	return IGLMock::getMock()->gl_DepthMask(flag);
}

void glDepthRange(GLclampd zNear, GLclampd zFar) {
	return IGLMock::getMock()->gl_DepthRange(zNear, zFar);
}

void glDisable(GLenum cap) {
	return IGLMock::getMock()->gl_Disable(cap);
}

void glDisableClientState(GLenum array) {
	return IGLMock::getMock()->gl_DisableClientState(array);
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count) {
	return IGLMock::getMock()->gl_DrawArrays(mode, first, count);
}

void glDrawBuffer(GLenum mode) {
	return IGLMock::getMock()->gl_DrawBuffer(mode);
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
	return IGLMock::getMock()->gl_DrawElements(mode, count, type, indices);
}

void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
	return IGLMock::getMock()->gl_DrawPixels(width, height, format, type, pixels);
}

void glEdgeFlag(GLboolean flag) {
	return IGLMock::getMock()->gl_EdgeFlag(flag);
}

void glEdgeFlagPointer(GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_EdgeFlagPointer(stride, pointer);
}

void glEdgeFlagv(const GLboolean* flag) {
	return IGLMock::getMock()->gl_EdgeFlagv(flag);
}

void glEnable(GLenum cap) {
	return IGLMock::getMock()->gl_Enable(cap);
}

void glEnableClientState(GLenum array) {
	return IGLMock::getMock()->gl_EnableClientState(array);
}

void glEnd() {
	return IGLMock::getMock()->gl_End();
}

void glEndList() {
	return IGLMock::getMock()->gl_EndList();
}

void glEvalCoord1d(GLdouble u) {
	return IGLMock::getMock()->gl_EvalCoord1d(u);
}

void glEvalCoord1dv(const GLdouble* u) {
	return IGLMock::getMock()->gl_EvalCoord1dv(u);
}

void glEvalCoord1f(GLfloat u) {
	return IGLMock::getMock()->gl_EvalCoord1f(u);
}

void glEvalCoord1fv(const GLfloat* u) {
	return IGLMock::getMock()->gl_EvalCoord1fv(u);
}

void glEvalCoord2d(GLdouble u, GLdouble v) {
	return IGLMock::getMock()->gl_EvalCoord2d(u, v);
}

void glEvalCoord2dv(const GLdouble* u) {
	return IGLMock::getMock()->gl_EvalCoord2dv(u);
}

void glEvalCoord2f(GLfloat u, GLfloat v) {
	return IGLMock::getMock()->gl_EvalCoord2f(u, v);
}

void glEvalCoord2fv(const GLfloat* u) {
	return IGLMock::getMock()->gl_EvalCoord2fv(u);
}

void glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
	return IGLMock::getMock()->gl_EvalMesh1(mode, i1, i2);
}

void glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
	return IGLMock::getMock()->gl_EvalMesh2(mode, i1, i2, j1, j2);
}

void glEvalPoint1(GLint i) {
	return IGLMock::getMock()->gl_EvalPoint1(i);
}

void glEvalPoint2(GLint i, GLint j) {
	return IGLMock::getMock()->gl_EvalPoint2(i, j);
}

void glFeedbackBuffer(GLsizei size, GLenum type, GLfloat* buffer) {
	return IGLMock::getMock()->gl_FeedbackBuffer(size, type, buffer);
}

void glFinish() {
	return IGLMock::getMock()->gl_Finish();
}

void glFlush() {
	return IGLMock::getMock()->gl_Flush();
}

void glFogf(GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_Fogf(pname, param);
}

void glFogfv(GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_Fogfv(pname, params);
}

void glFogi(GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_Fogi(pname, param);
}

void glFogiv(GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_Fogiv(pname, params);
}

void glFrontFace(GLenum mode) {
	return IGLMock::getMock()->gl_FrontFace(mode);
}

void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
	return IGLMock::getMock()->gl_Frustum(left, right, bottom, top, zNear, zFar);
}

GLuint glGenLists(GLsizei range) {
	return IGLMock::getMock()->gl_GenLists(range);
}

void GLAPIENTRY glGenTextures(GLsizei n, GLuint* textures) {
	return IGLMock::getMock()->gl_GenTextures(n, textures);
}

void glGetBooleanv(GLenum pname, GLboolean* params) {
	return IGLMock::getMock()->gl_GetBooleanv(pname, params);
}

void glGetClipPlane(GLenum plane, GLdouble* equation) {
	return IGLMock::getMock()->gl_GetClipPlane(plane, equation);
}

void glGetDoublev(GLenum pname, GLdouble* params) {
	return IGLMock::getMock()->gl_GetDoublev(pname, params);
}

GLenum glGetError() {
	return IGLMock::getMock()->gl_GetError();
}

void glGetFloatv(GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetFloatv(pname, params);
}

void glGetIntegerv(GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetIntegerv(pname, params);
}

void glGetLightfv(GLenum light, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetLightfv(light, pname, params);
}

void glGetLightiv(GLenum light, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetLightiv(light, pname, params);
}

void glGetMapdv(GLenum target, GLenum query, GLdouble* v) {
	return IGLMock::getMock()->gl_GetMapdv(target, query, v);
}

void glGetMapfv(GLenum target, GLenum query, GLfloat* v) {
	return IGLMock::getMock()->gl_GetMapfv(target, query, v);
}

void glGetMapiv(GLenum target, GLenum query, GLint* v) {
	return IGLMock::getMock()->gl_GetMapiv(target, query, v);
}

void glGetMaterialfv(GLenum face, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetMaterialfv(face, pname, params);
}

void glGetMaterialiv(GLenum face, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetMaterialiv(face, pname, params);
}

void glGetPixelMapfv(GLenum map, GLfloat* values) {
	return IGLMock::getMock()->gl_GetPixelMapfv(map, values);
}

void glGetPixelMapuiv(GLenum map, GLuint* values) {
	return IGLMock::getMock()->gl_GetPixelMapuiv(map, values);
}

void glGetPixelMapusv(GLenum map, GLushort* values) {
	return IGLMock::getMock()->gl_GetPixelMapusv(map, values);
}

void glGetPointerv(GLenum pname, void** params) {
	return IGLMock::getMock()->gl_GetPointerv(pname, params);
}

void glGetPolygonStipple(GLubyte* mask) {
	return IGLMock::getMock()->gl_GetPolygonStipple(mask);
}

const GLubyte* glGetString(GLenum name) {
	return IGLMock::getMock()->gl_GetString(name);
}

void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetTexEnvfv(target, pname, params);
}

void glGetTexEnviv(GLenum target, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetTexEnviv(target, pname, params);
}

void glGetTexGendv(GLenum coord, GLenum pname, GLdouble* params) {
	return IGLMock::getMock()->gl_GetTexGendv(coord, pname, params);
}

void glGetTexGenfv(GLenum coord, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetTexGenfv(coord, pname, params);
}

void glGetTexGeniv(GLenum coord, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetTexGeniv(coord, pname, params);
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void* pixels) {
	return IGLMock::getMock()->gl_GetTexImage(target, level, format, type, pixels);
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetTexLevelParameterfv(target, level, pname, params);
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetTexLevelParameteriv(target, level, pname, params);
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params) {
	return IGLMock::getMock()->gl_GetTexParameterfv(target, pname, params);
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params) {
	return IGLMock::getMock()->gl_GetTexParameteriv(target, pname, params);
}

void glHint(GLenum target, GLenum mode) {
	return IGLMock::getMock()->gl_Hint(target, mode);
}

void glIndexMask(GLuint mask) {
	return IGLMock::getMock()->gl_IndexMask(mask);
}

void glIndexPointer(GLenum type, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_IndexPointer(type, stride, pointer);
}

void glIndexd(GLdouble c) {
	return IGLMock::getMock()->gl_Indexd(c);
}

void glIndexdv(const GLdouble* c) {
	return IGLMock::getMock()->gl_Indexdv(c);
}

void glIndexf(GLfloat c) {
	return IGLMock::getMock()->gl_Indexf(c);
}

void glIndexfv(const GLfloat* c) {
	return IGLMock::getMock()->gl_Indexfv(c);
}

void glIndexi(GLint c) {
	return IGLMock::getMock()->gl_Indexi(c);
}

void glIndexiv(const GLint* c) {
	return IGLMock::getMock()->gl_Indexiv(c);
}

void glIndexs(GLshort c) {
	return IGLMock::getMock()->gl_Indexs(c);
}

void glIndexsv(const GLshort* c) {
	return IGLMock::getMock()->gl_Indexsv(c);
}

void glIndexub(GLubyte c) {
	return IGLMock::getMock()->gl_Indexub(c);
}

void glIndexubv(const GLubyte* c) {
	return IGLMock::getMock()->gl_Indexubv(c);
}

void glInitNames() {
	return IGLMock::getMock()->gl_InitNames();
}

void glInterleavedArrays(GLenum format, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_InterleavedArrays(format, stride, pointer);
}

GLboolean glIsEnabled(GLenum cap) {
	return IGLMock::getMock()->gl_IsEnabled(cap);
}

GLboolean glIsList(GLuint list) {
	return IGLMock::getMock()->gl_IsList(list);
}

GLboolean glIsTexture(GLuint texture) {
	return IGLMock::getMock()->gl_IsTexture(texture);
}

void glLightModelf(GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_LightModelf(pname, param);
}

void glLightModelfv(GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_LightModelfv(pname, params);
}

void glLightModeli(GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_LightModeli(pname, param);
}

void glLightModeliv(GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_LightModeliv(pname, params);
}

void glLightf(GLenum light, GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_Lightf(light, pname, param);
}

void glLightfv(GLenum light, GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_Lightfv(light, pname, params);
}

void glLighti(GLenum light, GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_Lighti(light, pname, param);
}

void glLightiv(GLenum light, GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_Lightiv(light, pname, params);
}

void glLineStipple(GLint factor, GLushort pattern) {
	return IGLMock::getMock()->gl_LineStipple(factor, pattern);
}

void glLineWidth(GLfloat width) {
	return IGLMock::getMock()->gl_LineWidth(width);
}

void glListBase(GLuint base) {
	return IGLMock::getMock()->gl_ListBase(base);
}

void glLoadIdentity() {
	return IGLMock::getMock()->gl_LoadIdentity();
}

void glLoadMatrixd(const GLdouble* m) {
	return IGLMock::getMock()->gl_LoadMatrixd(m);
}

void glLoadMatrixf(const GLfloat* m) {
	return IGLMock::getMock()->gl_LoadMatrixf(m);
}

void glLoadName(GLuint name) {
	return IGLMock::getMock()->gl_LoadName(name);
}

void glLogicOp(GLenum opcode) {
	return IGLMock::getMock()->gl_LogicOp(opcode);
}

void glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points) {
	return IGLMock::getMock()->gl_Map1d(target, u1, u2, stride, order, points);
}

void glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points) {
	return IGLMock::getMock()->gl_Map1f(target, u1, u2, stride, order, points);
}

void glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points) {
	return IGLMock::getMock()->gl_Map2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points) {
	return IGLMock::getMock()->gl_Map2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
	return IGLMock::getMock()->gl_MapGrid1d(un, u1, u2);
}

void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
	return IGLMock::getMock()->gl_MapGrid1f(un, u1, u2);
}

void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) {
	return IGLMock::getMock()->gl_MapGrid2d(un, u1, u2, vn, v1, v2);
}

void glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
	return IGLMock::getMock()->gl_MapGrid2f(un, u1, u2, vn, v1, v2);
}

void glMaterialf(GLenum face, GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_Materialf(face, pname, param);
}

void glMaterialfv(GLenum face, GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_Materialfv(face, pname, params);
}

void glMateriali(GLenum face, GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_Materiali(face, pname, param);
}

void glMaterialiv(GLenum face, GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_Materialiv(face, pname, params);
}

void glMatrixMode(GLenum mode) {
	return IGLMock::getMock()->gl_MatrixMode(mode);
}

void glMultMatrixd(const GLdouble* m) {
	return IGLMock::getMock()->gl_MultMatrixd(m);
}

void glMultMatrixf(const GLfloat* m) {
	return IGLMock::getMock()->gl_MultMatrixf(m);
}

void glNewList(GLuint list, GLenum mode) {
	return IGLMock::getMock()->gl_NewList(list, mode);
}

void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
	return IGLMock::getMock()->gl_Normal3b(nx, ny, nz);
}

void glNormal3bv(const GLbyte* v) {
	return IGLMock::getMock()->gl_Normal3bv(v);
}

void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
	return IGLMock::getMock()->gl_Normal3d(nx, ny, nz);
}

void glNormal3dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Normal3dv(v);
}

void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz) {
	return IGLMock::getMock()->gl_Normal3f(nx, ny, nz);
}

void glNormal3fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Normal3fv(v);
}

void glNormal3i(GLint nx, GLint ny, GLint nz) {
	return IGLMock::getMock()->gl_Normal3i(nx, ny, nz);
}

void glNormal3iv(const GLint* v) {
	return IGLMock::getMock()->gl_Normal3iv(v);
}

void glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
	return IGLMock::getMock()->gl_Normal3s(nx, ny, nz);
}

void glNormal3sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Normal3sv(v);
}

void glNormalPointer(GLenum type, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_NormalPointer(type, stride, pointer);
}

void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) {
	return IGLMock::getMock()->gl_Ortho(left, right, bottom, top, zNear, zFar);
}

void glPassThrough(GLfloat token) {
	return IGLMock::getMock()->gl_PassThrough(token);
}

void glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat* values) {
	return IGLMock::getMock()->gl_PixelMapfv(map, mapsize, values);
}

void glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint* values) {
	return IGLMock::getMock()->gl_PixelMapuiv(map, mapsize, values);
}

void glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort* values) {
	return IGLMock::getMock()->gl_PixelMapusv(map, mapsize, values);
}

void glPixelStoref(GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_PixelStoref(pname, param);
}

void glPixelStorei(GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_PixelStorei(pname, param);
}

void glPixelTransferf(GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_PixelTransferf(pname, param);
}

void glPixelTransferi(GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_PixelTransferi(pname, param);
}

void glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
	return IGLMock::getMock()->gl_PixelZoom(xfactor, yfactor);
}

void glPointSize(GLfloat size) {
	return IGLMock::getMock()->gl_PointSize(size);
}

void glPolygonMode(GLenum face, GLenum mode) {
	return IGLMock::getMock()->gl_PolygonMode(face, mode);
}

void glPolygonOffset(GLfloat factor, GLfloat units) {
	return IGLMock::getMock()->gl_PolygonOffset(factor, units);
}

void glPolygonStipple(const GLubyte* mask) {
	return IGLMock::getMock()->gl_PolygonStipple(mask);
}

void glPopAttrib() {
	return IGLMock::getMock()->gl_PopAttrib();
}

void glPopClientAttrib() {
	return IGLMock::getMock()->gl_PopClientAttrib();
}

void glPopMatrix() {
	return IGLMock::getMock()->gl_PopMatrix();
}

void glPopName() {
	return IGLMock::getMock()->gl_PopName();
}

void glPrioritizeTextures(GLsizei n, const GLuint* textures, const GLclampf* priorities) {
	return IGLMock::getMock()->gl_PrioritizeTextures(n, textures, priorities);
}

void glPushAttrib(GLbitfield mask) {
	return IGLMock::getMock()->gl_PushAttrib(mask);
}

void glPushClientAttrib(GLbitfield mask) {
	return IGLMock::getMock()->gl_PushClientAttrib(mask);
}

void glPushMatrix() {
	return IGLMock::getMock()->gl_PushMatrix();
}

void glPushName(GLuint name) {
	return IGLMock::getMock()->gl_PushName(name);
}

void glRasterPos2d(GLdouble x, GLdouble y) {
	return IGLMock::getMock()->gl_RasterPos2d(x, y);
}

void glRasterPos2dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_RasterPos2dv(v);
}

void glRasterPos2f(GLfloat x, GLfloat y) {
	return IGLMock::getMock()->gl_RasterPos2f(x, y);
}

void glRasterPos2fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_RasterPos2fv(v);
}

void glRasterPos2i(GLint x, GLint y) {
	return IGLMock::getMock()->gl_RasterPos2i(x, y);
}

void glRasterPos2iv(const GLint* v) {
	return IGLMock::getMock()->gl_RasterPos2iv(v);
}

void glRasterPos2s(GLshort x, GLshort y) {
	return IGLMock::getMock()->gl_RasterPos2s(x, y);
}

void glRasterPos2sv(const GLshort* v) {
	return IGLMock::getMock()->gl_RasterPos2sv(v);
}

void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
	return IGLMock::getMock()->gl_RasterPos3d(x, y, z);
}

void glRasterPos3dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_RasterPos3dv(v);
}

void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
	return IGLMock::getMock()->gl_RasterPos3f(x, y, z);
}

void glRasterPos3fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_RasterPos3fv(v);
}

void glRasterPos3i(GLint x, GLint y, GLint z) {
	return IGLMock::getMock()->gl_RasterPos3i(x, y, z);
}

void glRasterPos3iv(const GLint* v) {
	return IGLMock::getMock()->gl_RasterPos3iv(v);
}

void glRasterPos3s(GLshort x, GLshort y, GLshort z) {
	return IGLMock::getMock()->gl_RasterPos3s(x, y, z);
}

void glRasterPos3sv(const GLshort* v) {
	return IGLMock::getMock()->gl_RasterPos3sv(v);
}

void glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	return IGLMock::getMock()->gl_RasterPos4d(x, y, z, w);
}

void glRasterPos4dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_RasterPos4dv(v);
}

void glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	return IGLMock::getMock()->gl_RasterPos4f(x, y, z, w);
}

void glRasterPos4fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_RasterPos4fv(v);
}

void glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
	return IGLMock::getMock()->gl_RasterPos4i(x, y, z, w);
}

void glRasterPos4iv(const GLint* v) {
	return IGLMock::getMock()->gl_RasterPos4iv(v);
}

void glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
	return IGLMock::getMock()->gl_RasterPos4s(x, y, z, w);
}

void glRasterPos4sv(const GLshort* v) {
	return IGLMock::getMock()->gl_RasterPos4sv(v);
}

void glReadBuffer(GLenum mode) {
	return IGLMock::getMock()->gl_ReadBuffer(mode);
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels) {
	return IGLMock::getMock()->gl_ReadPixels(x, y, width, height, format, type, pixels);
}

void glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	return IGLMock::getMock()->gl_Rectd(x1, y1, x2, y2);
}

void glRectdv(const GLdouble* v1, const GLdouble* v2) {
	return IGLMock::getMock()->gl_Rectdv(v1, v2);
}

void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	return IGLMock::getMock()->gl_Rectf(x1, y1, x2, y2);
}

void glRectfv(const GLfloat* v1, const GLfloat* v2) {
	return IGLMock::getMock()->gl_Rectfv(v1, v2);
}

void glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
	return IGLMock::getMock()->gl_Recti(x1, y1, x2, y2);
}

void glRectiv(const GLint* v1, const GLint* v2) {
	return IGLMock::getMock()->gl_Rectiv(v1, v2);
}

void glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
	return IGLMock::getMock()->gl_Rects(x1, y1, x2, y2);
}

void glRectsv(const GLshort* v1, const GLshort* v2) {
	return IGLMock::getMock()->gl_Rectsv(v1, v2);
}

GLint glRenderMode(GLenum mode) {
	return IGLMock::getMock()->gl_RenderMode(mode);
}

void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
	return IGLMock::getMock()->gl_Rotated(angle, x, y, z);
}

void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	return IGLMock::getMock()->gl_Rotatef(angle, x, y, z);
}

void glScaled(GLdouble x, GLdouble y, GLdouble z) {
	return IGLMock::getMock()->gl_Scaled(x, y, z);
}

void glScalef(GLfloat x, GLfloat y, GLfloat z) {
	return IGLMock::getMock()->gl_Scalef(x, y, z);
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
	return IGLMock::getMock()->gl_Scissor(x, y, width, height);
}

void glSelectBuffer(GLsizei size, GLuint* buffer) {
	return IGLMock::getMock()->gl_SelectBuffer(size, buffer);
}

void glShadeModel(GLenum mode) {
	return IGLMock::getMock()->gl_ShadeModel(mode);
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask) {
	return IGLMock::getMock()->gl_StencilFunc(func, ref, mask);
}

void glStencilMask(GLuint mask) {
	return IGLMock::getMock()->gl_StencilMask(mask);
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
	return IGLMock::getMock()->gl_StencilOp(fail, zfail, zpass);
}

void glTexCoord1d(GLdouble s) {
	return IGLMock::getMock()->gl_TexCoord1d(s);
}

void glTexCoord1dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_TexCoord1dv(v);
}

void glTexCoord1f(GLfloat s) {
	return IGLMock::getMock()->gl_TexCoord1f(s);
}

void glTexCoord1fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_TexCoord1fv(v);
}

void glTexCoord1i(GLint s) {
	return IGLMock::getMock()->gl_TexCoord1i(s);
}

void glTexCoord1iv(const GLint* v) {
	return IGLMock::getMock()->gl_TexCoord1iv(v);
}

void glTexCoord1s(GLshort s) {
	return IGLMock::getMock()->gl_TexCoord1s(s);
}

void glTexCoord1sv(const GLshort* v) {
	return IGLMock::getMock()->gl_TexCoord1sv(v);
}

void glTexCoord2d(GLdouble s, GLdouble t) {
	return IGLMock::getMock()->gl_TexCoord2d(s, t);
}

void glTexCoord2dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_TexCoord2dv(v);
}

void glTexCoord2f(GLfloat s, GLfloat t) {
	return IGLMock::getMock()->gl_TexCoord2f(s, t);
}

void glTexCoord2fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_TexCoord2fv(v);
}

void glTexCoord2i(GLint s, GLint t) {
	return IGLMock::getMock()->gl_TexCoord2i(s, t);
}

void glTexCoord2iv(const GLint* v) {
	return IGLMock::getMock()->gl_TexCoord2iv(v);
}

void glTexCoord2s(GLshort s, GLshort t) {
	return IGLMock::getMock()->gl_TexCoord2s(s, t);
}

void glTexCoord2sv(const GLshort* v) {
	return IGLMock::getMock()->gl_TexCoord2sv(v);
}

void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
	return IGLMock::getMock()->gl_TexCoord3d(s, t, r);
}

void glTexCoord3dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_TexCoord3dv(v);
}

void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
	return IGLMock::getMock()->gl_TexCoord3f(s, t, r);
}

void glTexCoord3fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_TexCoord3fv(v);
}

void glTexCoord3i(GLint s, GLint t, GLint r) {
	return IGLMock::getMock()->gl_TexCoord3i(s, t, r);
}

void glTexCoord3iv(const GLint* v) {
	return IGLMock::getMock()->gl_TexCoord3iv(v);
}

void glTexCoord3s(GLshort s, GLshort t, GLshort r) {
	return IGLMock::getMock()->gl_TexCoord3s(s, t, r);
}

void glTexCoord3sv(const GLshort* v) {
	return IGLMock::getMock()->gl_TexCoord3sv(v);
}

void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
	return IGLMock::getMock()->gl_TexCoord4d(s, t, r, q);
}

void glTexCoord4dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_TexCoord4dv(v);
}

void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
	return IGLMock::getMock()->gl_TexCoord4f(s, t, r, q);
}

void glTexCoord4fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_TexCoord4fv(v);
}

void glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
	return IGLMock::getMock()->gl_TexCoord4i(s, t, r, q);
}

void glTexCoord4iv(const GLint* v) {
	return IGLMock::getMock()->gl_TexCoord4iv(v);
}

void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
	return IGLMock::getMock()->gl_TexCoord4s(s, t, r, q);
}

void glTexCoord4sv(const GLshort* v) {
	return IGLMock::getMock()->gl_TexCoord4sv(v);
}

void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_TexCoordPointer(size, type, stride, pointer);
}

void glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_TexEnvf(target, pname, param);
}

void glTexEnvfv(GLenum target, GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_TexEnvfv(target, pname, params);
}

void glTexEnvi(GLenum target, GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_TexEnvi(target, pname, param);
}

void glTexEnviv(GLenum target, GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_TexEnviv(target, pname, params);
}

void glTexGend(GLenum coord, GLenum pname, GLdouble param) {
	return IGLMock::getMock()->gl_TexGend(coord, pname, param);
}

void glTexGendv(GLenum coord, GLenum pname, const GLdouble* params) {
	return IGLMock::getMock()->gl_TexGendv(coord, pname, params);
}

void glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_TexGenf(coord, pname, param);
}

void glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_TexGenfv(coord, pname, params);
}

void glTexGeni(GLenum coord, GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_TexGeni(coord, pname, param);
}

void glTexGeniv(GLenum coord, GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_TexGeniv(coord, pname, params);
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) {
	return IGLMock::getMock()->gl_TexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
	return IGLMock::getMock()->gl_TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
	return IGLMock::getMock()->gl_TexParameterf(target, pname, param);
}

void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params) {
	return IGLMock::getMock()->gl_TexParameterfv(target, pname, params);
}

void glTexParameteri(GLenum target, GLenum pname, GLint param) {
	return IGLMock::getMock()->gl_TexParameteri(target, pname, param);
}

void glTexParameteriv(GLenum target, GLenum pname, const GLint* params) {
	return IGLMock::getMock()->gl_TexParameteriv(target, pname, params);
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) {
	return IGLMock::getMock()->gl_TexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
	return IGLMock::getMock()->gl_TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void glTranslated(GLdouble x, GLdouble y, GLdouble z) {
	return IGLMock::getMock()->gl_Translated(x, y, z);
}

void glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
	return IGLMock::getMock()->gl_Translatef(x, y, z);
}

void glVertex2d(GLdouble x, GLdouble y) {
	return IGLMock::getMock()->gl_Vertex2d(x, y);
}

void glVertex2dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Vertex2dv(v);
}

void glVertex2f(GLfloat x, GLfloat y) {
	return IGLMock::getMock()->gl_Vertex2f(x, y);
}

void glVertex2fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Vertex2fv(v);
}

void glVertex2i(GLint x, GLint y) {
	return IGLMock::getMock()->gl_Vertex2i(x, y);
}

void glVertex2iv(const GLint* v) {
	return IGLMock::getMock()->gl_Vertex2iv(v);
}

void glVertex2s(GLshort x, GLshort y) {
	return IGLMock::getMock()->gl_Vertex2s(x, y);
}

void glVertex2sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Vertex2sv(v);
}

void glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
	return IGLMock::getMock()->gl_Vertex3d(x, y, z);
}

void glVertex3dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Vertex3dv(v);
}

void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
	return IGLMock::getMock()->gl_Vertex3f(x, y, z);
}

void glVertex3fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Vertex3fv(v);
}

void glVertex3i(GLint x, GLint y, GLint z) {
	return IGLMock::getMock()->gl_Vertex3i(x, y, z);
}

void glVertex3iv(const GLint* v) {
	return IGLMock::getMock()->gl_Vertex3iv(v);
}

void glVertex3s(GLshort x, GLshort y, GLshort z) {
	return IGLMock::getMock()->gl_Vertex3s(x, y, z);
}

void glVertex3sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Vertex3sv(v);
}

void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
	return IGLMock::getMock()->gl_Vertex4d(x, y, z, w);
}

void glVertex4dv(const GLdouble* v) {
	return IGLMock::getMock()->gl_Vertex4dv(v);
}

void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	return IGLMock::getMock()->gl_Vertex4f(x, y, z, w);
}

void glVertex4fv(const GLfloat* v) {
	return IGLMock::getMock()->gl_Vertex4fv(v);
}

void glVertex4i(GLint x, GLint y, GLint z, GLint w) {
	return IGLMock::getMock()->gl_Vertex4i(x, y, z, w);
}

void glVertex4iv(const GLint* v) {
	return IGLMock::getMock()->gl_Vertex4iv(v);
}

void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
	return IGLMock::getMock()->gl_Vertex4s(x, y, z, w);
}

void glVertex4sv(const GLshort* v) {
	return IGLMock::getMock()->gl_Vertex4sv(v);
}

void glVertexPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
	return IGLMock::getMock()->gl_VertexPointer(size, type, stride, pointer);
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
	return IGLMock::getMock()->gl_Viewport(x, y, width, height);
}