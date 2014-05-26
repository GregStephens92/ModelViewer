#include "MainCamera.h"


void MainCamera::InitializeCameraMatrixs() {
	InitializeViewMatrix();
	InitializeProjMatrix();
	InitializeViewProjMatrix();
}


void MainCamera::InitializeViewMatrix() {
		
	//defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	defaultForward.x = 0.0f;
	defaultForward.y = 0.0f;
	defaultForward.z = 1.0f;
	defaultForward.w = 0.0f;
	
	//defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	defaultRight.x = 1.0f;
	defaultRight.y = 0.0f;
	defaultRight.z = 0.0f;
	defaultRight.w = 0.0f;

	//forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	forward.x = 0.0f;
	forward.y = 0.0f;
	forward.z = 1.0f;
	forward.w = 0.0f;

	//right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	right.x = 1.0f;
	right.y = 0.0f;
	right.z = 0.0f;
	right.w = 0.0f;

	leftRight = 0.0f;
	forwardBackward = 0.0f;
	upDown = 0.0f;

	yaw = 0.0f;
	pitch = 0.0f;

	//cameraPos = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	cameraPos.x = 0.0f;
	cameraPos.y = 0.0f;
	cameraPos.z = -5.0f;
	cameraPos.w = 0.0f;

	//lookAt = XMVectorZero();
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 0.0f;
	lookAt.w = 0.0f;

	//up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	up.w = 1.0f;

	XMMATRIX matrixViewMatrix;;

	matrixViewMatrix = XMMatrixLookAtLH(XMLoadFloat4(&cameraPos), XMLoadFloat4(&lookAt), XMLoadFloat4(&up));

	XMStoreFloat4x4(&viewMatrix, matrixViewMatrix);

}

void MainCamera::InitializeProjMatrix() {
	XMMATRIX matrixProj;
	
	matrixProj = XMMatrixPerspectiveFovLH(0.25f * XM_PI, (float)800 / (float)640, 0.1f, 1000.0f);

	XMStoreFloat4x4(&projMatrix, matrixProj);
}

void MainCamera::InitializeViewProjMatrix() {

	XMMATRIX matrixViewproj;
	
	matrixViewproj = XMMatrixMultiply(XMLoadFloat4x4(&GetViewMatrix()), XMLoadFloat4x4(&GetProjMatrix()));
	
	XMStoreFloat4x4(&viewprojMatrix, matrixViewproj);
}

XMFLOAT4X4 MainCamera::GetViewMatrix() {
	return viewMatrix;
}

XMFLOAT4X4 MainCamera::GetProjMatrix() {
	return projMatrix;
}

XMFLOAT4X4 MainCamera::GetViewProjMatrix() {
	return viewprojMatrix;
}