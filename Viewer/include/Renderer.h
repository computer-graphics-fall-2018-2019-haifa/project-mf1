#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

/*
 * Renderer class.
 */
class Renderer
{
private:
	float *colorBuffer;
	float *zBuffer;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;

	void putPixel(int x, int y, const glm::vec3& color);
	void createBuffers(int viewportWidth, int viewportHeight);

	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();

	void Render(Scene& scene, ImGuiIO& io);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);

	void DrawLineBresenhamAlgorithm(float p1, float q1, float p2, float q2, const glm::vec3& color);
	void plotLineHigh(int x0, int y0, int x1, int y1, const glm::vec3& color);
	void plotLineLow(int x0, int y0, int x1, int y1, const glm::vec3& color);
	void DrawFace(Face curr_face,  std::vector<glm::vec4> curr_vertices);
	std::vector<glm::vec4> TransformVertecies(std::vector<glm::vec3> curr_vertices, glm::mat4x4 curr_tran);
	void DrawBoundBox(std::vector<std::pair <glm::vec3, glm::vec3>>* curr_vertecies);

};
