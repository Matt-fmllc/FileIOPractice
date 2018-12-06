#pragma once

#include <string>

class CFileIO
{
private:
	FILE* m_pFile;
	std::string m_szFileName;
	std::string m_szFilePath;

protected:
	bool IsValidFileName();
	bool IsValidFileName(std::string _szFileName, std::string _szFilePath);

	const FILE* GetFilePointer() const { return m_pFile; }

public:
	CFileIO();
	CFileIO(std::string _szFileName, std::string _szFilePath);
	virtual ~CFileIO();

	virtual bool OpenFile();
	virtual bool OpenFile(std::string _szFileName, std::string _szFilePath);
	virtual bool CloseFile();

	virtual bool WriteFile(std::string _szOutString);
	virtual bool ReadFile(std::string* _szInString);
};
