#include "VertexBuffer.h"

#include <glad/glad.h>
#include <cstdarg>

//create the buffer
gl::VertexBuffer::VertexBuffer(gl::BufferType type) {
    glGenBuffers(1, &id);
    this->type = type;
}

//delete the buffer
gl::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}

//add data to the buffer
void gl::VertexBuffer::addData(int count, ...) {
    va_list args;
    va_start(args, count);
    for(int i = 0; i < count; i++) {
        double value = va_arg(args, double);
        data.push_back(static_cast<float>(value));
    }
    va_end(args);
}

//send buffer data to the GPU
void gl::VertexBuffer::sendData() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    if(type == STATIC)
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
    else if(type == DYNAMIC)
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_DYNAMIC_DRAW);
}