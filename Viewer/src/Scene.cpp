#include "Scene.h"
#include "MeshModel.h"
#include <string>

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

	translationMat = glm::mat4(1.0);
	scaleMat = glm::mat4(1.0);
	RotationMatX = glm::mat4(1.0);
	RotationMatY = glm::mat4(1.0);
	RotationMatZ = glm::mat4(1.0);

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

glm::mat4x4 Scene::GetActiveCamera()
{
	return cameras[activeCameraIndex].GetViewTransformation();
}



glm::mat4x4 Scene::GetActiveCameraProjection()
{
	return cameras[activeCameraIndex].GetOrthographicMat();
}



void Scene::SetTranslationMat(float x, float y, float z)
{
	translationMat[0][3] = x;
	translationMat[1][3] = y;
	translationMat[2][3] = z;
	return;
}

const glm::mat4x4 Scene::GetTranslationMat() const
{
	return translationMat;
}




void Scene::SetScaleMat(float x, float y, float z)
{
	scaleMat[0][0] = x;
	scaleMat[1][1] = y;
	scaleMat[2][2] = z;
	return;
}
const glm::mat4x4 Scene::GetScaleMat() const
{
	return scaleMat;
}

void Scene::SetRotationMatX(float angle)
{
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);

	/*
	RotationMatX[1][1] = cos_angle;
	RotationMatX[1][2] = -sin_angle;
	RotationMatX[2][1] = sin_angle;
	RotationMatX[2][2] = cos_angle;
	*/
	return;
}
const glm::mat4x4 Scene::GetRotationMatX()
{
	return RotationMatX;
}

void Scene::SetRotationMatY(float angle) const
{
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);

	/*
	RotationMatY[1][1] = cos_angle;
	RotationMatY[1][2] = -sin_angle;
	RotationMatY[2][1] = sin_angle;
	RotationMatY[2][2] = cos_angle;
	*/

	return;
}
const glm::mat4x4 Scene::GetRotationMatY()
{
	return RotationMatY;
}
void Scene::SetRotationMatZ(float angle) const
{
	float sin_angle = sin(angle);
	float cos_angle = cos(angle);

	/*
	RotationMatZ[1][1] = cos_angle;
	RotationMatZ[1][2] = -sin_angle;
	RotationMatZ[2][1] = sin_angle;
	RotationMatZ[2][2] = cos_angle;
	*/

	return;
}
const glm::mat4x4 Scene::GetRotationMatZ()
{
	return RotationMatZ;
}