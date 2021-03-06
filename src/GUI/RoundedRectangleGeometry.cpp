#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, Left, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, Top, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, Width, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, Height, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, RadiusX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RoundedRectangleGeometry, RadiusY, 0.0f)

DependencyClass* RoundedRectangleGeometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_LeftProperty(),
		get_TopProperty(),
		get_WidthProperty(),
		get_HeightProperty(),
		get_RadiusXProperty(),
		get_RadiusYProperty(),
	};

	return &depclass;
}

DependencyClass* RoundedRectangleGeometry::pClass(get_Class());

RoundedRectangleGeometry::RoundedRectangleGeometry() : Geometry(get_Class())
{
}

/*
RoundedRectangleGeometry::RoundedRectangleGeometry(float x, float y, float width, float height, float rx, float ry) : Geometry(&s_Class)
{
	set_X(x);
	set_Y(y);
	set_Width(width);
	set_Height(height);
	set_RadiusX(rx);
	set_RadiusY(ry);
}
*/

/*
RoundedRectangleGeometry::RoundedRectangleGeometry(const Expressive::typed_expression<float>& x, const Expressive::typed_expression<float>& y, const Expressive::typed_expression<float>& width, const Expressive::typed_expression<float>& height, const Expressive::typed_expression<float>& rx, const Expressive::typed_expression<float>& ry) : Geometry(&s_Class)
{
	GetProperty(&XProperty)->SetInputBinding(new ExpressionBinding(this, x));
	GetProperty(&YProperty)->SetInputBinding(new ExpressionBinding(this, y));
	GetProperty(&WidthProperty)->SetInputBinding(new ExpressionBinding(this, width));
	GetProperty(&HeightProperty)->SetInputBinding(new ExpressionBinding(this, height));
	GetProperty(&RadiusXProperty)->SetInputBinding(new ExpressionBinding(this, rx));
	GetProperty(&RadiusYProperty)->SetInputBinding(new ExpressionBinding(this, ry));
}
*/

RoundedRectangleGeometry::RoundedRectangleGeometry(typed<float> left, typed<float> top, typed<float> width, typed<float> height, typed<float> rx, typed<float> ry) : Geometry(get_Class())
{
	SetBinding(this, get_LeftProperty(), left);
	SetBinding(this, get_TopProperty(), top);
	SetBinding(this, get_WidthProperty(), width);
	SetBinding(this, get_HeightProperty(), height);
	SetBinding(this, get_RadiusXProperty(), rx);
	SetBinding(this, get_RadiusYProperty(), ry);
}

ID2D1RoundedRectangleGeometry* RoundedRectangleGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == NULL)
	{
		D2D1_ROUNDED_RECT roundedRect;
		roundedRect.rect.left = get_Left();
		roundedRect.rect.top = get_Top();
		roundedRect.rect.right = roundedRect.rect.left + get_Width();
		roundedRect.rect.bottom = roundedRect.rect.top + get_Height();
		roundedRect.radiusX = get_RadiusX();
		roundedRect.radiusY = get_RadiusY();

		Graphics::Direct10::get_D2DFactory()->CreateRoundedRectangleGeometry(roundedRect, &m_D2DGeometry);
	}

	return m_D2DGeometry;
}

HRGN RoundedRectangleGeometry::CreateHRGN()
{
	float x1 = get_Left();
	float y1 = get_Top();
	float x2 = x1 + get_Width();
	float y2 = y1 +get_Height();
	float rx = get_RadiusX();
	float ry = get_RadiusY();

	return CreateRoundRectRgn(int(x1), int(y1), int(x2), int(y2), int(rx*2), int(ry*2));
}

void RoundedRectangleGeometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
	if (renderContext.m_p->GetRT()->m_spRT)
	{
		if (brush)
		{
			D2D1_ROUNDED_RECT roundedRect;
			roundedRect.rect.left = get_Left();
			roundedRect.rect.top = get_Top();
			roundedRect.rect.right = roundedRect.rect.left + get_Width();
			roundedRect.rect.bottom = roundedRect.rect.top + get_Height();
			roundedRect.radiusX = get_RadiusX();
			roundedRect.radiusY = get_RadiusY();

			renderContext.m_p->GetRT()->m_spRT->FillRoundedRectangle(roundedRect, brush->Create(renderContext.m_p, NULL/*this*/));
		}
	}
}

void RoundedRectangleGeometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
	if (renderContext.m_p->GetRT()->m_spRT)
	{
		if (brush)
		{
			D2D1_ROUNDED_RECT roundedRect;
			roundedRect.rect.left = get_Left();
			roundedRect.rect.top = get_Top();
			roundedRect.rect.right = roundedRect.rect.left + get_Width();
			roundedRect.rect.bottom = roundedRect.rect.top + get_Height();
			roundedRect.radiusX = get_RadiusX();
			roundedRect.radiusY = get_RadiusY();

			ID2D1StrokeStyle* strokeStyle = NULL;
			renderContext.m_p->GetRT()->m_spRT->DrawRoundedRectangle(roundedRect, brush->Create(renderContext.m_p, NULL/*this*/), width, strokeStyle);
		}
	}
}

}	// Gui
}	// System
