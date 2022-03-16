#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Matrix = D3DXMATRIX;
using Vec2 = D3DXVECTOR2;
using Vec3 = D3DXVECTOR3;
using Vec4 = D3DXVECTOR4;
using Color = D3DCOLOR;




struct Vertex
{
	float x, y, z;
	static const uint32 FVF;
};

