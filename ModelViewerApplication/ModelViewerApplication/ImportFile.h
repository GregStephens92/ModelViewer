#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ImportFile {


	private:



	protected:

		//FILE* modeliFile;
		ifstream modelFile;



	public:

		virtual bool LoadFile() = 0;
		virtual void ReadModelData() = 0;


};

