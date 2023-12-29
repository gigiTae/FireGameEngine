#include "pch.h"
#include "ImpLoader.h"

using namespace std;

using namespace ImpGraphics;

ImpStructure::ImpMesh* ImpLoader::GetMesh(const std::wstring& path)
{
	char* next_token1 = NULL;

	string line{};
	ifstream file(path); // example.txt 파일을 연다. 없으면 생성. 

	ImpStructure::ImpMesh* mesh = new ImpStructure::ImpMesh;
	ImpStructure::ImpVertex* impVertex = nullptr;
	ImpStructure::ImpFace* impFace = nullptr;

	bool isPosColorTex = false;
	bool isQuadVertex = false;

	int vertexSize = 0;
	int faceSize = 0;

#pragma warning(disable : 4244) // double -> float 변환 데이터 손상 에러 안나게...

	if (file.is_open())
	{
		/// 첫 번째 줄 읽어오기
		getline(file, line);
		const char* str = line.c_str(); //구분할 문자열
		char* tempchar = const_cast<char*>(str);
		char* ptr = strtok_s(tempchar, " ", &next_token1); //첫번째 strtok 사용.
		int cnt = 0;
		while (ptr != NULL) //ptr이 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
		{
			if (!strcmp(ptr, "PosColorTex"))
			{
				isPosColorTex = true;
			}
			if (!strcmp(ptr, "QuadVertex"))
			{
				isQuadVertex = true;
			}
			if (cnt == 2) // vertexSize
			{
				vertexSize = atoi(ptr);
			}
			if (cnt == 3) // indexSize
			{
				faceSize = atoi(ptr);
			}
			ptr = strtok_s(NULL, " ", &next_token1); //자른 문자 다음부터 구분자 또 찾기
			cnt++;
		}

		/// 버텍스 읽기
		for (size_t i = 0; i < vertexSize; i++)
		{
			getline(file, line);
			const char* str = line.c_str(); //구분할 문자열
			char* tempchar = const_cast<char*>(str);
			char* ptr = strtok_s(tempchar, " ", &next_token1); //첫번째 strtok 사용.
			impVertex = new ImpStructure::ImpVertex;

			if (isPosColorTex)
			{
				int tokenNumber = 0;
				while (ptr != NULL) //ptr이 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
				{
					if (tokenNumber == 0)
					{
						impVertex->_localPos.x = atof(ptr);
					}
					else if (tokenNumber == 1)
					{
						impVertex->_localPos.y = atof(ptr);
					}
					else if (tokenNumber == 2)
					{
						impVertex->_localPos.z = atof(ptr);
					}
					else if (tokenNumber == 3)
					{
						impVertex->_color.x = atof(ptr);
					}
					else if (tokenNumber == 4)
					{
						impVertex->_color.y = atof(ptr);
					}
					else if (tokenNumber == 5)
					{
						impVertex->_color.z = atof(ptr);
					}
					else if (tokenNumber == 6)
					{
						impVertex->_color.w = atof(ptr);
					}
					else if (tokenNumber == 7)
					{
						impVertex->_u = atof(ptr);
					}
					else if (tokenNumber == 8)
					{
						impVertex->_v = atof(ptr);
					}

					ptr = strtok_s(NULL, " ", &next_token1); //자른 문자 다음부터 구분자 또 찾기
					tokenNumber++;
				}
				mesh->_hasTexture = true;
				mesh->_hasColor = true;
				mesh->_meshVertex.push_back(impVertex);
			}

			if (isQuadVertex)
			{
				int tokenNumber = 0;
				while (ptr != NULL) //ptr이 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
				{
					if (tokenNumber == 0)
					{
						impVertex->_localPos.x = atof(ptr);
					}
					else if (tokenNumber == 1)
					{
						impVertex->_localPos.y = atof(ptr);
					}
					else if (tokenNumber == 2)
					{
						impVertex->_localPos.z = atof(ptr);
					}
					else if (tokenNumber == 3)
					{
						impVertex->_u = atof(ptr);
					}
					else if (tokenNumber == 4)
					{
						impVertex->_v = atof(ptr);
					}

					ptr = strtok_s(NULL, " ", &next_token1); //자른 문자 다음부터 구분자 또 찾기
					tokenNumber++;
				}
				mesh->_hasTexture = true;
				mesh->_meshVertex.push_back(impVertex);
			}
		}

		/// 페이스 읽기(인덱스)
		for (size_t i = 0; i < faceSize; i++)
		{
			getline(file, line);
			const char* str = line.c_str(); //구분할 문자열
			char* tempchar = const_cast<char*>(str);
			char* ptr = strtok_s(tempchar, " ", &next_token1); //첫번째 strtok 사용.
			impFace = new ImpStructure::ImpFace;

			int tokenNumber = 0;
			while (ptr != NULL) //ptr이 NULL일때까지 (= strtok 함수가 NULL을 반환할때까지)
			{
				if (tokenNumber == 0)
				{
					impFace->vertexIndex[0] = atoi(ptr);
				}
				else if (tokenNumber == 1)
				{
					impFace->vertexIndex[1] = atoi(ptr);
				}
				else if (tokenNumber == 2)
				{
					impFace->vertexIndex[2] = atoi(ptr);
				}

				ptr = strtok_s(NULL, " ", &next_token1); //자른 문자 다음부터 구분자 또 찾기
				tokenNumber++;
			}
			mesh->_meshFace.push_back(impFace);
		}

		while (getline(file, line))
		{
			// 혹시 남은 줄이 있을까봐?
		}
		file.close(); // 열었던 파일을 닫는다. 
	}
	else
	{
		// 에러!
	}
	
#pragma warning(default : 4244) // double -> float 변환 데이터 손상 에러 안나게...

	return mesh;
}
