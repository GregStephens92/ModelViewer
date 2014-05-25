#include "ImportObj.h"

bool ImportObj::LoadFile() {
	
	cout << "Loading file" << endl;
	
	modelFile.open("boy.obj");

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
			
			cout << "first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "second: " << value << endl;

			//get third float
			value = vertexLine.substr(vertexLine.find_last_of(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "third: " << value << endl;
						
		}

		//texture uv's
		if (line[0] == 'v' && line[1] == 't' && line[2] == ' ') {
				
			vertexLine = line.substr(3);

			//get first float
			value = vertexLine.substr(0, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "second: " << value << endl;

		}

		//vertex normals
		//texture uv's
		if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ') {
				
			vertexLine = line.substr(3);

			//get first float
			value = vertexLine.substr(0, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "first: " << value << endl;

			//get second float
			value = vertexLine.substr(value.length() + 1, vertexLine.find(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "second: " << value << endl;

			//get third float
			value = vertexLine.substr(vertexLine.find_last_of(' '));
			vertices.push_back((float)atof(value.c_str()));
			
			cout << "third: " << value << endl;
						
		}
		

		//faces
		if (line[0] == 'f' && line[1] == ' ') {
			vertexLine = line.substr(3);



			cout << vertexLine << endl;

		}


	}

	cout << "Done";	
	modelFile.close();

}