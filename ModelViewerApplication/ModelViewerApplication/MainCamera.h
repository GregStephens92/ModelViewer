#include <Windows.h>
#include <xnamath.h>

class MainCamera { 

	private:

		XMFLOAT4 defaultForward;
		XMFLOAT4 defaultRight;

		XMFLOAT4 forward;
		XMFLOAT4 right;

		XMFLOAT4 cameraPos;
		XMFLOAT4 lookAt;
		XMFLOAT4 up;

		XMFLOAT4X4 rotationMatrix;
	
		XMFLOAT4X4 viewMatrix;
		XMFLOAT4X4 projMatrix;
		XMFLOAT4X4 viewprojMatrix;

		float leftRight;
		float forwardBackward;
		float upDown;

		float yaw;
		float pitch;


	public:

		void InitializeCameraMatrixs();

		void InitializeViewMatrix();
		void InitializeProjMatrix();
		void InitializeViewProjMatrix();
				
		XMFLOAT4X4 GetViewMatrix();
		XMFLOAT4X4 GetProjMatrix();
		XMFLOAT4X4 GetViewProjMatrix();

};


