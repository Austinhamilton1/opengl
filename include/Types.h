#pragma once

#include <glad/glad.h>

namespace gl {
    //initializing buffer draw method
    enum BufferDrawType {
        STATIC,
        DYNAMIC,
    };

    //results of compiling a shader
    enum CompileResult {
        SUCCESS,
        VERTEX_COMPILATION_ERROR,
        FRAGMENT_COMPILATION_ERROR,
        PROGRAM_LINK_ERROR,
    };

    //initializing texture wrapping
    enum TextureWrapping {
        REPEAT,
        MIRROR,
        CLAMP_TO_EDGE,
        CLAMP_TO_BORDER,
    };

    //initializing texture filtering
    enum TextureFiltering {
        NEAREST,
        LINEAR,
        NEAREST_NEAREST,
        NEAREST_LINEAR,
        LINEAR_NEAREST,
        LINEAR_LINEAR,
    };

    //initializing color types
    enum ColorType {
        RGB,
        RGBA,
    };

    //convert c++ types to gl type
    template<typename T> GLenum getGLType();
    template<> inline GLenum getGLType<float>() { return GL_FLOAT; };
    template<> inline GLenum getGLType<int>() { return GL_INT; };
    template<> inline GLenum getGLType<unsigned int>() { return GL_UNSIGNED_INT; };

    //convert type enums to gl type
    template<typename T> GLenum getGLType(unsigned int);
    
    //convert BufferDrawType to GLenum
    template<> inline GLenum getGLType<BufferDrawType>(unsigned int type) {
        if(type == STATIC)
            return GL_STATIC_DRAW;
        if(type == DYNAMIC)
            return GL_DYNAMIC_DRAW;
        return 0;
    }

    //convert TextureWrapping to GLenum
    template<> inline GLenum getGLType<TextureWrapping>(unsigned int type) {
        if(type == REPEAT)
            return GL_REPEAT;
        if(type == MIRROR)
            return GL_MIRRORED_REPEAT;
        if(type == CLAMP_TO_EDGE)
            return GL_CLAMP_TO_EDGE;
        if(type == CLAMP_TO_BORDER)
            return GL_CLAMP_TO_BORDER;
        return 0;
    }

    //convert TextureFiltering to GLenum
    template<> inline GLenum getGLType<TextureFiltering>(unsigned int type) {
        if(type == NEAREST)
            return GL_NEAREST;
        if(type == LINEAR)
            return GL_LINEAR;
        if(type == NEAREST_NEAREST)
            return GL_NEAREST_MIPMAP_NEAREST;
        if(type == NEAREST_LINEAR)
            return GL_NEAREST_MIPMAP_LINEAR;
        if(type == LINEAR_NEAREST)
            return GL_LINEAR_MIPMAP_NEAREST;
        if(type == LINEAR_LINEAR)
            return GL_LINEAR_MIPMAP_LINEAR;
        return 0;
    }

    //convert ColorType to GLenum
    template<> inline GLenum getGLType<ColorType>(unsigned int type) {
        if(type == RGB)
            return GL_RGB;
        if(type == RGBA)
            return GL_RGBA;
        return 0;
    }
}