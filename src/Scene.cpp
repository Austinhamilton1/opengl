#include "Scene.h"

//get the object associated with the key
std::shared_ptr<gl::GraphicsObject> gl::Scene::get(std::string key) {
    if(objects.find(key) == objects.end())
        return nullptr;
    return objects[key];
}

//set the object associated with the key
void gl::Scene::set(std::string key, std::shared_ptr<gl::GraphicsObject> object) {
    objects[key] = object;
}

//add a render callback to the scene
void gl::Scene::addCallback(void (*callback)(Scene *)) {
    renderCallbacks.push_back(callback);
}

//render all the objects in the scene to the screen
void gl::Scene::render() {
    //call any render callbacks
    for(auto& callback : renderCallbacks)
        callback(this);

    //render all the objects in the scene
    for(const auto& pair : objects)
        pair.second->render();
}