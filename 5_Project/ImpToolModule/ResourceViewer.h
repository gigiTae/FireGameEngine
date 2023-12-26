#pragma once


namespace ImpToolModule
{
	/// <summary>
	/// 리소스 데이터를 관리하는 GUI
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
		void EntityTabBar();

	public:
		std::filesystem::path _entityPath;

	};

}