//#include <iostream>
//#include <filesystem>
//#include <string>
//
//namespace fs = std::filesystem;
//d
//int main()
//{
//	std::string fileName = "MyWorld";
//
//	fs::path resourcePath = fs::current_path().parent_path();
//
//	resourcePath += "\\Resource\\World\\";
//
//	fs::file_status status = fs::status(resourcePath);
//
//	// World �����͸� �����ϴ� ������ "World" ���� ����
//	try { if (!fs::is_directory(status))
//			fs::create_directory(resourcePath);
//	}catch(const std::exception& e)
//	{
//		std::cerr << "���� ���� ����: " << e.what() << std::endl;
//	}
//
//	// World ������ ���� World�� Entity �������� ����
//
//	fs::path savePath = resourcePath;
//	savePath += fileName;
//
//	fs::file_status status2 = fs::status(savePath);
//
//	if (!fs::is_directory(status2))
//	{
//		fs::create_directories(savePath);
//	}
//	
//	// ���� Entity�� ���� �������� �����Ѵ�.
//	
//	
//
//
//	return 0;
//}
//
