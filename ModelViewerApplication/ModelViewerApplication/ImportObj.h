#pragma once

#include "ImportFile.h"

class ImportObj: public ImportFile {

	private:




	public:

		bool LoadFile(PWSTR filePath);
		void ReadModelData(Model* inModel);
		void GetCounts();
		void SetupModelInfo();

};
