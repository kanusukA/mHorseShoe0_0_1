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


void Gui::StatusTab(ImVec2 pos,int* fps)
{
	
	this->StatusWindowPos = pos;
	this->fps = fps;

	if (this->playerObserver == nullptr) {
		std::cout << "Information not provided for Status Tab!";
	}
	else {
		showStatusTab = true;
	}

}

void Gui::ShowADDTab(bool b)
{
	std::cout << "Showing Add Status - " << b << std::endl;
	showAddTab = b;
}

void Gui::setPlayerObserver(PlayerObserver* pObserver)
{
	this->playerObserver = pObserver;
}


void Gui::updateGui()
{
	imOverlay->NewFrame();

	if (this->showStatusTab) {
		_statusTab();
	}
	if (this->showAddTab) {
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
	ImGui::SetNextWindowPos(ImVec2(0,0));
	ImGui::SetNextWindowSize(ImVec2(250, 100));
	
	ImGui::Begin("STATUS",0,ImGuiWindowFlags_NoMove && ImGuiWindowFlags_NoCollapse && ImGuiWindowFlags_NoResize);

	ImGui::Text("Position");
	ImGui::Value("X", this->playerObserver->getPlayerPosition().x);
	ImGui::SameLine();
	ImGui::Value("Y", this->playerObserver->getPlayerPosition().y);
	ImGui::SameLine();
	ImGui::Value("Z", this->playerObserver->getPlayerPosition().z);

	ImGui::Text("Rotation");
	ImGui::Value("X", this->playerObserver->getPlayerRotation().x);
	ImGui::SameLine();
	ImGui::Value("Y", this->playerObserver->getPlayerRotation().y);
	ImGui::SameLine();
	ImGui::Value("Z", this->playerObserver->getPlayerRotation().z);

	ImGui::Value("FPS", *this->fps);

	ImGui::End();

}

void Gui::_addTab()
{
	ImGui::Begin("ADD");
	ImGui::InputText("Add Name",this->guiComponent->getObjectName());

	if(this->renderMeshes->size() > 0) {

		ImGui::BeginCombo("Render Mesh", this->renderMeshes->at(renderMeshesPosition).c_str());

		for (int i = 0; i < this->renderMeshes->size(); i++)
		{
			if (ImGui::Selectable(this->renderMeshes->at(i).c_str(), i == this->renderMeshesPosition)) {
				this->renderMeshesPosition = i;
			}
		}

		ImGui::EndCombo();

	}
	else {
		ImGui::Text("No Render Mesh Found.");
	}
	
	ImGui::Text("PhysX Type");

	if (ImGui::RadioButton("DYNAMIC", this->guiComponent->getPhysicsType() == phyType::DYNAMIC))
	{
		this->guiComponent->setPhysicsType(phyType::DYNAMIC);
	}
	if (ImGui::RadioButton("STATIC", this->guiComponent->getPhysicsType() == phyType::STATIC))
	{
		this->guiComponent->setPhysicsType(phyType::STATIC);
	}
	if (ImGui::RadioButton("MESH", this->guiComponent->getPhysicsType() == phyType::MESH))
	{
		this->guiComponent->setPhysicsType(phyType::MESH);
	}

	if (this->guiComponent->getPhysicsType() == phyType::DYNAMIC) {
		ImGui::InputInt("Mass", this->guiComponent->getMass());
		ImGui::InputInt3("Collider Size", this->c_size);

	}else if (this->guiComponent->getPhysicsType() == phyType::STATIC) {
		ImGui::InputInt3("Collider Size", this->c_size);
	}
	

	ImGui::InputInt3("Position", this->pos);

	if (ImGui::Button("ADD")) {
		this->guiComponent->addObject();
	}

	ImGui::End();
}

void Gui::_debugTab()
{
	ImGui::Begin("Debug");
	if (ImGui::Button("ShowRender"))
	{
		this->guiComponent->showRenderMeshes();
	}
	if (ImGui::Button("ShowDebugLines"))
	{
		this->guiComponent->showDebugLines();
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