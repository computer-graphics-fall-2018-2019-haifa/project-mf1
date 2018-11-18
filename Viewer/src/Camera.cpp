#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);

	SetOrthographicProjection((-500.0),500.0, (-500.0),500.0,1.0,200.0);
}

Camera::~Camera()
{
}



void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	/*
	glm::vec4 z = glm::normalize(eye - at);
	glm::vec4 x = glm::normalize(glm::cross(up, n));
	glm::vec4 y = glm::normalize(glm::cross(n, u));
	glm::vec4 t = vec4(0.0, 0.0, 0.0, 1.0);
	glm::mat4 c = mat4(u, v, n, t);
	viewTransformation = c * Translate(-eye);
	*/


	glm::vec3 z = glm::normalize(eye - at);
	glm::vec4 _z(z[0], z[1], z[2], 0);

	glm::vec3 x = glm::normalize(glm::cross(up, z));
	glm::vec4 _x(x[0], x[1], x[2], 0);

	glm::vec3 y = glm::normalize(glm::cross(x, z));
	glm::vec4 _y(y[0], y[1], y[2], 0);

	glm::vec4 t = glm::vec4(0.0, 0.0, 0.0, 1.0);
	
	glm::mat4 c = glm::transpose(glm::mat4(_x, _y, _z, t));
	
	glm::mat4x4 identity(1.0);
	identity[0][3] = eye[0];
	identity[1][3] = eye[1];
	identity[2][3] = eye[2];
	viewTransformation = c * identity;
}

void Camera::SetOrthographicProjection(
	const float left,
	const float right,
	const float bottom,
	const float top,
	const float near,
	const float far
	)
{
	glm::mat4x4 orthographicMat(glm::mat4(1.0));

	orthographicMat[0][0] = 2.0 / (right - left);
	orthographicMat[1][1] = 2.0 / (top-bottom);
	orthographicMat[2][2] = 2.0 / (near - far);

	orthographicMat[0][3] = -1*((right + left) / (right - left));
	orthographicMat[1][3] = -1 * ((top + bottom) / (top - bottom));
	orthographicMat[2][3] = -1 * ((far + near) / (far - near));

	// Update projection
	projectionTransformation = orthographicMat;

}



void Camera::SetCameraProjection(const float left,
	const float right,
	const float bottom,
	const float top,
	const float near,
	const float far,
	bool is_orth)
{
	if (is_orth)
	{
		SetOrthographicProjection(left, right, bottom, top, near, far);
	}
	else
	{
		SetPerspectiveProjection(left, right, bottom, top, near, far);
	}
	
}




void Camera::SetPerspectiveProjection(
	const float left,
	const float right,
	const float bottom,
	const float top,
	const float near,
	const float far)
{
	glm::mat4x4 PerspectiveMat(glm::mat4(0.0));

	PerspectiveMat[0][0] = (2.0f*near) / (right - left);
	PerspectiveMat[0][2] = (right + left) / (right - left);
	PerspectiveMat[1][1] = (2.0f*near) / (top - bottom);
	PerspectiveMat[1][2] = (top + bottom) / (top - bottom);
	PerspectiveMat[2][2] = (-1.0f)*((far + near) / (far - near));
	PerspectiveMat[2][3] = (-1.0f)*((2.0f*far*near) / (far - near));
	PerspectiveMat[3][2] = (-1.0f);

	// Update projection
	projectionTransformation = PerspectiveMat;
}

void Camera::SetZoom(const float zoom)
{

}



glm::mat4x4 Camera::GetViewTransformation()
{
	return viewTransformation;
}

glm::mat4x4 Camera::GetCameraProjection()
{
	return projectionTransformation;
}

