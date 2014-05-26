#include <Windows.h>
#include <string>
#include <iostream>
#include <xnamath.h>
#include <d3d11.h>
#include "MainCamera.h"



class DirectX {


	private:

		D3D_DRIVER_TYPE         driverType;
		D3D_FEATURE_LEVEL       featureLevel;
		ID3D11Device*           d3dDevice;
		ID3D11DeviceContext*	immediateContext;
		IDXGISwapChain*         swapChain;
		ID3D11RenderTargetView* renderTargetView;
		HWND					hWnd;

		//Depth stencil buffer
		ID3D11DepthStencilView* depthStencilView;
		ID3D11Texture2D* depthStencilBuffer;
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		XMFLOAT4X4 wvp;

		MainCamera* camera;

	public:

		DirectX();
		
		void InitializeDirectX(HWND inHWnd, MainCamera* inCamera);

		ID3D11Device* GetDevice();
		ID3D11DeviceContext* GetContext();

		ID3D11RenderTargetView* GetRenderTarget();
		IDXGISwapChain* GetSwapChain();
		ID3D11DepthStencilView* GetDepthStencilView();

};