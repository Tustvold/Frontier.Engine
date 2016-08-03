#include "GL/glew.h"

GLboolean glewExperimental = GL_FALSE;

void GLAPIENTRY mockgl_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{

}
PFNGLCOPYTEXSUBIMAGE3DPROC __glewCopyTexSubImage3D = mockgl_CopyTexSubImage3D;

void GLAPIENTRY mockgl_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{

}
PFNGLDRAWRANGEELEMENTSPROC __glewDrawRangeElements = mockgl_DrawRangeElements;

void GLAPIENTRY mockgl_TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{

}
PFNGLTEXIMAGE3DPROC __glewTexImage3D = mockgl_TexImage3D;

void GLAPIENTRY mockgl_ActiveTexture(GLenum texture)
{

}
PFNGLACTIVETEXTUREPROC __glewActiveTexture = mockgl_ActiveTexture;

void GLAPIENTRY mockgl_ClientActiveTexture(GLenum texture)
{

}
PFNGLCLIENTACTIVETEXTUREPROC __glewClientActiveTexture = mockgl_ClientActiveTexture;

void GLAPIENTRY mockgl_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{

}
PFNGLCOMPRESSEDTEXIMAGE1DPROC __glewCompressedTexImage1D = mockgl_CompressedTexImage1D;

void GLAPIENTRY mockgl_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{

}
PFNGLCOMPRESSEDTEXIMAGE2DPROC __glewCompressedTexImage2D = mockgl_CompressedTexImage2D;

void GLAPIENTRY mockgl_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{

}
PFNGLCOMPRESSEDTEXIMAGE3DPROC __glewCompressedTexImage3D = mockgl_CompressedTexImage3D;

void GLAPIENTRY mockgl_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{

}
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __glewCompressedTexSubImage1D = mockgl_CompressedTexSubImage1D;

void GLAPIENTRY mockgl_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{

}
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __glewCompressedTexSubImage2D = mockgl_CompressedTexSubImage2D;

void GLAPIENTRY mockgl_GetCompressedTexImage(GLenum target, GLint lod, void * img)
{

}
PFNGLGETCOMPRESSEDTEXIMAGEPROC __glewGetCompressedTexImage = mockgl_GetCompressedTexImage;

void GLAPIENTRY mockgl_LoadTransposeMatrixd(const GLdouble * m)
{

}
PFNGLLOADTRANSPOSEMATRIXDPROC __glewLoadTransposeMatrixd = mockgl_LoadTransposeMatrixd;

void GLAPIENTRY mockgl_LoadTransposeMatrixf(const GLfloat * m)
{

}
PFNGLLOADTRANSPOSEMATRIXFPROC __glewLoadTransposeMatrixf = mockgl_LoadTransposeMatrixf;

void GLAPIENTRY mockgl_MultTransposeMatrixd(const GLdouble * m)
{

}
PFNGLMULTTRANSPOSEMATRIXDPROC __glewMultTransposeMatrixd = mockgl_MultTransposeMatrixd;

void GLAPIENTRY mockgl_MultTransposeMatrixf(const GLfloat * m)
{

}
PFNGLMULTTRANSPOSEMATRIXFPROC __glewMultTransposeMatrixf = mockgl_MultTransposeMatrixf;

void GLAPIENTRY mockgl_MultiTexCoord1d(GLenum target, GLdouble s)
{

}
PFNGLMULTITEXCOORD1DPROC __glewMultiTexCoord1d = mockgl_MultiTexCoord1d;

void GLAPIENTRY mockgl_MultiTexCoord1dv(GLenum target, const GLdouble * v)
{

}
PFNGLMULTITEXCOORD1DVPROC __glewMultiTexCoord1dv = mockgl_MultiTexCoord1dv;

void GLAPIENTRY mockgl_MultiTexCoord1f(GLenum target, GLfloat s)
{

}
PFNGLMULTITEXCOORD1FPROC __glewMultiTexCoord1f = mockgl_MultiTexCoord1f;

