#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop) {
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	//one point for the top
	vector3 top(0, 0, -a_fHeight);
	//circle of points for the base
	std::vector<vector3> base;
	vector3 baseCenter(0, 0, a_fHeight);
	float angle = 0;
	float increment = 360 / a_nSubdivisions;
	for (int x = 0; x < a_nSubdivisions; x++) {
		//create a point and add it to the list
		//cos of angle
		vector3 point(cos(glm::radians(angle)) * a_fRadius, sin(glm::radians(angle)) * a_fRadius, a_fHeight);
		base.push_back(point);
		//increment angle
		angle += increment;
	}

	//Create tris from point, point+1, top
	for (int t = 0; t < a_nSubdivisions - 1; t++) {
		AddTri(base[t+1], base[t], top);
	}
	AddTri(base[0], base[a_nSubdivisions - 1], top);
	for (int b = 0; b < a_nSubdivisions - 1; b++) {
		AddTri(base[b], base[b+1], baseCenter);
	}
	AddTri(base[a_nSubdivisions - 1], base[0], baseCenter);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	//make a ring of points for the base and the top
	std::vector<vector3> base;
	vector3 baseCenter(0, 0, -a_fHeight);
	std::vector<vector3> top;
	vector3 topCenter(0, 0, a_fHeight);
	float angle = 0;
	float increment = 360 / a_nSubdivisions;
	for (int x = 0; x < a_nSubdivisions; x++) {
		//create points for ends and add them to corresponding lists
		vector3 basePoint(cos(glm::radians(angle)) * a_fRadius, sin(glm::radians(angle)) * a_fRadius, -a_fHeight);
		vector3 topPoint(cos(glm::radians(angle)) * a_fRadius, sin(glm::radians(angle)) * a_fRadius, a_fHeight);
		base.push_back(basePoint);
		top.push_back(topPoint);
		angle += increment;
	}

	//create quads from endpoints
	//3--2
	//|  |
	//0--1
	for (int c = 0; c < a_nSubdivisions - 1; c++) {
		AddQuad(base[c], base[c + 1], top[c], top[c + 1]);
	}
	AddQuad(base[a_nSubdivisions - 1], base[0], top[a_nSubdivisions - 1], top[0]);
	//fill in ends with tris
	for (int t = 0; t < a_nSubdivisions - 1; t++) {
		AddTri(top[t], top[t+1], topCenter);
	}
	AddTri(top[a_nSubdivisions - 1], top[0], topCenter);
	for (int b = 0; b < a_nSubdivisions - 1; b++) {
		AddTri(base[b + 1], base[b], baseCenter);
	}
	AddTri(base[0], base[a_nSubdivisions - 1], baseCenter);
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	
	//make 2 rings of points for base and top
	std::vector<vector3> baseOut;
	std::vector<vector3> topOut;
	std::vector<vector3> baseIn;
	std::vector<vector3> topIn;
	float angle = 0;
	float increment = 360 / a_nSubdivisions;
	//generate points
	//base outer
	for (int b = 0; b < a_nSubdivisions; b++) {
		vector3 bPoint(cos(glm::radians(angle)) * a_fOuterRadius, sin(glm::radians(angle)) * a_fOuterRadius, -a_fHeight);
		baseOut.push_back(bPoint);
		angle += increment;
	}
	angle = 0;
	//base inner
	for (int bi = 0; bi < a_nSubdivisions; bi++) {
		vector3 biPoint(cos(glm::radians(angle)) * a_fInnerRadius, sin(glm::radians(angle)) * a_fInnerRadius, -a_fHeight);
		baseIn.push_back(biPoint);
		angle += increment;
	}
	angle = 0;
	//top outer
	for (int t = 0; t < a_nSubdivisions; t++) {
		vector3 tPoint(cos(glm::radians(angle)) * a_fOuterRadius, sin(glm::radians(angle)) * a_fOuterRadius, a_fHeight);
		topOut.push_back(tPoint);
		angle += increment;
	}
	angle = 0;
	//top inner
	for (int ti = 0; ti < a_nSubdivisions; ti++) {
		vector3 tiPoint(cos(glm::radians(angle)) * a_fInnerRadius, sin(glm::radians(angle)) * a_fInnerRadius, a_fHeight);
		topIn.push_back(tiPoint);
		angle += increment;
	}

	//create quads
	//2---3		3---2 
	//| \ |		| \ | inner
	//0---1		1---0
	//outer surface
	for (int o = 0; o < a_nSubdivisions - 1; o++) {
		AddQuad(baseOut[o], baseOut[o+1], topOut[o], topOut[o+1]);
	}
	AddQuad(baseOut[a_nSubdivisions - 1], baseOut[0], topOut[a_nSubdivisions - 1], topOut[0]);
	//inner surface
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(baseIn[i+1], baseIn[i], topIn[i+1], topIn[i]);
	}
	AddQuad(baseIn[0], baseIn[a_nSubdivisions - 1], topIn[0], topIn[a_nSubdivisions - 1]);
	//connect surfaces
	//top surface
	for (int c = 0; c < a_nSubdivisions - 1; c++) {
		AddQuad(topOut[c], topOut[c+1], topIn[c], topIn[c+1]);
	}
	AddQuad(topOut[a_nSubdivisions - 1], topOut[0], topIn[a_nSubdivisions - 1], topIn[0]);
	//bottom text
	for (int cb = 0; cb < a_nSubdivisions - 1; cb++) {
		AddQuad(baseOut[cb+1], baseOut[cb], baseIn[cb+1], baseIn[cb]);
	}
	AddQuad(baseOut[0], baseOut[a_nSubdivisions - 1], baseIn[0], baseIn[a_nSubdivisions - 1]);
	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	
	//make two rings of points for the midsection
	std::vector<vector3> midOuter;
	std::vector<vector3> midInner;
	//make a ring of points for the top and bottom
	//use trig to generate smoothing rings

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	int s = a_nSubdivisions; //abbrev. for rest of code
	float r = a_fRadius;
	float scale = 1;
	float increment = 2 * PI / s;
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			float angle1 = increment * i;
			float angle2 = increment * j;
			//2---3
			//| \ |
			//0---1
			vector3 point0(r * sin(glm::radians(angle1)) * cos(glm::radians(angle2)), r * sin(glm::radians(angle1)) * sin(glm::radians(angle2)), r * cos(glm::radians(angle1)));
			vector3 point1(r * sin(glm::radians(angle1)) * cos(glm::radians(angle2)), r * sin(glm::radians(angle1)) * sin(glm::radians(angle2)), r * cos(glm::radians(angle1)));
			vector3 point2(r * sin(glm::radians(angle1)) * cos(glm::radians(angle2)), r * sin(glm::radians(angle1)) * sin(glm::radians(angle2)), r * cos(glm::radians(angle1)));
			vector3 point3(r * sin(glm::radians(angle1)) * cos(glm::radians(angle2)), r * sin(glm::radians(angle1)) * sin(glm::radians(angle2)), r * cos(glm::radians(angle1)));
			AddQuad(point0 * scale, point1 * scale, point2 * scale, point3 * scale);
		}
	}

	//Your code ends here
	CompileObject(a_v3Color);
}