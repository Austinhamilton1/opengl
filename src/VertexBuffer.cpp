#include "VertexBuffer.h"

//create the buffer
gl::VertexBuffer::VertexBuffer(gl::BufferDrawType drawType) {
    glGenBuffers(1, &id);
    this->drawType = drawType;
    elementSize = 0;
    //indexes = nullptr;
}

//delete the buffer
gl::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

//add data to the buffer
void gl::VertexBuffer::addData(int elementSize, int count, ...) {
    this->elementSize = elementSize;
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; i++) {
        double value = va_arg(args, double);
        data.push_back(static_cast<float>(value));
    }
    va_end(args);
}

//send buffer data to the GPU
void gl::VertexBuffer::staticAllocate() {
    //bind the buffer element
    select();
    
    //send the data to the GPU
    GLenum usage = getGLType<BufferDrawType>(drawType);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), usage);

    //allocate the index buffer if it exists
    if(indexes != nullptr) {
        indexes->staticAllocate();
    }
    
    //unbind the buffer
    deselect();
}

//set the layout of a vertex attribute
void gl::VertexBuffer::setLayout(unsigned int location, unsigned int size, size_t stride, size_t offset) {
    //set the attribute
    VertexAttribute attrib;
    attrib.index = location;
    attrib.elementSize = size;
    attrib.type = getGLType<float>();
    attrib.isNormalized = GL_FALSE;
    attrib.stride = stride;
    attrib.offset = offset;

    //add the attribute
    attributes.push_back(attrib);
}

//select the buffer for usage
void gl::VertexBuffer::select() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

//deselect the buffer 
void gl::VertexBuffer::deselect() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//enable the vertex buffer attributes
void gl::VertexBuffer::enableAttributes() {
    for(auto& attrib : attributes) {
        glVertexAttribPointer(attrib.index, attrib.elementSize, attrib.type, attrib.isNormalized, attrib.stride, (void *)attrib.offset);
        glEnableVertexAttribArray(attrib.index);
    }
}

//set a texture unit
void gl::VertexBuffer::setTexture(int key, std::shared_ptr<gl::Texture> texture) {
    textures[key] = texture;
}

//get a texture unit
std::shared_ptr<gl::Texture> gl::VertexBuffer::getTexture(int key) {
    if(textures.find(key) == textures.end())
        return nullptr;
    return textures[key];
}