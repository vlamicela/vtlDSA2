#include "vtlCamera.h"



vtlCamera::vtlCamera()
{
	v3Position = vector3(0.0f, 0.0f, 0.0f);
	v3Rotation = vector3(0.0f, 0.0f, 0.0f);
	v3Forward = REAXISX;
	v3Right = REAXISZ;
	v3Up = REAXISY;
	moveSpeed = 1.0f;
	matView = IDENTITY_M4;
	matProj = IDENTITY_M4;
}


vtlCamera::~vtlCamera()
{
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
		
	}
	else {
		//get perspective projection
		matProj = glm::perspective(0.0f, 0.0f, 0.0f, 0.0f);
	}
	return matProj;
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

void vtlCamera::MoveForward(float fMove)
{
	//double speed when shift is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		fMove *= 2;
	}
	//Move relative to Forward vector

	//If W is pressed, move forward
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		v3Position.x += -cos(v3Rotation.x) * fMove;
		v3Position.z += -sin(v3Rotation.x) * fMove;
	}
	//If S is pressed, move back
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		v3Position.x -= -cos(v3Rotation.x) * fMove;
		v3Position.z -= -sin(v3Rotation.x) * fMove;
	}
}

void vtlCamera::MoveSideways(float fMove)
{
	//double speed when shift is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		fMove *= 2;
	}
	//Move relative to Right vector

	//If A is pressed, move left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		v3Position.z += -cos(v3Rotation.z * PI/2) * fMove;
		v3Position.x += -sin(v3Rotation.x * PI/2) * fMove;
	}
	//If D is pressed, move right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		v3Position.z -= -cos(v3Rotation.z * PI / 2) * fMove;
		v3Position.x -= -sin(v3Rotation.x * PI / 2) * fMove;
	}
}

void vtlCamera::MoveVertical(float fMove)
{
	//double speed when shift is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		fMove *= 2;
	}

	//Move relative to Up vector

	//If Q is pressed, move up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		v3Position.y += fMove;
	}
	//If E is pressed, move down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		v3Position.y -= fMove;
	}
}

void vtlCamera::ChangePitch(float fTurn) //X axis
{
	if (fTurn != 0) {
		quaternion p = glm::angleAxis(fTurn, vector3(1.0f, 0.0f, 0.0f));
		matrix4 m4Pitch = glm::toMat4(p);
		v3Rotation;
	}
	//Use mouse movement to change the view and pitch
	//Research how to rotate vec3 with quaternion
	//get a variable based on mouse movement
}

void vtlCamera::ChangeRoll(float fTurn) //Z axis
{
	if (fTurn != 0) {
		quaternion r = glm::angleAxis(fTurn, vector3(0.0f, 0.0f, 1.0f));
		matrix4 m4Roll = glm::toMat4(r);
	}
}

void vtlCamera::ChangeYaw(float fTurn) //Y axis
{
	if (fTurn != 0) {
		quaternion y = glm::angleAxis(fTurn, vector3(0.0f, 1.0f, 0.0f));
		matrix4 m4Yaw = glm::toMat4(y);
	}
}
