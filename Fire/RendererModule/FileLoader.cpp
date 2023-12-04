#include "RendererPCH.h"
#include "FileLoader.h"


void RendererModule::File::GetFileMemberPath(std::vector<std::wstring>& _files, const std::wstring& _filePath, bool _allDirectories)
{
	std::wstring tmp = _filePath + std::wstring(L"\\*.*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(tmp.c_str(), &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do {
			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				/// ���� �������� �д���
				if (_allDirectories)
				{
					if (fd.cFileName[0] != '.')
					{
						tmp = _filePath + std::wstring(L"\\") + std::wstring(fd.cFileName);
						GetFileMemberPath(_files, tmp, _allDirectories);
					}
				}
			}
			else
			{
				/// ���Ϳ� ���� ��θ� �����Ѵ�.
				tmp = _filePath + std::wstring(L"\\") + std::wstring(fd.cFileName);
				_files.push_back(tmp);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}

}

void RendererModule::File::GetFileMemberName(std::vector<std::wstring>& _files, const std::wstring& _filePath, bool _allDirectories)
{
	std::wstring tmp = _filePath + std::wstring(L"\\*.*");
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(tmp.c_str(), &fd);

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do {
			if (fd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			{
				/// ���� �������� �д���
				if (_allDirectories)
				{
					if (fd.cFileName[0] != '.')
					{
						tmp = _filePath + std::wstring(L"\\") + std::wstring(fd.cFileName);
						GetFileMemberName(_files, tmp, _allDirectories);
					}
				}
			}
			else
			{
				/// ���Ϳ� ���� �̸��� �����Ѵ�.
				tmp = std::wstring(fd.cFileName);
				_files.push_back(tmp);
			}
		} while (FindNextFile(hFind, &fd));
		FindClose(hFind);
	}
}

const std::wstring& RendererModule::File::GetCurrentFilePath()
{
	static std::wstring filePath{};

	/// ���� ��� �ҷ�����
	if (filePath.size() == 0)
	{
		wchar_t relativePath[256]{};
		GetCurrentDirectoryW(255, relativePath);
		filePath = relativePath;

		while (filePath.back() != '\\')
		{
			filePath.pop_back();
		}
	}
	
	return filePath;
}

std::wstring RendererModule::File::GetFileExtension(const std::wstring& filePath)
{
	// ���� Ȯ���� ��������  
	std::wstring extension = filePath.substr(filePath.find_last_of(TEXT(".")) + 1);

	assert(filePath.length() != extension.length() || !L"Ȯ���ڸ� ã�� ���߽��ϴ�");

	// �빮�ڸ� �ҹ��ڷ� ��ȯ 
	std::transform(extension.begin(), extension.end(), extension.begin(), tolower);

	return extension; 
	// std::move�� ������� �ʾƵ� ����ȭ�� ���� 
	// C++ �����Ϸ��� RVO(Return Value Optimization)�� NRVO(Named Return Value Optimization) ���� 
	// ����ȭ ����� ����Ͽ� �Լ����� ������ ���� ������ ���� ���� ��ȯ�Ϸ��� �õ��մϴ�. 
	// ���� std::move �� ������� �ʾƵ� ����ȭ�� ����Ǿ� ȿ�������� ������ ���ɼ��� ����. 
}

std::wstring RendererModule::File::GetFileName(const std::wstring& filePath)
{
	// ���ϸ� ���� ��� ���� 
	std::wstring name = filePath.substr(filePath.find_last_of(L'\\') +1);

	std::wstring tmp = name;
	// Ȯ���� ����  
	while (true)
	{
		if (name.size() == 0)
		{
			return tmp;
		}

		wchar_t c = name.back();
		name.pop_back();

		if (c == L'.')
			break;
	}

	return name;
}
