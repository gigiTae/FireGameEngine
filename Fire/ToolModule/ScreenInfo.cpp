#include "ToolModulepch.h"
#include "ScreenInfo.h"


void ToolModule::ScreenInfo::LoadPosition(LONG& left, LONG& top)
{
	std::ifstream screenInfo("screenPosition");

	if (screenInfo.is_open())
	{
		std::string line{};
		try{
			std::getline(screenInfo, line);
			left = std::stol(line.c_str());

			std::getline(screenInfo, line);
			top = std::stol(line.c_str());
		}catch (const std::exception& e)
		{
			left = 100; top = 100;
		}
	}
	screenInfo.close();
}

void ToolModule::ScreenInfo::LoadResoltuion(LONG& width, LONG& height)
{
	std::ifstream screenInfo("screenResolution");

	if (screenInfo.is_open())
	{
		std::string line{};
		try{
			std::getline(screenInfo, line);
			height = std::stol(line.c_str());

			std::getline(screenInfo, line);
			width = std::stol(line.c_str());
		}catch (const std::exception& e)
		{
			width = 1920;
			height = 1080;
		}
	}
	screenInfo.close();
}

void ToolModule::ScreenInfo::SavePosition(LONG left, LONG top)
{
	std::ofstream os("screenPosition");

	if (os.is_open())
	{
		os << left << std::endl;
		os << top;
	}
	os.close();
}

void ToolModule::ScreenInfo::SaveResoltuion(LONG width, LONG height)
{
	std::ofstream os("screenResolution");

	if (os.is_open())
	{
		os << height << std::endl;
		os << width << std::endl;
	}
	os.close();
}
