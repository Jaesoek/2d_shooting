// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
//1.빈프로젝트[o] , 미리컴파일링된 헤더 [x]
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
//
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <map>

#include <time.h>
#include <assert.h>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;


#include <d3d9.h> //Window Sdk, Directx sdk
#include <d3dx9.h> //Directx SDk
//#include "c:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"
//#include "c:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"
//외부기호 참조 -> 함수이름은 아는데 함수의 내용(정의)을 모를때 
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

#include "./_ImGui/imgui.h"
#include "./_ImGui/imgui_impl_dx9.h"
#pragma comment(lib, "./_ImGui/ImGuiDx9.lib")

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "D2D.h"

#include "CommonMacroFunction.h"
#include "Intersect.h"

// simple Getter - Setter
#define GETTER_SETTER(TYPE, FUNC_NAME, PROP) \
		TYPE Get##FUNC_NAME() \
		{\
			return PROP;\
		}\
		void Set##FUNC_NAME(TYPE _PROP) \
		{\
			PROP = _PROP;\
		}

///////////////////// Manager Class //////////////////
#include "keybord.h"
#include "Texture.h"
#include "Font.h"
#include "Vertex.h"
#include "Rect.h"

#define WINSIZE_X 1000
#define WINSIZE_Y 1000

#define SAFE_DELETE(p)	{if((p) != NULL){delete(p);    (p) = NULL; }}
#define SAFE_RELEASE(p)	{if((p) != 0){p->Release(); (p) = 0; }}

extern bool _bDebug;
extern POINT _ptMouse;