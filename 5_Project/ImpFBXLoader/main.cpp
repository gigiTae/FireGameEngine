//#include "Common.h"
//#include "Loader.h"
//#include "Geometry.h"

#include "FbxLoader.h"
#include <iostream>

using namespace std;

int main()
{
	//const char* fileName = "file.fbx";
	// const char* fileName = "file2.fbx";
	//const char* fileName = "Axis2.fbx";
	const char* fileName = "a.fbx";
	FBXLoad::FbxLoader loader;

	//loader.LoadAMeshContent(fileName);
	auto m = loader.GetMesh(fileName, 0);

	/*
	cout << "<< --- Vertex --- >>" << endl;
	
	cout << "< local position >" << endl;
	for (auto& v : m->_meshVertex)
	{
		cout << v->_localPos.x << ", " << v->_localPos.y << ", " << v->_localPos.z << endl;
	}

	int i{ 0 };
	cout << "< uv >" << endl;
	for (auto& v : m->_meshVertex)
	{
		cout << "< set "<< i <<" >" << endl;
		i++;
		for (auto& uv : v->_uvs)
		{
			cout << uv.x <<", "<< uv.y << endl;

		}
	}

	if (m->_hasNormal)
	{
		cout << "< normal >" << endl;
		for (auto& v : m->_meshVertex)
		{
			cout << v->_normal.x << ", " << v->_normal.y << ", " << v->_normal.z << endl;
		}
	}
	
	if (m->_hasTangent)
	{
		cout << "< tangent >" << endl;
		for (auto& v : m->_meshVertex)
		{
			cout << v->_tangent.x << ", " << v->_tangent.y << ", " << v->_tangent.z << endl;
		}
	}
	*/
	
	cout << endl;
	
	cout << "<< --- Face --- >>" << endl;
	
	cout << "< Vertex index >" << endl;
	for (auto& f : m->_meshFace)
	{
		cout << f->vertexIndex[0] << ", " << f->vertexIndex[1] << ", " << f->vertexIndex[2] << endl;
	}
	
	//cout << "< Texture index >" << endl;
	//for (auto& f : m->_meshFace)
	//{
	//	cout << f->textureIndex[0] << ", " << f->textureIndex[1] << ", " << f->textureIndex[2] << endl;
	//}
	
}