#pragma once


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
	private:
		const string& mPath;
	};

	class AssetModel : Asset
	{
	public:
		AssetModel(const char* path);

		virtual bool Open() override;
		virtual void Close() override;

	private:
		ComPtr<ID3D11Buffer> mVertex;
		ComPtr<ID3D11Buffer> mIndex;



	};

}
