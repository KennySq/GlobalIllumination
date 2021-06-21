#include "pch.h"
#include "GUI.h"

GUI* GUI::mInstance = nullptr;

GUI::~GUI()
{
}

void GUIEntity::Slider(XMFLOAT4X4& matrix, float min, float max, const char* label)
{
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

void GUI::AboutInstance(Instance* inst, float min, float max)
{
    ImGui::Begin(inst->GetName());
    ImGui::NewFrame();

    AssetModel* model = inst->GetModel();
    const char* modelPath = model->GetPath();

    Shader* shader = inst->GetShader();
    const char* shaderPath = shader->GetPath();

    XMFLOAT4X4& transform = inst->GetRawTransform();
    float position[3] = { transform._14, transform._24, transform._34 };

    ImGui::Text("%s", modelPath);
    ImGui::Text("%s", shaderPath);
    ImGui::NewLine();
    ImGui::SliderFloat4("Position", position, min, max);

    ImGui::EndFrame();
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
