#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
	static bool bLastW = false, bLastA = false, bLastS = false, bLastD = false, bLastQ = false, bLastE = false, bLastLShift = false;
	//test turning with IJKL
	static bool bLastI = false, bLastJ = false, bLastK = false, bLastL = false, bLastU = false, bLastO = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

	//W Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//Move the camera forward
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) m_vCam->MoveForward(m_vCam->moveSpeed * 2);
		else m_vCam->MoveForward(m_vCam->moveSpeed);
		//m_pMeshMngr->Print(std::to_string(m_vCam->v3Position.x));
	}
	//S Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) m_vCam->MoveForward(-m_vCam->moveSpeed * 2);
		else m_vCam->MoveForward(-m_vCam->moveSpeed);
	}
	//A Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) m_vCam->MoveSideways(m_vCam->moveSpeed * 2);
		else m_vCam->MoveSideways(m_vCam->moveSpeed);
	}
	//D Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) m_vCam->MoveSideways(-m_vCam->moveSpeed * 2);
		else m_vCam->MoveSideways(-m_vCam->moveSpeed);
	}
	//Q Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		m_vCam->MoveVertical(m_vCam->moveSpeed);
	}
	//E Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		m_vCam->MoveVertical(-m_vCam->moveSpeed);
	}

	//IJKLUO Turning controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		//pitch forward
		m_vCam->ChangePitch(m_vCam->turnSpeed * 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		//pitch back
		m_vCam->ChangePitch(-m_vCam->turnSpeed * 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
		//yaw left
		m_vCam->ChangeYaw(-m_vCam->turnSpeed * 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		//yaw right
		m_vCam->ChangeYaw(m_vCam->turnSpeed * 10.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
		//roll clockwise
		m_vCam->ChangeRoll(-2.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		//roll counterclockwise
		m_vCam->ChangeRoll(2.0f);
	}

	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}