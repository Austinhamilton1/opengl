#pragma once

#include "Types.h"

#include <glad/glad.h>
#include <vector>
#include <cstdarg>
#include <cstddef>

namespace gl {
    class VertexBuffer {
    private:
        unsigned int id, VAO;
        BufferDrawType drawType;
        int elementSize;
        std::vector<float> data;

    public:
        VertexBuffer(BufferDrawType);
        ~VertexBuffer();

        void addData(int elementSize, int count, ...);
        void sendData();
        void setLayout(int location, int size, size_t stride, size_t offset);
        void render();
    };
}