#pragma once

#include "Types.h"

#include <vector>

namespace gl {
    class IndexBuffer {
        private:
            unsigned int id;
            BufferType type;
            std::vector<int> data;

        public:
            IndexBuffer(BufferType type);
            ~IndexBuffer();

            void addData(int count, ...);
            void sendData();
    };
}