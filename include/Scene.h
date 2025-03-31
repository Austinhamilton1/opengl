#pragma once

#include "GraphicsObject.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

namespace gl {
    class Scene {
    private:
        std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objects;
        std::vector<void (*)(Scene *)> renderCallbacks;

    public:
        Scene() {};
        ~Scene() {};

        std::shared_ptr<GraphicsObject> get(std::string key);
        void set(std::string key, std::shared_ptr<GraphicsObject> object);
        void addCallback(void (*callback)(Scene *));
        void render();
    };
}