#include "pch.h"
#include "Asset.h"

Assets::AssetModel::AssetModel(const char* path)
	: Asset(path)
{
}

bool Assets::AssetModel::Open()
{
	

	return true;
}

void Assets::AssetModel::Close()
{
}

Assets::Asset::Asset(const char* path)
	: mPath(MemoryBank::Find(path))
{
}
