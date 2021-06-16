#include "pch.h"
#include "Asset.h"

using namespace std;
using namespace DirectX;

Assets::AssetModel::AssetModel(const char* path)
	: Asset(path)
{
	string ext = mPath.substr(mPath.find_first_of("."));

	if (ext == ".fbx")
	{
		mType = MODEL_TYPE::MODEL_FBX;
	}

}

bool Assets::AssetModel::Open()
{
	switch (mType)
	{
	case MODEL_TYPE::MODEL_FBX:
		openFBX();
		break;


	}

	return true;
}

void Assets::AssetModel::Close()
{
}

bool Assets::AssetModel::openFBX()
{
	FbxManager* manager = FbxManager::Create();
	FbxIOSettings* io = FbxIOSettings::Create(manager, IOSROOT);
	
	manager->SetIOSettings(io);

	FbxImporter* importer = FbxImporter::Create(manager, "");

	bool result = importer->Initialize(mPath.c_str(), -1, manager->GetIOSettings());

	if (result == false)
	{
		return false;
	}

	FbxScene* mainScene = FbxScene::Create(manager, "Scene");

	importer->Import(mainScene);

	importer->Destroy();

	FbxNode* root = mainScene->GetRootNode();

	//FbxAxisSystem::MayaYUp.ConvertScene(mainScene); // optional

	FbxGeometryConverter converter(manager);

	converter.Triangulate(mainScene, true);
	
	fbxLoadNode(root);

	delete mPositions;
	delete mNormals;
	delete mTexcoords;

	return true;
}

void Assets::AssetModel::fbxLoadNode(FbxNode* node)
{
	auto device = Hardware::GetDevice();
	const int childCount = node->GetChildCount();
	
	vector<StaticVertex> vertices;
	vector<unsigned int> indices;
	map<StaticVertex, unsigned int> indexMap;

	FbxNodeAttribute* nodeAttr = node->GetNodeAttribute();

	if (nodeAttr != nullptr)
	{
		if (nodeAttr->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			FbxMesh* mesh = node->GetMesh();

			HRESULT result;
			D3D11_BUFFER_DESC vbufferDesc{};
			D3D11_BUFFER_DESC ibufferDesc{};
			D3D11_SUBRESOURCE_DATA subData{};
			ComPtr<ID3D11Buffer> vbuffer;
			ComPtr<ID3D11Buffer> ibuffer;

			fbxGetControlPoints(mesh);


			unsigned int triCount = mesh->GetPolygonCount();
			unsigned int vertexCount = 0;

			for (unsigned int i = 0; i < triCount; i++)
			{
				for (unsigned int j = 0; j < 3; j++)
				{
					int cpi = mesh->GetPolygonVertex(i, j);

					XMFLOAT3 position = mPositions[cpi];
					XMFLOAT3 normal = fbxGetNormal(mesh, cpi, vertexCount);
					XMFLOAT2 texcoord = fbxGetUV(mesh, cpi, vertexCount);

					StaticVertex vertex(position, normal, texcoord);

					fbxAddVertex(vertex, indexMap, vertices, indices);



					vertexCount++;
				}
			}

			vbufferDesc.ByteWidth = sizeof(StaticVertex) * vertices.size();
			vbufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbufferDesc.Usage = D3D11_USAGE_DEFAULT;

			ibufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
			ibufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			ibufferDesc.Usage = D3D11_USAGE_DEFAULT;

			subData.pSysMem = vertices.data();

			result = device->CreateBuffer(&vbufferDesc, &subData, vbuffer.GetAddressOf());
			if (result != S_OK)
			{
				MessageBoxA(nullptr, "failed to create vertex buffer. (fbx)", nullptr, 0);
				DebugLog("failed to create vertex buffer. (fbx)");
			}

			subData.pSysMem = indices.data();

			result = device->CreateBuffer(&ibufferDesc, &subData, ibuffer.GetAddressOf());
			if (result != S_OK)
			{
				MessageBoxA(nullptr, "failed to create index buffer. (fbx)", nullptr, 0);
				DebugLog("failed to create index buffer. (fbx)");
			}

			mVertexList.emplace_back(vbuffer);
			mIndexList.emplace_back(ibuffer);

		}
	}

	for (unsigned int i = 0; i < childCount; i++)
	{
		fbxLoadNode(node->GetChild(i));
	}
}