void GLAPIENTRY mockgl_MultiTexCoord1fv(GLenum target, const GLfloat * v)
{

}
PFNGLMULTITEXCOORD1FVPROC __glewMultiTexCoord1fv = mockgl_MultiTexCoord1fv;

void GLAPIENTRY mockgl_MultiTexCoord1i(GLenum target, GLint s)
{

}
PFNGLMULTITEXCOORD1IPROC __glewMultiTexCoord1i = mockgl_MultiTexCoord1i;

void GLAPIENTRY mockgl_MultiTexCoord1iv(GLenum target, const GLint * v)
{

}
PFNGLMULTITEXCOORD1IVPROC __glewMultiTexCoord1iv = mockgl_MultiTexCoord1iv;

void GLAPIENTRY mockgl_MultiTexCoord1s(GLenum target, GLshort s)
{

}
PFNGLMULTITEXCOORD1SPROC __glewMultiTexCoord1s = mockgl_MultiTexCoord1s;

void GLAPIENTRY mockgl_MultiTexCoord1sv(GLenum target, const GLshort * v)
{

}
PFNGLMULTITEXCOORD1SVPROC __glewMultiTexCoord1sv = mockgl_MultiTexCoord1sv;

void GLAPIENTRY mockgl_MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)
{

}
PFNGLMULTITEXCOORD2DPROC __glewMultiTexCoord2d = mockgl_MultiTexCoord2d;

void GLAPIENTRY mockgl_MultiTexCoord2dv(GLenum target, const GLdouble * v)
{

}
PFNGLMULTITEXCOORD2DVPROC __glewMultiTexCoord2dv = mockgl_MultiTexCoord2dv;

void GLAPIENTRY mockgl_MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)
{

}
PFNGLMULTITEXCOORD2FPROC __glewMultiTexCoord2f = mockgl_MultiTexCoord2f;

void GLAPIENTRY mockgl_MultiTexCoord2fv(GLenum target, const GLfloat * v)
{

}
PFNGLMULTITEXCOORD2FVPROC __glewMultiTexCoord2fv = mockgl_MultiTexCoord2fv;

void GLAPIENTRY mockgl_MultiTexCoord2i(GLenum target, GLint s, GLint t)
{

}
PFNGLMULTITEXCOORD2IPROC __glewMultiTexCoord2i = mockgl_MultiTexCoord2i;

void GLAPIENTRY mockgl_MultiTexCoord2iv(GLenum target, const GLint * v)
{

}
PFNGLMULTITEXCOORD2IVPROC __glewMultiTexCoord2iv = mockgl_MultiTexCoord2iv;

void GLAPIENTRY mockgl_MultiTexCoord2s(GLenum target, GLshort s, GLshort t)
{

}
PFNGLMULTITEXCOORD2SPROC __glewMultiTexCoord2s = mockgl_MultiTexCoord2s;

void GLAPIENTRY mockgl_MultiTexCoord2sv(GLenum target, const GLshort * v)
{

}
PFNGLMULTITEXCOORD2SVPROC __glewMultiTexCoord2sv = mockgl_MultiTexCoord2sv;

void GLAPIENTRY mockgl_MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{

}
PFNGLMULTITEXCOORD3DPROC __glewMultiTexCoord3d = mockgl_MultiTexCoord3d;

void GLAPIENTRY mockgl_MultiTexCoord3dv(GLenum target, const GLdouble * v)
{

}
PFNGLMULTITEXCOORD3DVPROC __glewMultiTexCoord3dv = mockgl_MultiTexCoord3dv;

void GLAPIENTRY mockgl_MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{

}
PFNGLMULTITEXCOORD3FPROC __glewMultiTexCoord3f = mockgl_MultiTexCoord3f;

void GLAPIENTRY mockgl_MultiTexCoord3fv(GLenum target, const GLfloat * v)
{

}
PFNGLMULTITEXCOORD3FVPROC __glewMultiTexCoord3fv = mockgl_MultiTexCoord3fv;

