/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#include "gl_loader_implementation.h"

#include "headers.h"

#include "global_shenanigans.h"

const void (*p_glgenvertexarrays)(glsizei n, gluint *arrays);
const void (*p_glbindvertexarray)(gluint array);
const void (*p_glgenbuffers)(glsizei n, gluint *buffers);
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

const gluint (*p_glcreateshader)(glenum shader_type);
const void (*p_glshadersource)(gluint shader, glsizei count,
const glchar **string, const glint *length);
const void (*p_glcompileshader)(gluint shader);
const void (*p_glgetshaderiv)(gluint shader, glenum pname, glint *params);
const void (*p_glgetshaderinfolog)(gluint shader, glsizei max_length,
glsizei *length, glchar *info_log);
const gluint (*p_glcreateprogram)(void);
const void (*p_glattachshader)(gluint program, gluint shader);
const void (*p_gllinkprogram)(gluint program);
const void (*p_glgetprogramiv)(gluint program, glenum pname, glint *params);
const void (*p_gldetachshader)(gluint program, gluint shader);
const void (*p_gldeleteshader)(gluint shader);

const void (*p_glgetintegerv)(glenum pname, glint *params);
const void (*p_glgetintegeri_v)(glenum pname, gluint index, glint *params);

static void load_1(void)
{
    p_glgenvertexarrays = glXGetProcAddressARB("glGenVertexArrays");
    p_glbindvertexarray = glXGetProcAddressARB("glBindVertexArray");
    p_glgenbuffers = glXGetProcAddressARB("glGenBuffers");
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
}

static void load_3(void)
{
    p_glcreateshader = glXGetProcAddressARB("glCreateShader");
    p_glshadersource = glXGetProcAddressARB("glShaderSource");
    p_glcompileshader = glXGetProcAddressARB("glCompileShader");
    p_glgetshaderiv = glXGetProcAddressARB("glGetShaderiv");
    p_glgetshaderinfolog = glXGetProcAddressARB("glGetShaderInfoLog");
    p_glcreateprogram = glXGetProcAddressARB("glCreateProgram");
    p_glattachshader = glXGetProcAddressARB("glAttachShader");
    p_gllinkprogram = glXGetProcAddressARB("glLinkProgram");
    p_glgetprogramiv = glXGetProcAddressARB("glGetProgramiv");
    p_gldetachshader = glXGetProcAddressARB("glDetachShader");
    p_gldeleteshader = glXGetProcAddressARB("glDeleteShader");
}

void load_gl_fun(void)
{
    load_1();
    load_2();
    load_3();
    p_glgetintegerv = glXGetProcAddressARB("glGetIntegerv");
    p_glgetintegeri_v = glXGetProcAddressARB("glGetIntegeri_v");
}
