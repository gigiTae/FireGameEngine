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
//	// World 데이터를 저장하는 공간인 "World" 폴더 생성
//	try { if (!fs::is_directory(status))
//			fs::create_directory(resourcePath);
//	}catch(const std::exception& e)
//	{
//		std::cerr << "폴더 생성 실패: " << e.what() << std::endl;
//	}
//
//	// World 폴더에 나의 World에 Entity 정보들을 저장
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
//	// 이후 Entity에 대한 정보들을 저장한다.
//	
//	
//
//
//	return 0;
//}
//
