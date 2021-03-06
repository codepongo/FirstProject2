#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* WindowThumbnailVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_BoundsLeftProperty(),
		get_BoundsTopProperty(),
		get_BoundsWidthProperty(),
		get_BoundsHeightProperty(),
		get_FillAreaProperty(),
		get_ContourLengthProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* WindowThumbnailVisual::pClass(get_Class());

WindowThumbnailVisual::WindowThumbnailVisual() : UIElement(get_Class())
{
}

WindowThumbnailVisual::WindowThumbnailVisual(HWND hwndSource) : UIElement(get_Class()),
	m_hWndSource(hwndSource)
{
}

void WindowThumbnailVisual::Render(ManagedRenderContext renderContext)
{
	if (m_phThumbnailId == nullptr)
	{
		Window* root = dynamic_cast<Window*>(GetRoot());
		if (root)
		{
			HWND hWndDest = root->get_PWindow()->get_Handle();

			HRESULT hr;

			hr = DwmRegisterThumbnail(hWndDest, m_hWndSource, &m_phThumbnailId);
			ASSERT(SUCCEEDED(hr));
		}
	}

	if (m_phThumbnailId)
	{
	//destination rectangle size
		RECT destRect = {10,10,250,250};

		//Set thumbnail properties for use
		DWM_THUMBNAIL_PROPERTIES dskThumbProps;
		dskThumbProps.dwFlags = DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE | DWM_TNP_OPACITY | DWM_TNP_SOURCECLIENTAREAONLY;

		if (m_srcRect.Width > 0)
		{
			RECT srcRect =
			{
				m_srcRect.X,
				m_srcRect.Y,
				m_srcRect.GetRight(),
				m_srcRect.GetBottom()
			};

			dskThumbProps.dwFlags |= DWM_TNP_RECTSOURCE;
			dskThumbProps.rcSource = srcRect;
		}

		float opacity = get_Opacity();
		if (opacity < 0) opacity = 0;
		else if (opacity > 1) opacity = 1;

		//use window frame and client area
		dskThumbProps.fSourceClientAreaOnly = FALSE;
		dskThumbProps.fVisible = TRUE;
		dskThumbProps.opacity = BYTE(opacity*255);
		dskThumbProps.rcDestination = destRect;

		//display the thumbnail
		HRESULT hr = DwmUpdateThumbnailProperties(m_phThumbnailId, &dskThumbProps);
		ASSERT(SUCCEEDED(hr));
	}
}

}	// Gui
}	// System
