#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
	SetOrthographicProjection((-500.0f),500.0f, (-200.0f),200.0f,10.0f,150.0f);


	// Init identity matricies
	translationMat = glm::mat4(1.0);
	scaleMat = glm::mat4(1.0);
	RotationMatX = glm::mat4(1.0);
	RotationMatY = glm::mat4(1.0);
	RotationMatZ = glm::mat4(1.0);

	f_camera_trans_x = 0;
	f_camera_trans_y = 0;
	f_camera_trans_z = 0;
}

Camera::~Camera()
{
}


void Camera::SetActiveCameraProjectionParams(float _f_fovy,
	float _apect_ratio,
	float _f_near,
	float _f_far) 
{
	f_fovy = _f_fovy;
	apect_ratio = _apect_ratio;
	f_near = _f_near;
	f_far = _f_far;
}


void Camera::SetActiveCameraViewParams(float _f_camera_trans_x,
	float _f_camera_trans_y,
	float _f_camera_trans_z,
	float _f_camera_rotate_x,
	float _f_camera_rotate_y,
	float _f_camera_rotate_z)
{
	f_camera_trans_x = _f_camera_trans_x;
	f_camera_trans_y = _f_camera_trans_y;
	f_camera_trans_z = _f_camera_trans_z;
	f_camera_rotate_x = _f_camera_rotate_x;
	f_camera_rotate_y = _f_camera_rotate_y;
	f_camera_rotate_z = _f_camera_rotate_z;
}



void Camera::SetTranslationMat()
{
	glm::mat4x4 _translationMat(1.0f);

	_translationMat[0][3] = f_camera_trans_x;
	_translationMat[1][3] = f_camera_trans_y;
	_translationMat[2][3] = f_camera_trans_z;

	translationMat = glm::transpose(_translationMat);
	//translationMat = _translationMat;

	return;
}


void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	/*
	// Classroom:
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

	orthographicMat[0][0] = 2.0f / (right - left);
	orthographicMat[1][1] = 2.0f / (top-bottom);
	orthographicMat[2][2] = 2.0f / (near - far);

	orthographicMat[0][3] = (-1.0f) * ((right + left) / (right - left));
	orthographicMat[1][3] = (-1.0f) * ((top + bottom) / (top - bottom));
	orthographicMat[2][3] = (-1.0f) * ((far + near) / (far - near));

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

