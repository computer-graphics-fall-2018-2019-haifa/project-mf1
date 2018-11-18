#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3* viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}









void Renderer::plotLineHigh(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	int D = 2 * dx - dy;
	int y = y0;
	int x = x0;

	while (y <= y1)
	{
		putPixel(x, y, glm::vec3(0, 1, 0));
		if (D > 0)
		{
			x = x + xi;
			D = D - 2 * dy;
		}
		D = D + 2 * dx;
		y++;
	}
}



void Renderer::plotLineLow(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	int D = 2 * dy - dx;
	int y = y0;
	int x = x0;

	while (x <= x1)
	{
		putPixel(x, y, glm::vec3(0, 1, 0));
		if (D > 0)
		{
			y = y + yi;
			D = D - 2 * dx;
		}
		D = D + 2 * dy;
		x++;
	}
}



void Renderer::DrawLineBresenhamAlgorithm(float _x0, float _y0, float _x1, float _y1)
{
	int x0 = int(_x0);
	int y0 = int(_y0);
	int x1 = int(_x1);
	int y1 = int(_y1);


	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
		{
			plotLineLow(x1, y1, x0, y0);
		}
		else
		{
			plotLineLow(x0, y0, x1, y1);
		}
	}
	else
	{
		if (y0 > y1)
		{
			plotLineHigh(x1, y1, x0, y0);
		}
		else
		{
			plotLineHigh(x0, y0, x1, y1);
		}
	}
}


void Renderer::DrawFace(Face curr_face, std::vector<glm::vec4> curr_vertices, bool is_2d_debug)
{
	float mul_factor = 1.0f;
	if (is_2d_debug)
	{
		mul_factor = 10000;
	}


	int vertex_index_0 = curr_face.GetVertexIndex(0);
	vertex_index_0 -= 1;
	glm::vec4 curr_vertex_0 = curr_vertices[vertex_index_0];

	int vertex_index_1 = curr_face.GetVertexIndex(1);
	vertex_index_1 -= 1;
	glm::vec4 curr_vertex_1 = curr_vertices[vertex_index_1];

	int vertex_index_2 = curr_face.GetVertexIndex(2);
	vertex_index_2 -= 1;
	glm::vec4 curr_vertex_2 = curr_vertices[vertex_index_2];

	// The relevant data is vertex.x and vertex.y
	DrawLineBresenhamAlgorithm(curr_vertex_0[0] * mul_factor, curr_vertex_0[1] * mul_factor, curr_vertex_1[0] * mul_factor, curr_vertex_1[1] * mul_factor);
	DrawLineBresenhamAlgorithm(curr_vertex_0[0] * mul_factor, curr_vertex_0[1] * mul_factor, curr_vertex_2[0] * mul_factor, curr_vertex_2[1] * mul_factor);
	DrawLineBresenhamAlgorithm(curr_vertex_1[0] * mul_factor, curr_vertex_1[1] * mul_factor, curr_vertex_2[0] * mul_factor, curr_vertex_2[1] * mul_factor);
}



// Simply iterate all over the vertecies and muliply in tranform matrix
std::vector<glm::vec4> Renderer::TransformVertecies(std::vector<glm::vec3> curr_vertices, glm::mat4x4 curr_tran)
{
	std::vector<glm::vec4> transed_vetricies;

	for (std::vector<glm::vec3>::iterator it = curr_vertices.begin(); it != curr_vertices.end(); ++it)
	{
		glm::vec4 tmp(1.0);
		tmp[0] = it->x;
		tmp[1] = it->y;
		tmp[2] = it->z;

		glm::vec4 res_vertex = curr_tran * tmp;
		transed_vetricies.push_back(res_vertex);
	}

	return transed_vetricies;
}



// Apply gui input on current model
void SetWorldTransMat(Scene& scene, MeshModel& curr_model)
{
	curr_model.SetTranslationMat(scene.translationX, scene.translationY, scene.translationZ);
	curr_model.SetScaleMat(scene.scaleX, scene.scaleY, scene.scaleZ);
	curr_model.SetRotationMatX(scene.rotationAngle_x);
	curr_model.SetRotationMatY(scene.rotationAngle_y);
	curr_model.SetRotationMatZ(scene.rotationAngle_z);
}


// Get all world transformed matricies and calc them together
glm::mat4x4 getScenceTransMat(MeshModel curr_model)
{
	glm::mat4x4 trans_mat = curr_model.GetTranslationMat();
	glm::mat4x4 scale_mat = curr_model.GetScaleMat();
	glm::mat4x4 rot_mat_x = curr_model.GetRotationMatX();
	glm::mat4x4 rot_mat_y = curr_model.GetRotationMatY();
	glm::mat4x4 rot_mat_z = curr_model.GetRotationMatZ();

	glm::mat4x4 res_mat = trans_mat  * rot_mat_x * rot_mat_y * rot_mat_z* scale_mat;

	return res_mat;
}


// Apply camera projection
void SetCameraProjection(Scene& scene)
{
	float left= (-500.0f);
	float right = (500.0);
	float bottom = (-200.0);
	float top = (200.0);
	float near_ = 10.0;
	float far_ = 150.0;
	scene.SetCameraProjection(left,
		right,
		bottom,
		top,
		near_,
		far_);
}


// Apply gui input on camera view
void SetCameraViewFromGui(Scene& scene)
{
	glm::vec3 eye(scene.cam_eye_x, scene.cam_eye_y, scene.cam_eye_z);
	glm::vec3 at(scene.cam_at_x, scene.cam_at_y, scene.cam_at_z);
	glm::vec3 up(scene.cam_up_x, scene.cam_up_y, scene.cam_up_z);

	scene.SetCameraView(eye,at,up);
}


// Main function
void Renderer::Render(Scene& scene, ImGuiIO& io)
{
	bool is_2d_debug = true; // For debug

	// Draw all models
	int num_models = scene.GetModelCount();
	for (int x = 0; x < num_models; x++)
	{
		MeshModel curr_model = scene.GetModel(x);
		int num_faces = curr_model.GetFacesCount();
		for (int y = 0; y < num_faces; y++)
		{
			// Handle world Trans mat 
			SetWorldTransMat(scene, curr_model);
			glm::mat4x4 curr_tran = getScenceTransMat(curr_model);
			//glm::mat4x4 curr_tran(1.0f);


			// Handle view camera
			SetCameraViewFromGui(scene);
			glm::mat4x4 viewCamera(1.0f);
			if (!is_2d_debug)
			{
				glm::mat4x4 viewCamera = scene.GetActiveCamera();
			}


			


			// Handle projection
			SetCameraProjection(scene);
			glm::mat4x4 projection(1.0f);
			if (!is_2d_debug)
			{
				glm::mat4x4 projection = scene.GetActiveCameraProjection();
			}
			
			
			

			// Calc all maticies
			glm::mat4x4 tarns_mat = curr_tran * viewCamera * projection;


			// Apply on all verticies
			Face curr_face = curr_model.GetFace(y);
			std::vector<glm::vec3> curr_vetices = curr_model.GetVertices();
			std::vector<glm::vec4> transed_vertices = TransformVertecies(curr_vetices, tarns_mat);

			// Draw the faces lines
			DrawFace(curr_face, transed_vertices, is_2d_debug);
		}
	}
	






	
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}