#include "glewmock.hpp"


GlewMock::GlewMock() {
	
}

GlewMock::~GlewMock() {

}

GlewMock* GlewMock::getMock() {
	return (GlewMock*)GLMock::getMock();
}

GLboolean glewExperimental = GL_FALSE;

void GLAPIENTRY mockgl_CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return GlewMock::getMock()->gl_CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}
PFNGLCOPYTEXSUBIMAGE3DPROC __glewCopyTexSubImage3D = mockgl_CopyTexSubImage3D;

void GLAPIENTRY mockgl_DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
    return GlewMock::getMock()->gl_DrawRangeElements(mode, start, end, count, type, indices);
}
PFNGLDRAWRANGEELEMENTSPROC __glewDrawRangeElements = mockgl_DrawRangeElements;

void GLAPIENTRY mockgl_TexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return GlewMock::getMock()->gl_TexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels);
}
PFNGLTEXIMAGE3DPROC __glewTexImage3D = mockgl_TexImage3D;

void GLAPIENTRY mockgl_ActiveTexture(GLenum texture)
{
    return GlewMock::getMock()->gl_ActiveTexture(texture);
}
PFNGLACTIVETEXTUREPROC __glewActiveTexture = mockgl_ActiveTexture;

void GLAPIENTRY mockgl_ClientActiveTexture(GLenum texture)
{
    return GlewMock::getMock()->gl_ClientActiveTexture(texture);
}
PFNGLCLIENTACTIVETEXTUREPROC __glewClientActiveTexture = mockgl_ClientActiveTexture;

void GLAPIENTRY mockgl_CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
    return GlewMock::getMock()->gl_CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE1DPROC __glewCompressedTexImage1D = mockgl_CompressedTexImage1D;

void GLAPIENTRY mockgl_CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
    return GlewMock::getMock()->gl_CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE2DPROC __glewCompressedTexImage2D = mockgl_CompressedTexImage2D;

void GLAPIENTRY mockgl_CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
    return GlewMock::getMock()->gl_CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}
PFNGLCOMPRESSEDTEXIMAGE3DPROC __glewCompressedTexImage3D = mockgl_CompressedTexImage3D;

void GLAPIENTRY mockgl_CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
    return GlewMock::getMock()->gl_CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC __glewCompressedTexSubImage1D = mockgl_CompressedTexSubImage1D;

void GLAPIENTRY mockgl_CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
    return GlewMock::getMock()->gl_CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC __glewCompressedTexSubImage2D = mockgl_CompressedTexSubImage2D;

void GLAPIENTRY mockgl_GetCompressedTexImage(GLenum target, GLint lod, void * img)
{
    return GlewMock::getMock()->gl_GetCompressedTexImage(target, lod, img);
}
PFNGLGETCOMPRESSEDTEXIMAGEPROC __glewGetCompressedTexImage = mockgl_GetCompressedTexImage;

void GLAPIENTRY mockgl_LoadTransposeMatrixd(const GLdouble * m)
{
    return GlewMock::getMock()->gl_LoadTransposeMatrixd(m);
}
PFNGLLOADTRANSPOSEMATRIXDPROC __glewLoadTransposeMatrixd = mockgl_LoadTransposeMatrixd;

void GLAPIENTRY mockgl_LoadTransposeMatrixf(const GLfloat * m)
{
    return GlewMock::getMock()->gl_LoadTransposeMatrixf(m);
}
PFNGLLOADTRANSPOSEMATRIXFPROC __glewLoadTransposeMatrixf = mockgl_LoadTransposeMatrixf;

void GLAPIENTRY mockgl_MultTransposeMatrixd(const GLdouble * m)
{
    return GlewMock::getMock()->gl_MultTransposeMatrixd(m);
}
PFNGLMULTTRANSPOSEMATRIXDPROC __glewMultTransposeMatrixd = mockgl_MultTransposeMatrixd;

void GLAPIENTRY mockgl_MultTransposeMatrixf(const GLfloat * m)
{
    return GlewMock::getMock()->gl_MultTransposeMatrixf(m);
}
PFNGLMULTTRANSPOSEMATRIXFPROC __glewMultTransposeMatrixf = mockgl_MultTransposeMatrixf;

void GLAPIENTRY mockgl_MultiTexCoord1d(GLenum target, GLdouble s)
{
    return GlewMock::getMock()->gl_MultiTexCoord1d(target, s);
}
PFNGLMULTITEXCOORD1DPROC __glewMultiTexCoord1d = mockgl_MultiTexCoord1d;

