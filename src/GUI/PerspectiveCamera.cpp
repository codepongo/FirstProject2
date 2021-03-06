#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

DependencyClass* Camera::get_Class()
{
	static DependencyClass depclass(typeid(Camera), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_EyeProperty(),
		get_AtProperty(),
		get_UpProperty(),
	};
	*/

	return &depclass;
}

//

IMP_DEPENDENCY_PROPERTY(Vector3_F*, PerspectiveCamera, Eye, new Vector3_F(0.0f, 0.0f, 10.0f)/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(Vector3_F*, PerspectiveCamera, At, new Vector3_F(0.0f, 0.0f, 0.0f)/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(Vector3_F*, PerspectiveCamera, Up, new Vector3_F(0.0f, 1.0f, 0.0f)/*, new PropertyMetadata(true)*/)
IMP_DEPENDENCY_PROPERTY(float, PerspectiveCamera, FieldOfView, gmRadians(45.0f)/*, new PropertyMetadata(true)*/)

DependencyClass* PerspectiveCamera::get_Class()
{
	static DependencyClass depclass(typeid(PerspectiveCamera), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_EyeProperty(),
		get_AtProperty(),
		get_UpProperty(),
		get_FieldOfViewProperty(),
	};

	return &depclass;
}

DependencyClass* PerspectiveCamera::pClass(get_Class());

CTOR PerspectiveCamera::PerspectiveCamera() : Camera(get_Class())
{
}

void PerspectiveCamera::LookAt(Vec3f eye, Vec3f at, Vec3f up)
{
	set_Eye(new Vector3_F(eye));
	set_At(new Vector3_F(at));
	set_Up(new Vector3_F(up));
}

D3DXMATRIX PerspectiveCamera::GetViewMatrix()
{
	Vector3_F* pEye = get_Eye();
	Vector3_F* pAt = get_At();
	Vector3_F* pUp = get_Up();

	D3DXVECTOR3 eye(pEye->get_X(), pEye->get_Y(), pEye->get_Z());
	D3DXVECTOR3 at(pAt->get_X(), pAt->get_Y(), pAt->get_Z());
	D3DXVECTOR3 up(pUp->get_X(), pUp->get_Y(), pUp->get_Z());

	D3DXMATRIX m;
	D3DXMatrixLookAtRH(&m, &eye, &at, &up);
	return m;
}

D3DXMATRIX PerspectiveCamera::GetViewMatrixI()
{
	D3DXMATRIX m;
	return m;
}

D3DXMATRIX PerspectiveCamera::GetProjectionMatrixLH(float width, float height, float zNear, float zFar)
{
	float aspect = width/height;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovLH(&projection, get_FieldOfView(), aspect, zNear, zFar);
	return projection;
}

D3DXMATRIX PerspectiveCamera::GetProjectionMatrixRH(float width, float height, float zNear, float zFar)
{
	float aspect = width/height;
	D3DXMATRIX projection;
	D3DXMatrixPerspectiveFovRH(&projection, get_FieldOfView(), aspect, zNear, zFar);
	return projection;
}

}	// Media3D
}	// Gui
}	// System
