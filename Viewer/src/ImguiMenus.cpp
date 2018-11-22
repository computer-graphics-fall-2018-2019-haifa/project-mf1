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




		// Select active model using gui
		int num_models = scene.GetModelCount();
		if (num_models > 0)
		{
			std::vector<std::string> modelNames;
			for (int i = 0; i < num_models; i++)
			{
				std::string modelName = scene.GetModelName(i);
				modelNames.push_back(modelName);
			}
			char** items = new char*[num_models];
			for (int i = 0; i < num_models; i++)
			{
				items[i] = const_cast<char*>(modelNames[i].c_str());
			}
			static int item_current = scene.GetActiveModelIndex();
			ImGui::Combo("combo", &item_current, items, num_models);
			scene.SetActiveModelIndex(item_current);

			//std::string modelName = scene.GetActiveModelName();
			//ImGui::Text("Model name:"); ImGui::SameLine();
			//ImGui::Text(const_cast<char*>(modelName.c_str()));


			// Model sliders: scale, translate, rotate
			ImGui::Text("");
			ImGui::Text("Model");

			float f_scale_x;
			float f_scale_y;
			float f_scale_z;
			float f_trans_x;
			float f_trans_y;
			float f_trans_z;
			float f_rotation_x;
			float f_rotation_y;
			float f_rotation_z;

			scene.GetWorldTranform(
				&f_scale_x,
				&f_scale_y,
				&f_scale_z,
				&f_trans_x,
				&f_trans_y,
				&f_trans_z,
				&f_rotation_x,
				&f_rotation_y,
				&f_rotation_z
			);



			{
				ImGui::SliderFloat("scaleX", &f_scale_x, 0.001f, 100.0f);
				ImGui::SliderFloat("scaleY", &f_scale_y, 0.001f, 100.0f);
				ImGui::SliderFloat("scaleZ", &f_scale_z, 0.001f, 100.0f);
			}

			ImGui::SliderFloat("transX", &f_trans_x, -1.0f, 1.0f);
			ImGui::SliderFloat("transY", &f_trans_y, -1.0f, 1.0f);
			ImGui::SliderFloat("transZ", &f_trans_z, -1.0f, 1.0f);

			ImGui::SliderFloat("rotation x", &f_rotation_x, -360.0f, 360.0f);
			ImGui::SliderFloat("rotation y", &f_rotation_y, -360.0f, 360.0f);
			ImGui::SliderFloat("rotation z", &f_rotation_z, -360.0f, 360.0f);


			scene.SetActiveModelWorldTransParams(f_scale_x, f_scale_y, f_scale_z, f_trans_x, f_trans_y, f_trans_z, f_rotation_x, f_rotation_y, f_rotation_z);


			// Camera sliders: perspective/ orthographic, eye, at, up
			ImGui::Text("");
			ImGui::Text("Camera");

			static int active_axes = scene.is_orth;
			if (ImGui::RadioButton("Perspective", &active_axes, 0))
			{
				scene.is_orth = false;
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("Orthographic", &active_axes, 1))
			{
				scene.is_orth = true;
			}

			static float f_camera_trans_x = 0.0f;
			ImGui::SliderFloat("eye x", &f_camera_trans_x, -100.0f, 100.0f);
			static float f_camera_trans_y = 0.0f;
			ImGui::SliderFloat("eye y", &f_camera_trans_y, -100.0f, 100.0f);
			static float f_camera_trans_z = 0.0f;
			ImGui::SliderFloat("eye z", &f_camera_trans_z, -100.0f, 100.0f);


			scene.SetActiveCameraViewParams(f_camera_trans_x, 
				f_camera_trans_y, 
				f_camera_trans_z);




			// projection params
			static float f_fovy = 0.0f;
			ImGui::SliderFloat("fovy", &f_fovy, -100.0f, 100.0f);
			static float apect_ratio = 0.0f;
			ImGui::SliderFloat("apect ratio", &apect_ratio, -100.0f, 100.0f);
			static float f_near = 0.0f;
			ImGui::SliderFloat("near", &f_near, -100.0f, 100.0f);
			static float f_far = 0.0f;
			ImGui::SliderFloat("far", &f_far, -100.0f, 100.0f);



			// bound box
			bool checkbox_bound_box = scene.GetBoundBox();
			ImGui::Checkbox("Bound box", &checkbox_bound_box);
			scene.SetBoundBox(checkbox_bound_box);




			



		}
		else
		{
			ImGui::Text("Please load model to start: File->Load Model");
		}
		

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