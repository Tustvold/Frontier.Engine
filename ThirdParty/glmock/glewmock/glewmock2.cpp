#include "glewmock2.hpp"
#include <stdexcept>


GlewMock2::GlewMock2() {

}

GlewMock2::~GlewMock2() {

}

GlewMock2* GlewMock2::getMock() {
    return (GlewMock2*)IGLMock::getMock();
}

void mockgl_GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    return GlewMock2::getMock()->gl_GetProgramInfoLog(program, bufSize, length, infoLog);
}

PFNGLGETPROGRAMINFOLOGPROC __glewGetProgramInfoLog = mockgl_GetProgramInfoLog;

void mockgl_GetProgramiv(GLuint program, GLenum pname, GLint* param) {
    switch (pname) {
    case GL_LINK_STATUS:
        *param = GL_TRUE;
        break;
    case GL_INFO_LOG_LENGTH:
        *param = 0;
        break;
    default:
        throw new std::invalid_argument("Unsupported GetProgramIV Enum");
    }
}

PFNGLGETPROGRAMIVPROC __glewGetProgramiv = mockgl_GetProgramiv;

void mockgl_GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    return GlewMock2::getMock()->gl_GetShaderInfoLog(shader, bufSize, length, infoLog);
}

PFNGLGETSHADERINFOLOGPROC __glewGetShaderInfoLog = mockgl_GetShaderInfoLog;

void mockgl_GetShaderSource(GLuint obj, GLsizei maxLength, GLsizei* length, GLchar* source) {
    return GlewMock2::getMock()->gl_GetShaderSource(obj, maxLength, length, source);
}

PFNGLGETSHADERSOURCEPROC __glewGetShaderSource = mockgl_GetShaderSource;

void mockgl_GetShaderiv(GLuint shader, GLenum pname, GLint* param) {
    switch (pname) {
    case GL_COMPILE_STATUS:
        *param = GL_TRUE;
        break;
    case GL_INFO_LOG_LENGTH:
        *param = 0;
        break;
    default:
        throw new std::invalid_argument("Unsupported GetShaderIV Enum");
    }
}

PFNGLGETSHADERIVPROC __glewGetShaderiv = mockgl_GetShaderiv;

int mockgl_GetUniformLocation(GLuint program, const GLchar* name) {
    return GlewMock2::getMock()->gl_GetUniformLocation(program, name);
}

PFNGLGETUNIFORMLOCATIONPROC __glewGetUniformLocation = mockgl_GetUniformLocation;

void mockgl_GetUniformfv(GLuint program, GLint location, GLfloat* params) {
    return GlewMock2::getMock()->gl_GetUniformfv(program, location, params);
}

PFNGLGETUNIFORMFVPROC __glewGetUniformfv = mockgl_GetUniformfv;

void mockgl_GetUniformiv(GLuint program, GLint location, GLint* params) {
    return GlewMock2::getMock()->gl_GetUniformiv(program, location, params);
}

PFNGLGETUNIFORMIVPROC __glewGetUniformiv = mockgl_GetUniformiv;

void mockgl_GetVertexAttribPointerv(GLuint index, GLenum pname, void** pointer) {
    return GlewMock2::getMock()->gl_GetVertexAttribPointerv(index, pname, pointer);
}

PFNGLGETVERTEXATTRIBPOINTERVPROC __glewGetVertexAttribPointerv = mockgl_GetVertexAttribPointerv;

void mockgl_GetVertexAttribdv(GLuint index, GLenum pname, GLdouble* params) {
    return GlewMock2::getMock()->gl_GetVertexAttribdv(index, pname, params);
}

PFNGLGETVERTEXATTRIBDVPROC __glewGetVertexAttribdv = mockgl_GetVertexAttribdv;

void mockgl_GetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params) {
    return GlewMock2::getMock()->gl_GetVertexAttribfv(index, pname, params);
}

PFNGLGETVERTEXATTRIBFVPROC __glewGetVertexAttribfv = mockgl_GetVertexAttribfv;

void mockgl_GetVertexAttribiv(GLuint index, GLenum pname, GLint* params) {
    return GlewMock2::getMock()->gl_GetVertexAttribiv(index, pname, params);
}

PFNGLGETVERTEXATTRIBIVPROC __glewGetVertexAttribiv = mockgl_GetVertexAttribiv;

unsigned char mockgl_IsProgram(GLuint program) {
    return GlewMock2::getMock()->gl_IsProgram(program);
}

PFNGLISPROGRAMPROC __glewIsProgram = mockgl_IsProgram;

unsigned char mockgl_IsShader(GLuint shader) {
    return GlewMock2::getMock()->gl_IsShader(shader);
}

PFNGLISSHADERPROC __glewIsShader = mockgl_IsShader;

void mockgl_LinkProgram(GLuint program) {
    return GlewMock2::getMock()->gl_LinkProgram(program);
}

PFNGLLINKPROGRAMPROC __glewLinkProgram = mockgl_LinkProgram;

void mockgl_ShaderSource(GLuint shader, GLsizei count, const GLchar*const * string, const GLint* length) {
    return GlewMock2::getMock()->gl_ShaderSource(shader, count, string, length);
}

PFNGLSHADERSOURCEPROC __glewShaderSource = mockgl_ShaderSource;

void mockgl_StencilFuncSeparate(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask) {
    return GlewMock2::getMock()->gl_StencilFuncSeparate(frontfunc, backfunc, ref, mask);
}

PFNGLSTENCILFUNCSEPARATEPROC __glewStencilFuncSeparate = mockgl_StencilFuncSeparate;

void mockgl_StencilMaskSeparate(GLenum face, GLuint mask) {
    return GlewMock2::getMock()->gl_StencilMaskSeparate(face, mask);
}

PFNGLSTENCILMASKSEPARATEPROC __glewStencilMaskSeparate = mockgl_StencilMaskSeparate;

