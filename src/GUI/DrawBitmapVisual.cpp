#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* DrawBitmapVisual::get_Class()
{
	static DependencyClass depclass(typeid(DrawBitmapVisual), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BitmapProperty(),
		get_DestLeftProperty(),
		get_DestTopProperty(),
		get_DestWidthProperty(),
		get_DestHeightProperty(),
	};

	return &depclass;
}

DependencyClass* DrawBitmapVisual::pClass(get_Class());

IMP_DEPENDENCY_PROPERTY(Graphics::Bitmap*, DrawBitmapVisual, Bitmap, nullptr)
IMP_DEPENDENCY_PROPERTY(float, DrawBitmapVisual, DestLeft, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, DrawBitmapVisual, DestTop, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, DrawBitmapVisual, DestWidth, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, DrawBitmapVisual, DestHeight, 0.0f)
//TypedDependencyProperty<float> DrawBitmapVisual::DestRightProperty(&Class, WSTR("DestRight"), _this().Rect().getRight());
//TypedDependencyProperty<float> DrawBitmapVisual::DestBottomProperty(&Class, WSTR("DestBottom"), _this().getDestRect().getBottom());

DrawBitmapVisual::DrawBitmapVisual() : UIElement(get_Class())
{
}

DrawBitmapVisual::DrawBitmapVisual(Graphics::Bitmap* bitmap) : UIElement(get_Class())
{
	set_Bitmap(bitmap);
	if (bitmap)
	{
		set_DestRect(gm::RectF(gm::PointF(0,0), gm::SizeF(float(bitmap->GetWidth()), float(bitmap->GetHeight()))));
	}
}

DrawBitmapVisual::DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::PointF topleft) : UIElement(get_Class())
{
	set_Bitmap(bitmap);
	if (bitmap)
	{
		set_DestRect(gm::RectF(topleft, gm::SizeF(bitmap->GetWidth(), bitmap->GetHeight())));
	}
}

DrawBitmapVisual::DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect) : UIElement(get_Class())
{
	set_Bitmap(bitmap);
	set_DestRect(dstRect);
}

DrawBitmapVisual::DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect, float opacity) : UIElement(get_Class())
{
	set_Bitmap(bitmap);
	set_DestRect(dstRect);
	set_Opacity(opacity);
}

DrawBitmapVisual::DrawBitmapVisual(Graphics::Bitmap* bitmap, gm::RectF dstRect, float opacity, gm::RectF srcRect) : UIElement(get_Class())
{
	set_Bitmap(bitmap);
	set_DestRect(dstRect);
	set_Opacity(opacity);

	// TODO srcRect
}

gm::RectF DrawBitmapVisual::get_DestRect()
{
	return gm::RectF(
		get_DestLeft(),
		get_DestTop(),
		get_DestWidth(),
		get_DestHeight());
}

void DrawBitmapVisual::set_DestRect(gm::RectF destRect)
{
	set_DestLeft(destRect.GetLeft());
	set_DestTop(destRect.GetTop());
	set_DestWidth(destRect.Width);
	set_DestHeight(destRect.Height);
}

void DrawBitmapVisual::Render(ManagedRenderContext renderContext)
{
	Graphics::Bitmap* bitmap = get_Bitmap();
	if (bitmap)
	{
		gm::RectF dstRect = get_DestRect();

		renderContext.DrawBitmap(bitmap, dstRect, get_Opacity());
	}
}

Graphics::Bitmap* DrawBitmapVisual::GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY)
{
	Graphics::Bitmap* bitmap = get_Bitmap();
	return bitmap;
}

UIElement* DrawBitmapVisual::HitTest(gm::PointF point)
{
	gm::RectF r = get_DestRect();
	if (r.Contains(point))
		return this;
	else
		return nullptr;
}

}	// Gui
}	// System