void GLAPIENTRY mockgl_MultiTexCoord1dv(GLenum target, const GLdouble * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord1dv(target, v);
}
PFNGLMULTITEXCOORD1DVPROC __glewMultiTexCoord1dv = mockgl_MultiTexCoord1dv;

void GLAPIENTRY mockgl_MultiTexCoord1f(GLenum target, GLfloat s)
{
    return GlewMock::getMock()->gl_MultiTexCoord1f(target, s);
}
PFNGLMULTITEXCOORD1FPROC __glewMultiTexCoord1f = mockgl_MultiTexCoord1f;

void GLAPIENTRY mockgl_MultiTexCoord1fv(GLenum target, const GLfloat * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord1fv(target, v);
}
PFNGLMULTITEXCOORD1FVPROC __glewMultiTexCoord1fv = mockgl_MultiTexCoord1fv;

void GLAPIENTRY mockgl_MultiTexCoord1i(GLenum target, GLint s)
{
    return GlewMock::getMock()->gl_MultiTexCoord1i(target, s);
}
PFNGLMULTITEXCOORD1IPROC __glewMultiTexCoord1i = mockgl_MultiTexCoord1i;

void GLAPIENTRY mockgl_MultiTexCoord1iv(GLenum target, const GLint * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord1iv(target, v);
}
PFNGLMULTITEXCOORD1IVPROC __glewMultiTexCoord1iv = mockgl_MultiTexCoord1iv;

void GLAPIENTRY mockgl_MultiTexCoord1s(GLenum target, GLshort s)
{
    return GlewMock::getMock()->gl_MultiTexCoord1s(target, s);
}
PFNGLMULTITEXCOORD1SPROC __glewMultiTexCoord1s = mockgl_MultiTexCoord1s;

void GLAPIENTRY mockgl_MultiTexCoord1sv(GLenum target, const GLshort * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord1sv(target, v);
}
PFNGLMULTITEXCOORD1SVPROC __glewMultiTexCoord1sv = mockgl_MultiTexCoord1sv;

void GLAPIENTRY mockgl_MultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)
{
    return GlewMock::getMock()->gl_MultiTexCoord2d(target, s, t);
}
PFNGLMULTITEXCOORD2DPROC __glewMultiTexCoord2d = mockgl_MultiTexCoord2d;

void GLAPIENTRY mockgl_MultiTexCoord2dv(GLenum target, const GLdouble * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord2dv(target, v);
}
PFNGLMULTITEXCOORD2DVPROC __glewMultiTexCoord2dv = mockgl_MultiTexCoord2dv;

void GLAPIENTRY mockgl_MultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)
{
    return GlewMock::getMock()->gl_MultiTexCoord2f(target, s, t);
}
PFNGLMULTITEXCOORD2FPROC __glewMultiTexCoord2f = mockgl_MultiTexCoord2f;

void GLAPIENTRY mockgl_MultiTexCoord2fv(GLenum target, const GLfloat * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord2fv(target, v);
}
PFNGLMULTITEXCOORD2FVPROC __glewMultiTexCoord2fv = mockgl_MultiTexCoord2fv;

void GLAPIENTRY mockgl_MultiTexCoord2i(GLenum target, GLint s, GLint t)
{
    return GlewMock::getMock()->gl_MultiTexCoord2i(target, s, t);
}
PFNGLMULTITEXCOORD2IPROC __glewMultiTexCoord2i = mockgl_MultiTexCoord2i;

void GLAPIENTRY mockgl_MultiTexCoord2iv(GLenum target, const GLint * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord2iv(target, v);
}
PFNGLMULTITEXCOORD2IVPROC __glewMultiTexCoord2iv = mockgl_MultiTexCoord2iv;

void GLAPIENTRY mockgl_MultiTexCoord2s(GLenum target, GLshort s, GLshort t)
{
    return GlewMock::getMock()->gl_MultiTexCoord2s(target, s, t);
}
PFNGLMULTITEXCOORD2SPROC __glewMultiTexCoord2s = mockgl_MultiTexCoord2s;

void GLAPIENTRY mockgl_MultiTexCoord2sv(GLenum target, const GLshort * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord2sv(target, v);
}
PFNGLMULTITEXCOORD2SVPROC __glewMultiTexCoord2sv = mockgl_MultiTexCoord2sv;

