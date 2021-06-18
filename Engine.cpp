#include "pch.h"
#include "Engine.h"
#include"ResourceManager.h"

using namespace Resources;
using namespace Assets;

Engine::Engine(HWND handle, HINSTANCE handleInst, unsigned int width, unsigned height)
	: mHardware(Hardware::GetInstance(width, height, handle, handleInst)), mMainDisplay(width, height)
{
	Init();
}

Engine::~Engine()
{
	Release();
}

void Engine::Init()
{
	MemoryBank* memory = MemoryBank::GetInstance();

	unsigned int width = mMainDisplay.GetWidth();
	unsigned int height = mMainDisplay.GetHeight();

	mScreenTex = new Buffer2D(width, height);
	mDepthTex = new Tex2D(width, height, TEX_TYPE::eDepth, DXGI_FORMAT_R24G8_TYPELESS);

	mAsset_Roman = new AssetModel("resources/roman/roman.fbx");
	//mAsset_Roman->Open();

	AssetModel* handModel = new AssetModel("resources/hand/hand.fbx");
	handModel->Open();

	mMainCamera = new Camera({ -200,-200,-200 }, { 1,0,0 }, XMConvertToRadians(90.0f), mMainDisplay.GetAspectRatio());
	mShader_Default = new Shader("resources/shaders/Default.hlsl", (eVertex | ePixel));

	mInput = new Input(width, height);

	Instance* instance1 = new Instance("instance 1");
	instance1->BindModel("resources/hand/hand.fbx");
	instance1->BindShader("resources/shaders/Default.hlsl");
}

void Engine::Update(float delta)
{
	static auto context = Hardware::GetContext();
	static MemoryBank* memory = MemoryBank::GetInstance();
	static Instance* inst1 = MemoryBank::FindInstance(0);

	context->ClearRenderTargetView(mScreenTex->GetRTV(), DirectX::Colors::Green);
	context->ClearDepthStencilView(mDepthTex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	mMainCamera->Update(delta);
	mInput->Update(delta);

	if (mInput->GetKey('W'))
	{

	}

	drawInstance(inst1);
}

void Engine::Render(float delta)
{
	static auto swapChain = Hardware::GetSwapChain();
	
	mMainCamera->Render(delta);

	

	swapChain->Present(0, 0);
}

void Engine::Release()
{
	delete mScreenTex;
	delete mDepthTex;
	delete mMainCamera;
	delete mAsset_Roman;
}

void Engine::drawInstance(Instance* inst)
{
	static auto context = Hardware::GetContext();

	Shader* shader = inst->GetShader();
	AssetModel* model = inst->GetModel();

	ID3D11Buffer* buffer = inst->GetBuffer();
	ID3D11Buffer* buffers[] = { mMainCamera->GetBuffer() };
	ID3D11Buffer* vertexBuffers[] = { model->GetVertex(0) };
	ID3D11Buffer* indexBuffers = model->GetIndex();

	unsigned int strides[] = { sizeof(StaticVertex) };
	unsigned int offsets[] = { 0 };

	ID3D11VertexShader* vertex = shader->GetVertex();
	ID3D11GeometryShader* geometry = shader->GetGeometry();
	ID3D11DomainShader* domain = shader->GetDomain();
	ID3D11HullShader* hull = shader->GetHull();
	ID3D11PixelShader* pixel = shader->GetPixel();
	ID3D11ComputeShader* compute = shader->GetCompute();

	ID3D11RenderTargetView* renderTargets[] = { mScreenTex->GetRTV() };
	ID3D11DepthStencilView* depthStencil = { mDepthTex->GetDSV() };

	ID3D11ShaderResourceView* shaderResources[] = { inst->GetResourceView() };

	D3D11_VIEWPORT viewports[] = { mMainDisplay.GetViewport() };

	context->OMSetRenderTargets(1, renderTargets, depthStencil);

	if (vertex != nullptr)
	{
		context->VSSetShader(vertex, nullptr, 0);
		context->VSSetConstantBuffers(0, 1, buffers);
		context->VSSetShaderResources(0, 1, shaderResources);
	}

	if (geometry != nullptr)
	{
		context->GSSetShader(geometry, nullptr, 0);
	}

	if(domain != nullptr)
	{
		context->DSSetShader(domain, nullptr, 0);
	}

	if (hull != nullptr)
	{
		context->HSSetShader(hull, nullptr, 0);
	}

	if (pixel != nullptr)
	{
		context->PSSetShader(pixel, nullptr, 0);
	}

	context->IASetVertexBuffers(0, 1, vertexBuffers, strides, offsets);
	context->IASetIndexBuffer(indexBuffers, DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(shader->GetLayout());

	context->RSSetViewports(1, viewports);

	context->DrawIndexed(model->GetIndexCount(), 0, 0);

	context->ClearState();
}
