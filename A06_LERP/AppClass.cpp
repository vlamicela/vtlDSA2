#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	static DWORD timerSinceBoot = GetTickCount(); //time passed since computer booted up
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot; //time elapsed since program started
	float fTimer = timerSinceStart / 1000.0f; //in milliseconds
	//m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");
	m_pMeshMngr->PrintLine(""); //empty space
	m_pMeshMngr->PrintLine(std::to_string(fTimer)); //display timer

	//create a list of points to seek
	std::vector<vector3> path;
	path.push_back(vector3(-4.0f, -2.0f, 5.0f));
	path.push_back(vector3(1.0f, -2.0f, 5.0f));
	path.push_back(vector3(-3.0f, -1.0f, 3.0f));
	path.push_back(vector3(2.0f, -1.0f, 3.0f));
	path.push_back(vector3(-2.0f, 0.0f, 0.0f));
	path.push_back(vector3(3.0f, 0.0f, 0.0f));
	path.push_back(vector3(-1.0f, 1.0f, -3.0f));
	path.push_back(vector3(4.0f, 1.0f, -3.0f));
	path.push_back(vector3(0.0f, 2.0f, -5.0f));
	path.push_back(vector3(5.0f, 2.0f, -5.0f));
	path.push_back(vector3(1.0f, 3.0f, -5.0f));
	//create sphere for each point
	for (int p = 0; p < path.size(); p++) {
		vector3 pathPoint = path[p];
		matrix4 pathPos = glm::translate(pathPoint) * glm::scale(vector3(0.1));
		m_pMeshMngr->AddSphereToRenderList(pathPos, RERED, WIRE | SOLID);
	}
	int flag = 0; //tracks current point in path
	int flagNext = flag + 1 % (path.size()); //tracks next point
	vector3 v3Start = path[flag];
	vector3 v3End = path[flagNext];
	vector3 v3Current = vector3(0, 0, 0);
	vector3 v3Pos = vector3(1, 0, 0);
	//matrix4 m4Pos = glm::translate(v3Pos);

	float percentage = MapValue(fTimer, 0.0f, 1.0f, 0.0f, 1.0f);
	while (percentage > 1.0f) {
		//set percentage back to 0, then increment flag
		percentage -= 1.0f;
		flag ++;
		if (flag > path.size() - 1) {
			flag = 0;
		}
		flagNext = flag + 1;
		if (flagNext > path.size() - 1) {
			flagNext = 0;
		}
	}
	v3Start = path[flag]; //point A
	v3End = path[flagNext]; //point B
	v3Current = glm::lerp(v3Start, v3End, percentage); //distance between points A and B
	m_pMeshMngr->PrintLine("AB progress: "+ std::to_string(percentage * 100)); //display progress between points
	
	matrix4 m4Pos = glm::translate(v3Current);
	m_pMeshMngr->SetModelMatrix(m4Pos, "WallEye");
	

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	//m_pMeshMngr->Print(std::to_string(fTimer));
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}