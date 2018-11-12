#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	/*
	glm::vec4 z = normalize(eye - at);
	glm::vec4 x = normalize(cross(up, n));
	glm::vec4 y = normalize(cross(n, u));
	glm::vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 c = mat4(u, v, n, t);
	return c * Translate(-eye);
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