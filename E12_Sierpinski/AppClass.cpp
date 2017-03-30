#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	m_pMesh->AddVertexPosition(vector3(0.5f, 0.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3( 0.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-0.5f,  0.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)											   //clear the screen
	int r = 3; //number of recursions (Only works properly with 3 right now)
	float left = 0; //starting point for the first triangle in each row
	float row = 0; //layer in the triangle
	float block = 0; //current triangle in row
	for (int i = 0; i < r; i++) {
		//start from the top
		//new row
		left -= 0.5;
		block = left;
		for (int j = 0; j < i; j++) {
			block++;
			m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(block, -row, 0.0)));
			
			//Comment the above line and uncomment this one for a meme
			//m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(block - r/3, -row, 0.0)));
			//noobs cant sierpinski
		}
		row++;
	}
	//repeat process for two more triforces
	row = 0;
	block = 0;
	left = 0;
	for (int i = 0; i < r; i++) {
		//start from the top
		//new row
		left -= 0.5;
		block = left;
		for (int j = 0; j < i; j++) {
			block++;
			m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(block - (r / 3), -row - (r - r/2), 0.0)));
		}
		row++;
	}
	row = 0;
	block = 0;
	left = 0;
	for (int i = 0; i < r; i++) {
		//start from the top
		//new row
		left -= 0.5;
		block = left;
		for (int j = 0; j < i; j++) {
			block++;
			m_pMesh->Render(m4Projection, m4View, glm::translate(vector3(block + (r / 3), -row - (r - r / 2), 0.0)));
		}
		row++;
	}

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}