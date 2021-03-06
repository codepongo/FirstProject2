// Graphics.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Graphics.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "Imaging")

// Direct3D 9
#pragma comment(lib, "d3d9")

#ifdef _DEBUG
#pragma comment(lib, "d3dx9d")
#else
#pragma comment(lib, "d3dx9")
#endif

// Direct3D 10_1
#ifdef _DEBUG
#pragma comment(lib, "d3d10_1")
#pragma comment(lib, "d3d10")
#pragma comment(lib, "d3dx10d")
#else
#pragma comment(lib, "d3d10_1")
#pragma comment(lib, "d3d10")
#pragma comment(lib, "d3dx10")
#endif

#pragma comment(lib, "dxgi")

#pragma comment(lib, "D3D11")
#pragma comment(lib, "D3dcompiler")
//#pragma comment(lib, "Effects11")

#ifdef _DEBUG
#pragma comment(lib, "D3DX11d")
#else
#pragma comment(lib, "D3DX11")
#endif

// Direct2D
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

// OpenGL
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// CG
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")
#pragma comment(lib, "cgD3D9.lib")

namespace System
{
namespace Graphics
{

Light::Light()
{
	m_ambient = gm::vector4f(0, 0, 0, 1);
	m_diffuse = gm::vector4f(0, 0, 0, 1);
	m_specular = gm::vector4f(0, 0, 0, 1);

	m_constant_attenuation = 1.0f;
	m_linear_attenuation = 0;
	m_quadratic_attenuation = 0;
}

}	// Graphics
}	// System
