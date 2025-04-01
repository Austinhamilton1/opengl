#include "GraphicsObject.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

void gl::GraphicsObject::render() {
    //call all the render callbacks
    for(auto& callback : renderCallbacks) {
        callback(this);
    }
}

//add a render callback to the object
void gl::GraphicsObject::addCallback(std::function<void(GraphicsObject *)> callback) {
    renderCallbacks.push_back(callback);
}

//allocate the data for the vertex buffer
void gl::GraphicsObject::allocateBuffers() {
    vertexBuffer->staticAllocate();
}

//transform the object with a transformation object
void gl::GraphicsObject::transform(glm::mat4 transformation) {
    referenceFrame = transformation;
}

//translate the object by a vector
void gl::GraphicsObject::translate(glm::vec3 translation) {
    glm::mat4 mat(1.0f);
    mat = glm::translate(mat, translation);
    referenceFrame = mat * referenceFrame;
}

//rotate the object by radians around a vector
void gl::GraphicsObject::rotate(float radians, glm::vec3 axis) {
    glm::mat4 mat(1.0f);
    mat = glm::rotate(mat, radians, axis);
    referenceFrame = mat * referenceFrame;
}

//scale the object by a scale factor
void gl::GraphicsObject::scale(glm::vec3 scaleFactor) {
    glm::mat4 mat(1.0f);
    mat = glm::scale(mat, scaleFactor);
    referenceFrame = mat * referenceFrame;
}

//get the position of the object
glm::vec3 gl::GraphicsObject::getPosition() {
    return referenceFrame[3];
}

//set the position of the object
void gl::GraphicsObject::setPosition(glm::vec3 position) {
    referenceFrame[3] = glm::vec4(position, 1.0f);
}