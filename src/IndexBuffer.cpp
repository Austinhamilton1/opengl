#include "IndexBuffer.h"

//create the buffer
gl::IndexBuffer::IndexBuffer(BufferDrawType drawType) {
    glGenBuffers(1, &id);
    this->drawType = drawType;
}

//delete the buffer
gl::IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &id);
}

//add data to the buffer
void gl::IndexBuffer::addData(int count, ...) {
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; i++) {
        double value = va_arg(args, unsigned int);
        data.push_back(value);
    }
    va_end(args);
}

//send buffer data to the GPU
void gl::IndexBuffer::staticAllocate() {
    //bind the buffer element
    select();
    
    //send the data to the GPU
    GLenum usage = getGLType<BufferDrawType>(drawType);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(), data.data(), usage);
    
    //unbind the buffer
    deselect();
}

//select the buffer
void gl::IndexBuffer::select() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

//deselect the buffer
void gl::IndexBuffer::deselect() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}