
#include "TalonPrefix.h"

#include <Talon/Platform/Platform.h>

namespace Talon 
{
	bool Platform::SetWorkingPath(const std::string& path)
	{
		return SetCurrentDirectoryW(convert(path).c_str()) == TRUE;
	}

	std::string Platform::GetEnginePath()
	{
		std::string exePath(_pgmptr);
		return exePath.substr(0, exePath.find_last_of('\\') + 1);
	}

	std::string Platform::GetResourcePath(const std::string& fileName)
	{
		// TODO: Find the actual file name, returning empty string if not found.
		return GetEnginePath() + fileName;
	}

	std::string Platform::GetTextFromFile(const std::string& fileName)
	{
		std::string fullFileName = GetResourcePath(fileName);
		std::string contents;
		HANDLE file = CreateFileW(convert(fullFileName).c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (file != INVALID_HANDLE_VALUE)
		{
			DWORD bytesRead = 0;
			DWORD fileSize = GetFileSize(file, nullptr);
			char* fileData = new char[fileSize + 1];
			BOOL success = ReadFile(file, fileData, fileSize, &bytesRead, nullptr);
			if (success && bytesRead == fileSize)
			{
				fileData[fileSize] = '\0';
				contents = fileData;
			}

			delete [] fileData;

			CloseHandle(file);
		}

		return contents;
	}
}