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
	const int GetActiveModelNumFaces() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;
	std::string GetActiveModelName();
	std::string GetModelName(int index);
	void SetWorldTranToActiveModel();
	glm::mat4x4 GetActiveModelTransMat();
	glm::mat4x4 GetActiveModelScaleMat();
	glm::mat4x4 GetActiveModelRotationMatX();
	glm::mat4x4 GetActiveModelRotationMatY();
	glm::mat4x4 GetActiveModelRotationMatZ();
	void SetActiveModelWorldTransParams(float _f_scale_x,
		float _f_scale_y,
		float _f_scale_z,
		float _f_trans_x,
		float _f_trans_y,
		float _f_trans_z,
		float _f_rotation_x,
		float _f_rotation_y,
		float _f_rotation_z);
	void Scene::GetWorldTranform(float* _f_scale_x,
		float* _f_scale_y,
		float* _f_scale_z,
		float* _f_trans_x,
		float* _f_trans_y,
		float* _f_trans_z,
		float* _f_rotation_x,
		float* _f_rotation_y,
		float* _f_rotation_z);

	Face GetActiveModelFace(int index);
	std::vector<glm::vec3> GetActiveModelVerticies();






	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveCameraViewParams(float f_camera_trans_x,
		float f_camera_trans_y,
		float f_camera_trans_z);


	void SetCameraView(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetCameraProjection(const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);


	glm::mat4x4 GetActiveCameraTransformation();
	glm::mat4x4 GetActiveCameraProjection();


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