void GLAPIENTRY mockgl_MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)
{

}
PFNGLMULTITEXCOORD3IPROC __glewMultiTexCoord3i = mockgl_MultiTexCoord3i;

void GLAPIENTRY mockgl_MultiTexCoord3iv(GLenum target, const GLint * v)
{

}
PFNGLMULTITEXCOORD3IVPROC __glewMultiTexCoord3iv = mockgl_MultiTexCoord3iv;

void GLAPIENTRY mockgl_MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)
{

}
PFNGLMULTITEXCOORD3SPROC __glewMultiTexCoord3s = mockgl_MultiTexCoord3s;

void GLAPIENTRY mockgl_MultiTexCoord3sv(GLenum target, const GLshort * v)
{

}
PFNGLMULTITEXCOORD3SVPROC __glewMultiTexCoord3sv = mockgl_MultiTexCoord3sv;

void GLAPIENTRY mockgl_MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{

}
PFNGLMULTITEXCOORD4DPROC __glewMultiTexCoord4d = mockgl_MultiTexCoord4d;

void GLAPIENTRY mockgl_MultiTexCoord4dv(GLenum target, const GLdouble * v)
{

}
PFNGLMULTITEXCOORD4DVPROC __glewMultiTexCoord4dv = mockgl_MultiTexCoord4dv;

void GLAPIENTRY mockgl_MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{

}
PFNGLMULTITEXCOORD4FPROC __glewMultiTexCoord4f = mockgl_MultiTexCoord4f;

void GLAPIENTRY mockgl_MultiTexCoord4fv(GLenum target, const GLfloat * v)
{

}
PFNGLMULTITEXCOORD4FVPROC __glewMultiTexCoord4fv = mockgl_MultiTexCoord4fv;

void GLAPIENTRY mockgl_MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)
{

}
PFNGLMULTITEXCOORD4IPROC __glewMultiTexCoord4i = mockgl_MultiTexCoord4i;

void GLAPIENTRY mockgl_MultiTexCoord4iv(GLenum target, const GLint * v)
{

}
PFNGLMULTITEXCOORD4IVPROC __glewMultiTexCoord4iv = mockgl_MultiTexCoord4iv;

void GLAPIENTRY mockgl_MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{

}
PFNGLMULTITEXCOORD4SPROC __glewMultiTexCoord4s = mockgl_MultiTexCoord4s;

void GLAPIENTRY mockgl_MultiTexCoord4sv(GLenum target, const GLshort * v)
{

}
PFNGLMULTITEXCOORD4SVPROC __glewMultiTexCoord4sv = mockgl_MultiTexCoord4sv;

void GLAPIENTRY mockgl_SampleCoverage(GLclampf value, GLboolean invert)
{

}
PFNGLSAMPLECOVERAGEPROC __glewSampleCoverage = mockgl_SampleCoverage;

void GLAPIENTRY mockgl_BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{

}
PFNGLBLENDCOLORPROC __glewBlendColor = mockgl_BlendColor;

void GLAPIENTRY mockgl_BlendEquation(GLenum mode)
{

}
PFNGLBLENDEQUATIONPROC __glewBlendEquation = mockgl_BlendEquation;

void GLAPIENTRY mockgl_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{

}
PFNGLBLENDFUNCSEPARATEPROC __glewBlendFuncSeparate = mockgl_BlendFuncSeparate;

void GLAPIENTRY mockgl_FogCoordPointer(GLenum type, GLsizei stride, const void * pointer)
{

}
PFNGLFOGCOORDPOINTERPROC __glewFogCoordPointer = mockgl_FogCoordPointer;

void GLAPIENTRY mockgl_FogCoordd(GLdouble coord)
{

}
PFNGLFOGCOORDDPROC __glewFogCoordd = mockgl_FogCoordd;

void GLAPIENTRY mockgl_FogCoorddv(const GLdouble * coord)
{

}
PFNGLFOGCOORDDVPROC __glewFogCoorddv = mockgl_FogCoorddv;

