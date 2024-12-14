#include "Gui.h"



void Gui::initGui(Ogre::ImGuiOverlay* overlay, GuiComponent* component) {
	
	this->guiComponent = component;

	overlay->setZOrder(300);
	overlay->show();

	imOverlay = overlay;

	// Get Resources loaded by the Resource Handler.
	this->renderMeshes = ResourceHandler::GetInstance()->renderMeshes;
	this->colliderMeshes = ResourceHandler::GetInstance()->colliderMeshes;

}


void Gui::StatusTab(ImVec2 pos,int* fps,const Ogre::Vector3* position, Ogre::Vector3* rotation)
{
	
	param->statusPosition = pos;
	param->pPosition = position;
	param->pRotation = rotation;
	param->FPS = fps;

}

void Gui::ShowADDTab(bool b)
{
	param->showADD = b;
}


void Gui::updateGui()
{
	imOverlay->NewFrame();

	if (param->showStatus) {
		_statusTab();
	}
	if (param->showADD) {
		_addTab();
	}
	_debugTab();

	ImGui::EndFrame();
}



void Gui::shutdown()
{
}

void Gui::_statusTab()
{
	ImGui::SetNextWindowPos(param->statusPosition);
	ImGui::SetNextWindowSize(ImVec2(250, 100));
	
	ImGui::Begin("STATUS",0,ImGuiWindowFlags_NoMove && ImGuiWindowFlags_NoCollapse && ImGuiWindowFlags_NoResize);

	ImGui::Text("Position");
	ImGui::Value("X", param->pPosition->x);
	ImGui::SameLine();
	ImGui::Value("Y", param->pPosition->y);
	ImGui::SameLine();
	ImGui::Value("Z", param->pPosition->z);

	ImGui::Text("Rotation");
	ImGui::Value("X", param->pRotation->x);
	ImGui::SameLine();
	ImGui::Value("Y", param->pRotation->y);
	ImGui::SameLine();
	ImGui::Value("Z", param->pRotation->z);

	ImGui::Value("FPS", *param->FPS);

	ImGui::End();

}

void Gui::_addTab()
{
	ImGui::Begin("ADD");
	ImGui::InputText("Add Name", &ap->add_name);

	ImGui::BeginCombo("Render Mesh", ap->renderMeshes[ap->positionRenderMesh]->c_str());

	for (int i = 0; i < ap->renderMeshes.size(); i++)
	{
		if (ImGui::Selectable(ap->renderMeshes[i]->c_str(), i == ap->positionRenderMesh)) {
			ap->positionRenderMesh = i;
		}
	}

	ImGui::EndCombo();
	
	
	ImGui::Text("PhysX Type");

	if (ImGui::RadioButton("DYNAMIC", ap->type == phyType::DYNAMIC))
	{
		ap->type = phyType::DYNAMIC;
	}
	if (ImGui::RadioButton("STATIC", ap->type == phyType::STATIC))
	{
		ap->type = phyType::STATIC;
	}
	if (ImGui::RadioButton("MESH", ap->type == phyType::MESH))
	{
		ap->type = phyType::MESH;
	}

	if (ap->type == phyType::DYNAMIC) {
		ImGui::InputInt("Mass", &ap->mass);
		ImGui::InputInt3("Collider Size", ap->c_size);

	}else if (ap->type == phyType::STATIC) {
		ImGui::InputInt3("Collider Size", ap->c_size);
	}
	

	ImGui::InputInt3("Position", ap->pos);

	if (ImGui::Button("ADD")) {
		if (addObject()) {
			ap->add_name = "Object_Name";
			ap->msh_name = "Mesh_Path_Name";

			param->showADD = false;
		}
	}

	ImGui::End();
}

void Gui::_debugTab()
{
	ImGui::Begin("Debug");
	if (ImGui::Button("ShowRender"))
	{
		param->showRenderShapes = !param->showRenderShapes;
		showRenderShapes(param->showRenderShapes);
	}
	if (ImGui::Button("ShowDebugLines"))
	{
		param->showDebugLines = !param->showDebugLines;
		showDebugLines(param->showDebugLines);
	}
	ImGui::End();
}


void Gui::setWindowGrabPoints(int WIDTH, int HEIGHT)
{
	guiWPos->TOP_RIGHT = ImVec2(WIDTH, 0);
	guiWPos->TOP_LEFT = ImVec2(0, 0);
	guiWPos->TOP_CENTER = ImVec2(WIDTH / 2, 0);

	guiWPos->RIGHT = ImVec2(WIDTH, HEIGHT / 2);
	guiWPos->LEFT = ImVec2(0, HEIGHT / 2);
	guiWPos->CENTER = ImVec2(WIDTH / 2, HEIGHT / 2);

	guiWPos->BOTTOM_RIGHT = ImVec2(WIDTH, HEIGHT);
	guiWPos->BOTTOM_LEFT = ImVec2(0, HEIGHT);
	guiWPos->BOTTOM_CENTER = ImVec2(WIDTH / 2, HEIGHT);
	
}