void mockgl_StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    return GlewMock2::getMock()->gl_StencilOpSeparate(face, sfail, dpfail, dppass);
}

PFNGLSTENCILOPSEPARATEPROC __glewStencilOpSeparate = mockgl_StencilOpSeparate;

void mockgl_Uniform1f(GLint location, GLfloat v0) {
    return GlewMock2::getMock()->gl_Uniform1f(location, v0);
}

PFNGLUNIFORM1FPROC __glewUniform1f = mockgl_Uniform1f;

void mockgl_Uniform1fv(GLint location, GLsizei count, const GLfloat* value) {
    return GlewMock2::getMock()->gl_Uniform1fv(location, count, value);
}

PFNGLUNIFORM1FVPROC __glewUniform1fv = mockgl_Uniform1fv;

void mockgl_Uniform1i(GLint location, GLint v0) {
    return GlewMock2::getMock()->gl_Uniform1i(location, v0);
}

PFNGLUNIFORM1IPROC __glewUniform1i = mockgl_Uniform1i;

void mockgl_Uniform1iv(GLint location, GLsizei count, const GLint* value) {
    return GlewMock2::getMock()->gl_Uniform1iv(location, count, value);
}

PFNGLUNIFORM1IVPROC __glewUniform1iv = mockgl_Uniform1iv;

void mockgl_Uniform2f(GLint location, GLfloat v0, GLfloat v1) {
    return GlewMock2::getMock()->gl_Uniform2f(location, v0, v1);
}

PFNGLUNIFORM2FPROC __glewUniform2f = mockgl_Uniform2f;

void mockgl_Uniform2fv(GLint location, GLsizei count, const GLfloat* value) {
    return GlewMock2::getMock()->gl_Uniform2fv(location, count, value);
}

PFNGLUNIFORM2FVPROC __glewUniform2fv = mockgl_Uniform2fv;

void mockgl_Uniform2i(GLint location, GLint v0, GLint v1) {
    return GlewMock2::getMock()->gl_Uniform2i(location, v0, v1);
}

PFNGLUNIFORM2IPROC __glewUniform2i = mockgl_Uniform2i;

void mockgl_Uniform2iv(GLint location, GLsizei count, const GLint* value) {
    return GlewMock2::getMock()->gl_Uniform2iv(location, count, value);
}

PFNGLUNIFORM2IVPROC __glewUniform2iv = mockgl_Uniform2iv;

void mockgl_Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    return GlewMock2::getMock()->gl_Uniform3f(location, v0, v1, v2);
}

PFNGLUNIFORM3FPROC __glewUniform3f = mockgl_Uniform3f;

void mockgl_Uniform3fv(GLint location, GLsizei count, const GLfloat* value) {
    return GlewMock2::getMock()->gl_Uniform3fv(location, count, value);
}

PFNGLUNIFORM3FVPROC __glewUniform3fv = mockgl_Uniform3fv;

void mockgl_Uniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    return GlewMock2::getMock()->gl_Uniform3i(location, v0, v1, v2);
}

PFNGLUNIFORM3IPROC __glewUniform3i = mockgl_Uniform3i;

void mockgl_Uniform3iv(GLint location, GLsizei count, const GLint* value) {
    return GlewMock2::getMock()->gl_Uniform3iv(location, count, value);
}

PFNGLUNIFORM3IVPROC __glewUniform3iv = mockgl_Uniform3iv;

void mockgl_Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    return GlewMock2::getMock()->gl_Uniform4f(location, v0, v1, v2, v3);
}

PFNGLUNIFORM4FPROC __glewUniform4f = mockgl_Uniform4f;

void mockgl_Uniform4fv(GLint location, GLsizei count, const GLfloat* value) {
    return GlewMock2::getMock()->gl_Uniform4fv(location, count, value);
}

PFNGLUNIFORM4FVPROC __glewUniform4fv = mockgl_Uniform4fv;

void mockgl_Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    return GlewMock2::getMock()->gl_Uniform4i(location, v0, v1, v2, v3);
}

PFNGLUNIFORM4IPROC __glewUniform4i = mockgl_Uniform4i;

void mockgl_Uniform4iv(GLint location, GLsizei count, const GLint* value) {
    return GlewMock2::getMock()->gl_Uniform4iv(location, count, value);
}

PFNGLUNIFORM4IVPROC __glewUniform4iv = mockgl_Uniform4iv;

void mockgl_UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix2fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX2FVPROC __glewUniformMatrix2fv = mockgl_UniformMatrix2fv;

void mockgl_UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix3fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX3FVPROC __glewUniformMatrix3fv = mockgl_UniformMatrix3fv;

void mockgl_UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix4fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX4FVPROC __glewUniformMatrix4fv = mockgl_UniformMatrix4fv;

void mockgl_UseProgram(GLuint program) {
    return GlewMock2::getMock()->gl_UseProgram(program);
}

PFNGLUSEPROGRAMPROC __glewUseProgram = mockgl_UseProgram;

void mockgl_ValidateProgram(GLuint program) {
    return GlewMock2::getMock()->gl_ValidateProgram(program);
}

PFNGLVALIDATEPROGRAMPROC __glewValidateProgram = mockgl_ValidateProgram;

void mockgl_VertexAttrib1d(GLuint index, GLdouble x) {
    return GlewMock2::getMock()->gl_VertexAttrib1d(index, x);
}

PFNGLVERTEXATTRIB1DPROC __glewVertexAttrib1d = mockgl_VertexAttrib1d;

void mockgl_VertexAttrib1dv(GLuint index, const GLdouble* v) {
    return GlewMock2::getMock()->gl_VertexAttrib1dv(index, v);
}

PFNGLVERTEXATTRIB1DVPROC __glewVertexAttrib1dv = mockgl_VertexAttrib1dv;

