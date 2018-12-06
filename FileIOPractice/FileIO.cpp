

#include "stdafx.h"
#include "FileIO.h"

CFileIO::CFileIO() : 
	m_pFile(nullptr)
{

}

CFileIO::CFileIO(std::string _szFileName, std::string _szFilePath) :
	m_pFile(nullptr)
{
	if (!IsValidFileName(_szFileName, _szFilePath)) {
		assert(0 && "invalid file name");
		return;
	}

	if (!OpenFile()) {
		assert(0 && "Unable to open file");
		return;
	}
	
}

CFileIO::~CFileIO()
{
	CloseFile();
}
bool CFileIO::CloseFile()
{
	int iRetVal;

	if (m_pFile != nullptr) {
		iRetVal = fclose(m_pFile);
		if (iRetVal == 0) {
			return true;
		}
	}
	return false;
}

bool CFileIO::IsValidFileName()
{
	// add basic file name checks here

	if ( m_szFileName.empty() )
		return false;
	if (m_szFileName.length() < 3)
		return false;

	return true;
}

bool CFileIO::IsValidFileName(std::string _szFileName, std::string _szFilePath)
{
	m_szFileName = _szFileName;
	m_szFilePath = _szFilePath;

	return IsValidFileName();
}

bool CFileIO::OpenFile()
{
	std::string szFullFileName = m_szFilePath + m_szFileName;

	//errno_t err = fopen_s(&m_pFile, szFullFileName.c_str(), "r+");
	m_pFile = fopen(szFullFileName.c_str(), "r+");
	if (m_pFile == nullptr) {
		m_pFile = fopen(szFullFileName.c_str(), "w+");
	}

	if (m_pFile != nullptr) {
		return true;
	}

	return false;
}

bool CFileIO::OpenFile(std::string _szFileName, std::string _szFilePath)
{
	if (!IsValidFileName(_szFileName, _szFilePath))
		return false;

	return OpenFile();
}

bool CFileIO::WriteFile(std::string _szOutString)
{
	if (m_pFile != nullptr) {
		fwrite(_szOutString.c_str(), sizeof(char), _szOutString.length(), m_pFile);
		return true;
	}

	return false;
}
bool CFileIO::ReadFile(std::string* _szInString)
{
	int iFileSize = 0;

	// determine file size
	char c;
	bool bKeepReading = true;
	int iRetVal = 0;
	while (bKeepReading) {
		iRetVal = fread(&c, sizeof(char), sizeof(char), m_pFile);
		//int iRetVal = fread_s(&c, sizeof(char), sizeof(char), sizeof(char), m_pFile);
		if (iRetVal != 0) {
			iFileSize += iRetVal;
		}
		else {
			bKeepReading = false;
		}
	}
	fseek(m_pFile, 0, SEEK_SET);
	//freopen_s(&m_pFile, m_szFileName.c_str(), "w", m_pFile);
	
	// allocate buffer for file contents
	char* pBuffer = (char*) malloc((sizeof(char)*iFileSize) +1);
	if (!pBuffer) {
		assert(0 && "Unable to allocate buffer");
		return false;
	}
	memset(pBuffer, 0, iFileSize + 1);
	if (m_pFile != nullptr) {
		fread(pBuffer, sizeof(char), iFileSize, m_pFile);
		(*_szInString) = pBuffer;
//		fread_s(_szInString->c_str(), _szInString->length(), sizeof(char), _szInString->length(), m_pFile);
	}
	return true;
}