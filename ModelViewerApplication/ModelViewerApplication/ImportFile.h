#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Model.h"

using namespace std;

class ImportFile {


	private:



	protected:

		//FILE* modeliFile;
		ifstream modelFile;

		struct ColorVertex {
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
			XMFLOAT3 Normal;
		};

		ColorVertex* modelInfo;

		int vertexCount, uvCount, normalCount, faceCount;

		Model* model;


	public:

		virtual bool LoadFile(PWSTR filePath) = 0;
		virtual void ReadModelData(Model* inModel) = 0;
		virtual void GetCounts() = 0;
		virtual void SetupModelInfo() = 0;


};

