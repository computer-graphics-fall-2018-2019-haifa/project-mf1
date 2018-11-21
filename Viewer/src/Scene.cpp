#include "Scene.h"
#include "MeshModel.h"
#include <string>


Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

	

	is_orth = true;

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
}

const int Scene::GetModelCount() const
{
	return (int)models.size();
}


const int Scene::GetActiveModelNumFaces() const
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetFacesCount();
}

 void Scene::SetWorldTranToActiveModel()
 {
	 std::shared_ptr<MeshModel> tmp = models[activeModelIndex];

	 tmp->SetTranslationMat();
	 tmp->SetScaleMat();
	 tmp->SetRotationMatX();
	 tmp->SetRotationMatY();
	 tmp->SetRotationMatZ();
 }




void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return (int)cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < int(cameras.size()))
	{
		activeCameraIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < int(models.size()))
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}



glm::mat4x4 Scene::GetActiveModelTransMat()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetTranslationMat();
}

glm::mat4x4 Scene::GetActiveModelScaleMat()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetScaleMat();
}

glm::mat4x4 Scene::GetActiveModelRotationMatX()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetRotationMatX();
}

glm::mat4x4 Scene::GetActiveModelRotationMatY()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetRotationMatY();
}

glm::mat4x4 Scene::GetActiveModelRotationMatZ()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetRotationMatZ();
}


void Scene::GetWorldTranform(
	float* _f_scale_x,
	float* _f_scale_y,
	float* _f_scale_z,
	float* _f_trans_x,
	float* _f_trans_y,
	float* _f_trans_z,
	float* _f_rotation_x,
	float* _f_rotation_y,
	float* _f_rotation_z)
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	tmp->GetWorldTranform(
		_f_scale_x,
		_f_scale_y,
		_f_scale_z,
		_f_trans_x,
		_f_trans_y,
		_f_trans_z,
		_f_rotation_x,
		_f_rotation_y,
		_f_rotation_z);
}



void Scene::SetActiveModelWorldTransParams(float _f_scale_x,
	float _f_scale_y,
	float _f_scale_z,
	float _f_trans_x,
	float _f_trans_y,
	float _f_trans_z,
	float _f_rotation_x,
	float _f_rotation_y,
	float _f_rotation_z)
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];

	tmp->SetWorldTranform(
		_f_scale_x,
		_f_scale_y,
		_f_scale_z,
		_f_trans_x,
		_f_trans_y,
		_f_trans_z,
		_f_rotation_x,
		_f_rotation_y,
		_f_rotation_z);
}


std::string Scene::GetModelName(int index)
{
	std::shared_ptr<MeshModel> tmp = models[index];

	return tmp->GetModelName();
}


std::string Scene::GetActiveModelName()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];

	return tmp->GetModelName();
}

void Scene::SetCameraView(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	cameras[activeCameraIndex].SetCameraLookAt(eye,at,up);
}


void Scene::SetCameraProjection(const float left,
	const float right,
	const float bottom,
	const float top,
	const float near_,
	const float far_)
{
	cameras[activeCameraIndex].SetCameraProjection(left,
		right,
		bottom,
		top,
		near_,
		far_,
		is_orth);
}


glm::mat4x4 Scene::GetActiveCameraTransformation()
{
	return cameras[activeCameraIndex].GetViewTransformation();
}



glm::mat4x4 Scene::GetActiveCameraProjection()
{
	return  cameras[activeCameraIndex].GetCameraProjection();
}


Face Scene::GetActiveModelFace(int index)
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetFace(index);
}


std::vector<glm::vec3> Scene::GetActiveModelVerticies()
{
	std::shared_ptr<MeshModel> tmp = models[activeModelIndex];
	return tmp->GetVertices();
}


