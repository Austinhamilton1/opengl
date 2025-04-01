#pragma once

#include "Types.h"

#include <string>

namespace gl {
    class Texture {
    private:
        unsigned int texture;
        TextureWrapping wrapType;
        TextureFiltering filterType;

    public:
        Texture(TextureWrapping wrapType, TextureFiltering filterType);
        ~Texture();

        void setBorderColor(float r, float g, float b, float a);
        void loadImage(std::string filename, ColorType openGLColorType, ColorType fileColorType);
        void select();
        void deselect();
    };
}