#include "vtlCamera.h"



vtlCamera::vtlCamera()
{
	v3Position = vector3(0.0f, 0.0f, 0.0f);
	v3Rotation = vector3(0.0f, 0.0f, 0.0f);
	v3Forward = REAXISZ;
	v3Right = REAXISX;
	v3Up = REAXISY;
	v3Target = vector3(0.0f, 0.0f, 0.0f);

	moveSpeed = 0.1f;
	turnSpeed = 0.1f;
	matView = IDENTITY_M4;
	matProj = IDENTITY_M4; //active projection matrix
	matProjO = glm::ortho(0.0f, 1080.0f, 768.0f, 0.0f);
	matProjP = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);

	fYaw = fPitch = fRoll = 0.0f;
}


vtlCamera::~vtlCamera()
{
}

void vtlCamera::MouseMove(int x, int y)
{
	//check to see if mouse is pressed
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->ChangeYaw(x * turnSpeed);
		this->ChangePitch(y * turnSpeed);
	}
	//get deltaX and deltaY, differences between this frame's coords and last frame's
	//plug them into the Yaw and Pitch methods, respectively
	int mouseX, mouseY;
	
}

//position * rotation = view
matrix4 vtlCamera::GetView()
{
	return matView;
}


matrix4 vtlCamera::GetProjection(bool bOrt)
{
	
	if (bOrt) {
		//get orthographic projection
		//matProj = glm::ortho(0.0f, 0.0f, 0.0f, 0.0f);
		matProj = matProjO;
	}
	else {
		//get perspective projection
		//matProj = glm::perspective(0.0f, 0.0f, 0.0f, 0.0f);
		matProj = matProjP;
	}
	return matProj;
}

void vtlCamera::UpdateView()
{
	/*quatKey = glm::quat(vector3(keyP, keyY, keyR));
	keyP = keyY = keyR = 0.0f;

	qRotation = glm::quat(vector3(keyP, keyY, keyR));*/
	p = glm::angleAxis(fPitch, REAXISX);
	y = glm::angleAxis(fYaw, REAXISY);
	r = glm::angleAxis(fRoll, REAXISZ);
	qRotation = p * y * r;
	qRotation = glm::normalize(qRotation);
	matrix4 turn = glm::mat4_cast(qRotation);

	//matView = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	matView = turn * glm::translate(IDENTITY_M4, v3Position);
}

void vtlCamera::SetPosition(vector3 vPos)
{
	//Move the vtlCamera to the position indicated by vPos
	v3Position = vPos;
}

void vtlCamera::SetTarget(vector3 vTarg)
{
	//Turn the vtlCamera to face the target point indicated by vTarg
	matrix4 look = glm::lookAt(v3Position, vTarg, vector3(0.0f, 1.0f, 0.0f));
	matView = look;
	//change the forward, right and up vectors
}



void vtlCamera::SetUp(vector3 vUp)
{
	//make the up vector point up in terms of the object
	v3Up = vUp;
}

void vtlCamera::SetProjection(vector3 pos, vector3 rot)
{
	//matProj = glm::translate(IDENTITY_M4, pos) * glm::rotate(IDENTITY_M4, 1.0f, rot);
	matView = glm::translate(IDENTITY_M4, pos) * glm::rotate(IDENTITY_M4, 1.0f, rot);
}

void vtlCamera::MoveForward(float fMove)
{
	//Move relative to Forward vector
	//v3Position += v3Forward * fMove;
	v3Position += vector3(
		cos(glm::radians(fPitch)) * -sin(glm::radians(fYaw)), 
		0.0f, 
		cos(glm::radians(fPitch)) * cos(glm::radians(fYaw))) * fMove;
}

void vtlCamera::MoveSideways(float fMove)
{
	//Move relative to Right vector
	vector3 vecMove = vector3(0.0f, 0.0f, 0.0f);
	//v3Position += v3Right * fMove;
	v3Position += vector3(
		cos(glm::radians(fPitch)) * cos(glm::radians(fYaw)),
		0.0f,
		cos(glm::radians(fPitch)) * sin(glm::radians(fYaw))) * fMove;
}

void vtlCamera::MoveVertical(float fMove)
{
	//Move relative to Up vector
	v3Position -= v3Up * fMove;
}

void vtlCamera::ChangePitch(float fTurn) //X axis
{
	fPitch += fTurn;
	
	//if (fTurn != 0) {
	//	p = glm::angleAxis(fTurn, vector3(1.0f, 0.0f, 0.0f));
	//	matrix4 m4Pitch = glm::toMat4(p);
	//	v3Rotation;
	//	//store quats in member field, then apply them when calculating the view
	//	//
	//}
	//Use mouse movement to change the view and pitch
	//Research how to rotate vec3 with quaternion
	//get a variable based on mouse movement
}

void vtlCamera::ChangeRoll(float fTurn) //Z axis
{
	fRoll += fTurn;
	/*if (fTurn != 0) {
		r = glm::angleAxis(fTurn, vector3(0.0f, 0.0f, 1.0f));
		matrix4 m4Roll = glm::toMat4(r);
	}*/
}

void vtlCamera::ChangeYaw(float fTurn) //Y axis
{
	fYaw += fTurn;
	/*if (fTurn != 0) {
		y = glm::angleAxis(fTurn, vector3(0.0f, 1.0f, 0.0f));
		matrix4 m4Yaw = glm::toMat4(y);
	}*/
}
