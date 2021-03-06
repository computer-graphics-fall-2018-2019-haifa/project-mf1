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


	bool is_bound_box;

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
	std::vector<std::pair <glm::vec3, glm::vec3>> Scene::GetActiveModelBoundBoxVerticies();




	void SetBoundBox(bool is_bound_box);
	bool GetBoundBox();



	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveCameraViewParams(float f_camera_trans_x,
		float f_camera_trans_y,
		float f_camera_trans_z,
		float f_camera_rotate_x,
		float f_camera_rotate_y,
		float f_camera_rotate_z);


	void SetActiveCameraProjectionParams(float f_fovy,
		float apect_ratio,
		float f_near,
		float f_far);



	void SetCameraView(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetCameraProjection(const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);


	glm::mat4x4 GetActiveCameraTransformation();
	glm::mat4x4 GetActiveCameraProjection();



	bool is_orth;

};