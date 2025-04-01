#include "VertexBuffer.h"

//create the buffer
gl::VertexBuffer::VertexBuffer(gl::BufferDrawType drawType) {
    glGenBuffers(1, &id);
    glGenVertexArrays(1, &VAO);
    this->drawType = drawType;
    elementSize = 0;
}

//delete the buffer
gl::VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
    glDeleteVertexArrays(1, &VAO);
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
void gl::VertexBuffer::sendData() {
    //bind the vertex array object
    glBindVertexArray(VAO);

    //bind the buffer element
    glBindBuffer(GL_ARRAY_BUFFER, id);

    //send the data to the GPU
    GLenum usage = getGLType<BufferDrawType>(drawType);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), usage);
}

//set the layout of a vertex attribute
void gl::VertexBuffer::setLayout(int location, int size, size_t stride, size_t offset) {
    glBindVertexArray(VAO);
    glVertexAttribPointer(location, size, getGLType<float>(), GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(location);
}

//draw the buffer to the screen
void gl::VertexBuffer::render() {
    //bind the vertex array object
    glBindVertexArray(VAO);

    //calculate how many elements to draw
    int elementCount = data.size() / elementSize;

    //draw the data in the buffer
    glDrawArrays(GL_TRIANGLES, 0, elementCount);
}