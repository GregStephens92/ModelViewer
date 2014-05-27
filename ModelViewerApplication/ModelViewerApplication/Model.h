#pragma once

#include <windows.h>
#include <iostream>
#include <string>
#include <d3dx11.h>
#include <d3dx11effect.h>
#include <xnamath.h>
#include "DirectX.h"
#include "MainCamera.h"
#include <vector>

using namespace std;

class Model {


	private:

	DirectX* directX;
	MainCamera* camera;

	//Device / Context
	ID3D11Device*			device;
	ID3D11DeviceContext*	immediateContext;
	
	IDXGISwapChain*         swapChain;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11VertexShader*		vertexShader;

	//Vertex / index Buffer
	ID3D11Buffer*			vertexBuffer;
	ID3D11Buffer*			indexBuffer;

	//Input Layout
	ID3D11InputLayout*		vertexLayout;
	
	//Effect / Technique
	ID3DX11Effect* fx;
	//ID3DBlob* compiledShader;
	//ID3DBlob* compilationMsgs;
	ID3DX11EffectTechnique* technique;

	//Effect variables
	ID3DX11EffectMatrixVariable* fxWVP;
	ID3DX11EffectMatrixVariable* fxWorldMatrix;

	//Matrix's
	XMFLOAT4X4 worldMatrix;
	ID3DX11EffectMatrixVariable* fxWorldInvTransMatrix;

	//Lighting
	ID3DX11EffectVariable* fxDiffuseMaterial;
	ID3DX11EffectVariable* fxDiffuseLight;

	ID3DX11EffectVariable* fxLightVector;
	ID3DX11EffectVariable* fxAmbientLightcolor;

	ID3DX11EffectVariable* fxSpecularMaterial;
	ID3DX11EffectVariable* fxSpecularLight;
	ID3DX11EffectScalarVariable* fxSpecularPower;
	ID3DX11EffectVariable* fxEyePos;

	//Texturing Stuff
	ID3D11ShaderResourceView* faceTextureRV;
	ID3DX11EffectShaderResourceVariable* faceTextureVariable;

	ID3D11ShaderResourceView* faceNormalTextureRV;
	ID3DX11EffectShaderResourceVariable* faceNormalTextureVariable;

	ID3D11ShaderResourceView* skyBoxTextureRV;
	ID3DX11EffectShaderResourceVariable* skyBoxTextureVariable;

	ID3D11ShaderResourceView* houseTextureRV;
	ID3DX11EffectShaderResourceVariable* houseTextureVariable;

	ID3D11ShaderResourceView* houseNormalTextureRV;
	ID3DX11EffectShaderResourceVariable* houseNormalTextureVariable;

	ID3D11ShaderResourceView* gunTextureRV;
	ID3DX11EffectShaderResourceVariable* gunTextureVariable;


	//effect
	ID3D10Blob* compiledShader;
	ID3D10Blob* compilationMsgs;

	//Rasterizer state
	ID3D11RasterizerState* rasterizerState;
	D3D11_RASTERIZER_DESC rasterizerDesc;

	int verticesCount;
	int indexCount;
	float rotation;

	//Mesh Structures
	struct Vertex {
		XMFLOAT3 Pos;
	};

	struct ColorVertex {
		XMFLOAT3 Pos;
		XMFLOAT4 Color;
		XMFLOAT3 Normal;
	};

	struct TexVertex {
		XMFLOAT3 Pos;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
	};

	struct BumpVertex {
		XMFLOAT3 Pos;
		XMFLOAT2 Tex;
		XMFLOAT3 Normal;
		XMFLOAT3 Tangent;
	};

	struct ModelType {
		float x, y, z;
		float u, v;
		float nx, ny, nz;
	};


	HRESULT hr;

	vector<DWORD>* indices;
	vector<ColorVertex>* vertexBufferList; 
	


	public:

		void InitializeModel(DirectX* inDirectX, MainCamera* inCamera);
		void InitializeModelWorldMatrix();

		void InitializeMesh();
		void InitializeEffect();
		void InitializeLayout();
		void InitializeStates();

		void SetupWVPMatrix();

		void Update();
		void Render();
		
		void SetupRender();
		
		void SetVertices(int inVerticesCount, ColorVertex inModelInfo[]);
		void SetIndices();
		void SetNormals();


		XMFLOAT4X4 GetWorldMatrix();

};