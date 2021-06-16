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
	mAsset_Roman->Open();

	mMainCamera = new Camera({ 1,0,0 }, { -1,0,0 }, XMConvertToRadians(60.0f), mMainDisplay.GetAspectRatio());
	

}

void Engine::Update(float delta)
{
	static auto context = Hardware::GetContext();
	
	context->ClearRenderTargetView(mScreenTex->GetRTV(), DirectX::Colors::Green);
	context->ClearDepthStencilView(mDepthTex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	mMainCamera->Update(delta);

	

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
