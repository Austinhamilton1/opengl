#pragma once

#include "Types.h"

#include <glad/glad.h>
#include <vector>
#include <cstdarg>
#include <cstddef>

namespace gl {
    template<typename T> class Buffer {
    private:
        unsigned int id, VAO;
        BufferType type;
        BufferDrawType drawType;
        int elementSize;
        std::vector<T> data;

    public:
        //create the buffer
        Buffer<T>(BufferType type, BufferDrawType drawType) {
            glGenBuffers(1, &id);
            glGenVertexArrays(1, &VAO);
            this->type = type;
            this->drawType = drawType;
            elementSize = 0;
        };

        //create the buffer with a specified VAO
        Buffer<T>(unsigned int VAO, BufferType type, BufferDrawType drawType) {
            glGenBuffers(1, &id);
            this->VAO = VAO;
            this->type = type;
            this->drawType = drawType;
            elementSize = 0;
        }

        //delete the buffer
        ~Buffer<T>() {
            glDeleteBuffers(1, &id);
            glDeleteVertexArrays(1, &VAO);
        };

        unsigned int getVAO() { return VAO; };

        //add data to the buffer
        void addData(int elementSize, int count, ...) {
            this->elementSize = elementSize;
            va_list args;
            va_start(args, count);
            for(int i = 0; i < count; i++) {
                double value = va_arg(args, double);
                data.push_back(static_cast<T>(value));
            }
            va_end(args);
        };

        //send buffer data to the GPU
        void sendData() {
            //bind the vertex array object
            glBindVertexArray(VAO);

            //bind the correct buffer element
            GLenum target = getGLType<BufferType>(type);
            glBindBuffer(target, id);

            //send the data to the GPU
            GLenum usage = getGLType<BufferDrawType>(drawType);
            glBufferData(target, sizeof(T) * data.size(), data.data(), usage);
        };

        //set the layout of a vertex attribute
        void setLayout(int location, int size, size_t stride, size_t offset) {
            glBindVertexArray(VAO);
            glVertexAttribPointer(location, size, getGLType<T>(), GL_FALSE, stride, (void *)offset);
            glEnableVertexAttribArray(location);
        };

        //draw the buffer to the screen
        void render() {
            //bind the vertex array object
            glBindVertexArray(VAO);

            //calculate how many elements to draw
            int elementCount = data.size() / elementSize;

            //draw the data in the buffer
            if(type == VERTEX)
                glDrawArrays(GL_TRIANGLES, 0, elementCount);
            else if(type == INDEX)
                glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
        }
    };
}