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

	if (modelName._Equal("cow.obj"))
	{
		f_scale_x = 0.09f;
		f_scale_y = 0.09f;
		f_scale_z = 0.09f;
	}
	else
	{
		f_scale_x = 5.0f;
		f_scale_y = 5.0f;
		f_scale_z = 5.0f;
	}
	
	f_trans_x = 0.5f;
	f_trans_y = 0.5f;
	f_trans_z = 0.5f;
	f_rotation_x = 0.0f;
	f_rotation_y = 0.0f;
	f_rotation_z = 0.0f;

	CalcBoundBoxVerticies();

}

MeshModel::~MeshModel()
{
}



// find the 8 verticies / 12 lines
void MeshModel::CalcBoundBoxVerticies()
{
	int num_verticies = vertices.size();
	float min_x = vertices[0].x, min_y = vertices[0].y, min_z= vertices[0].z, max_x = vertices[0].x, max_y = vertices[0].y, max_z = vertices[0].z;
	for (int i = 0; i < num_verticies; i++)
	{
		if (vertices[i].x < min_x)
		{
			min_x = vertices[i].x;
		}
		if (vertices[i].x > max_x)
		{
			max_x = vertices[i].x;
		}

		if (vertices[i].y < min_y)
		{
			min_y = vertices[i].y;
		}
		if (vertices[i].y > max_y)
		{
			max_y = vertices[i].y;
		}

		if (vertices[i].z < min_z)
		{
			min_z = vertices[i].z;
		}
		if (vertices[i].z > max_z)
		{
			max_z = vertices[i].z;
		}
	}

	// 8 verticies
	glm::vec3 vertex_1 = glm::vec3(min_x, min_y, min_z);
	glm::vec3 vertex_2 = glm::vec3(min_x, min_y, max_z);
	glm::vec3 vertex_3 = glm::vec3(min_x, max_y, min_z);
	glm::vec3 vertex_4 = glm::vec3(min_x, max_y, max_z);
	glm::vec3 vertex_5 = glm::vec3(max_x, min_y, min_z);
	glm::vec3 vertex_6 = glm::vec3(max_x, min_y, max_z);
	glm::vec3 vertex_7 = glm::vec3(max_x, max_y, min_z);
	glm::vec3 vertex_8 = glm::vec3(max_x, max_y, max_z);

	
	// 12 lines
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_1, vertex_5));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_1, vertex_3));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_7, vertex_5));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_7, vertex_3));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_2, vertex_6));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_2, vertex_4));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_8, vertex_6));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_8, vertex_4));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_1, vertex_2));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_5, vertex_6));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_3, vertex_4));
	lines_bound_box.push_back(std::pair <glm::vec3, glm::vec3> (vertex_7, vertex_8));

	
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



std::vector<std::pair <glm::vec3, glm::vec3>> MeshModel::GetBoundBoxVerticies()
{
	return lines_bound_box;
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



void MeshModel::SetTranslationMat()
{
	glm::mat4x4 _translationMat(1.0f);

	_translationMat[0][3] = f_trans_x;
	_translationMat[1][3] = f_trans_y;
	_translationMat[2][3] = f_trans_z;

	translationMat = glm::transpose(_translationMat);
	//translationMat = _translationMat;

	return;
}

const glm::mat4x4 MeshModel::GetTranslationMat() const
{
	return translationMat;
}




void MeshModel::SetScaleMat()
{
	scaleMat[0][0] = f_scale_x;
	scaleMat[1][1] = f_scale_y;
	scaleMat[2][2] = f_scale_z;
	return;
}
const glm::mat4x4 MeshModel::GetScaleMat() const
{
	return scaleMat;
}

void MeshModel::SetRotationMatX()
{
	float sin_angle = float(sin(f_rotation_x* M_PI / 180.0f));
	float cos_angle = float(cos(f_rotation_x* M_PI / 180.0f));

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

void MeshModel::SetRotationMatY()
{
	float sin_angle = float(sin(f_rotation_y* M_PI / 180.0));
	float cos_angle = float(cos(f_rotation_y* M_PI / 180.0));

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
void MeshModel::SetRotationMatZ()
{
	float sin_angle = float(sin(f_rotation_z * M_PI / 180.0));
	float cos_angle = float(cos(f_rotation_z * M_PI / 180.0));

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


void MeshModel::SetWorldTranform(
	float _f_scale_x,
	float _f_scale_y,
	float _f_scale_z,
	float _f_trans_x,
	float _f_trans_y,
	float _f_trans_z,
	float _f_rotation_x,
	float _f_rotation_y,
	float _f_rotation_z)
{
	f_scale_x = _f_scale_x;
	f_scale_y = _f_scale_y;
	f_scale_z = _f_scale_z;
	f_trans_x = _f_trans_x;
	f_trans_y = _f_trans_y;
	f_trans_z = _f_trans_z;
	f_rotation_x = _f_rotation_x;
	f_rotation_y = _f_rotation_y;
	f_rotation_z = _f_rotation_z;
}


void MeshModel::GetWorldTranform(
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
	*_f_scale_x = f_scale_x;
	*_f_scale_y = f_scale_y;
	*_f_scale_z = f_scale_z;
	*_f_trans_x = f_trans_x;
	*_f_trans_y = f_trans_y;
	*_f_trans_z = f_trans_z;
	*_f_rotation_x = f_rotation_x;
	*_f_rotation_y = f_rotation_y;
	*_f_rotation_z = f_rotation_z;
}
