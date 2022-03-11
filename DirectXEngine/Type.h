#pragma once


using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;



struct Vertex
{
	float x, y, z, rhw;	// from the D3DFVF_XYZRHW flag
	uint32 color;		// from the D3DFVF_DIFFUSE flag
};

