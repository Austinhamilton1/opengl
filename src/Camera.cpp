#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

gl::Camera::Camera() {
    referenceFrame = glm::mat4(1.0f);
    lookFrame = glm::mat4(1.0f);
	speed = 0.0f;
	torque = 0.0f;
}

glm::mat4 gl::Camera::lookForward() {
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraForward = -lookFrame[2];
	glm::vec3 cameraTarget = cameraPosition + cameraForward;
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

glm::mat4 gl::Camera::lookAt(glm::vec3 point) {
	glm::vec3 cameraPosition = referenceFrame[3];
	glm::vec3 cameraUp = lookFrame[1];
	return glm::lookAt(cameraPosition, point, cameraUp);
}

void gl::Camera::moveForward(float elapsedTime) {
	glm::vec3 forward = -lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	forward = forward * speed * elapsedTime;
	position += forward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::moveBackwards(float elapsedTime) {
	glm::vec3 backward = lookFrame[2];
	glm::vec3 position = referenceFrame[3];
	backward = backward * speed * elapsedTime;
	position += backward;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::moveLeft(float elapsedTime) {
	glm::vec3 left = -lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	left = left * speed * elapsedTime;
	position += left;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::moveRight(float elapsedTime) {
	glm::vec3 right = lookFrame[0];
	glm::vec3 position = referenceFrame[3];
	right = right * speed * elapsedTime;
	position += right;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::moveUp(float elapsedTime) {
	glm::vec3 up = referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	up = up * speed * elapsedTime;
	position += up;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::moveDown(float elapsedTime) {
	glm::vec3 down = -referenceFrame[1];
	glm::vec3 position = referenceFrame[3];
	down = down * speed * elapsedTime;
	position += down;
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void gl::Camera::rotateRight(float elapsedTime) {
	lookFrame = glm::rotate(lookFrame, -torque * elapsedTime, glm::vec3(0.0f, 1.0f, 0.0f));
}

void gl::Camera::rotateLeft(float elapsedTime) {
	lookFrame = glm::rotate(lookFrame, torque * elapsedTime, glm::vec3(0.0f, 1.0f, 0.0f));
}

void gl::Camera::rotateUp(float elapsedTime) {
	lookFrame = glm::rotate(lookFrame, torque * elapsedTime, glm::vec3(1.0f, 0.0f, 0.0f));
}

void gl::Camera::rotateDown(float elapsedTime) {
	lookFrame = glm::rotate(lookFrame, -torque * elapsedTime, glm::vec3(1.0f, 0.0f, 0.0f));
}