#pragma once
#include"Hardware.h"
#include "IRoutine.h"

#include"ResourceManager.h"
#include"Asset.h"

#include"Camera.h"
#include"Shader.h"

using namespace Resources;

class Engine :
    public IRoutine
{
public:
    Engine(HWND handle, HINSTANCE handleInst, unsigned int width, unsigned height);
    ~Engine();


    virtual void Update(float delta) override;
    virtual void Render(float delta) override;

    const Hardware* GetHardware() const { return mHardware; }

private:
    Hardware* mHardware;
    Display mMainDisplay;

    Buffer2D* mScreenTex;
    Tex2D* mDepthTex;

    Camera* mMainCamera;

    Assets::AssetModel* mAsset_Roman;
    Shader* mShader_Default;

    Input* mInput;

    virtual void Init() override;
    virtual void Release() override;

    void bindBuffer();
    void drawInstance(Instance* inst);


};

