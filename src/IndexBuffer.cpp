#include "IndexBuffer.h"

#include <glad/glad.h>
#include <cstdarg>

//create the buffer
gl::IndexBuffer::IndexBuffer(gl::BufferType type) {
    glGenBuffers(1, &id);
    this->type = type;
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
        int value = va_arg(args, int);
        data.push_back(value);
    }
    va_end(args);
}

//send buffer data to the GPU
void gl::IndexBuffer::sendData() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    if(type == STATIC)
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
    else if(type == DYNAMIC)
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_DYNAMIC_DRAW);
}