void GLAPIENTRY mockgl_MultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
    return GlewMock::getMock()->gl_MultiTexCoord3d(target, s, t, r);
}
PFNGLMULTITEXCOORD3DPROC __glewMultiTexCoord3d = mockgl_MultiTexCoord3d;

void GLAPIENTRY mockgl_MultiTexCoord3dv(GLenum target, const GLdouble * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord3dv(target, v);
}
PFNGLMULTITEXCOORD3DVPROC __glewMultiTexCoord3dv = mockgl_MultiTexCoord3dv;

void GLAPIENTRY mockgl_MultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
    return GlewMock::getMock()->gl_MultiTexCoord3f(target, s, t, r);
}
PFNGLMULTITEXCOORD3FPROC __glewMultiTexCoord3f = mockgl_MultiTexCoord3f;

void GLAPIENTRY mockgl_MultiTexCoord3fv(GLenum target, const GLfloat * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord3fv(target, v);
}
PFNGLMULTITEXCOORD3FVPROC __glewMultiTexCoord3fv = mockgl_MultiTexCoord3fv;

void GLAPIENTRY mockgl_MultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)
{
    return GlewMock::getMock()->gl_MultiTexCoord3i(target, s, t, r);
}
PFNGLMULTITEXCOORD3IPROC __glewMultiTexCoord3i = mockgl_MultiTexCoord3i;

void GLAPIENTRY mockgl_MultiTexCoord3iv(GLenum target, const GLint * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord3iv(target, v);
}
PFNGLMULTITEXCOORD3IVPROC __glewMultiTexCoord3iv = mockgl_MultiTexCoord3iv;

void GLAPIENTRY mockgl_MultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)
{
    return GlewMock::getMock()->gl_MultiTexCoord3s(target, s, t, r);
}
PFNGLMULTITEXCOORD3SPROC __glewMultiTexCoord3s = mockgl_MultiTexCoord3s;

void GLAPIENTRY mockgl_MultiTexCoord3sv(GLenum target, const GLshort * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord3sv(target, v);
}
PFNGLMULTITEXCOORD3SVPROC __glewMultiTexCoord3sv = mockgl_MultiTexCoord3sv;

void GLAPIENTRY mockgl_MultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    return GlewMock::getMock()->gl_MultiTexCoord4d(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4DPROC __glewMultiTexCoord4d = mockgl_MultiTexCoord4d;

void GLAPIENTRY mockgl_MultiTexCoord4dv(GLenum target, const GLdouble * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord4dv(target, v);
}
PFNGLMULTITEXCOORD4DVPROC __glewMultiTexCoord4dv = mockgl_MultiTexCoord4dv;

void GLAPIENTRY mockgl_MultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    return GlewMock::getMock()->gl_MultiTexCoord4f(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4FPROC __glewMultiTexCoord4f = mockgl_MultiTexCoord4f;

void GLAPIENTRY mockgl_MultiTexCoord4fv(GLenum target, const GLfloat * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord4fv(target, v);
}
PFNGLMULTITEXCOORD4FVPROC __glewMultiTexCoord4fv = mockgl_MultiTexCoord4fv;

void GLAPIENTRY mockgl_MultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
    return GlewMock::getMock()->gl_MultiTexCoord4i(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4IPROC __glewMultiTexCoord4i = mockgl_MultiTexCoord4i;

void GLAPIENTRY mockgl_MultiTexCoord4iv(GLenum target, const GLint * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord4iv(target, v);
}
PFNGLMULTITEXCOORD4IVPROC __glewMultiTexCoord4iv = mockgl_MultiTexCoord4iv;

void GLAPIENTRY mockgl_MultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
    return GlewMock::getMock()->gl_MultiTexCoord4s(target, s, t, r, q);
}
PFNGLMULTITEXCOORD4SPROC __glewMultiTexCoord4s = mockgl_MultiTexCoord4s;

void GLAPIENTRY mockgl_MultiTexCoord4sv(GLenum target, const GLshort * v)
{
    return GlewMock::getMock()->gl_MultiTexCoord4sv(target, v);
}
PFNGLMULTITEXCOORD4SVPROC __glewMultiTexCoord4sv = mockgl_MultiTexCoord4sv;

void GLAPIENTRY mockgl_SampleCoverage(GLclampf value, GLboolean invert)
{
    return GlewMock::getMock()->gl_SampleCoverage(value, invert);
}
PFNGLSAMPLECOVERAGEPROC __glewSampleCoverage = mockgl_SampleCoverage;

void GLAPIENTRY mockgl_BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    return GlewMock::getMock()->gl_BlendColor(red, green, blue, alpha);
}
PFNGLBLENDCOLORPROC __glewBlendColor = mockgl_BlendColor;

void GLAPIENTRY mockgl_BlendEquation(GLenum mode)
{
    return GlewMock::getMock()->gl_BlendEquation(mode);
}
PFNGLBLENDEQUATIONPROC __glewBlendEquation = mockgl_BlendEquation;

void GLAPIENTRY mockgl_BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    return GlewMock::getMock()->gl_BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}
PFNGLBLENDFUNCSEPARATEPROC __glewBlendFuncSeparate = mockgl_BlendFuncSeparate;

