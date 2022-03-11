#pragma once

#include <Windows.h>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>

#include <cmath>
#include <string>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"


using namespace std;

template<typename T>
using Ref = shared_ptr<T>;

template<typename T>
using WRef = weak_ptr<T>;

#include "Macro.h"
#include "Type.h"

