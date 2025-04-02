#pragma once

#include <glm/glm.hpp>

namespace gl {
    class Camera {
    private:
        glm::mat4 referenceFrame;
        glm::mat4 lookFrame;
        float speed, torque;

    public:
        Camera();
        ~Camera() {};

        glm::vec3 getPosition() { return referenceFrame[3]; };
        
        void setSpeed(float speed) { this->speed = speed; };
        void setLookFrame(glm::mat4 lookFrame) { this->lookFrame = lookFrame; };
        void setPosition(glm::vec3 position) { this->referenceFrame[3] = glm::vec4(position, 1.0f); };
        void setTorque(float torque) { this->torque = torque; };

        glm::mat4 lookForward();
        glm::mat4 lookAt(glm::vec3 point);

        void moveForward(float elapsedTime);
        void moveBackwards(float elapsedTime);
        void moveLeft(float elapsedTime);
        void moveRight(float elapsedTime);
        void moveUp(float elapsedTime);
        void moveDown(float elapsedTime);
        void rotateLeft(float elapsedTime);
        void rotateRight(float elapsedTime);
        void rotateUp(float elapsedTime);
        void rotateDown(float elapsedTime);
    };
}