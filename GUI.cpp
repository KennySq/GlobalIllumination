#include "pch.h"
#include "GUI.h"

GUI* GUI::mInstance = nullptr;

GUI::~GUI()
{
}

void GUIEntity::Slider(XMFLOAT4X4& matrix, float min, float max, const char* label)
{
    CheckFrame();

    ImGui::SliderFloat4(label, matrix.m[0], min, max);
    ImGui::SliderFloat4(label, matrix.m[1], min, max);
    ImGui::SliderFloat4(label, matrix.m[2], min, max);
    ImGui::SliderFloat4(label, matrix.m[3], min, max);
}

GUI* GUI::GetInstance(unsigned int width, unsigned int height)
{
    if (mInstance == nullptr)
    {
        mInstance = new GUI(width, height);
    }

    return mInstance;
}

void GUI::Draw()
{

    ImDrawData* drawData = ImGui::GetDrawData();
    ImGui_ImplDX11_RenderDrawData(drawData);

}

GUIFrame* GUIEntity::CheckFrame()
{
    if (mFrame == nullptr)
    {
        mFrame = new GUIFrame();
    }

    mFrame->Open();
}

GUI::GUI(unsigned int width, unsigned int height) : mWidth(width), mHeight(height)
{
    HWND handle = Hardware::GetHandle();
    ID3D11Device* device = Hardware::GetDevice();
    ID3D11DeviceContext* context = Hardware::GetContext();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplWin32_Init(handle);
    ImGui_ImplDX11_Init(device, context);
    ImGui::StyleColorsDark();

}

GUIEntity::GUIEntity(GUIFrame* frame)
    : mFrame(frame)
{
}

void GUIEntity::Slider(XMFLOAT4& vector, float min, float max, const char* label)
{

    float scalars[4] = { vector.x,vector.y,vector.z,vector.w };
    ImGui::SliderFloat4(label, scalars, min, max);

    vector.x = scalars[0];
    vector.y = scalars[1];
    vector.z = scalars[2];
    vector.w = scalars[3];

    return;
}

void GUIFrame::Open()
{
    ImGui::NewFrame();

}

void GUIFrame::Close()
{
    ImGui::EndFrame();
}
