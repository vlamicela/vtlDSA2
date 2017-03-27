#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve
	static DWORD timeSinceBoot = GetTickCount(); //time since bootup
	DWORD timeSinceStart = GetTickCount() - timeSinceBoot; //time since program started
	float fTime = timeSinceStart / 1000.0f; //in milliseconds
	std::vector<vector3> traPath; //translation path
	traPath.push_back(vector3(0.0f, 0.0f, 0.0f)); //base
	traPath.push_back(vector3(0.0f, 5.0f, 0.0f)); //top

	int flagT = 0; //tracks point in translate path
	int nextT = flagT + 1 % (traPath.size());
	vector3 tStart = traPath[flagT]; //point A
	vector3 tEnd = traPath[nextT]; //point B
	vector3 tCurrent = vector3(0, 0, 0); //progress from A to B
	//vector3 tPos = vector3(0, 0, 0);

	float perc = MapValue(fTime, 0.0f, 5.0f, 0.0f, 1.0f); //percentage from A to B
	while (perc > 1.0f) {
		//reset percentage, seek next flag
		perc -= 1.0f;
		flagT++;
		if (flagT > traPath.size() - 1) {
			flagT = 0;
		}
		nextT = flagT + 1;
		if (nextT > traPath.size() - 1) {
			nextT = 0;
		}
	}
	tStart = traPath[flagT]; //new point A
	tEnd = traPath[nextT]; //new point B
	tCurrent = glm::lerp(tStart, tEnd, perc); //distance from point A to B

	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	m_m4Steve = glm::rotate(IDENTITY_M4, fTime * 72, vector3(0.0f, 0.0f, 1.0f)) * glm::translate(tCurrent); //rotate and translate the Steve

#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
