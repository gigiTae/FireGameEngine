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
		void EntityTabBar();

	public:
		std::filesystem::path _entityPath;

	};

}