void mockgl_VertexAttrib1f(GLuint index, GLfloat x) {
    return GlewMock2::getMock()->gl_VertexAttrib1f(index, x);
}

PFNGLVERTEXATTRIB1FPROC __glewVertexAttrib1f = mockgl_VertexAttrib1f;

void mockgl_VertexAttrib1fv(GLuint index, const GLfloat* v) {
    return GlewMock2::getMock()->gl_VertexAttrib1fv(index, v);
}

PFNGLVERTEXATTRIB1FVPROC __glewVertexAttrib1fv = mockgl_VertexAttrib1fv;

void mockgl_VertexAttrib1s(GLuint index, GLshort x) {
    return GlewMock2::getMock()->gl_VertexAttrib1s(index, x);
}

PFNGLVERTEXATTRIB1SPROC __glewVertexAttrib1s = mockgl_VertexAttrib1s;

void mockgl_VertexAttrib1sv(GLuint index, const GLshort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib1sv(index, v);
}

PFNGLVERTEXATTRIB1SVPROC __glewVertexAttrib1sv = mockgl_VertexAttrib1sv;

void mockgl_VertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
    return GlewMock2::getMock()->gl_VertexAttrib2d(index, x, y);
}

PFNGLVERTEXATTRIB2DPROC __glewVertexAttrib2d = mockgl_VertexAttrib2d;

void mockgl_VertexAttrib2dv(GLuint index, const GLdouble* v) {
    return GlewMock2::getMock()->gl_VertexAttrib2dv(index, v);
}

PFNGLVERTEXATTRIB2DVPROC __glewVertexAttrib2dv = mockgl_VertexAttrib2dv;

void mockgl_VertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    return GlewMock2::getMock()->gl_VertexAttrib2f(index, x, y);
}

PFNGLVERTEXATTRIB2FPROC __glewVertexAttrib2f = mockgl_VertexAttrib2f;

void mockgl_VertexAttrib2fv(GLuint index, const GLfloat* v) {
    return GlewMock2::getMock()->gl_VertexAttrib2fv(index, v);
}

PFNGLVERTEXATTRIB2FVPROC __glewVertexAttrib2fv = mockgl_VertexAttrib2fv;

void mockgl_VertexAttrib2s(GLuint index, GLshort x, GLshort y) {
    return GlewMock2::getMock()->gl_VertexAttrib2s(index, x, y);
}

PFNGLVERTEXATTRIB2SPROC __glewVertexAttrib2s = mockgl_VertexAttrib2s;

void mockgl_VertexAttrib2sv(GLuint index, const GLshort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib2sv(index, v);
}

PFNGLVERTEXATTRIB2SVPROC __glewVertexAttrib2sv = mockgl_VertexAttrib2sv;

void mockgl_VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    return GlewMock2::getMock()->gl_VertexAttrib3d(index, x, y, z);
}

PFNGLVERTEXATTRIB3DPROC __glewVertexAttrib3d = mockgl_VertexAttrib3d;

void mockgl_VertexAttrib3dv(GLuint index, const GLdouble* v) {
    return GlewMock2::getMock()->gl_VertexAttrib3dv(index, v);
}

PFNGLVERTEXATTRIB3DVPROC __glewVertexAttrib3dv = mockgl_VertexAttrib3dv;

void mockgl_VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    return GlewMock2::getMock()->gl_VertexAttrib3f(index, x, y, z);
}

PFNGLVERTEXATTRIB3FPROC __glewVertexAttrib3f = mockgl_VertexAttrib3f;

void mockgl_VertexAttrib3fv(GLuint index, const GLfloat* v) {
    return GlewMock2::getMock()->gl_VertexAttrib3fv(index, v);
}

PFNGLVERTEXATTRIB3FVPROC __glewVertexAttrib3fv = mockgl_VertexAttrib3fv;

void mockgl_VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
    return GlewMock2::getMock()->gl_VertexAttrib3s(index, x, y, z);
}

PFNGLVERTEXATTRIB3SPROC __glewVertexAttrib3s = mockgl_VertexAttrib3s;

void mockgl_VertexAttrib3sv(GLuint index, const GLshort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib3sv(index, v);
}

PFNGLVERTEXATTRIB3SVPROC __glewVertexAttrib3sv = mockgl_VertexAttrib3sv;

void mockgl_VertexAttrib4Nbv(GLuint index, const GLbyte* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nbv(index, v);
}

PFNGLVERTEXATTRIB4NBVPROC __glewVertexAttrib4Nbv = mockgl_VertexAttrib4Nbv;

void mockgl_VertexAttrib4Niv(GLuint index, const GLint* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Niv(index, v);
}

PFNGLVERTEXATTRIB4NIVPROC __glewVertexAttrib4Niv = mockgl_VertexAttrib4Niv;

void mockgl_VertexAttrib4Nsv(GLuint index, const GLshort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nsv(index, v);
}

PFNGLVERTEXATTRIB4NSVPROC __glewVertexAttrib4Nsv = mockgl_VertexAttrib4Nsv;

void mockgl_VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nub(index, x, y, z, w);
}

PFNGLVERTEXATTRIB4NUBPROC __glewVertexAttrib4Nub = mockgl_VertexAttrib4Nub;

void mockgl_VertexAttrib4Nubv(GLuint index, const GLubyte* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nubv(index, v);
}

PFNGLVERTEXATTRIB4NUBVPROC __glewVertexAttrib4Nubv = mockgl_VertexAttrib4Nubv;

void mockgl_VertexAttrib4Nuiv(GLuint index, const GLuint* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nuiv(index, v);
}

PFNGLVERTEXATTRIB4NUIVPROC __glewVertexAttrib4Nuiv = mockgl_VertexAttrib4Nuiv;

void mockgl_VertexAttrib4Nusv(GLuint index, const GLushort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4Nusv(index, v);
}