void GLAPIENTRY mockgl_FogCoordPointer(GLenum type, GLsizei stride, const void * pointer)
{
    return GlewMock::getMock()->gl_FogCoordPointer(type, stride, pointer);
}
PFNGLFOGCOORDPOINTERPROC __glewFogCoordPointer = mockgl_FogCoordPointer;

void GLAPIENTRY mockgl_FogCoordd(GLdouble coord)
{
    return GlewMock::getMock()->gl_FogCoordd(coord);
}
PFNGLFOGCOORDDPROC __glewFogCoordd = mockgl_FogCoordd;

void GLAPIENTRY mockgl_FogCoorddv(const GLdouble * coord)
{
    return GlewMock::getMock()->gl_FogCoorddv(coord);
}
PFNGLFOGCOORDDVPROC __glewFogCoorddv = mockgl_FogCoorddv;

void GLAPIENTRY mockgl_FogCoordf(GLfloat coord)
{
    return GlewMock::getMock()->gl_FogCoordf(coord);
}
PFNGLFOGCOORDFPROC __glewFogCoordf = mockgl_FogCoordf;

void GLAPIENTRY mockgl_FogCoordfv(const GLfloat * coord)
{
    return GlewMock::getMock()->gl_FogCoordfv(coord);
}
PFNGLFOGCOORDFVPROC __glewFogCoordfv = mockgl_FogCoordfv;

void GLAPIENTRY mockgl_MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount)
{
    return GlewMock::getMock()->gl_MultiDrawArrays(mode, first, count, drawcount);
}
PFNGLMULTIDRAWARRAYSPROC __glewMultiDrawArrays = mockgl_MultiDrawArrays;

void GLAPIENTRY mockgl_MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void *const * indices, GLsizei drawcount)
{
    return GlewMock::getMock()->gl_MultiDrawElements(mode, count, type, indices, drawcount);
}
PFNGLMULTIDRAWELEMENTSPROC __glewMultiDrawElements = mockgl_MultiDrawElements;

void GLAPIENTRY mockgl_PointParameterf(GLenum pname, GLfloat param)
{
    return GlewMock::getMock()->gl_PointParameterf(pname, param);
}
PFNGLPOINTPARAMETERFPROC __glewPointParameterf = mockgl_PointParameterf;

void GLAPIENTRY mockgl_PointParameterfv(GLenum pname, const GLfloat * params)
{
    return GlewMock::getMock()->gl_PointParameterfv(pname, params);
}
PFNGLPOINTPARAMETERFVPROC __glewPointParameterfv = mockgl_PointParameterfv;

void GLAPIENTRY mockgl_PointParameteri(GLenum pname, GLint param)
{
    return GlewMock::getMock()->gl_PointParameteri(pname, param);
}
PFNGLPOINTPARAMETERIPROC __glewPointParameteri = mockgl_PointParameteri;

void GLAPIENTRY mockgl_PointParameteriv(GLenum pname, const GLint * params)
{
    return GlewMock::getMock()->gl_PointParameteriv(pname, params);
}
PFNGLPOINTPARAMETERIVPROC __glewPointParameteriv = mockgl_PointParameteriv;

void GLAPIENTRY mockgl_SecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3b(red, green, blue);
}
PFNGLSECONDARYCOLOR3BPROC __glewSecondaryColor3b = mockgl_SecondaryColor3b;

void GLAPIENTRY mockgl_SecondaryColor3bv(const GLbyte * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3bv(v);
}
PFNGLSECONDARYCOLOR3BVPROC __glewSecondaryColor3bv = mockgl_SecondaryColor3bv;

void GLAPIENTRY mockgl_SecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3d(red, green, blue);
}
PFNGLSECONDARYCOLOR3DPROC __glewSecondaryColor3d = mockgl_SecondaryColor3d;

