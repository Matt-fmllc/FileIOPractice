// FileIOPractice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileIO.h"


int main()
{
	CFileIO* pFileIO = new CFileIO("test.txt", "");
	assert(pFileIO != nullptr);

	std::string szOutString = "Write Test";
	pFileIO->WriteFile(szOutString);

	pFileIO->CloseFile();
	pFileIO->OpenFile();

	std::string szInString;
	pFileIO->ReadFile(&szInString);

	if (pFileIO) {
		delete(pFileIO);
	}

    return 0;
}