PFNGLVERTEXATTRIB4NUSVPROC __glewVertexAttrib4Nusv = mockgl_VertexAttrib4Nusv;

void mockgl_VertexAttrib4bv(GLuint index, const GLbyte* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4bv(index, v);
}

PFNGLVERTEXATTRIB4BVPROC __glewVertexAttrib4bv = mockgl_VertexAttrib4bv;

void mockgl_VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    return GlewMock2::getMock()->gl_VertexAttrib4d(index, x, y, z, w);
}

PFNGLVERTEXATTRIB4DPROC __glewVertexAttrib4d = mockgl_VertexAttrib4d;

void mockgl_VertexAttrib4dv(GLuint index, const GLdouble* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4dv(index, v);
}

PFNGLVERTEXATTRIB4DVPROC __glewVertexAttrib4dv = mockgl_VertexAttrib4dv;

void mockgl_VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    return GlewMock2::getMock()->gl_VertexAttrib4f(index, x, y, z, w);
}

PFNGLVERTEXATTRIB4FPROC __glewVertexAttrib4f = mockgl_VertexAttrib4f;

void mockgl_VertexAttrib4fv(GLuint index, const GLfloat* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4fv(index, v);
}

PFNGLVERTEXATTRIB4FVPROC __glewVertexAttrib4fv = mockgl_VertexAttrib4fv;

void mockgl_VertexAttrib4iv(GLuint index, const GLint* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4iv(index, v);
}

PFNGLVERTEXATTRIB4IVPROC __glewVertexAttrib4iv = mockgl_VertexAttrib4iv;

void mockgl_VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    return GlewMock2::getMock()->gl_VertexAttrib4s(index, x, y, z, w);
}

PFNGLVERTEXATTRIB4SPROC __glewVertexAttrib4s = mockgl_VertexAttrib4s;

void mockgl_VertexAttrib4sv(GLuint index, const GLshort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4sv(index, v);
}

PFNGLVERTEXATTRIB4SVPROC __glewVertexAttrib4sv = mockgl_VertexAttrib4sv;

void mockgl_VertexAttrib4ubv(GLuint index, const GLubyte* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4ubv(index, v);
}

PFNGLVERTEXATTRIB4UBVPROC __glewVertexAttrib4ubv = mockgl_VertexAttrib4ubv;

void mockgl_VertexAttrib4uiv(GLuint index, const GLuint* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4uiv(index, v);
}

PFNGLVERTEXATTRIB4UIVPROC __glewVertexAttrib4uiv = mockgl_VertexAttrib4uiv;

void mockgl_VertexAttrib4usv(GLuint index, const GLushort* v) {
    return GlewMock2::getMock()->gl_VertexAttrib4usv(index, v);
}

PFNGLVERTEXATTRIB4USVPROC __glewVertexAttrib4usv = mockgl_VertexAttrib4usv;

void mockgl_VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    return GlewMock2::getMock()->gl_VertexAttribPointer(index, size, type, normalized, stride, pointer);
}

PFNGLVERTEXATTRIBPOINTERPROC __glewVertexAttribPointer = mockgl_VertexAttribPointer;

void mockgl_UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix2x3fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX2X3FVPROC __glewUniformMatrix2x3fv = mockgl_UniformMatrix2x3fv;

void mockgl_UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix2x4fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX2X4FVPROC __glewUniformMatrix2x4fv = mockgl_UniformMatrix2x4fv;

void mockgl_UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix3x2fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX3X2FVPROC __glewUniformMatrix3x2fv = mockgl_UniformMatrix3x2fv;

void mockgl_UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix3x4fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX3X4FVPROC __glewUniformMatrix3x4fv = mockgl_UniformMatrix3x4fv;

void mockgl_UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix4x2fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX4X2FVPROC __glewUniformMatrix4x2fv = mockgl_UniformMatrix4x2fv;

void mockgl_UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    return GlewMock2::getMock()->gl_UniformMatrix4x3fv(location, count, transpose, value);
}

PFNGLUNIFORMMATRIX4X3FVPROC __glewUniformMatrix4x3fv = mockgl_UniformMatrix4x3fv;

void mockgl_BeginConditionalRender(GLuint id, GLenum mode) {
    return GlewMock2::getMock()->gl_BeginConditionalRender(id, mode);
}

PFNGLBEGINCONDITIONALRENDERPROC __glewBeginConditionalRender = mockgl_BeginConditionalRender;

void mockgl_BeginTransformFeedback(GLenum primitiveMode) {
    return GlewMock2::getMock()->gl_BeginTransformFeedback(primitiveMode);
}

PFNGLBEGINTRANSFORMFEEDBACKPROC __glewBeginTransformFeedback = mockgl_BeginTransformFeedback;

void mockgl_BindFragDataLocation(GLuint program, GLuint colorNumber, const GLchar* name) {
    return GlewMock2::getMock()->gl_BindFragDataLocation(program, colorNumber, name);
}

PFNGLBINDFRAGDATALOCATIONPROC __glewBindFragDataLocation = mockgl_BindFragDataLocation;

void mockgl_ClampColor(GLenum target, GLenum clamp) {
    return GlewMock2::getMock()->gl_ClampColor(target, clamp);
}

PFNGLCLAMPCOLORPROC __glewClampColor = mockgl_ClampColor;

void mockgl_ClearBufferfi(GLenum buffer, GLint drawBuffer, GLfloat depth, GLint stencil) {
    return GlewMock2::getMock()->gl_ClearBufferfi(buffer, drawBuffer, depth, stencil);
}

PFNGLCLEARBUFFERFIPROC __glewClearBufferfi = mockgl_ClearBufferfi;

void mockgl_ClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat* value) {
    return GlewMock2::getMock()->gl_ClearBufferfv(buffer, drawBuffer, value);
}