void GLAPIENTRY mockgl_SecondaryColor3dv(const GLdouble * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3dv(v);
}
PFNGLSECONDARYCOLOR3DVPROC __glewSecondaryColor3dv = mockgl_SecondaryColor3dv;

void GLAPIENTRY mockgl_SecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3f(red, green, blue);
}
PFNGLSECONDARYCOLOR3FPROC __glewSecondaryColor3f = mockgl_SecondaryColor3f;

void GLAPIENTRY mockgl_SecondaryColor3fv(const GLfloat * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3fv(v);
}
PFNGLSECONDARYCOLOR3FVPROC __glewSecondaryColor3fv = mockgl_SecondaryColor3fv;

void GLAPIENTRY mockgl_SecondaryColor3i(GLint red, GLint green, GLint blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3i(red, green, blue);
}
PFNGLSECONDARYCOLOR3IPROC __glewSecondaryColor3i = mockgl_SecondaryColor3i;

void GLAPIENTRY mockgl_SecondaryColor3iv(const GLint * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3iv(v);
}
PFNGLSECONDARYCOLOR3IVPROC __glewSecondaryColor3iv = mockgl_SecondaryColor3iv;

void GLAPIENTRY mockgl_SecondaryColor3s(GLshort red, GLshort green, GLshort blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3s(red, green, blue);
}
PFNGLSECONDARYCOLOR3SPROC __glewSecondaryColor3s = mockgl_SecondaryColor3s;

void GLAPIENTRY mockgl_SecondaryColor3sv(const GLshort * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3sv(v);
}
PFNGLSECONDARYCOLOR3SVPROC __glewSecondaryColor3sv = mockgl_SecondaryColor3sv;

void GLAPIENTRY mockgl_SecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3ub(red, green, blue);
}
PFNGLSECONDARYCOLOR3UBPROC __glewSecondaryColor3ub = mockgl_SecondaryColor3ub;

void GLAPIENTRY mockgl_SecondaryColor3ubv(const GLubyte * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3ubv(v);
}
PFNGLSECONDARYCOLOR3UBVPROC __glewSecondaryColor3ubv = mockgl_SecondaryColor3ubv;

void GLAPIENTRY mockgl_SecondaryColor3ui(GLuint red, GLuint green, GLuint blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3ui(red, green, blue);
}
PFNGLSECONDARYCOLOR3UIPROC __glewSecondaryColor3ui = mockgl_SecondaryColor3ui;

void GLAPIENTRY mockgl_SecondaryColor3uiv(const GLuint * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3uiv(v);
}
PFNGLSECONDARYCOLOR3UIVPROC __glewSecondaryColor3uiv = mockgl_SecondaryColor3uiv;

void GLAPIENTRY mockgl_SecondaryColor3us(GLushort red, GLushort green, GLushort blue)
{
    return GlewMock::getMock()->gl_SecondaryColor3us(red, green, blue);
}
PFNGLSECONDARYCOLOR3USPROC __glewSecondaryColor3us = mockgl_SecondaryColor3us;

void GLAPIENTRY mockgl_SecondaryColor3usv(const GLushort * v)
{
    return GlewMock::getMock()->gl_SecondaryColor3usv(v);
}
PFNGLSECONDARYCOLOR3USVPROC __glewSecondaryColor3usv = mockgl_SecondaryColor3usv;

void GLAPIENTRY mockgl_SecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return GlewMock::getMock()->gl_SecondaryColorPointer(size, type, stride, pointer);
}
PFNGLSECONDARYCOLORPOINTERPROC __glewSecondaryColorPointer = mockgl_SecondaryColorPointer;

void GLAPIENTRY mockgl_WindowPos2d(GLdouble x, GLdouble y)
{
    return GlewMock::getMock()->gl_WindowPos2d(x, y);
}
PFNGLWINDOWPOS2DPROC __glewWindowPos2d = mockgl_WindowPos2d;

void GLAPIENTRY mockgl_WindowPos2dv(const GLdouble * p)
{
    return GlewMock::getMock()->gl_WindowPos2dv(p);
}
PFNGLWINDOWPOS2DVPROC __glewWindowPos2dv = mockgl_WindowPos2dv;

void GLAPIENTRY mockgl_WindowPos2f(GLfloat x, GLfloat y)
{
    return GlewMock::getMock()->gl_WindowPos2f(x, y);
}
PFNGLWINDOWPOS2FPROC __glewWindowPos2f = mockgl_WindowPos2f;

