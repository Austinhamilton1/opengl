#include "Renderer.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//initialize the renderer
gl::Renderer::Renderer(std::shared_ptr<Shader> shader) {
    this->shader = shader;
    glGenVertexArrays(1, &VAO);
}

//cleanup
void gl::Renderer::clear() {
    scene->clear();
}

//allocate the buffers in the scene
void gl::Renderer::allocate() {
    glBindVertexArray(VAO);
    auto objects = scene->getObjects();
    for(auto& object : objects) {
        object.second->allocateBuffers();
    }
    glBindVertexArray(0);
}

//render a graphics object to the screen
void gl::Renderer::renderObject(std::shared_ptr<GraphicsObject> object) {
    //send the object reference frame to the shader
    glm::mat4 referenceFrame = object->getReferenceFrame();
    shader->sendMatrix("model", 4, 4, glm::value_ptr(referenceFrame));
    shader->sendMatrix("view", 4, 4, glm::value_ptr(view));
    shader->sendMatrix("projection", 4, 4, glm::value_ptr(projection));

    //select the object's buffer
    auto buffer = object->getVertexBuffer();
    buffer->select();

    //apply the buffer textures
    auto textures = buffer->getTextures();
    for(auto pair : textures) {
        GLenum textureUnit = GL_TEXTURE0 + pair.first;
        glActiveTexture(textureUnit);
        pair.second->select();
    }

    //call render callbacks for object
    object->render();

    //draw the buffer to the screen
    buffer->enableAttributes();

    //if the buffer has an index buffer, draw that, otherwise draw the buffer
    auto indexes = buffer->getIndexeBuffer();
    if(indexes != nullptr) {
        indexes->select();
        glDrawElements(GL_TRIANGLES, indexes->getElementCount(), GL_UNSIGNED_INT, 0);
        indexes->deselect();
    }
    else
        glDrawArrays(GL_TRIANGLES, 0, buffer->getElementCount());

    //deselect the buffer
    buffer->deselect();
}

//render the scene
void gl::Renderer::renderScene(std::shared_ptr<Camera> camera) {
    //use the shader program and attribute array
    shader->use();
    glBindVertexArray(VAO);

    //render objects
    auto objects = scene->getObjects();
    for(auto object : objects) {
        renderObject(object.second);
    }

    //reset shader program and vertex array
    glUseProgram(0);
    glBindVertexArray(0);
}