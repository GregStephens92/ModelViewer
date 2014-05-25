#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class ImportFile {


	private:



	protected:

		//FILE* modeliFile;
		ifstream modelFile;



	public:

		virtual bool LoadFile(PWSTR filePath) = 0;
		virtual void ReadModelData() = 0;


};

