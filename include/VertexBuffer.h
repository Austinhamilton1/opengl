#pragma once

#include "Types.h"

#include <vector>

namespace gl {
    class VertexBuffer {
        private:
            unsigned int id;
            BufferType type;
            std::vector<float> data;

        public:
            VertexBuffer(BufferType type);
            ~VertexBuffer();

            void addData(int count, ...);
            void sendData();
    };
}