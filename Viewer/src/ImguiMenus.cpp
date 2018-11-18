#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>

bool showDemoWindow = false;
bool showAnotherWindow = false;


glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("click me");                          // Create a window called "Hello, world!" and append into it.


		std::string modelName = scene.GetActiveModelName();
		ImGui::Text("Model name:"); ImGui::SameLine();
		ImGui::Text(const_cast<char*>(modelName.c_str()));
		
		
		// Model sliders: scale, translate, rotate
		ImGui::Text("");
		ImGui::Text("Model");

		static float f_scale_all = 5.0f;
		static float f_scale_x = 5.0f;
		static float f_scale_y = 5.0f;
		static float f_scale_z = 5.0f;
		if (ImGui::SliderFloat("scale all", &f_scale_all, 0.001f, 100.0f))
		{
			f_scale_x = f_scale_all;
			f_scale_y = f_scale_all;
			f_scale_z = f_scale_all;
		}
		else
		{
			ImGui::SliderFloat("scaleX", &f_scale_x, 0.001f, 100.0f);
			ImGui::SliderFloat("scaleY", &f_scale_y, 0.001f, 100.0f);
			ImGui::SliderFloat("scaleZ", &f_scale_z, 0.001f, 100.0f);
		}

		static float f_trans_x = 0.5f;
		ImGui::SliderFloat("transX", &f_trans_x, -1.0f, 1.0f);
		static float f_trans_y = 0.5f;
		ImGui::SliderFloat("transY", &f_trans_y, -1.0f, 1.0f);
		static float f_trans_z = 0.5f;
		ImGui::SliderFloat("transZ", &f_trans_z, -1.0f,1.0f);

		static float f_rotation_x = 0.0f;
		ImGui::SliderFloat("rotation x", &f_rotation_x, -360.0f,360.0f);
		static float f_rotation_y = 0.0f;
		ImGui::SliderFloat("rotation y", &f_rotation_y, -360.0f, 360.0f);
		static float f_rotation_z = 0.0f;
		ImGui::SliderFloat("rotation z", &f_rotation_z, -360.0f, 360.0f);

		scene.scaleX = f_scale_x;
		scene.scaleY = f_scale_y;
		scene.scaleZ = f_scale_z;

		scene.translationX = f_trans_x;
		scene.translationY = f_trans_y;
		scene.translationZ = f_trans_z;

		scene.rotationAngle_x = f_rotation_x;
		scene.rotationAngle_y = f_rotation_y;
		scene.rotationAngle_z = f_rotation_z;



		// Camera sliders: perspective/ orthographic, eye, at, up
		ImGui::Text("");
		ImGui::Text("Camera");

		static int active_axes = 1;
		if (ImGui::RadioButton("Perspective", &active_axes,0)) 
		{ 
			scene.is_orth = false; 
		} 
		ImGui::SameLine();
		if (ImGui::RadioButton("Orthographic", &active_axes ,1)) 
		{ 
			scene.is_orth = true; 
		}
	
		static float f_eye_x = 0.0f;
		ImGui::SliderFloat("eye x", &f_eye_x, -100.0f, 100.0f);
		static float f_eye_y = 0.0f;
		ImGui::SliderFloat("eye y", &f_eye_y, -100.0f, 100.0f);
		static float f_eye_z = 0.0f;
		ImGui::SliderFloat("eye z", &f_eye_z, -100.0f, 100.0f);

		static float f_at_x = 0.0f;
		ImGui::SliderFloat("at x", &f_at_x, -100.0f, 100.0f);
		static float f_at_y = 0.0f;
		ImGui::SliderFloat("at y", &f_at_y, -100.0f, 100.0f);
		static float f_at_z = 0.0f;
		ImGui::SliderFloat("at z", &f_at_z, -100.0f, 100.0f);

		static float f_up_x = 0.0f;
		ImGui::SliderFloat("up x", &f_up_x, -100.0f, 100.0f);
		static float f_up_y = 0.0f;
		ImGui::SliderFloat("up y", &f_up_y, -100.0f, 100.0f);
		static float f_up_z = 0.0f;
		ImGui::SliderFloat("up z", &f_up_z, -100.0f, 100.0f);

		scene.cam_eye_x = f_eye_x;
		scene.cam_eye_y = f_eye_x;
		scene.cam_eye_z = f_eye_x;
		scene.cam_at_x = f_at_x;
		scene.cam_at_y = f_at_x;
		scene.cam_at_z = f_at_x;
		scene.cam_up_x = f_up_x;
		scene.cam_up_y = f_up_x;
		scene.cam_up_z = f_up_x;

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	/*
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}
	*/

	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}