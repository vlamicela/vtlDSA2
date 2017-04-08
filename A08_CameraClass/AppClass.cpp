#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("E10_Projections"); // Window Name
}
//vtlCamera* m_vCam;
void AppClass::InitVariables(void)
{
	//Generate the floor
	m_pFloor = new PrimitiveClass();
	m_pFloor->GeneratePlane(100.0f, REGREEN);

	//Launch the lions
	lionB = new PrimitiveClass();
	lionB->GenerateCuboid(vector3(2.0f, 7.0f, 2.0f), REBLUE);
	lionY = new PrimitiveClass();
	lionY->GenerateCuboid(vector3(2.0f, 7.0f, 2.0f), REYELLOW);
	lionR = new PrimitiveClass();
	lionR->GenerateCuboid(vector3(2.0f, 7.0f, 2.0f), RERED);
	lionG = new PrimitiveClass();
	lionG->GenerateCuboid(vector3(2.0f, 7.0f, 2.0f), REGREENDARK);
	lionK = new PrimitiveClass();
	lionK->GenerateCuboid(vector3(4.0f, 7.0f, 2.0f), REBLACK);
	voltron = new PrimitiveClass();
	voltron->GenerateCube(3.0f, REWHITE);

	//The space mice are helping too
	mouseX = sf::Mouse::getPosition().x;
	mouseY = sf::Mouse::getPosition().y;

//	cornerA = new PrimitiveClass();
	//Calculate the first projections
	m_vCam = new vtlCamera();
	m_vCam->SetPosition(vector3(1.0f, 1.0f, -4.0f));
	m_vCam->matProj = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	m_vCam->matView = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	//m_m4View = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 14.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	camSpeed = 1.0f;
}

void AppClass::Update(void)
{
	//Update mouse coords
	lastX = mouseX;
	lastY = mouseY;
	mouseX = sf::Mouse::getPosition().x;
	mouseY = sf::Mouse::getPosition().y;
	deltaX = mouseX - lastX;
	deltaY = mouseY - lastY;
	m_vCam->MouseMove(deltaX, deltaY);
	
	//Update the system's time
	m_pSystem->UpdateTime();
	
	m_vCam->GetView();
	m_vCam->GetProjection(false);
	m_vCam->UpdateView();
	if (m_vCam->fRoll > 0.0f) {
		m_vCam->fRoll -= 0.1;
	}
	if (m_vCam->fRoll < 0.0f) {
		m_vCam->fRoll += 0.1;
	}
	//Update camera position/rotation; get input

	//Update matrix
	//m_vCam->SetProjection(vector3(1.0, 1.0, 1.0), vector3(0.0, 0.0, 0.0));

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Print info on screen
	m_pMeshMngr->PrintLine(" ");
	m_pMeshMngr->PrintLine("Controls:");
	m_pMeshMngr->PrintLine("WS - Forward/Backward		AD - Left/Right");
	m_pMeshMngr->PrintLine("Click and drag/IJKL - Look around");
	m_pMeshMngr->PrintLine("QE - Up/Down		UO - Roll");
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	
	//Render the grid
	//m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	//Render the floor
	m_pFloor->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, REAXISY * -1.5f) * glm::rotate(90.0f, vector3(1.0f, 0.0f, 0.0f)));

	//Form feet and legs
	lionY->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(1.0f, 2.0f, 0.0f)));
	lionB->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(-1.0f, 2.0f, 0.0f)));
	//Form arms and body
	lionR->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(-3.0f, 9.0f, 0.0f)));
	lionG->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(3.0f, 9.0f, 0.0f)));
	lionK->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(0.0f, 9.0f, 0.0f)));
	//And I'll form the head
	voltron->Render(m_vCam->matProj, m_vCam->matView, glm::translate(IDENTITY_M4, vector3(0.0f, 14.0f, 0.0f)));

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCylinder);

	//Release the memory of the inherited fields
	super::Release(); 
}