PFNGLCLEARBUFFERFVPROC __glewClearBufferfv = mockgl_ClearBufferfv;

void mockgl_ClearBufferiv(GLenum buffer, GLint drawBuffer, const GLint* value) {
    return GlewMock2::getMock()->gl_ClearBufferiv(buffer, drawBuffer, value);
}

PFNGLCLEARBUFFERIVPROC __glewClearBufferiv = mockgl_ClearBufferiv;

void mockgl_ClearBufferuiv(GLenum buffer, GLint drawBuffer, const GLuint* value) {
    return GlewMock2::getMock()->gl_ClearBufferuiv(buffer, drawBuffer, value);
}

PFNGLCLEARBUFFERUIVPROC __glewClearBufferuiv = mockgl_ClearBufferuiv;

void mockgl_ColorMaski(GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    return GlewMock2::getMock()->gl_ColorMaski(buf, red, green, blue, alpha);
}

PFNGLCOLORMASKIPROC __glewColorMaski = mockgl_ColorMaski;

void mockgl_Disablei(GLenum cap, GLuint index) {
    return GlewMock2::getMock()->gl_Disablei(cap, index);
}

PFNGLDISABLEIPROC __glewDisablei = mockgl_Disablei;

void mockgl_Enablei(GLenum cap, GLuint index) {
    return GlewMock2::getMock()->gl_Enablei(cap, index);
}

PFNGLENABLEIPROC __glewEnablei = mockgl_Enablei;

void mockgl_EndConditionalRender() {
    return GlewMock2::getMock()->gl_EndConditionalRender();
}

PFNGLENDCONDITIONALRENDERPROC __glewEndConditionalRender = mockgl_EndConditionalRender;

void mockgl_EndTransformFeedback() {
    return GlewMock2::getMock()->gl_EndTransformFeedback();
}

PFNGLENDTRANSFORMFEEDBACKPROC __glewEndTransformFeedback = mockgl_EndTransformFeedback;

void mockgl_GetBooleani_v(GLenum pname, GLuint index, GLboolean* data) {
    return GlewMock2::getMock()->gl_GetBooleani_v(pname, index, data);
}

PFNGLGETBOOLEANI_VPROC __glewGetBooleani_v = mockgl_GetBooleani_v;

int mockgl_GetFragDataLocation(GLuint program, const GLchar* name) {
    return GlewMock2::getMock()->gl_GetFragDataLocation(program, name);
}

PFNGLGETFRAGDATALOCATIONPROC __glewGetFragDataLocation = mockgl_GetFragDataLocation;

const unsigned char* mockgl_GetStringi(GLenum name, GLuint index) {
    return GlewMock2::getMock()->gl_GetStringi(name, index);
}

PFNGLGETSTRINGIPROC __glewGetStringi = mockgl_GetStringi;

void mockgl_GetTexParameterIiv(GLenum target, GLenum pname, GLint* params) {
    return GlewMock2::getMock()->gl_GetTexParameterIiv(target, pname, params);
}

PFNGLGETTEXPARAMETERIIVPROC __glewGetTexParameterIiv = mockgl_GetTexParameterIiv;

void mockgl_GetTexParameterIuiv(GLenum target, GLenum pname, GLuint* params) {
    return GlewMock2::getMock()->gl_GetTexParameterIuiv(target, pname, params);
}

PFNGLGETTEXPARAMETERIUIVPROC __glewGetTexParameterIuiv = mockgl_GetTexParameterIuiv;

void mockgl_GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLsizei* size, GLenum* type, GLchar* name) {
    return GlewMock2::getMock()->gl_GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

PFNGLGETTRANSFORMFEEDBACKVARYINGPROC __glewGetTransformFeedbackVarying = mockgl_GetTransformFeedbackVarying;

void mockgl_GetUniformuiv(GLuint program, GLint location, GLuint* params) {
    return GlewMock2::getMock()->gl_GetUniformuiv(program, location, params);
}

PFNGLGETUNIFORMUIVPROC __glewGetUniformuiv = mockgl_GetUniformuiv;

void mockgl_GetVertexAttribIiv(GLuint index, GLenum pname, GLint* params) {
    return GlewMock2::getMock()->gl_GetVertexAttribIiv(index, pname, params);
}

PFNGLGETVERTEXATTRIBIIVPROC __glewGetVertexAttribIiv = mockgl_GetVertexAttribIiv;

void mockgl_GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint* params) {
    return GlewMock2::getMock()->gl_GetVertexAttribIuiv(index, pname, params);
}

PFNGLGETVERTEXATTRIBIUIVPROC __glewGetVertexAttribIuiv = mockgl_GetVertexAttribIuiv;

unsigned char mockgl_IsEnabledi(GLenum cap, GLuint index) {
    return GlewMock2::getMock()->gl_IsEnabledi(cap, index);
}

PFNGLISENABLEDIPROC __glewIsEnabledi = mockgl_IsEnabledi;

void mockgl_TexParameterIiv(GLenum target, GLenum pname, const GLint* params) {
    return GlewMock2::getMock()->gl_TexParameterIiv(target, pname, params);
}

PFNGLTEXPARAMETERIIVPROC __glewTexParameterIiv = mockgl_TexParameterIiv;

void mockgl_TexParameterIuiv(GLenum target, GLenum pname, const GLuint* params) {
    return GlewMock2::getMock()->gl_TexParameterIuiv(target, pname, params);
}

PFNGLTEXPARAMETERIUIVPROC __glewTexParameterIuiv = mockgl_TexParameterIuiv;

void mockgl_TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar*const * varyings, GLenum bufferMode) {
    return GlewMock2::getMock()->gl_TransformFeedbackVaryings(program, count, varyings, bufferMode);
}

PFNGLTRANSFORMFEEDBACKVARYINGSPROC __glewTransformFeedbackVaryings = mockgl_TransformFeedbackVaryings;

