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
	std::string GetActiveModelName();


	void SetCameraView(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetCameraProjection(const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);


	glm::mat4x4 GetActiveCamera();
	glm::mat4x4 GetActiveCameraProjection();



	float scaleX;
	float scaleY;
	float scaleZ;

	float translationX;
	float translationY;
	float translationZ;

	float rotationAngle_x;
	float rotationAngle_y;
	float rotationAngle_z;

	float cam_eye_x;
	float cam_eye_y;
	float cam_eye_z;
	float cam_at_x;
	float cam_at_y;
	float cam_at_z;
	float cam_up_x;
	float cam_up_y;
	float cam_up_z;

	bool is_orth;

};