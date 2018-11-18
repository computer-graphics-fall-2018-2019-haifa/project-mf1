#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "corecrt_math_defines.h"


MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1))
{
	this->vertices = vertices;
	this->faces = faces;

	// Init identity matricies
	translationMat = glm::mat4(1.0);
	scaleMat = glm::mat4(1.0);
	RotationMatX = glm::mat4(1.0);
	RotationMatY = glm::mat4(1.0);
	RotationMatZ = glm::mat4(1.0);
}

MeshModel::~MeshModel()
{
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return color;
}


const glm::vec3& MeshModel::GetVertex(int index) const
{
	return vertices[index];
}


const std::vector<glm::vec3> MeshModel::GetVertices() const
{
	return vertices;
}


const Face MeshModel::GetFace(int index) const
{
	return faces[index];
}


const int MeshModel::GetFacesCount() const
{
	return (int)faces.size();
}



const std::string& MeshModel::GetModelName()
{
	return modelName;
}



const int MeshModel::GetVerticesCount() const
{
	return (int)vertices.size();
}



void MeshModel::SetTranslationMat(float x, float y, float z)
{
	glm::mat4x4 _translationMat(1.0f);

	_translationMat[0][3] = x;
	_translationMat[1][3] = y;
	_translationMat[2][3] = z;

	//translationMat = glm::transpose(_translationMat);
	translationMat = _translationMat;

	return;
}

const glm::mat4x4 MeshModel::GetTranslationMat() const
{
	return translationMat;
}




void MeshModel::SetScaleMat(float x, float y, float z)
{
	scaleMat[0][0] = x;
	scaleMat[1][1] = y;
	scaleMat[2][2] = z;
	return;
}
const glm::mat4x4 MeshModel::GetScaleMat() const
{
	return scaleMat;
}

void MeshModel::SetRotationMatX(float angle)
{
	float sin_angle = float(sin(angle* M_PI / 180.0f));
	float cos_angle = float(cos(angle* M_PI / 180.0f));

	RotationMatX[1][1] = cos_angle;
	RotationMatX[1][2] = (-1.0f)*sin_angle;
	RotationMatX[2][1] = sin_angle;
	RotationMatX[2][2] = cos_angle;

	return;
}
const glm::mat4x4 MeshModel::GetRotationMatX() const
{
	return RotationMatX;
}

void MeshModel::SetRotationMatY(float angle)
{
	float sin_angle = float(sin(angle* M_PI / 180.0));
	float cos_angle = float(cos(angle* M_PI / 180.0));

	RotationMatY[0][0] = cos_angle;
	RotationMatY[0][2] = sin_angle;
	RotationMatY[2][0] = (-1.0f)*sin_angle;
	RotationMatY[2][2] = cos_angle;


	return;
}
const glm::mat4x4 MeshModel::GetRotationMatY() const
{
	return RotationMatY;
}
void MeshModel::SetRotationMatZ(float angle)
{
	float sin_angle = float(sin(angle * M_PI / 180.0));
	float cos_angle = float(cos(angle * M_PI / 180.0));

	RotationMatZ[0][0] = cos_angle;
	RotationMatZ[0][1] = (-1.0f)*sin_angle;
	RotationMatZ[1][0] = sin_angle;
	RotationMatZ[1][1] = cos_angle;


	return;
}
const glm::mat4x4 MeshModel::GetRotationMatZ()
{
	return RotationMatZ;
}