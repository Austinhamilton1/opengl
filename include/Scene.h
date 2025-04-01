#pragma once

#include "GraphicsObject.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>

namespace gl {
    class Scene {
    private:
        std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objects;
        std::vector<std::function<void(Scene *)>> renderCallbacks;

    public:
        Scene() {};
        ~Scene() {};

        std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> getObjects() { return objects; };
        std::shared_ptr<GraphicsObject> get(std::string key);
        void set(std::string key, std::shared_ptr<GraphicsObject> object);
        void addCallback(std::function<void(Scene *)> callback);
        void clear();
    };
}