#include "GraphicsObject.h"

void gl::GraphicsObject::render() {
    //call all the render callbacks
    for(auto& callback : renderCallbacks) {
        callback(this);
    }

    //use the shader if it is initialized
    if(shader != nullptr)
        shader->use();

    //use the vertex buffer if it is defined
    if(vertexBuffer != nullptr)
        vertexBuffer->render();
}

//add a render callback to the object
void gl::GraphicsObject::addCallback(std::function<void(GraphicsObject *)> callback) {
    renderCallbacks.push_back(callback);
}