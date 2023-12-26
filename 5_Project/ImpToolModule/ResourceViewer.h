#pragma once


namespace ImpToolModule
{
	/// <summary>
	/// ���ҽ� �����͸� �����ϴ� GUI
	/// 
	/// </summary>
	class ResourceViewer
	{
	public:
		ResourceViewer();
		~ResourceViewer();

		void Initalize();
		void Update();

	private:
		void ProjectTabBar();

	public:
		std::filesystem::path _resourcesPath;
		std::filesystem::path _currentPath;

	};

}