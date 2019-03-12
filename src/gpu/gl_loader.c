/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "gl_loader_implementation.h"

#include "headers.h"

#include "global_shenanigans.h"

const glenum (*p_glgeterror)(void);
const void (*p_glgenvertexarrays)(glsizei n, gluint *arrays);
const void (*p_gldeletevertexarrays)(glsizei n, const gluint *arrays);
const void (*p_glbindvertexarray)(gluint array);
const void (*p_glgenbuffers)(glsizei n, gluint *buffers);
const void (*p_gldeletebuffers)(glsizei n, const gluint *buffers);
const void (*p_glbindbuffer)(glenum target, gluint buffer);
const void (*p_glbufferdata)(glenum target, glsizeiptr size,
const glvoid *data, glenum usage);
const void (*p_glclearcolor)(glfloat red, glfloat green,
glfloat blue, glfloat alpha);

const void (*p_glenable)(glenum cap);
const void (*p_gldepthfunc)(glenum cap);
const void (*p_glclear)(glbitfield mask);
const void (*p_gluseprogram)(gluint program);
const glint (*p_glgetuniformlocation)(gluint program, const glchar *name);
const void (*p_gluniformmatrix4fv)(glint location, glsizei count,
glboolean transform, const glfloat *value);

const void (*p_glenablevertexattribarray)(gluint index);
const void (*p_gldisablevertexattribarray)(gluint index);
const void (*p_glvertexattribpointer)(gluint index, glint size, glenum type,
glboolean normalized, glsizei stride, const glvoid *pointer);
const void (*p_gldrawarrays)(glenum mode, glint first, glsizei count);
const void (*p_gluniform1f)(glint location, float value);
const void (*p_gluniform2fv)(glint location, glsizei count,
const glfloat *value);
const void (*p_glactivetexture)(glenum texture);

const gluint (*p_glcreateshader)(glenum shader_type);
const void (*p_glshadersource)(gluint shader, glsizei count,
const glchar **string, const glint *length);
const void (*p_glcompileshader)(gluint shader);
const void (*p_glgetshaderiv)(gluint shader, glenum pname, glint *params);
const void (*p_glgetshaderinfolog)(gluint shader, glsizei max_length,
glsizei *length, glchar *info_log);
const void (*p_glgetprograminfolog)(gluint shader, glsizei max_length,
glsizei *length, glchar *info_log);
const gluint (*p_glcreateprogram)(void);
const void (*p_glattachshader)(gluint program, gluint shader);
const void (*p_gllinkprogram)(gluint program);
const void (*p_glgetprogramiv)(gluint program, glenum pname, glint *params);
const void (*p_gldetachshader)(gluint program, gluint shader);
const void (*p_gldeleteshader)(gluint shader);
const void (*p_gldeleteprogram)(gluint program);
const void (*p_glfinish)(void);

const void (*p_glgentextures)(glsizei n, gluint *textures);
const void (*p_gldeletetextures)(glsizei n, const gluint *textures);
const void (*p_glbindtexture)(glenum target, gluint texture);
const void (*p_gltexparameteri)(glenum target, glenum pname, glint param);
const void (*p_glteximage2d)(glenum target, glint level, glint internalformat,
glsizei width, glsizei height, glint border, glenum format, glenum type,
const glvoid *data);
const void (*p_glbindimagetexture)(gluint unit, gluint texture, glint level,
glboolean layered, glint layer, glenum access, glenum format);
const void (*p_gldispatchcompute)(gluint num_groups_x, gluint num_groups_y,
gluint num_groups_z);
const void (*p_glmemorybarrier)(glbitfield barriers);
const void (*p_glgetteximage)(glenum target, glint level, glenum format,
glenum type, glvoid *pixels);

const void (*p_glgetintegerv)(glenum pname, glint *params);
const void (*p_glgetintegeri_v)(glenum pname, gluint index, glint *params);

