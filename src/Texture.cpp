#include "Texture.h"

#include <glad/glad.h>
#include "stb_image.h"

gl::Texture::Texture(TextureWrapping wrapType, TextureFiltering filterType) {
    this->wrapType = wrapType;
    this->filterType = filterType;

    //generate the texture
    glGenTextures(1, &texture);

    //set the options for the texture
    GLenum wrapParam = getGLType<TextureWrapping>(wrapType);
    GLenum filterParam = getGLType<TextureFiltering>(filterType);
    select();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam);
    deselect();
}

gl::Texture::~Texture() {
    glDeleteTextures(1, &texture);
}

//set the border color of the texture
void gl::Texture::setBorderColor(float r, float g, float b, float a) {
    float borderColor[] = {r, g, b, a};
    select();
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    deselect();
}

//load in texture data from an image file
void gl::Texture::loadImage(std::string filename, ColorType openGLColorType, ColorType fileColorType) {
    //read in the file data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    
    //add the data to the texture and generate mipmaps
    if(data) {
        GLenum internalFormat = getGLType<ColorType>(openGLColorType);
        GLenum format = getGLType<ColorType>(fileColorType);
        select();
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        deselect();
    }

    //free up the unecessary data
    stbi_image_free(data);
}

//use the texture when rendering
void gl::Texture::select() {
    glBindTexture(GL_TEXTURE_2D, texture);
}

void gl::Texture::deselect() {
    glBindTexture(GL_TEXTURE_2D, 0);
}