void GLAPIENTRY mockgl_FogCoordf(GLfloat coord)
{

}
PFNGLFOGCOORDFPROC __glewFogCoordf = mockgl_FogCoordf;

void GLAPIENTRY mockgl_FogCoordfv(const GLfloat * coord)
{

}
PFNGLFOGCOORDFVPROC __glewFogCoordfv = mockgl_FogCoordfv;

void GLAPIENTRY mockgl_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{

}
PFNGLMULTIDRAWARRAYSPROC __glewMultiDrawArrays = mockgl_MultiDrawArrays;

void GLAPIENTRY mockgl_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const * indices, GLsizei drawcount)
{

}
PFNGLMULTIDRAWELEMENTSPROC __glewMultiDrawElements = mockgl_MultiDrawElements;

void GLAPIENTRY mockgl_PointParameterf(GLenum pname, GLfloat param)
{

}
PFNGLPOINTPARAMETERFPROC __glewPointParameterf = mockgl_PointParameterf;

void GLAPIENTRY mockgl_PointParameterfv(GLenum pname, const GLfloat * params)
{

}
PFNGLPOINTPARAMETERFVPROC __glewPointParameterfv = mockgl_PointParameterfv;

void GLAPIENTRY mockgl_PointParameteri(GLenum pname, GLint param)
{

}
PFNGLPOINTPARAMETERIPROC __glewPointParameteri = mockgl_PointParameteri;

void GLAPIENTRY mockgl_PointParameteriv(GLenum pname, const GLint * params)
{

}
PFNGLPOINTPARAMETERIVPROC __glewPointParameteriv = mockgl_PointParameteriv;

void GLAPIENTRY mockgl_SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue)
{

}
PFNGLSECONDARYCOLOR3BPROC __glewSecondaryColor3b = mockgl_SecondaryColor3b;

void GLAPIENTRY mockgl_SecondaryColor3bv(const GLbyte * v)
{

}
PFNGLSECONDARYCOLOR3BVPROC __glewSecondaryColor3bv = mockgl_SecondaryColor3bv;

void GLAPIENTRY mockgl_SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue)
{

}
PFNGLSECONDARYCOLOR3DPROC __glewSecondaryColor3d = mockgl_SecondaryColor3d;

void GLAPIENTRY mockgl_SecondaryColor3dv(const GLdouble * v)
{

}
PFNGLSECONDARYCOLOR3DVPROC __glewSecondaryColor3dv = mockgl_SecondaryColor3dv;

void GLAPIENTRY mockgl_SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue)
{

}
PFNGLSECONDARYCOLOR3FPROC __glewSecondaryColor3f = mockgl_SecondaryColor3f;

void GLAPIENTRY mockgl_SecondaryColor3fv(const GLfloat * v)
{

}
PFNGLSECONDARYCOLOR3FVPROC __glewSecondaryColor3fv = mockgl_SecondaryColor3fv;

void GLAPIENTRY mockgl_SecondaryColor3i(GLint red, GLint green, GLint blue)
{

}
PFNGLSECONDARYCOLOR3IPROC __glewSecondaryColor3i = mockgl_SecondaryColor3i;

void GLAPIENTRY mockgl_SecondaryColor3iv(const GLint * v)
{

}
PFNGLSECONDARYCOLOR3IVPROC __glewSecondaryColor3iv = mockgl_SecondaryColor3iv;

void GLAPIENTRY mockgl_SecondaryColor3s(GLshort red, GLshort green, GLshort blue)
{

}
PFNGLSECONDARYCOLOR3SPROC __glewSecondaryColor3s = mockgl_SecondaryColor3s;

void GLAPIENTRY mockgl_SecondaryColor3sv(const GLshort * v)
{

}
PFNGLSECONDARYCOLOR3SVPROC __glewSecondaryColor3sv = mockgl_SecondaryColor3sv;

void GLAPIENTRY mockgl_SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{

}
PFNGLSECONDARYCOLOR3UBPROC __glewSecondaryColor3ub = mockgl_SecondaryColor3ub;

