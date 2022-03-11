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

using namespace std;

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

template<typename T>
using Ref = shared_ptr<T>;

template<typename T>
using WRef = weak_ptr<T>;

#include "Macro.h"

