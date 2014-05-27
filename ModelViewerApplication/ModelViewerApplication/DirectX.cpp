#include "DirectX.h"

using namespace std;

DirectX::DirectX() {

}


void DirectX::InitializeDirectX(HWND inHWnd, MainCamera* inCamera) {

	cout << "Initializing DirectX..." << endl;

	hWnd = inHWnd;
	camera = inCamera;

    GetClientRect(hWnd, &rc);
    width = rc.right - rc.left;
    height = rc.bottom - rc.top;
	
	driverType = D3D_DRIVER_TYPE_NULL;
	featureLevel = D3D_FEATURE_LEVEL_11_0;
	d3dDevice = NULL;
	immediateContext = NULL;
	swapChain = NULL;
	renderTargetView = NULL;
	
    UINT createDeviceFlags = 0;
	#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        driverType = driverTypes[driverTypeIndex];
       D3D11CreateDeviceAndSwapChain( NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
                                            D3D11_SDK_VERSION, &sd, &swapChain, &d3dDevice, &featureLevel, &immediateContext);

    }


    // Create a render target view
    ID3D11Texture2D* backBuffer = NULL;
    swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&backBuffer );

	d3dDevice->CreateRenderTargetView( backBuffer, NULL, &renderTargetView );
    backBuffer->Release();
	
    immediateContext->OMSetRenderTargets( 1, &renderTargetView, NULL );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    immediateContext->RSSetViewports( 1, &vp );

	//Setting full screen
	// pSwapChain->SetFullscreenState(true, NULL);

	//Depth stencil description
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0; 
	depthStencilDesc.MiscFlags = 0;

	d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	d3dDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	immediateContext->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );
	
}

ID3D11Device* DirectX::GetDevice() {
	return d3dDevice;
}

ID3D11DeviceContext* DirectX::GetContext() {
	return immediateContext;
}

ID3D11RenderTargetView* DirectX::GetRenderTarget() {
	return renderTargetView;
}

IDXGISwapChain* DirectX::GetSwapChain() {
	return swapChain;
}

ID3D11DepthStencilView* DirectX::GetDepthStencilView() {
	return depthStencilView;
}