void GLAPIENTRY mockgl_SecondaryColor3ubv(const GLubyte * v)
{

}
PFNGLSECONDARYCOLOR3UBVPROC __glewSecondaryColor3ubv = mockgl_SecondaryColor3ubv;

void GLAPIENTRY mockgl_SecondaryColor3ui(GLuint red, GLuint green, GLuint blue)
{

}
PFNGLSECONDARYCOLOR3UIPROC __glewSecondaryColor3ui = mockgl_SecondaryColor3ui;

void GLAPIENTRY mockgl_SecondaryColor3uiv(const GLuint * v)
{

}
PFNGLSECONDARYCOLOR3UIVPROC __glewSecondaryColor3uiv = mockgl_SecondaryColor3uiv;

void GLAPIENTRY mockgl_SecondaryColor3us(GLushort red, GLushort green, GLushort blue)
{

}
PFNGLSECONDARYCOLOR3USPROC __glewSecondaryColor3us = mockgl_SecondaryColor3us;

void GLAPIENTRY mockgl_SecondaryColor3usv(const GLushort * v)
{

}
PFNGLSECONDARYCOLOR3USVPROC __glewSecondaryColor3usv = mockgl_SecondaryColor3usv;

void GLAPIENTRY mockgl_SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{

}
PFNGLSECONDARYCOLORPOINTERPROC __glewSecondaryColorPointer = mockgl_SecondaryColorPointer;

void GLAPIENTRY mockgl_WindowPos2d(GLdouble x, GLdouble y)
{

}
PFNGLWINDOWPOS2DPROC __glewWindowPos2d = mockgl_WindowPos2d;

void GLAPIENTRY mockgl_WindowPos2dv(const GLdouble * p)
{

}
PFNGLWINDOWPOS2DVPROC __glewWindowPos2dv = mockgl_WindowPos2dv;

void GLAPIENTRY mockgl_WindowPos2f(GLfloat x, GLfloat y)
{

}
PFNGLWINDOWPOS2FPROC __glewWindowPos2f = mockgl_WindowPos2f;

void GLAPIENTRY mockgl_WindowPos2fv(const GLfloat * p)
{

}
PFNGLWINDOWPOS2FVPROC __glewWindowPos2fv = mockgl_WindowPos2fv;

void GLAPIENTRY mockgl_WindowPos2i(GLint x, GLint y)
{

}
PFNGLWINDOWPOS2IPROC __glewWindowPos2i = mockgl_WindowPos2i;

void GLAPIENTRY mockgl_WindowPos2iv(const GLint * p)
{

}
PFNGLWINDOWPOS2IVPROC __glewWindowPos2iv = mockgl_WindowPos2iv;

void GLAPIENTRY mockgl_WindowPos2s(GLshort x, GLshort y)
{

}
PFNGLWINDOWPOS2SPROC __glewWindowPos2s = mockgl_WindowPos2s;

void GLAPIENTRY mockgl_WindowPos2sv(const GLshort * p)
{

}
PFNGLWINDOWPOS2SVPROC __glewWindowPos2sv = mockgl_WindowPos2sv;

void GLAPIENTRY mockgl_WindowPos3d(GLdouble x, GLdouble y, GLdouble z)
{

}
PFNGLWINDOWPOS3DPROC __glewWindowPos3d = mockgl_WindowPos3d;

void GLAPIENTRY mockgl_WindowPos3dv(const GLdouble * p)
{

}
PFNGLWINDOWPOS3DVPROC __glewWindowPos3dv = mockgl_WindowPos3dv;

void GLAPIENTRY mockgl_WindowPos3f(GLfloat x, GLfloat y, GLfloat z)
{

}
PFNGLWINDOWPOS3FPROC __glewWindowPos3f = mockgl_WindowPos3f;

void GLAPIENTRY mockgl_WindowPos3fv(const GLfloat * p)
{

}
PFNGLWINDOWPOS3FVPROC __glewWindowPos3fv = mockgl_WindowPos3fv;

