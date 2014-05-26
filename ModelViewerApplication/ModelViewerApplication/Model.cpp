#include "Model.h"

void Model::InitializeModel(DirectX* inDirectX, MainCamera* inCamera) {
		
	directX = inDirectX;
	camera = inCamera;

	immediateContext = directX->GetContext();
	device = directX->GetDevice();
	swapChain = directX->GetSwapChain();
	renderTargetView = directX->GetRenderTarget();
	depthStencilView = directX->GetDepthStencilView();

	InitializeMesh();
	InitializeEffect();
	InitializeLayout();
	InitializeStates();

}

void Model::Update() {


}

void Model::SetupRender() {
	UINT stride = sizeof( ColorVertex );
    UINT offset = 0;
    immediateContext->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );

	technique = fx->GetTechniqueByName("Tech");
	immediateContext->IASetInputLayout(vertexLayout);

	immediateContext->RSSetState(rasterizerState);
		
	XMFLOAT4 cameraPos = camera->getPositon();
	XMFLOAT4 camLookAt = camera->getLookAt();

	fxEyePos->SetRawValue(new XMFLOAT3(cameraPos.x, cameraPos.y, cameraPos.z), 0, sizeof(XMFLOAT3));
	
	fxLightVector->SetRawValue(new XMFLOAT3(camLookAt.x, camLookAt.y, camLookAt.z), 0, sizeof(XMFLOAT3));
	
}

void Model::SetupWVPMatrix() {

	XMMATRIX matrixViewproj = XMLoadFloat4x4(&camera->GetViewProjMatrix());
	
	XMMATRIX matrixWorld = XMLoadFloat4x4(&worldMatrix);

	XMMATRIX wvp = XMMatrixMultiply(matrixWorld, matrixViewproj);

	fxWVP->SetMatrix((float*)&wvp);
}


void Model::Render() {
		
	float ClearColor[4] = { 0.0f, 0.7f, 0.9f, 0.0f }; // red,green,blue,alpha
	immediateContext->ClearRenderTargetView(renderTargetView, ClearColor );
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	D3DX11_TECHNIQUE_DESC techDesc;
	technique->GetDesc(&techDesc);
		
	for(UINT p = 0; p < techDesc.Passes; ++p) {
		
		technique->GetPassByIndex(p)->Apply(0, immediateContext);

		immediateContext->Draw( verticesCount, 0 );
	}
	
	swapChain->Present(0, 0);
}


void Model::InitializeMesh() {
	
	verticesCount = 36;

    D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
    bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( ColorVertex ) * verticesCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory( &InitData, sizeof(InitData) );
	InitData.pSysMem = cube;
	
	device->CreateBuffer( &bd, &InitData, &vertexBuffer );

    // Set vertex buffer
    UINT stride = sizeof( ColorVertex );
    UINT offset = 0;
    immediateContext->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );

    // Set primitive topology
    immediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );


}

void Model::InitializeEffect() {
	//Creating the effect
	compiledShader = 0;
	compilationMsgs = 0;
	
	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "VS", "fx_5_0", 0, 0, 0, 
		&compiledShader, &compilationMsgs, 0);

	if (FAILED(hr)) {
		MessageBox( NULL,
                    L"Compiling the .fx from file failed", L"Error", MB_OK );
	}

	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &fx);

	if (FAILED(hr)) {
		MessageBox( NULL,
                    L"create effect from memory failed", L"Error", MB_OK );
	}

	//getting the right technique
	technique = fx->GetTechniqueByName("Tech");

	//setting the cbuffer to the world view proj matrix
	fxWVP = fx->GetVariableByName("gWVP")->AsMatrix();
	fxWorldInvTransMatrix = fx->GetVariableByName("worldInv")->AsMatrix();

	//setNormals();
	
	//setting the lighting variables
	fxDiffuseMaterial = fx->GetVariableByName("diffuseMaterial");
	fxDiffuseLight = fx->GetVariableByName("diffuseLight");
	fxLightVector = fx->GetVariableByName("lightVector");
	fxAmbientLightcolor = fx->GetVariableByName("ambientLightColor");

	fxDiffuseMaterial->SetRawValue(new XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), 0,sizeof(XMFLOAT4));
	fxDiffuseLight->SetRawValue(new XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f), 0, sizeof(XMFLOAT4));
	
	fxLightVector->SetRawValue(new XMFLOAT3(0.0f, 0.0f, 0.0f), 0, sizeof(XMFLOAT3));

	fxAmbientLightcolor->SetRawValue(new XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f), 0, sizeof(XMFLOAT4));

	fxSpecularMaterial = fx->GetVariableByName("specularMaterial"); 
	fxSpecularLight = fx->GetVariableByName("specularLight"); 
	fxSpecularPower = fx->GetVariableByName("specularPower")->AsScalar(); 
	fxEyePos = fx->GetVariableByName("eyePos");

	fxSpecularMaterial->SetRawValue(new XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), 0, sizeof(XMFLOAT4));
	fxSpecularLight->SetRawValue(new XMFLOAT4 (0.8, 0.8f, 0.8f, 1.0f), 0, sizeof(XMFLOAT4));
	fxSpecularPower->SetFloat(1.0f);
	
	//XMFLOAT4 cameraPos = camera->getPositon();

	//fxEyePos->SetRawValue(new XMFLOAT3(0, 0, 0), 0, sizeof(XMFLOAT3));
}

void Model::InitializeLayout() {
	// Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	D3DX11_PASS_DESC passDesc;
	technique->GetPassByIndex(0)->GetDesc(&passDesc);
	hr = device->CreateInputLayout(layout, numElements, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &vertexLayout );

    // Set the input layout
    immediateContext->IASetInputLayout(vertexLayout);
}

void Model::InitializeStates() {
	//Set up rastierizer state
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	
	device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	immediateContext->RSSetState(rasterizerState);
}

void Model::InitializeModelWorldMatrix() {
	XMMATRIX matrixWorld;
	matrixWorld = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, matrixWorld);
}

XMFLOAT4X4 Model::GetWorldMatrix() {
	return worldMatrix;
}
