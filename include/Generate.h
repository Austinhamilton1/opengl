#pragma once

#include "VertexBuffer.h"

#include <memory>
#include <glm/glm.hpp>

namespace gl {
    class Generate {
    public:
        static std::shared_ptr<VertexBuffer> plane(float width, float height, glm::vec3 color, glm::vec2 tex);
        static std::shared_ptr<VertexBuffer> cube(float width, float height, float depth, glm::vec3 color, glm::vec2 tex);
    };
}