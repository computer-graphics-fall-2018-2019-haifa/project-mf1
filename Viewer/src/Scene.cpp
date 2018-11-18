#include "Scene.h"
#include "MeshModel.h"
#include <string>
#include "corecrt_math_defines.h"

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

	translationMat = glm::mat4(1.0);
	scaleMat = glm::mat4(1.0);
	RotationMatX = glm::mat4(1.0);
	RotationMatY = glm::mat4(1.0);
	RotationMatZ = glm::mat4(1.0);

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
		far_);
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
	glm::mat4x4 _translationMat(1.0f);

	_translationMat[0][3] = x;
	_translationMat[1][3] = y;
	_translationMat[2][3] = z;

	translationMat = glm::transpose(_translationMat);


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
	float sin_angle = float(sin(angle* M_PI / 180.0f));
	float cos_angle = float(cos(angle* M_PI / 180.0f));

	
	RotationMatX[1][1] = cos_angle;
	RotationMatX[1][2] = (-1.0)*sin_angle;
	RotationMatX[2][1] = sin_angle;
	RotationMatX[2][2] = cos_angle;
	
	return;
}
const glm::mat4x4 Scene::GetRotationMatX() const
{
	return RotationMatX;
}

void Scene::SetRotationMatY(float angle)
{
	float sin_angle = float(sin(angle* M_PI / 180.0));
	float cos_angle = float(cos(angle* M_PI / 180.0));

	RotationMatY[1][1] = cos_angle;
	RotationMatY[1][2] = (-1.0)*sin_angle;
	RotationMatY[2][1] = sin_angle;
	RotationMatY[2][2] = cos_angle;
	

	return;
}
const glm::mat4x4 Scene::GetRotationMatY() const
{
	return RotationMatY;
}
void Scene::SetRotationMatZ(float angle)
{
	float sin_angle = float(sin(angle * M_PI / 180.0));
	float cos_angle = float(cos(angle * M_PI / 180.0));

	
	RotationMatZ[1][1] = cos_angle;
	RotationMatZ[1][2] = (-1.0)*sin_angle;
	RotationMatZ[2][1] = sin_angle;
	RotationMatZ[2][2] = cos_angle;
	

	return;
}
const glm::mat4x4 Scene::GetRotationMatZ()
{
	return RotationMatZ;
}