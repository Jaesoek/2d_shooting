#include "stdafx.h"
#include "Vertex.h"

DWORD VertexP::FVF = D3DFVF_XYZW;
const DWORD VertexPT::FVF = D3DFVF_XYZW | D3DFVF_TEX1;
const DWORD VertexPC::FVF = D3DFVF_XYZW | D3DFVF_DIFFUSE;
