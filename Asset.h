#pragma once
#include"Geometry.h"

using namespace DirectX;

namespace Assets
{
	enum class MODEL_TYPE
	{
		MODEL_FBX,
		MODEL_OBJ,
	};

	class Asset
	{
	public:
		Asset(const char* path);
		virtual bool Open() = 0;
		virtual void Close() = 0;
	protected:
		const string& mPath;
	};

	class AssetModel : Asset
	{
	public:
		AssetModel(const char* path);

		virtual bool Open() override;
		virtual void Close() override;

	private:
		bool openFBX();
		// ** CAUTION, This method is recursive. **
		void fbxLoadNode(FbxNode* node);
		void fbxGetControlPoints(FbxMesh* mesh);
		XMFLOAT3 fbxGetNormal(FbxMesh* mesh, unsigned int cpi, unsigned int vertexCount);
		XMFLOAT2 fbxGetUV(FbxMesh* mesh, unsigned int cpi, unsigned int vertexCount);
		void fbxAddVertex(StaticVertex vertex, map<StaticVertex, unsigned int>& indexMap
		, vector<StaticVertex>& vertices, vector<unsigned int>& indices);
		
		
		//bool openOBJ();

		XMFLOAT3* positions = nullptr;
		XMFLOAT3* normals = nullptr;
		XMFLOAT2* texcoords = nullptr;

		MODEL_TYPE mType;

		vector<ComPtr<ID3D11Buffer>> mVertexList;
		vector<ComPtr<ID3D11Buffer>> mIndexList;
	};

}
