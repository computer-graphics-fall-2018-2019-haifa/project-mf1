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

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &showAnotherWindow);

		//ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color



		/*
		static int active_axes = 1;
		ImGui::RadioButton("X", &active_axes, 0); ImGui::SameLine();
		ImGui::RadioButton("Y", &active_axes, 1); ImGui::SameLine();
		ImGui::RadioButton("Z", &active_axes, 2);
		*/
		//printf("%d\n", item_type);

		/*
		static int active_axes = 0;
		if (ImGui::RadioButton("X", active_axes == 0)) { mode = Mode_Copy; } ImGui::SameLine();
		if (ImGui::RadioButton("Y", active_axes == 1)) { mode = Mode_Move; } ImGui::SameLine();
		if (ImGui::RadioButton("Z", active_axes == 2)) { mode = Mode_Swap; }
		*/

		ImGui::Text("Model");


		static float f_scale_x = 1.0f;
		ImGui::SliderFloat("scaleX", &f_scale_x, 0.1f, 100.0f);
		static float f_scale_y = 1.0f;
		ImGui::SliderFloat("scaleY", &f_scale_y, 0.1f, 100.0f);
		static float f_scale_z = 1.0f;
		ImGui::SliderFloat("scaleZ", &f_scale_z, 0.1f, 100.0f);


		static float f_trans_x = 0.0f;
		ImGui::SliderFloat("transX", &f_trans_x, -500.0f, 500.0f);
		static float f_trans_y = 0.0f;
		ImGui::SliderFloat("transY", &f_trans_y, -500.0f, 500.0f);
		static float f_trans_z = 0.0f;
		ImGui::SliderFloat("transZ", &f_trans_z, -500.0f, 500.0f);

		static float f_rotation = 0.0f;
		ImGui::SliderFloat("rotation", &f_rotation, -360.0f,360.0f);

		scene.scaleX = f_scale_x;
		scene.scaleY = f_scale_y;
		scene.scaleZ = f_scale_z;

		scene.translationX = f_trans_x;
		scene.translationY = f_trans_y;
		scene.translationZ = f_trans_z;

		scene.rotationAngle = f_rotation;

		ImGui::Text("Camera");

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


		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

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