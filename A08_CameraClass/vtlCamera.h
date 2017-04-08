#pragma once

//#ifndef __VTLCAMERA_H_
//#define __VTLCAMERA_H_
//#include "AppClass.h"
#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
class vtlCamera
{
public:
	vtlCamera();
	~vtlCamera();
	float moveSpeed; //speed at which the vtlCamera moves
	float turnSpeed; //and rotates
	vector3 v3Position; //position vector
	vector3 v3Rotation; //rotation vector

	float fPitch, fYaw, fRoll;
	quaternion qRotation; //rotation quat

	vector3 v3Forward; //points forward
	vector3 v3Right; //points right
	vector3 v3Up; //points up
	vector3 v3Target; //indicates where we're looking
	
	float mouseX, mouseY, lastX, lastY; //mouse coordinates
	void MouseMove(int x, int y);

	matrix4 matView; //view matrix
	matrix4 matProj; //projection matrix
	matrix4 matProjO; //orthographic projection
	matrix4 matProjP; //perspective projection
	quaternion p, r, y; //pitch, roll, and yaw modifiers
	
	float keyP, keyR, keyY; //rotation quats
	quaternion quatKey; //

	//get View matrix
	matrix4 GetView();
	//get Projection matrix
	matrix4 GetProjection(bool bOrt);
	//update matrix
	void UpdateView();
	

	void SetPosition(vector3 vPos); //sets position of vtlCamera
	void SetTarget(vector3 vTarg); //focuses the vtlCamera
	void SetUp(vector3 vUp); //tells the vtlCamera which way is up
	void SetProjection(vector3 pos, vector3 rot); //Sets the projection matrix

	//Move the vtlCamera forward/backward
	void MoveForward(float fMove);
	//Move the vtlCamera left/right
	void MoveSideways(float fMove);
	//Move the vtlCamera up/down
	void MoveVertical(float fMove);
	//Pitch (X axis)
	void ChangePitch(float fTurn);
	//Roll (Z axis)
	void ChangeRoll(float fTurn);
	//Yaw (Y axis)
	void ChangeYaw(float fTurn);
	
};
//#endif //
