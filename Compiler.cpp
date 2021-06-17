#include "pch.h"
#include "Compiler.h"

using namespace std;

bool Compiler::Compile(const char* path, unsigned int passType, Shader* shader)
{
    USES_CONVERSION;

    HRESULT result;
    DWORD compileFlag = 0;
    ID3DBlob* vertexBlob, *geometryBlob, *domainBlob, *hullBlob, *pixelBlob, *computeBlob, *errorBlob;

#ifdef _DEBUG | DEBUG
    compileFlag |= D3DCOMPILE_DEBUG;
#endif

    auto device = Hardware::GetDevice();

    if ((passType & eVertex) == eVertex)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "vert", "vs_5_0", 0, compileFlag, &vertexBlob, &errorBlob);
        
        if (result != S_OK)
        {
            DebugLog("failed to compile vertex shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        }

        Reflect(vertexBlob, shader);



        result = device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, shader->mVertex.GetAddressOf());
        vertexBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a vertex shader.");
            return false;
        }
    
    }

    if ((passType & eGeometry) == eGeometry)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "geo", "gs_5_0", 0, compileFlag, &geometryBlob, &errorBlob);

        if (result != S_OK)
        {
            DebugLog("failed to compile geometry shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        }

        result = device->CreateGeometryShader(geometryBlob->GetBufferPointer(), geometryBlob->GetBufferSize(), nullptr, shader->mGeometry.GetAddressOf());
        geometryBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a geometry shader.");
            return false;
        }



    }

    if ((passType & eDomain) == eDomain)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "dom", "ds_5_0", 0, compileFlag, &domainBlob, &errorBlob);

        if (result != S_OK)
        {
            DebugLog("failed to compile domain shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());

            errorBlob->Release();
            return false;
        }

        result = device->CreateDomainShader(domainBlob->GetBufferPointer(), domainBlob->GetBufferSize(), nullptr, shader->mDomain.GetAddressOf());
        domainBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a domain shader.");
            return false;
        }

    }

    if ((passType & eHull) == eHull)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "hul", "hs_5_0", 0, compileFlag, &hullBlob, &errorBlob);

        if (result != S_OK)
        {
            DebugLog("failed to compile hull shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        }

        result = device->CreateHullShader(hullBlob->GetBufferPointer(), hullBlob->GetBufferSize(), nullptr, shader->mHull.GetAddressOf());
        hullBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a hull shader.");
            return false;
        }
    }

    if ((passType & ePixel) == ePixel)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "pix", "ps_5_0", 0, compileFlag, &pixelBlob, &errorBlob);

        if (result != S_OK)
        {
            DebugLog("failed to compile pixel shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        }

        result = device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, shader->mPixel.GetAddressOf());
        pixelBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a pixel shader.");
            return false;
        }
    }

    if ((passType & eCompute) == eCompute)
    {
        result = D3DCompileFromFile(A2W(path), nullptr,
            D3D_COMPILE_STANDARD_FILE_INCLUDE, "comp", "cs_5_0", 0, compileFlag, &computeBlob, &errorBlob);

        if (result != S_OK)
        {
            DebugLog("failed to compile compute shader.");
            DebugLog((const char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
            return false;
        }

        result = device->CreateComputeShader(computeBlob->GetBufferPointer(), computeBlob->GetBufferSize(), nullptr, shader->mCompute.GetAddressOf());
        computeBlob->Release();

        if (result != S_OK)
        {
            DebugLog("failed to create a compute shader.");
            return false;
        }
    }

    return true;
}

bool Compiler::Reflect(ID3DBlob* vertexBlob, Shader* shader)
{
    HRESULT result;

    auto device = Hardware::GetDevice();

    ID3D11ShaderReflection* reflection;

    result = D3DReflect(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), __uuidof(ID3D11ShaderReflection), (void**)&reflection);
    assert(result == S_OK);
    if (result != S_OK)
        return false;

    unsigned int byteOffset = 0;
    D3D11_SHADER_DESC shaderDesc{};
    vector<D3D11_INPUT_ELEMENT_DESC> inputElements;
    D3D11_SIGNATURE_PARAMETER_DESC signParam;
    reflection->GetDesc(&shaderDesc);
    for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
    {
        reflection->GetInputParameterDesc(i, &signParam);

        D3D11_INPUT_ELEMENT_DESC element;

        element.SemanticName = signParam.SemanticName;
        element.SemanticIndex = signParam.SemanticIndex;
        element.InputSlot = 0;
        element.AlignedByteOffset = byteOffset;
        element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        element.InstanceDataStepRate = 0;

        if (signParam.Mask == 1)
        {
            if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32_UINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32_SINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32_FLOAT;

            byteOffset += 4;
        }
        else if (signParam.Mask <= 3)
        {
            if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32_UINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32_SINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32_FLOAT;
            byteOffset += 8;
        }
        else if (signParam.Mask <= 7)
        {
            if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            byteOffset += 12;
        }

        else if (signParam.Mask <= 15)
        {
            if (signParam.ComponentType == D3D_REGISTER_COMPONENT_UINT32) element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_SINT32) element.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (signParam.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            byteOffset += 16;
        }


        inputElements.push_back(element);
    }

    result = device->CreateInputLayout(inputElements.data(), inputElements.size(), vertexBlob->GetBufferPointer(), static_cast<unsigned int>(vertexBlob->GetBufferSize()), shader->mLayout.GetAddressOf());
    assert(result == S_OK);

    if (result != S_OK)
        return false;

    return true;
}