void Assets::AssetModel::fbxGetControlPoints(FbxMesh* mesh)
{
	unsigned int count = mesh->GetControlPointsCount();
	unsigned int normalCount = mesh->GetElementNormalCount();
	unsigned int texcoordCount = mesh->GetElementUVCount();

	mPositions = new XMFLOAT3[count];
	mNormals = new XMFLOAT3[normalCount];
	mTexcoords = new XMFLOAT2[texcoordCount];

	for (unsigned int i = 0; i < count; i++)
	{
		XMFLOAT3 pos;

		pos.x = static_cast<float>(mesh->GetControlPointAt(i).mData[0]);
		pos.y = static_cast<float>(mesh->GetControlPointAt(i).mData[1]);
		pos.z = static_cast<float>(mesh->GetControlPointAt(i).mData[2]);
	
		mPositions[i] = pos;
	}

}

XMFLOAT2 Assets::AssetModel::fbxGetUV(FbxMesh* mesh, unsigned int cpi, unsigned int vertexCount)
{
	if (mesh->GetElementNormalCount() < 1)
	{
		return XMFLOAT2(0,0);
	}

	FbxGeometryElementUV* vertexUV = mesh->GetElementUV(0);

	XMFLOAT2 texcoord;

	switch (vertexUV->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (vertexUV->GetReferenceMode())
	case FbxGeometryElement::eDirect:
		texcoord.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[0]);
		texcoord.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[1]);
		break;

		break;

	case FbxGeometryElement::eByPolygonVertex:
	{
		switch (vertexUV->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			texcoord.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[0]);
			texcoord.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[1]);
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
			int index = vertexUV->GetIndexArray().GetAt(vertexCount);
			texcoord.x = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[0]);
			texcoord.y = static_cast<float>(vertexUV->GetDirectArray().GetAt(cpi).mData[1]);
			break;
		}
	}
	break;
	}

	return texcoord;
}

void Assets::AssetModel::fbxAddVertex(StaticVertex vertex, map<StaticVertex, unsigned int>& indexMap, vector<StaticVertex>& vertices, vector<unsigned int>& indices)
{
	auto lookup = indexMap.find(vertex);
	if (lookup != indexMap.end())
	{
		indices.emplace_back(lookup->second);
	}
	else
	{
		unsigned int index = vertices.size();
		indexMap[vertex] = index;
		indices.emplace_back(index);
		vertices.emplace_back(vertex);
	}


}

XMFLOAT3 Assets::AssetModel::fbxGetNormal(FbxMesh* mesh, unsigned int cpi, unsigned int vertexCount)
{
	if (mesh->GetElementNormalCount() < 1)
	{
		return XMFLOAT3(0, 0, 0);
	}

	FbxGeometryElementNormal* vertexNormal = mesh->GetElementNormal(0);

	XMFLOAT3 normal;

	switch (vertexNormal->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (vertexNormal->GetReferenceMode())
			case FbxGeometryElement::eDirect:
				normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[0]);
				normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[1]);
				normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[2]);
			break;
		
		break;

			case FbxGeometryElement::eByPolygonVertex:
			{
				switch (vertexNormal->GetReferenceMode())
				{
					case FbxGeometryElement::eDirect:
					{
						normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[0]);
						normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[1]);
						normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[2]);
					}
					break;

					case FbxGeometryElement::eIndexToDirect:
						int index = vertexNormal->GetIndexArray().GetAt(vertexCount);
						normal.x = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[0]);
						normal.y = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[1]);
						normal.z = static_cast<float>(vertexNormal->GetDirectArray().GetAt(cpi).mData[2]);
						break;
				}
			}
				break;
	}

	return normal;
}

Assets::Asset::Asset(const char* path)
	: mPath(MemoryBank::Find(path))
{

}