void GLAPIENTRY mockgl_WindowPos2fv(const GLfloat * p)
{
    return GlewMock::getMock()->gl_WindowPos2fv(p);
}
PFNGLWINDOWPOS2FVPROC __glewWindowPos2fv = mockgl_WindowPos2fv;

void GLAPIENTRY mockgl_WindowPos2i(GLint x, GLint y)
{
    return GlewMock::getMock()->gl_WindowPos2i(x, y);
}
PFNGLWINDOWPOS2IPROC __glewWindowPos2i = mockgl_WindowPos2i;

void GLAPIENTRY mockgl_WindowPos2iv(const GLint * p)
{
    return GlewMock::getMock()->gl_WindowPos2iv(p);
}
PFNGLWINDOWPOS2IVPROC __glewWindowPos2iv = mockgl_WindowPos2iv;

void GLAPIENTRY mockgl_WindowPos2s(GLshort x, GLshort y)
{
    return GlewMock::getMock()->gl_WindowPos2s(x, y);
}
PFNGLWINDOWPOS2SPROC __glewWindowPos2s = mockgl_WindowPos2s;

void GLAPIENTRY mockgl_WindowPos2sv(const GLshort * p)
{
    return GlewMock::getMock()->gl_WindowPos2sv(p);
}
PFNGLWINDOWPOS2SVPROC __glewWindowPos2sv = mockgl_WindowPos2sv;

void GLAPIENTRY mockgl_WindowPos3d(GLdouble x, GLdouble y, GLdouble z)
{
    return GlewMock::getMock()->gl_WindowPos3d(x, y, z);
}
PFNGLWINDOWPOS3DPROC __glewWindowPos3d = mockgl_WindowPos3d;

void GLAPIENTRY mockgl_WindowPos3dv(const GLdouble * p)
{
    return GlewMock::getMock()->gl_WindowPos3dv(p);
}
PFNGLWINDOWPOS3DVPROC __glewWindowPos3dv = mockgl_WindowPos3dv;

void GLAPIENTRY mockgl_WindowPos3f(GLfloat x, GLfloat y, GLfloat z)
{
    return GlewMock::getMock()->gl_WindowPos3f(x, y, z);
}
PFNGLWINDOWPOS3FPROC __glewWindowPos3f = mockgl_WindowPos3f;

void GLAPIENTRY mockgl_WindowPos3fv(const GLfloat * p)
{
    return GlewMock::getMock()->gl_WindowPos3fv(p);
}
PFNGLWINDOWPOS3FVPROC __glewWindowPos3fv = mockgl_WindowPos3fv;

void GLAPIENTRY mockgl_WindowPos3i(GLint x, GLint y, GLint z)
{
    return GlewMock::getMock()->gl_WindowPos3i(x, y, z);
}
PFNGLWINDOWPOS3IPROC __glewWindowPos3i = mockgl_WindowPos3i;

void GLAPIENTRY mockgl_WindowPos3iv(const GLint * p)
{
    return GlewMock::getMock()->gl_WindowPos3iv(p);
}
PFNGLWINDOWPOS3IVPROC __glewWindowPos3iv = mockgl_WindowPos3iv;

void GLAPIENTRY mockgl_WindowPos3s(GLshort x, GLshort y, GLshort z)
{
    return GlewMock::getMock()->gl_WindowPos3s(x, y, z);
}
PFNGLWINDOWPOS3SPROC __glewWindowPos3s = mockgl_WindowPos3s;

void GLAPIENTRY mockgl_WindowPos3sv(const GLshort * p)
{
    return GlewMock::getMock()->gl_WindowPos3sv(p);
}
PFNGLWINDOWPOS3SVPROC __glewWindowPos3sv = mockgl_WindowPos3sv;

void GLAPIENTRY mockgl_BeginQuery(GLenum target, GLuint id)
{
    return GlewMock::getMock()->gl_BeginQuery(target, id);
}
PFNGLBEGINQUERYPROC __glewBeginQuery = mockgl_BeginQuery;

void GLAPIENTRY mockgl_BindBuffer(GLenum target, GLuint buffer)
{
    return GlewMock::getMock()->gl_BindBuffer(target, buffer);
}
PFNGLBINDBUFFERPROC __glewBindBuffer = mockgl_BindBuffer;

void GLAPIENTRY mockgl_BufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage)
{
    return GlewMock::getMock()->gl_BufferData(target, size, data, usage);
}
PFNGLBUFFERDATAPROC __glewBufferData = mockgl_BufferData;

