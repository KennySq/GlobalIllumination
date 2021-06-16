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

		const char* GetPath() const { return mPath.c_str(); }

	protected:
		const string& mPath;
	};

	class AssetModel : public Asset
	{
	public:
		AssetModel(const char* path);

		virtual bool Open() override;
		virtual void Close() override;

		ID3D11Buffer* GetVertex(unsigned int i) const { return mVertexList[i].Get(); }
		ID3D11Buffer* GetIndex() const { return mIndex.Get(); }
		unsigned int GetIndexCount() const { return mIndexCount; }
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

		XMFLOAT3* mPositions = nullptr;
		XMFLOAT3* mNormals = nullptr;
		XMFLOAT2* mTexcoords = nullptr;

		unsigned int mIndexCount;

		MODEL_TYPE mType;

		vector<ComPtr<ID3D11Buffer>> mVertexList;
		ComPtr<ID3D11Buffer> mIndex;
	};

}
