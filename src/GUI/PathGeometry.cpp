#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(FillMode, PathGeometry, FillMode, FillMode_Winding)

DependencyClass* PathGeometry::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FillModeProperty(),
	};

	return &depclass;
}

DependencyClass* PathGeometry::pClass(get_Class());

PathGeometry::PathGeometry() : Geometry(get_Class())
{
}

PathGeometry::PathGeometry(ID2D1PathGeometry* d2d1geometry) : Geometry(get_Class()),
	m_D2DGeometry(d2d1geometry)
{
}

#if 0
void PathGeometry::BeginFigure()
{
	MoveToPathSegment* seg = new MoveToPathSegment(point);
	m_segments.push_back(seg);

	if (m_D2DGeometry)
	{
		m_D2DGeometry->Release();
		m_D2DGeometry = NULL;
	}

	/*
	if (GetRoot())
	{
		GetRoot()->Invalidate();
	}
	*/
}
#endif

void PathGeometry::LineTo(gm::PointF point)
{
	if (m_figures.size() == 0)
	{
		m_figures.push_back(new PathFigure);
	}

	PathFigure* figure = m_figures.back();
	figure->LineTo(point);

	/*
	LineToPathSegment* seg = new LineToPathSegment(point);
	figure->m_segments.push_back(seg);

	if (m_D2DGeometry)
	{
		m_D2DGeometry->Release();
		m_D2DGeometry = NULL;
	}
	*/

	/*
	if (GetRoot())
	{
		GetRoot()->Invalidate();
	}
	*/
}

HRGN PathGeometry::CreateHRGN()
{
	ASSERT(0);
	return NULL;
}

void PathGeometry::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_FillModeProperty())
	{
		if (m_D2DGeometry)
		{
			m_D2DGeometry->Release();
			m_D2DGeometry = NULL;
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

ID2D1PathGeometry* PathGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == NULL)
	{
		Graphics::Direct10::s.m_D2DFactory->CreatePathGeometry(&m_D2DGeometry);

		ID2D1GeometrySink* pGeometrySink;
		m_D2DGeometry->Open(&pGeometrySink);

		FillMode fillMode = get_FillMode();
		pGeometrySink->SetFillMode(fillMode == FillMode_Alternate? D2D1_FILL_MODE_ALTERNATE: D2D1_FILL_MODE_WINDING);

		for (auto it = m_figures.begin(); it != m_figures.end(); ++it)
		{
			PathFigure* figure = *it;
			figure->Sink(pGeometrySink);
		}

		pGeometrySink->Close();
		pGeometrySink->Release();
	}

	return m_D2DGeometry;
}

}	// Gui
}	// System