void mockgl_Uniform1ui(GLint location, GLuint v0) {
    return GlewMock2::getMock()->gl_Uniform1ui(location, v0);
}

PFNGLUNIFORM1UIPROC __glewUniform1ui = mockgl_Uniform1ui;

void mockgl_Uniform1uiv(GLint location, GLsizei count, const GLuint* value) {
    return GlewMock2::getMock()->gl_Uniform1uiv(location, count, value);
}

PFNGLUNIFORM1UIVPROC __glewUniform1uiv = mockgl_Uniform1uiv;

void mockgl_Uniform2ui(GLint location, GLuint v0, GLuint v1) {
    return GlewMock2::getMock()->gl_Uniform2ui(location, v0, v1);
}

PFNGLUNIFORM2UIPROC __glewUniform2ui = mockgl_Uniform2ui;

void mockgl_Uniform2uiv(GLint location, GLsizei count, const GLuint* value) {
    return GlewMock2::getMock()->gl_Uniform2uiv(location, count, value);
}

PFNGLUNIFORM2UIVPROC __glewUniform2uiv = mockgl_Uniform2uiv;

void mockgl_Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    return GlewMock2::getMock()->gl_Uniform3ui(location, v0, v1, v2);
}

PFNGLUNIFORM3UIPROC __glewUniform3ui = mockgl_Uniform3ui;

void mockgl_Uniform3uiv(GLint location, GLsizei count, const GLuint* value) {
    return GlewMock2::getMock()->gl_Uniform3uiv(location, count, value);
}

PFNGLUNIFORM3UIVPROC __glewUniform3uiv = mockgl_Uniform3uiv;

void mockgl_Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    return GlewMock2::getMock()->gl_Uniform4ui(location, v0, v1, v2, v3);
}

PFNGLUNIFORM4UIPROC __glewUniform4ui = mockgl_Uniform4ui;

void mockgl_Uniform4uiv(GLint location, GLsizei count, const GLuint* value) {
    return GlewMock2::getMock()->gl_Uniform4uiv(location, count, value);
}

PFNGLUNIFORM4UIVPROC __glewUniform4uiv = mockgl_Uniform4uiv;

void mockgl_VertexAttribI1i(GLuint index, GLint v0) {
    return GlewMock2::getMock()->gl_VertexAttribI1i(index, v0);
}

PFNGLVERTEXATTRIBI1IPROC __glewVertexAttribI1i = mockgl_VertexAttribI1i;

void mockgl_VertexAttribI1iv(GLuint index, const GLint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI1iv(index, v0);
}

PFNGLVERTEXATTRIBI1IVPROC __glewVertexAttribI1iv = mockgl_VertexAttribI1iv;

void mockgl_VertexAttribI1ui(GLuint index, GLuint v0) {
    return GlewMock2::getMock()->gl_VertexAttribI1ui(index, v0);
}

PFNGLVERTEXATTRIBI1UIPROC __glewVertexAttribI1ui = mockgl_VertexAttribI1ui;

void mockgl_VertexAttribI1uiv(GLuint index, const GLuint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI1uiv(index, v0);
}

PFNGLVERTEXATTRIBI1UIVPROC __glewVertexAttribI1uiv = mockgl_VertexAttribI1uiv;

void mockgl_VertexAttribI2i(GLuint index, GLint v0, GLint v1) {
    return GlewMock2::getMock()->gl_VertexAttribI2i(index, v0, v1);
}

PFNGLVERTEXATTRIBI2IPROC __glewVertexAttribI2i = mockgl_VertexAttribI2i;

void mockgl_VertexAttribI2iv(GLuint index, const GLint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI2iv(index, v0);
}

PFNGLVERTEXATTRIBI2IVPROC __glewVertexAttribI2iv = mockgl_VertexAttribI2iv;

void mockgl_VertexAttribI2ui(GLuint index, GLuint v0, GLuint v1) {
    return GlewMock2::getMock()->gl_VertexAttribI2ui(index, v0, v1);
}

PFNGLVERTEXATTRIBI2UIPROC __glewVertexAttribI2ui = mockgl_VertexAttribI2ui;

void mockgl_VertexAttribI2uiv(GLuint index, const GLuint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI2uiv(index, v0);
}

PFNGLVERTEXATTRIBI2UIVPROC __glewVertexAttribI2uiv = mockgl_VertexAttribI2uiv;

void mockgl_VertexAttribI3i(GLuint index, GLint v0, GLint v1, GLint v2) {
    return GlewMock2::getMock()->gl_VertexAttribI3i(index, v0, v1, v2);
}

PFNGLVERTEXATTRIBI3IPROC __glewVertexAttribI3i = mockgl_VertexAttribI3i;

void mockgl_VertexAttribI3iv(GLuint index, const GLint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI3iv(index, v0);
}

PFNGLVERTEXATTRIBI3IVPROC __glewVertexAttribI3iv = mockgl_VertexAttribI3iv;

void mockgl_VertexAttribI3ui(GLuint index, GLuint v0, GLuint v1, GLuint v2) {
    return GlewMock2::getMock()->gl_VertexAttribI3ui(index, v0, v1, v2);
}

PFNGLVERTEXATTRIBI3UIPROC __glewVertexAttribI3ui = mockgl_VertexAttribI3ui;

void mockgl_VertexAttribI3uiv(GLuint index, const GLuint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI3uiv(index, v0);
}

PFNGLVERTEXATTRIBI3UIVPROC __glewVertexAttribI3uiv = mockgl_VertexAttribI3uiv;

void mockgl_VertexAttribI4bv(GLuint index, const GLbyte* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4bv(index, v0);
}

PFNGLVERTEXATTRIBI4BVPROC __glewVertexAttribI4bv = mockgl_VertexAttribI4bv;

