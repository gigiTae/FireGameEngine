#include "Common.h"

#include "Parser.h"
#include "Geometry.h"

#include <mutex>

std::mutex fbxMutex{};

namespace FBXLoad
{
	void Import(const char* file)
	{
		assert(file);
		FBXLoad::Scene scene{};

		{
			std::lock_guard<std::mutex> lock{ fbxMutex };
			FBXLoad::Parser paser{ file, &scene};

			if (paser.IsValid())
			{
				paser.GetScene();
			}
			else
			{
				FBXSDK_printf("����: FBX �Ŵ����� ��������� ����.\n");
			}
		}
	}
}