void GLAPIENTRY mockgl_BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data)
{
    return GlewMock::getMock()->gl_BufferSubData(target, offset, size, data);
}
PFNGLBUFFERSUBDATAPROC __glewBufferSubData = mockgl_BufferSubData;

void GLAPIENTRY mockgl_DeleteBuffers(GLsizei n, const GLuint * buffers)
{
    return GlewMock::getMock()->gl_DeleteBuffers(n, buffers);
}
PFNGLDELETEBUFFERSPROC __glewDeleteBuffers = mockgl_DeleteBuffers;

void GLAPIENTRY mockgl_DeleteQueries(GLsizei n, const GLuint * ids)
{
    return GlewMock::getMock()->gl_DeleteQueries(n, ids);
}
PFNGLDELETEQUERIESPROC __glewDeleteQueries = mockgl_DeleteQueries;

void GLAPIENTRY mockgl_EndQuery(GLenum target)
{
    return GlewMock::getMock()->gl_EndQuery(target);
}
PFNGLENDQUERYPROC __glewEndQuery = mockgl_EndQuery;

void GLAPIENTRY mockgl_GenBuffers(GLsizei n, GLuint * buffers)
{
    return GlewMock::getMock()->gl_GenBuffers(n, buffers);
}
PFNGLGENBUFFERSPROC __glewGenBuffers = mockgl_GenBuffers;

void GLAPIENTRY mockgl_GenQueries(GLsizei n, GLuint * ids)
{
    return GlewMock::getMock()->gl_GenQueries(n, ids);
}
PFNGLGENQUERIESPROC __glewGenQueries = mockgl_GenQueries;

void GLAPIENTRY mockgl_GetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return GlewMock::getMock()->gl_GetBufferParameteriv(target, pname, params);
}
PFNGLGETBUFFERPARAMETERIVPROC __glewGetBufferParameteriv = mockgl_GetBufferParameteriv;

void GLAPIENTRY mockgl_GetBufferPointerv(GLenum target, GLenum pname, void ** params)
{
    return GlewMock::getMock()->gl_GetBufferPointerv(target, pname, params);
}
PFNGLGETBUFFERPOINTERVPROC __glewGetBufferPointerv = mockgl_GetBufferPointerv;

void GLAPIENTRY mockgl_GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data)
{
    return GlewMock::getMock()->gl_GetBufferSubData(target, offset, size, data);
}
PFNGLGETBUFFERSUBDATAPROC __glewGetBufferSubData = mockgl_GetBufferSubData;

void GLAPIENTRY mockgl_GetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
    return GlewMock::getMock()->gl_GetQueryObjectiv(id, pname, params);
}
PFNGLGETQUERYOBJECTIVPROC __glewGetQueryObjectiv = mockgl_GetQueryObjectiv;

void GLAPIENTRY mockgl_GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
    return GlewMock::getMock()->gl_GetQueryObjectuiv(id, pname, params);
}
PFNGLGETQUERYOBJECTUIVPROC __glewGetQueryObjectuiv = mockgl_GetQueryObjectuiv;

void GLAPIENTRY mockgl_GetQueryiv(GLenum target, GLenum pname, GLint * params)
{
    return GlewMock::getMock()->gl_GetQueryiv(target, pname, params);
}
PFNGLGETQUERYIVPROC __glewGetQueryiv = mockgl_GetQueryiv;

unsigned char GLAPIENTRY mockgl_IsBuffer(GLuint buffer)
{
    return GlewMock::getMock()->gl_IsBuffer(buffer);
}
PFNGLISBUFFERPROC __glewIsBuffer = mockgl_IsBuffer;

unsigned char GLAPIENTRY mockgl_IsQuery(GLuint id)
{
    return GlewMock::getMock()->gl_IsQuery(id);
}
PFNGLISQUERYPROC __glewIsQuery = mockgl_IsQuery;

void* GLAPIENTRY mockgl_MapBuffer(GLenum target, GLenum access)
{
    return GlewMock::getMock()->gl_MapBuffer(target, access);
}
PFNGLMAPBUFFERPROC __glewMapBuffer = mockgl_MapBuffer;

unsigned char GLAPIENTRY mockgl_UnmapBuffer(GLenum target)
{
    return GlewMock::getMock()->gl_UnmapBuffer(target);
}
PFNGLUNMAPBUFFERPROC __glewUnmapBuffer = mockgl_UnmapBuffer;

