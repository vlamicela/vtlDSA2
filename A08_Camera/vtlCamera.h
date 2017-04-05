#pragma once

#ifndef __vtlCamera_H_
#define __vtlCamera_H_
#include "AppClass.h"
class vtlCamera
{
public:
	vtlCamera();
	~vtlCamera();
	float moveSpeed; //speed at which the vtlCamera moves
	vector3 v3Position; //position vector
	vector3 v3Rotation; //rotation vector
	vector3 v3Forward; //points forward
	vector3 v3Right; //points right
	vector3 v3Up; //points up
	matrix4 matView; //view matrix
	matrix4 matProj; //projection matrix

	//get View matrix
	matrix4 GetView();
	//get Projection matrix
	matrix4 GetProjection(bool bOrt);

	void SetPosition(vector3 vPos); //sets position of vtlCamera
	void SetTarget(vector3 vTarg); //focuses the vtlCamera
	void SetUp(vector3 vUp); //tells the vtlCamera which way is up

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
#endif //
