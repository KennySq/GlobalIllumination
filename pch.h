// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

#define FBXSDK_SHARED

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "d3d10.lib")

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#include<fbxsdk.h>

#include<d3d11.h>
#include<d3d10.h>
#include<dxgi.h>
#include<d3dcompiler.h>
#include<d3d11shader.h>
#include<d3d10shader.h>
#include<DirectXMath.h>
#include<DirectXColors.h>
#include<dinput.h>

#include"include/imgui/imgui_impl_dx11.h"
//#include"include/imgui/"
#include"include/imgui/imgui.h"
#include"include/imgui/imgui_impl_win32.h"

#include<wrl.h>
#include<atlbase.h>

#include<string>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<map>

#include"Utility.h"
#include"Hardware.h"

#include"MemoryBank.h"

#include "Compiler.h"
#include"Input.h"

#include"GUI.h"

#endif //PCH_H