void GLAPIENTRY mockgl_AttachShader(GLuint program, GLuint shader)
{
    return GlewMock::getMock()->gl_AttachShader(program, shader);
}
PFNGLATTACHSHADERPROC __glewAttachShader = mockgl_AttachShader;

void GLAPIENTRY mockgl_BindAttribLocation(GLuint program, GLuint index, const GLchar * name)
{
    return GlewMock::getMock()->gl_BindAttribLocation(program, index, name);
}
PFNGLBINDATTRIBLOCATIONPROC __glewBindAttribLocation = mockgl_BindAttribLocation;

void GLAPIENTRY mockgl_BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
    return GlewMock::getMock()->gl_BlendEquationSeparate(modeRGB, modeAlpha);
}
PFNGLBLENDEQUATIONSEPARATEPROC __glewBlendEquationSeparate = mockgl_BlendEquationSeparate;

void GLAPIENTRY mockgl_CompileShader(GLuint shader)
{
    return GlewMock::getMock()->gl_CompileShader(shader);
}
PFNGLCOMPILESHADERPROC __glewCompileShader = mockgl_CompileShader;

unsigned int GLAPIENTRY mockgl_CreateProgram()
{
    return GlewMock::getMock()->gl_CreateProgram();
}
PFNGLCREATEPROGRAMPROC __glewCreateProgram = mockgl_CreateProgram;

unsigned int GLAPIENTRY mockgl_CreateShader(GLenum type)
{
    return GlewMock::getMock()->gl_CreateShader(type);
}
PFNGLCREATESHADERPROC __glewCreateShader = mockgl_CreateShader;

void GLAPIENTRY mockgl_DeleteProgram(GLuint program)
{
    return GlewMock::getMock()->gl_DeleteProgram(program);
}
PFNGLDELETEPROGRAMPROC __glewDeleteProgram = mockgl_DeleteProgram;

void GLAPIENTRY mockgl_DeleteShader(GLuint shader)
{
    return GlewMock::getMock()->gl_DeleteShader(shader);
}
PFNGLDELETESHADERPROC __glewDeleteShader = mockgl_DeleteShader;

void GLAPIENTRY mockgl_DetachShader(GLuint program, GLuint shader)
{
    return GlewMock::getMock()->gl_DetachShader(program, shader);
}
PFNGLDETACHSHADERPROC __glewDetachShader = mockgl_DetachShader;

void GLAPIENTRY mockgl_DisableVertexAttribArray(GLuint index)
{
    return GlewMock::getMock()->gl_DisableVertexAttribArray(index);
}
PFNGLDISABLEVERTEXATTRIBARRAYPROC __glewDisableVertexAttribArray = mockgl_DisableVertexAttribArray;

void GLAPIENTRY mockgl_DrawBuffers(GLsizei n, const GLenum * bufs)
{
    return GlewMock::getMock()->gl_DrawBuffers(n, bufs);
}
PFNGLDRAWBUFFERSPROC __glewDrawBuffers = mockgl_DrawBuffers;

void GLAPIENTRY mockgl_EnableVertexAttribArray(GLuint index)
{
    return GlewMock::getMock()->gl_EnableVertexAttribArray(index);
}
PFNGLENABLEVERTEXATTRIBARRAYPROC __glewEnableVertexAttribArray = mockgl_EnableVertexAttribArray;

void GLAPIENTRY mockgl_GetActiveAttrib(GLuint program, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
    return GlewMock::getMock()->gl_GetActiveAttrib(program, index, maxLength, length, size, type, name);
}
PFNGLGETACTIVEATTRIBPROC __glewGetActiveAttrib = mockgl_GetActiveAttrib;

void GLAPIENTRY mockgl_GetActiveUniform(GLuint program, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
    return GlewMock::getMock()->gl_GetActiveUniform(program, index, maxLength, length, size, type, name);
}
PFNGLGETACTIVEUNIFORMPROC __glewGetActiveUniform = mockgl_GetActiveUniform;

void GLAPIENTRY mockgl_GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders)
{
    return GlewMock::getMock()->gl_GetAttachedShaders(program, maxCount, count, shaders);
}
PFNGLGETATTACHEDSHADERSPROC __glewGetAttachedShaders = mockgl_GetAttachedShaders;

int GLAPIENTRY mockgl_GetAttribLocation(GLuint program, const GLchar * name)
{
    return GlewMock::getMock()->gl_GetAttribLocation(program, name);
}
PFNGLGETATTRIBLOCATIONPROC __glewGetAttribLocation = mockgl_GetAttribLocation;

