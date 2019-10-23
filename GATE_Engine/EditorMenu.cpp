#include "EditorMenu.h"
#include "libs/imgui/imgui.h"
#include "Application.h"

void EditorMenu::Update() {
	if (ImGui::BeginMenuBar()) {

		// Menu - File: Options for file and App management
		if (ImGui::BeginMenu("File")) {

			if (ImGui::MenuItem("New Scene", "Ctrl+N")) {

			}

			if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Save", "Ctrl+S")) {

			}

			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("New Project", "Ctrl+Shift+N")) {

			}

			if (ImGui::MenuItem("Open Project", "Ctrl+Shift+O")) {

			}

			if (ImGui::MenuItem("Save Project")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit", "(Alt+F4)", false)) {

				//return update_status::UPDATE_STOP;	//CHANGE/FIX: Create an App bool which flags the desire of shutting down the app
			}

			ImGui::EndMenu();
		}

		// Menu - Edit: Tools for easier edition
		if (ImGui::BeginMenu("Edit")) {

			if (ImGui::MenuItem("Undo", "Ctrl+Z")) {

			}

			if (ImGui::MenuItem("Redo", "Ctrl+Y")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Select All", "Ctrl+A")) {

			}

			if (ImGui::MenuItem("Deselect All", "Shift+D")) {

			}

			if (ImGui::MenuItem("Select Children", "Shift+C")) {

			}

			if (ImGui::MenuItem("Invert Selection", "Ctrl+I")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Duplicate", "Ctrl+D")) {

			}

			if (ImGui::MenuItem("Delete", "Supr")) {

			}

			ImGui::Separator();

			if (ImGui::MenuItem("Play", "Ctrl+P")) {

			}

			if (ImGui::MenuItem("Pause", "Ctrl+Shift+P")) {

			}

			if (ImGui::MenuItem("Step", "Ctrl+Alt+P")) {

			}

			ImGui::Separator();

			// MenuItem - Settings: Engine confiuration settings
			if (ImGui::MenuItem("Settings...")) {
				App->editor->editor_configuration.show_window = !App->editor->editor_configuration.show_window;
			}

			ImGui::EndMenu();
		}

		// Menu - Window: View options
		if (ImGui::BeginMenu("Window")) {

			if (ImGui::BeginMenu("Viewport")) {

				//ImGui::Checkbox("Framerate", false);
				//ImGui::Checkbox("Polycount", false);
				//ImGui::Checkbox("Base Grid", false);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Menus")) {

				/*ImGui::MenuItem("hierarchy", NULL, &show_hierarchy_window);
				ImGui::MenuItem("Project", NULL, &show_project_window);
				ImGui::MenuItem("Console", NULL, &show_console_window);
				ImGui::MenuItem("Inspector", NULL, &show_inspector_window);
				ImGui::MenuItem("Scene", NULL, &show_scene_window);
				ImGui::MenuItem("Game", NULL, &show_game_window);*/

				ImGui::EndMenu();
			}


			ImGui::Separator();

			// Menu: Engine Development Tools
			if (ImGui::BeginMenu("DevDebug")) {
				if (ImGui::MenuItem("Show UI Demo"))
					App->editor->show_demo_window = !App->editor->show_demo_window;

				if (ImGui::MenuItem("Generate Random Game"))
					App->RequestBrowser("https://www.youtube.com/watch?v=dQw4w9WgXcQ");

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		// Menu - GameObjects: Create premade objects and primitives
		if (ImGui::BeginMenu("GameObjects")) {

			if (ImGui::BeginMenu("Create...")) {

				if (ImGui::MenuItem("Plane"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::PLANE, 1, 1);
				}

				if (ImGui::MenuItem("Cube"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::CUBE);
				}

				if (ImGui::MenuItem("Sphere"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::SPHERE, 30, 30);
				}

				if (ImGui::MenuItem("Hemisphere"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::HEMISPHERE, 30, 30);
				}

				if (ImGui::MenuItem("Cylinder"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::CYLINDER, 30, 30);
				}

				if (ImGui::MenuItem("Cone"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::CONE, 30, 30);
				}

				if (ImGui::MenuItem("Torus"))
				{
					App->geometry_loader->CreatePrimitive(PRIMITIVE::TORUS, 30, 30, 0.5f);
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Draw Mode")) {

				if (ImGui::RadioButton("Mesh", &App->editor->drawMode, (int)draw_mode::MESH)
					|| ImGui::RadioButton("Wireframe", &App->editor->drawMode, (int)draw_mode::WIREFRAME)
					|| ImGui::RadioButton("Vertexs", &App->editor->drawMode, (int)draw_mode::VERTEX))
				{
					App->editor->DrawModeChange();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		// Menu - Help: Information & Documentation
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::Button("About GATE...")) {
				App->editor->show_about_window = true;
				ImGui::OpenPopup("About this engine...");
			}

			// PopupModal - About: Information about the engine and its properties
			if (ImGui::BeginPopupModal("About this engine...", &App->editor->show_about_window, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("%s\nA simple engine for 3D game development.\nBy %s, %s", App->GetTitle(), App->GetAuthors(), App->GetOrganization());
				ImGui::Separator();

				ImGui::Text("3rd Party Libraries used:\n");
				ImGui::Bullet();
				if (ImGui::SmallButton("STL (C++11)")) {
					App->RequestBrowser("https://www.geeksforgeeks.org/the-c-standard-template-library-stl/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("SDL (v2.0.10)")) {
					App->RequestBrowser("https://www.libsdl.org/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("OpenGL (v3.1.0)")) {
					App->RequestBrowser("https://www.opengl.org/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("DevIL (v1.8.0)")) {
					App->RequestBrowser("http://openil.sourceforge.net/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("Assimp (v5.0.0)")) {
					App->RequestBrowser("http://assimp.org/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("Dear ImGui (v1.73, Base Code)")) {
					App->RequestBrowser("https://github.com/ocornut/imgui");
				}
				ImGui::Text("  "); ImGui::SameLine();
				if (ImGui::SmallButton("Docking Test Branch (Commit 18/10/19)")) {
					App->RequestBrowser("https://github.com/ocornut/imgui/tree/7feccf9ab2fad261aa873dfa067e64ad9fab8a03");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("glew (v2.0)")) {
					App->RequestBrowser("http://glew.sourceforge.net/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("MathGeoLib (v1.5)")) {
					App->RequestBrowser("https://github.com/juj/MathGeoLib");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("Par (vN/A)")) {
					App->RequestBrowser("https://github.com/prideout/par");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("JSON for Modern C++ (v3.7.0)")) {
					App->RequestBrowser("https://github.com/nlohmann/json");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("Brofiler (v1.1.2)")) {
					App->RequestBrowser("http://www.brofiler.com/");
				}
				ImGui::Bullet();
				if (ImGui::SmallButton("mmgr (vN/A)")) {
					App->RequestBrowser("http://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");
				}

				ImGui::Separator();

				if (ImGui::CollapsingHeader("License")) {
					ImGui::PushTextWrapPos(App->editor->standard_text_width);
					ImGui::Text(App->GetLicense());
					ImGui::PopTextWrapPos();
				}

				ImGui::EndPopup();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/DocDonkeys/GATE/wiki");

			if (ImGui::MenuItem("Download Latest Version"))
				App->RequestBrowser("https://github.com/DocDonkeys/GATE/releases");

			ImGui::Separator();

			if (ImGui::MenuItem("Report Bug / Suggest Feature"))
				App->RequestBrowser("https://github.com/DocDonkeys/GATE/issues");

			if (ImGui::MenuItem("Give us Feedback!"))
				App->RequestBrowser("https://www.youtube.com/watch?v=8o6c1UuoMwI");

			if (ImGui::MenuItem("Contact us!"))
				App->RequestBrowser("https://github.com/DocDonkeys/");



			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}