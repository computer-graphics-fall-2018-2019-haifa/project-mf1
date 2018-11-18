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



const MeshModel Scene::GetModel(int model_index) const
{
	MeshModel tmp = *models[model_index];
	return tmp;
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
	if (index >= 0 && index < cameras.size())
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
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}


std::string Scene::GetActiveModelName()
{
	MeshModel tmp = *models[activeModelIndex];
	return tmp.GetModelName();
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


glm::mat4x4 Scene::GetActiveCamera()
{
	return cameras[activeCameraIndex].GetViewTransformation();
}



glm::mat4x4 Scene::GetActiveCameraProjection()
{
	return  cameras[activeCameraIndex].GetCameraProjection();
}



