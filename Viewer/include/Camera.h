#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"


class Camera
{
private:
	glm::mat4x4 viewTransformation;			// holds the view tranform
	glm::mat4x4 projectionTransformation;	// holds the projection tranform
	float zoom;

	float f_camera_trans_x;
	float f_camera_trans_y;
	float f_camera_trans_z;

	// Transform matricies
	glm::mat4x4 translationMat;
	glm::mat4x4 scaleMat;
	glm::mat4x4 RotationMatX;
	glm::mat4x4 RotationMatY;
	glm::mat4x4 RotationMatZ;


public:
	Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	~Camera();

	void SetActiveCameraViewParams(float f_camera_trans_x,
		float f_camera_trans_y,
		float f_camera_trans_z);

	void SetTranslationMat();



	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);

	void SetCameraProjection(const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far,
		bool is_orth);

	void SetOrthographicProjection(
		const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far
	);

	void SetPerspectiveProjection(
		const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);

	void SetZoom(const float zoom);


	glm::mat4x4 GetViewTransformation();
	glm::mat4x4 GetCameraProjection();
};