void GLAPIENTRY mockgl_WindowPos3i(GLint x, GLint y, GLint z)
{

}
PFNGLWINDOWPOS3IPROC __glewWindowPos3i = mockgl_WindowPos3i;

void GLAPIENTRY mockgl_WindowPos3iv(const GLint * p)
{

}
PFNGLWINDOWPOS3IVPROC __glewWindowPos3iv = mockgl_WindowPos3iv;

void GLAPIENTRY mockgl_WindowPos3s(GLshort x, GLshort y, GLshort z)
{

}
PFNGLWINDOWPOS3SPROC __glewWindowPos3s = mockgl_WindowPos3s;

void GLAPIENTRY mockgl_WindowPos3sv(const GLshort * p)
{

}
PFNGLWINDOWPOS3SVPROC __glewWindowPos3sv = mockgl_WindowPos3sv;

void GLAPIENTRY mockgl_BeginQuery(GLenum target, GLuint id)
{

}
PFNGLBEGINQUERYPROC __glewBeginQuery = mockgl_BeginQuery;

void GLAPIENTRY mockgl_BindBuffer(GLenum target, GLuint buffer)
{

}
PFNGLBINDBUFFERPROC __glewBindBuffer = mockgl_BindBuffer;

void GLAPIENTRY mockgl_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{

}
PFNGLBUFFERDATAPROC __glewBufferData = mockgl_BufferData;

void GLAPIENTRY mockgl_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{

}
PFNGLBUFFERSUBDATAPROC __glewBufferSubData = mockgl_BufferSubData;

void GLAPIENTRY mockgl_DeleteBuffers(GLsizei n, const GLuint * buffers)
{

}
PFNGLDELETEBUFFERSPROC __glewDeleteBuffers = mockgl_DeleteBuffers;

void GLAPIENTRY mockgl_DeleteQueries(GLsizei n, const GLuint * ids)
{

}
PFNGLDELETEQUERIESPROC __glewDeleteQueries = mockgl_DeleteQueries;

void GLAPIENTRY mockgl_EndQuery(GLenum target)
{

}
PFNGLENDQUERYPROC __glewEndQuery = mockgl_EndQuery;

void GLAPIENTRY mockgl_GenBuffers(GLsizei n, GLuint * buffers)
{

}
PFNGLGENBUFFERSPROC __glewGenBuffers = mockgl_GenBuffers;

void GLAPIENTRY mockgl_GenQueries(GLsizei n, GLuint * ids)
{

}
PFNGLGENQUERIESPROC __glewGenQueries = mockgl_GenQueries;

void GLAPIENTRY mockgl_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{

}
PFNGLGETBUFFERPARAMETERIVPROC __glewGetBufferParameteriv = mockgl_GetBufferParameteriv;

void GLAPIENTRY mockgl_GetBufferPointerv(GLenum target, GLenum pname, void ** params)
{

}
PFNGLGETBUFFERPOINTERVPROC __glewGetBufferPointerv = mockgl_GetBufferPointerv;

void GLAPIENTRY mockgl_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{

}
PFNGLGETBUFFERSUBDATAPROC __glewGetBufferSubData = mockgl_GetBufferSubData;

void GLAPIENTRY mockgl_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{

}
PFNGLGETQUERYOBJECTIVPROC __glewGetQueryObjectiv = mockgl_GetQueryObjectiv;

void GLAPIENTRY mockgl_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{

}
PFNGLGETQUERYOBJECTUIVPROC __glewGetQueryObjectuiv = mockgl_GetQueryObjectuiv;

void GLAPIENTRY mockgl_GetQueryiv(GLenum target, GLenum pname, GLint * params)
{

}
PFNGLGETQUERYIVPROC __glewGetQueryiv = mockgl_GetQueryiv;

unsigned char GLAPIENTRY mockgl_IsBuffer(GLuint buffer)
{
    return 0;

}
PFNGLISBUFFERPROC __glewIsBuffer = mockgl_IsBuffer;

