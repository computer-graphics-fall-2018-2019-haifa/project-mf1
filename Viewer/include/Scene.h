#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;

	glm::mat4x4 translationMat;
	glm::mat4x4 scaleMat;
	glm::mat4x4 RotationMatX;
	glm::mat4x4 RotationMatY;
	glm::mat4x4 RotationMatZ;



	int activeCameraIndex;
	int activeModelIndex;



	




public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& model);
	const int GetModelCount() const;
	const MeshModel GetModel(int model_index) const;

	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;

	// Add more methods as needed...

	void SetTranslationMat(float x, float y, float z);
	const glm::mat4x4 GetTranslationMat() const;
	void SetScaleMat(float x, float y, float z);
	const glm::mat4x4 GetScaleMat() const;
	void SetRotationMatX(float angle);
	const glm::mat4x4 GetRotationMatX();
	void SetRotationMatY(float angle) const;
	const glm::mat4x4 GetRotationMatY();
	void SetRotationMatZ(float angle) const;
	const glm::mat4x4 GetRotationMatZ();


	void SetCameraView(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetCameraProjection(const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);


	glm::mat4x4 GetActiveCamera();
	glm::mat4x4 GetActiveCameraProjection();



	// TODO delete those fields
	float scaleX;
	float scaleY;
	float scaleZ;

	float translationX;
	float translationY;
	float translationZ;

	float rotationAngle;

	float cam_eye_x;
	float cam_eye_y;
	float cam_eye_z;
	float cam_at_x;
	float cam_at_y;
	float cam_at_z;
	float cam_up_x;
	float cam_up_y;
	float cam_up_z;




	// TODO delete those fields
};