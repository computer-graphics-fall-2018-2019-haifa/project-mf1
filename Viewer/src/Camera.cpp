#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& tmp)
{
	glm::vec3 forward = glm::normalize(from - to);
	glm::vec3 right = glm::cross(glm::normalize(tmp), forward);
	glm::vec3 up = glm::cross(forward, right);

	viewTransformation[0][0] = right.x;
	viewTransformation[0][1] = right.y;
	viewTransformation[0][2] = right.z;
	viewTransformation[1][0] = up.x;
	viewTransformation[1][1] = up.y;
	viewTransformation[1][2] = up.z;
	viewTransformation[2][0] = forward.x;
	viewTransformation[2][1] = forward.y;
	viewTransformation[2][2] = forward.z;

	viewTransformation[3][0] = from.x;
	viewTransformation[3][1] = from.y;
	viewTransformation[3][2] = from.z;

	/*
	glm::vec4 z = glm::normalize(eye - at);
	glm::vec4 x = glm::normalize(glm::cross(up, n));
	glm::vec4 y = glm::normalize(glm::cross(n, u));
	glm::vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 c = mat4(u, v, n, t);
	viewTransformation = c * Translate(-eye);
	*/
}

void Camera::SetOrthographicProjection(
	const float height,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetZoom(const float zoom)
{

}