void mockgl_VertexAttribI4i(GLuint index, GLint v0, GLint v1, GLint v2, GLint v3) {
    return GlewMock2::getMock()->gl_VertexAttribI4i(index, v0, v1, v2, v3);
}

PFNGLVERTEXATTRIBI4IPROC __glewVertexAttribI4i = mockgl_VertexAttribI4i;

void mockgl_VertexAttribI4iv(GLuint index, const GLint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4iv(index, v0);
}

PFNGLVERTEXATTRIBI4IVPROC __glewVertexAttribI4iv = mockgl_VertexAttribI4iv;

void mockgl_VertexAttribI4sv(GLuint index, const GLshort* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4sv(index, v0);
}

PFNGLVERTEXATTRIBI4SVPROC __glewVertexAttribI4sv = mockgl_VertexAttribI4sv;

void mockgl_VertexAttribI4ubv(GLuint index, const GLubyte* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4ubv(index, v0);
}

PFNGLVERTEXATTRIBI4UBVPROC __glewVertexAttribI4ubv = mockgl_VertexAttribI4ubv;

void mockgl_VertexAttribI4ui(GLuint index, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    return GlewMock2::getMock()->gl_VertexAttribI4ui(index, v0, v1, v2, v3);
}

PFNGLVERTEXATTRIBI4UIPROC __glewVertexAttribI4ui = mockgl_VertexAttribI4ui;

void mockgl_VertexAttribI4uiv(GLuint index, const GLuint* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4uiv(index, v0);
}

PFNGLVERTEXATTRIBI4UIVPROC __glewVertexAttribI4uiv = mockgl_VertexAttribI4uiv;

void mockgl_VertexAttribI4usv(GLuint index, const GLushort* v0) {
    return GlewMock2::getMock()->gl_VertexAttribI4usv(index, v0);
}

PFNGLVERTEXATTRIBI4USVPROC __glewVertexAttribI4usv = mockgl_VertexAttribI4usv;

void mockgl_VertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) {
    return GlewMock2::getMock()->gl_VertexAttribIPointer(index, size, type, stride, pointer);
}

PFNGLVERTEXATTRIBIPOINTERPROC __glewVertexAttribIPointer = mockgl_VertexAttribIPointer;

void mockgl_DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount) {
    return GlewMock2::getMock()->gl_DrawArraysInstanced(mode, first, count, primcount);
}

PFNGLDRAWARRAYSINSTANCEDPROC __glewDrawArraysInstanced = mockgl_DrawArraysInstanced;

void mockgl_DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei primcount) {
    return GlewMock2::getMock()->gl_DrawElementsInstanced(mode, count, type, indices, primcount);
}

PFNGLDRAWELEMENTSINSTANCEDPROC __glewDrawElementsInstanced = mockgl_DrawElementsInstanced;

void mockgl_PrimitiveRestartIndex(GLuint buffer) {
    return GlewMock2::getMock()->gl_PrimitiveRestartIndex(buffer);
}

PFNGLPRIMITIVERESTARTINDEXPROC __glewPrimitiveRestartIndex = mockgl_PrimitiveRestartIndex;

void mockgl_TexBuffer(GLenum target, GLenum internalFormat, GLuint buffer) {
    return GlewMock2::getMock()->gl_TexBuffer(target, internalFormat, buffer);
}

PFNGLTEXBUFFERPROC __glewTexBuffer = mockgl_TexBuffer;

void mockgl_FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    return GlewMock2::getMock()->gl_FramebufferTexture(target, attachment, texture, level);
}

PFNGLFRAMEBUFFERTEXTUREPROC __glewFramebufferTexture = mockgl_FramebufferTexture;

void mockgl_GetBufferParameteri64v(GLenum target, GLenum value, GLint64* data) {
    return GlewMock2::getMock()->gl_GetBufferParameteri64v(target, value, data);
}

PFNGLGETBUFFERPARAMETERI64VPROC __glewGetBufferParameteri64v = mockgl_GetBufferParameteri64v;

void mockgl_GetInteger64i_v(GLenum pname, GLuint index, GLint64* data) {
    return GlewMock2::getMock()->gl_GetInteger64i_v(pname, index, data);
}

PFNGLGETINTEGER64I_VPROC __glewGetInteger64i_v = mockgl_GetInteger64i_v;

void mockgl_VertexAttribDivisor(GLuint index, GLuint divisor) {
    return GlewMock2::getMock()->gl_VertexAttribDivisor(index, divisor);
}

PFNGLVERTEXATTRIBDIVISORPROC __glewVertexAttribDivisor = mockgl_VertexAttribDivisor;

void mockgl_BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) {
    return GlewMock2::getMock()->gl_BlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

PFNGLBLENDEQUATIONSEPARATEIPROC __glewBlendEquationSeparatei = mockgl_BlendEquationSeparatei;

void mockgl_BlendEquationi(GLuint buf, GLenum mode) {
    return GlewMock2::getMock()->gl_BlendEquationi(buf, mode);
}

PFNGLBLENDEQUATIONIPROC __glewBlendEquationi = mockgl_BlendEquationi;

void mockgl_BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
    return GlewMock2::getMock()->gl_BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

PFNGLBLENDFUNCSEPARATEIPROC __glewBlendFuncSeparatei = mockgl_BlendFuncSeparatei;

void mockgl_BlendFunci(GLuint buf, GLenum src, GLenum dst) {
    return GlewMock2::getMock()->gl_BlendFunci(buf, src, dst);
}

PFNGLBLENDFUNCIPROC __glewBlendFunci = mockgl_BlendFunci;

void mockgl_MinSampleShading(GLclampf value) {
    return GlewMock2::getMock()->gl_MinSampleShading(value);
}

PFNGLMINSAMPLESHADINGPROC __glewMinSampleShading = mockgl_MinSampleShading;

unsigned int mockgl_GetGraphicsResetStatus() {
    return GlewMock2::getMock()->gl_GetGraphicsResetStatus();
}

PFNGLGETGRAPHICSRESETSTATUSPROC __glewGetGraphicsResetStatus = mockgl_GetGraphicsResetStatus;

void mockgl_GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, GLvoid* pixels) {
    return GlewMock2::getMock()->gl_GetnCompressedTexImage(target, lod, bufSize, pixels);
}

