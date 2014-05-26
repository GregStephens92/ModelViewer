#include "ImportObj.h"
#include <Windows.h>

bool ImportObj::LoadFile(PWSTR filePath) {
	
	cout << "Loading file" << endl;
	
	//PWSTR test = L"boy.obj";

	modelFile.open(filePath);
	//modelFile.open("boy.obj");


	if (modelFile.is_open() || !modelFile) {
		return true;
	} else {
		return false;
	}

}

void ImportObj::ReadModelData() {
	cout << "Reading data" << endl;
	
	string line;
	string vertexLine;

	string value;

	//float vertexX, vertexY, vertexZ;

	vector<float> vertices;
	vector<float> uvs;
	vector<float> normals;
	vector<float> faces;

	while(!modelFile.eof()) {
		
		getline(modelFile, line);

		//find vertex infomation
		if(line[0] == 'v' && line[1] == ' ') {
			
			vertexLine = line.substr(2);

			//get first float
			value = vertexLine.substr(0, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "vertex first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "vertex second: " << value << endl;

			//get third float
			value = vertexLine.substr(vertexLine.find_last_of(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "vertex third: " << value << endl;
						
		}

		//texture uv's
		if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
				
			vertexLine = line.substr(3);

			//get first float
			value = vertexLine.substr(0, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "uv first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "uv second: " << value << endl;

		}

		//vertex normals
		if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
				
			vertexLine = line.substr(3);

			//get first float
			value = vertexLine.substr(0, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "normal first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "normal second: " << value << endl;

			//get third float
			value = vertexLine.substr(vertexLine.find_last_of(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "normal third: " << value << endl;
						
		}
		

		////faces
		//if (line[0] == 'f' && line[1] == ' ') {
		//	vertexLine = line.substr(3);
		//	cout << vertexLine << endl;
		//}


	}

	cout << "Done";	
	modelFile.close();

}