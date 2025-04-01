#pragma once

#include "Types.h"

#include <glad/glad.h>
#include <vector>
#include <cstdarg>
#include <unordered_map>
#include <memory>

namespace gl {
    class IndexBuffer {
    private:
        unsigned int id;
        BufferDrawType drawType;
        std::vector<unsigned int> data;

    public:
        IndexBuffer(BufferDrawType);
        ~IndexBuffer();

        void addData(int count, ...);
        void staticAllocate();
        void select();
        void deselect();

        unsigned int getElementCount() { return data.size(); };
    };
}