unsigned char GLAPIENTRY mockgl_IsQuery(GLuint id)
{
    return 0;

}
PFNGLISQUERYPROC __glewIsQuery = mockgl_IsQuery;

void* GLAPIENTRY mockgl_MapBuffer(GLenum target, GLenum access)
{
    return 0;

}
PFNGLMAPBUFFERPROC __glewMapBuffer = mockgl_MapBuffer;

unsigned char GLAPIENTRY mockgl_UnmapBuffer(GLenum target)
{
    return 0;

}
PFNGLUNMAPBUFFERPROC __glewUnmapBuffer = mockgl_UnmapBuffer;

void GLAPIENTRY mockgl_AttachShader(GLuint program, GLuint shader)
{

}
PFNGLATTACHSHADERPROC __glewAttachShader = mockgl_AttachShader;

void GLAPIENTRY mockgl_BindAttribLocation(GLuint program, GLuint index, const GLchar * name)
{

}
PFNGLBINDATTRIBLOCATIONPROC __glewBindAttribLocation = mockgl_BindAttribLocation;

void GLAPIENTRY mockgl_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{

}
PFNGLBLENDEQUATIONSEPARATEPROC __glewBlendEquationSeparate = mockgl_BlendEquationSeparate;

void GLAPIENTRY mockgl_CompileShader(GLuint shader)
{

}
PFNGLCOMPILESHADERPROC __glewCompileShader = mockgl_CompileShader;

unsigned int GLAPIENTRY mockgl_CreateProgram()
{
    return 0;
}
PFNGLCREATEPROGRAMPROC __glewCreateProgram = mockgl_CreateProgram;

unsigned int GLAPIENTRY mockgl_CreateShader(GLenum type)
{
    return 0;
}
PFNGLCREATESHADERPROC __glewCreateShader = mockgl_CreateShader;

void GLAPIENTRY mockgl_DeleteProgram(GLuint program)
{

}
PFNGLDELETEPROGRAMPROC __glewDeleteProgram = mockgl_DeleteProgram;

void GLAPIENTRY mockgl_DeleteShader(GLuint shader)
{

}
PFNGLDELETESHADERPROC __glewDeleteShader = mockgl_DeleteShader;

void GLAPIENTRY mockgl_DetachShader(GLuint program, GLuint shader)
{

}
PFNGLDETACHSHADERPROC __glewDetachShader = mockgl_DetachShader;

void GLAPIENTRY mockgl_DisableVertexAttribArray(GLuint index)
{

}
PFNGLDISABLEVERTEXATTRIBARRAYPROC __glewDisableVertexAttribArray = mockgl_DisableVertexAttribArray;

void GLAPIENTRY mockgl_DrawBuffers(GLsizei n, const GLenum * bufs)
{

}
PFNGLDRAWBUFFERSPROC __glewDrawBuffers = mockgl_DrawBuffers;

void GLAPIENTRY mockgl_EnableVertexAttribArray(GLuint index)
{

}
PFNGLENABLEVERTEXATTRIBARRAYPROC __glewEnableVertexAttribArray = mockgl_EnableVertexAttribArray;

void GLAPIENTRY mockgl_GetActiveAttrib(GLuint program, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{

}
PFNGLGETACTIVEATTRIBPROC __glewGetActiveAttrib = mockgl_GetActiveAttrib;

void GLAPIENTRY mockgl_GetActiveUniform(GLuint program, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{

}
PFNGLGETACTIVEUNIFORMPROC __glewGetActiveUniform = mockgl_GetActiveUniform;

void GLAPIENTRY mockgl_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{

}
PFNGLGETATTACHEDSHADERSPROC __glewGetAttachedShaders = mockgl_GetAttachedShaders;

int GLAPIENTRY mockgl_GetAttribLocation(GLuint program, const GLchar * name)
{
    return 0;
}
PFNGLGETATTRIBLOCATIONPROC __glewGetAttribLocation = mockgl_GetAttribLocation;

