#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

MeshModel::MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1))
{
	this->vertices = vertices;
	this->faces = faces;
}

MeshModel::~MeshModel()
{

}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
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