static void load_1(void)
{
    p_glgeterror = glXGetProcAddressARB("glGetError");
    p_glgenvertexarrays = glXGetProcAddressARB("glGenVertexArrays");
    p_gldeletevertexarrays = glXGetProcAddressARB("glDeleteVertexArrays");
    p_glbindvertexarray = glXGetProcAddressARB("glBindVertexArray");
    p_glgenbuffers = glXGetProcAddressARB("glGenBuffers");
    p_gldeletebuffers = glXGetProcAddressARB("glDeleteBuffers");
    p_glbindbuffer = glXGetProcAddressARB("glBindBuffer");
    p_glbufferdata = glXGetProcAddressARB("glBufferData");
    p_glclearcolor = glXGetProcAddressARB("glClearColor");
    p_glenable = glXGetProcAddressARB("glEnable");
    p_gldepthfunc = glXGetProcAddressARB("glDepthFunc");
    p_glclear = glXGetProcAddressARB("glClear");
    p_gluseprogram = glXGetProcAddressARB("glUseProgram");
    p_glgetuniformlocation = glXGetProcAddressARB("glGetUniformLocation");
    p_gluniformmatrix4fv = glXGetProcAddressARB("glUniformMatrix4fv");
}

static void load_2(void)
{
    p_glenablevertexattribarray =
    glXGetProcAddressARB("glEnableVertexAttribArray");
    p_gldisablevertexattribarray =
    glXGetProcAddressARB("glDisableVertexAttribArray");
    p_glvertexattribpointer = glXGetProcAddressARB("glVertexAttribPointer");
    p_gldrawarrays = glXGetProcAddressARB("glDrawArrays");
    p_gluniform1f = glXGetProcAddressARB("glUniform1f");
    p_gluniform2fv = glXGetProcAddressARB("glUniform2fv");
    p_glactivetexture = glXGetProcAddressARB("glActiveTexture");
}

static void load_3(void)
{
    p_glcreateshader = glXGetProcAddressARB("glCreateShader");
    p_glshadersource = glXGetProcAddressARB("glShaderSource");
    p_glcompileshader = glXGetProcAddressARB("glCompileShader");
    p_glgetshaderiv = glXGetProcAddressARB("glGetShaderiv");
    p_glgetshaderinfolog = glXGetProcAddressARB("glGetShaderInfoLog");
    p_glgetprograminfolog = glXGetProcAddressARB("glGetProgramInfoLog");
    p_glcreateprogram = glXGetProcAddressARB("glCreateProgram");
    p_glattachshader = glXGetProcAddressARB("glAttachShader");
    p_gllinkprogram = glXGetProcAddressARB("glLinkProgram");
    p_glgetprogramiv = glXGetProcAddressARB("glGetProgramiv");
    p_gldetachshader = glXGetProcAddressARB("glDetachShader");
    p_gldeleteshader = glXGetProcAddressARB("glDeleteShader");
    p_gldeleteprogram = glXGetProcAddressARB("glDeleteProgram");
    p_glfinish = glXGetProcAddressARB("glFinish");
}

static void load_4(void)
{
    p_glgentextures = glXGetProcAddressARB("glGenTextures");
    p_gldeletetextures = glXGetProcAddressARB("glDeleteTextures");
    p_glbindtexture = glXGetProcAddressARB("glBindTexture");
    p_gltexparameteri = glXGetProcAddressARB("glTexParameteri");
    p_glteximage2d = glXGetProcAddressARB("glTexImage2D");
    p_glbindimagetexture = glXGetProcAddressARB("glBindImageTexture");
    p_gldispatchcompute = glXGetProcAddressARB("glDispatchCompute");
    p_glmemorybarrier = glXGetProcAddressARB("glMemoryBarrier");
    p_glgetteximage = glXGetProcAddressARB("glGetTexImage");
}

void load_gl_fun(void)
{
    load_1();
    load_2();
    load_3();
    load_4();
    p_glgetintegerv = glXGetProcAddressARB("glGetIntegerv");
    p_glgetintegeri_v = glXGetProcAddressARB("glGetIntegeri_v");
}
