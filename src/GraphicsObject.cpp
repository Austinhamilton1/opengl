#include "GraphicsObject.h"

void gl::GraphicsObject::render() {
    //call all the render callbacks
    for(auto& callback : renderCallbacks) {
        callback(this);
    }

    //use the shader if it is initialized
    if(shader != nullptr)
        shader->use();

    //use the index buffer if it is defined, otherwise use the vertex buffer
    if(indexBuffer != nullptr)
        indexBuffer->render();
    else if(vertexBuffer != nullptr)
        vertexBuffer->render();
}

//add a render callback to the object
void gl::GraphicsObject::addCallback(void (*callback)(GraphicsObject *)) {
    renderCallbacks.push_back(callback);
}