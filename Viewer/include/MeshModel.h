#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform;
	glm::vec4 color;
	std::string modelName;


	// World Transform matricies
	glm::mat4x4 translationMat;
	glm::mat4x4 scaleMat;
	glm::mat4x4 RotationMatX;
	glm::mat4x4 RotationMatY;
	glm::mat4x4 RotationMatZ;


	// world trans params
	float f_scale_x;
	float f_scale_y;
	float f_scale_z;
	float f_trans_x;
	float f_trans_y;
	float f_trans_z;
	float f_rotation_x;
	float f_rotation_y;
	float f_rotation_z;


public:
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();

	const glm::vec3& GetVertex(int index) const;
	const int GetVerticesCount() const;
	const std::vector<glm::vec3> GetVertices() const;
	const Face GetFace(int index) const;
	const int GetFacesCount() const;


	// World Transform matricies
	void SetTranslationMat();
	const glm::mat4x4 GetTranslationMat() const;
	void SetScaleMat();
	const glm::mat4x4 GetScaleMat() const;
	void SetRotationMatX();
	const glm::mat4x4 GetRotationMatX() const;
	void SetRotationMatY();
	const glm::mat4x4 GetRotationMatY() const;
	void SetRotationMatZ();
	const glm::mat4x4 GetRotationMatZ();


	void SetWorldTranform(
		float f_scale_x, 
		float  f_scale_y, 
		float  f_scale_z, 
		float  f_trans_x, 
		float  f_trans_y, 
		float  f_trans_z, 
		float f_rotation_x, 
		float f_rotation_y, 
		float f_rotation_z);
};
