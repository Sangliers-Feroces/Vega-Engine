/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** vulkan ftw
*/

#ifndef _GLLOADER_H
#define _GLLOADER_H

#include "gl_enums.h"

#define glxgetprocaddressarb glXGetProcAddressARB

void* glxgetprocaddressarb(const char*);

void load_gl_fun(void);

#ifndef GL_LOADER_IMPLEMENTATION

extern void (*p_glgenvertexarrays)(glsizei n, gluint *arrays);
extern void (*p_glbindvertexarray)(gluint array);
extern void (*p_glgenbuffers)(glsizei n, gluint *buffers);
extern void (*p_glbindbuffer)(glenum target, gluint buffer);
extern void (*p_glbufferdata)(glenum target, glsizeiptr size,
glvoid *data, glenum usage);
extern void (*p_glclearcolor)(glfloat red, glfloat green,
glfloat blue, glfloat alpha);

extern void (*p_glenable)(glenum cap);
extern void (*p_gldepthfunc)(glenum cap);
extern void (*p_glclear)(glbitfield mask);
extern void (*p_gluseprogram)(gluint program);
extern glint (*p_glgetuniformlocation)(gluint program, const glchar *name);
extern void (*p_gluniformmatrix4fv)(glint location, glsizei count,
glboolean transform, const glfloat *value);

extern void (*p_glenablevertexattribarray)(gluint index);
extern void (*p_gldisablevertexattribarray)(gluint index);
extern void (*p_glvertexattribpointer)(gluint index, glint size, glenum type,
glboolean normalized, glsizei stride, const glvoid *pointer);
extern void (*p_gldrawarrays)(glenum mode, glint first, glsizei count);

extern gluint (*p_glcreateshader)(glenum shader_type);
extern void (*p_glshadersource)(gluint shader, glsizei count,
const glchar **string, const glint *length);
extern void (*p_glcompileshader)(gluint shader);
extern void (*p_glgetshaderiv)(gluint shader, glenum pname, glint *params);
extern void (*p_glgetshaderinfolog)(gluint shader, glsizei max_length,
glsizei *length, glchar *info_log);
extern gluint (*p_glcreateprogram)(void);
extern void (*p_glattachshader)(gluint program, gluint shader);
extern void (*p_gllinkprogram)(gluint program);
extern void (*p_glgetprogramiv)(gluint program, glenum pname, glint *params);
extern void (*p_gldetachshader)(gluint program, gluint shader);
extern void (*p_gldeleteshader)(gluint shader);

extern void (*p_glgetintegerv)(glenum pname, glint *params);
extern void (*p_glgetintegeri_v)(glenum pname, gluint index, glint *params);

#define glGenVertexArrays p_glgenvertexarrays
#define glBindVertexArray p_glbindvertexarray
#define glGenBuffers p_glgenbuffers
#define glBindBuffer p_glbindbuffer
#define glBufferData p_glbufferdata
#define glClearColor p_glclearcolor

#define glEnable p_glenable
#define glDepthFunc p_gldepthfunc
#define glClear p_glclear
#define glUseProgram p_gluseprogram
#define glGetUniformLocation p_glgetuniformlocation
#define glUniformMatrix4fv p_gluniformmatrix4fv

#define glEnableVertexAttribArray p_glenablevertexattribarray
#define glDisableVertexAttribArray p_gldisablevertexattribarray
#define glVertexAttribPointer p_glvertexattribpointer
#define glDrawArrays p_gldrawarrays

#define glCreateShader p_glcreateshader
#define glShaderSource p_glshadersource
#define glCompileShader p_glcompileshader
#define glGetShaderiv p_glgetshaderiv
#define glGetShaderInfoLog p_glgetshaderinfolog
#define glCreateProgram p_glcreateprogram
#define glAttachShader p_glattachshader
#define glLinkProgram p_gllinkprogram
#define glGetProgramiv p_glgetprogramiv
#define glDetachShader p_gldetachshader
#define glDeleteShader p_gldeleteshader

#define glGetIntegerv p_glgetintegerv
#define glGetIntegeri_v p_glgetintegeri_v

#endif

#endif