PFNGLGETNCOMPRESSEDTEXIMAGEPROC __glewGetnCompressedTexImage = mockgl_GetnCompressedTexImage;

void mockgl_GetnTexImage(GLenum tex, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid* pixels) {
    return GlewMock2::getMock()->gl_GetnTexImage(tex, level, format, type, bufSize, pixels);
}

PFNGLGETNTEXIMAGEPROC __glewGetnTexImage = mockgl_GetnTexImage;

void mockgl_GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble* params) {
    return GlewMock2::getMock()->gl_GetnUniformdv(program, location, bufSize, params);
}

PFNGLGETNUNIFORMDVPROC __glewGetnUniformdv = mockgl_GetnUniformdv;

void mockgl_BindBufferARB(GLenum target, GLuint buffer) {
    return GlewMock2::getMock()->gl_BindBufferARB(target, buffer);
}

PFNGLBINDBUFFERARBPROC __glewBindBufferARB = mockgl_BindBufferARB;

void mockgl_BufferDataARB(GLenum target, GLsizeiptrARB size, const void* data, GLenum usage) {
    return GlewMock2::getMock()->gl_BufferDataARB(target, size, data, usage);
}

PFNGLBUFFERDATAARBPROC __glewBufferDataARB = mockgl_BufferDataARB;

void mockgl_BufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void* data) {
    return GlewMock2::getMock()->gl_BufferSubDataARB(target, offset, size, data);
}

PFNGLBUFFERSUBDATAARBPROC __glewBufferSubDataARB = mockgl_BufferSubDataARB;

void mockgl_DeleteBuffersARB(GLsizei n, const GLuint* buffers) {
    return GlewMock2::getMock()->gl_DeleteBuffersARB(n, buffers);
}

PFNGLDELETEBUFFERSARBPROC __glewDeleteBuffersARB = mockgl_DeleteBuffersARB;

void mockgl_GenBuffersARB(GLsizei n, GLuint* buffers) {
    return GlewMock2::getMock()->gl_GenBuffersARB(n, buffers);
}

PFNGLGENBUFFERSARBPROC __glewGenBuffersARB = mockgl_GenBuffersARB;

void mockgl_GetBufferParameterivARB(GLenum target, GLenum pname, GLint* params) {
    return GlewMock2::getMock()->gl_GetBufferParameterivARB(target, pname, params);
}

PFNGLGETBUFFERPARAMETERIVARBPROC __glewGetBufferParameterivARB = mockgl_GetBufferParameterivARB;

void mockgl_GetBufferPointervARB(GLenum target, GLenum pname, void** params) {
    return GlewMock2::getMock()->gl_GetBufferPointervARB(target, pname, params);
}

PFNGLGETBUFFERPOINTERVARBPROC __glewGetBufferPointervARB = mockgl_GetBufferPointervARB;

void mockgl_GetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void* data) {
    return GlewMock2::getMock()->gl_GetBufferSubDataARB(target, offset, size, data);
}

PFNGLGETBUFFERSUBDATAARBPROC __glewGetBufferSubDataARB = mockgl_GetBufferSubDataARB;

unsigned char mockgl_IsBufferARB(GLuint buffer) {
    return GlewMock2::getMock()->gl_IsBufferARB(buffer);
}

PFNGLISBUFFERARBPROC __glewIsBufferARB = mockgl_IsBufferARB;

void* mockgl_MapBufferARB(GLenum target, GLenum access) {
    return GlewMock2::getMock()->gl_MapBufferARB(target, access);
}

PFNGLMAPBUFFERARBPROC __glewMapBufferARB = mockgl_MapBufferARB;

unsigned char mockgl_UnmapBufferARB(GLenum target) {
    return GlewMock2::getMock()->gl_UnmapBufferARB(target);
}

PFNGLUNMAPBUFFERARBPROC __glewUnmapBufferARB = mockgl_UnmapBufferARB;

void mockgl_BindVertexArray(GLuint array) {
    GlewMock2::getMock()->gl_BindVertexArray(array);
}

PFNGLBINDVERTEXARRAYPROC __glewBindVertexArray = mockgl_BindVertexArray;

void mockgl_DeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    GlewMock2::getMock()->gl_DeleteVertexArrays(n, arrays);
}

PFNGLDELETEVERTEXARRAYSPROC __glewDeleteVertexArrays = mockgl_DeleteVertexArrays;

void mockgl_GenVertexArrays(GLsizei n, GLuint* arrays) {

}

PFNGLGENVERTEXARRAYSPROC __glewGenVertexArrays = mockgl_GenVertexArrays;

GLboolean mockgl_isVertexArray(GLuint array) {
    return GlewMock2::getMock()->gl_IsVertexArray(array);
}

PFNGLISVERTEXARRAYPROC __glewIsVertexArray = mockgl_isVertexArray;

GLenum glewInit() {
    return GlewMock2::getMock()->glew_Init();
}

GLboolean glewIsSupported(const char* name) {
    return GlewMock2::getMock()->glew_IsSupported(name);
}

GLboolean glewGetExtension(const char* name) {
    return GlewMock2::getMock()->glew_GetExtension(name);
}

const GLubyte* glewGetErrorString(GLenum error) {
    return GlewMock2::getMock()->glew_GetErrorString(error);
}

const GLubyte* glewGetString(GLenum name) {
    return GlewMock2::getMock()->glew_GetString(name);
}
