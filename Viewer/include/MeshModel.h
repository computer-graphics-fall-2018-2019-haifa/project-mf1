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



	glm::mat4x4 translationMat;
	glm::mat4x4 scaleMat;
	glm::mat4x4 RotationMatX;
	glm::mat4x4 RotationMatY;
	glm::mat4x4 RotationMatZ;


public:
	MeshModel(const std::vector<Face>& faces, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& normals, const std::string& modelName = "");
	virtual ~MeshModel();

	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	const glm::mat4x4& GetWorldTransformation() const;

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();

	// Add more methods/functionality as needed...
	const glm::vec3& GetVertex(int index) const;
	const int GetVerticesCount() const;
	const std::vector<glm::vec3> GetVertices() const;


	const Face GetFace(int index) const;
	const int GetFacesCount() const;



	void SetTranslationMat(float x, float y, float z);
	const glm::mat4x4 GetTranslationMat() const;
	void SetScaleMat(float x, float y, float z);
	const glm::mat4x4 GetScaleMat() const;
	void SetRotationMatX(float angle);
	const glm::mat4x4 GetRotationMatX() const;
	void SetRotationMatY(float angle);
	const glm::mat4x4 GetRotationMatY() const;
	void SetRotationMatZ(float angle);
	const glm::mat4x4 GetRotationMatZ();



};
