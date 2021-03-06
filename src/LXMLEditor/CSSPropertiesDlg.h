// CSSPropertiesDlg.h : Declaration of the CCSSPropertiesDlg

#ifndef __CSSPROPERTIESDLG_H_
#define __CSSPROPERTIESDLG_H_

#include "resource.h"       // main symbols

#include "item.h"

class CView;

namespace System
{
namespace LXmlEdit
{

void DrawPopupArrow(MSWindows::HDC hDC, int midx, int topy, int size);

#define NM_SETNUMBER	WM_USER+2

class CPopupSlider :
public UI::Control//CWindowImpl<CPopupSlider>
{
public:
//	DECLARE_WND_CLASS_EX("PopupSlider", CS_DBLCLKS, COLOR_BTNFACE)

	CPopupSlider()
	{
		m_dragging = 0;
	}

	double m_minValue;
	double m_maxValue;
	double m_value;
	UI::Control* m_hParent;

	int m_dragging;

	void GetValue(UI::Control* hParent, double minValue, double maxValue, double value, int x, int top, int width)
	{
		m_hParent = hParent;

		m_minValue = minValue;
		m_maxValue = maxValue;
		m_value = value;

		double range = m_maxValue-m_minValue;

		int left = x-(width*(m_value-m_minValue))/range;

		ASSERT(0);
#if 0
		CRect rc(left-5, top, left+width+5, top+12);

		AdjustWindowRectEx(&rc, WS_DLGFRAME, FALSE, 0/*WS_EX_TOOLWINDOW*/);

		Create(m_hParent, rc, NULL, WS_POPUP | WS_VISIBLE | WS_DLGFRAME/*, WS_EX_TOOLWINDOW*/);
		ASSERT(m_hWnd);

		SetCapture();
#endif

		m_dragging = 1;
	}

#if 0
BEGIN_MSG_MAP(CPopupSlider)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPoint point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

		point.x -= 5;

		CRect client;
		GetClientRect(&client);

		client.right -= 10;

		double range = m_maxValue-m_minValue;

		m_value = (point.x*range + m_minValue) / client.Width();

		if (m_value < m_minValue) m_value = m_minValue;
		else if (m_value > m_maxValue) m_value = m_maxValue;

		Invalidate();
		UpdateWindow();

		::SendMessage(m_hParent, SBM_SETPOS, (int)(m_value*65536), 0);

		return 0;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_dragging = 0;
		ReleaseCapture();
		DestroyWindow();

		::SendMessage(::GetParent(m_hParent), NM_SETNUMBER, 0, (int)(m_value*65536));

		return 0;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);

		CRect client;
		GetClientRect(&client);

		client.right -= 10;

		double range = m_maxValue-m_minValue;

		dc.Draw3dRect(5, 2, client.Width()+1, 3, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));

		int x = 5+(client.Width()*(m_value-m_minValue))/range;

		POINT pt[] =
		{
			x, 5+0,
			x-5, 5+5,
			x+5, 5+5,
		};

		dc.Polygon(pt, 3);

		return 0;
	}
#endif
};

class CEditNumberWnd : public UI::Control//CWindowImpl<CEditNumberWnd>
{
public:
	CEditNumberWnd()// : m_edit("EDIT", this, 1)
	{
	}

	//CContainedWindow m_edit;
	CPopupSlider m_slider;

	int m_value;
	int m_minValue;
	int m_maxValue;

	/*
BEGIN_MSG_MAP(CEditNumberWnd)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(SBM_SETPOS, OnSetPos)
	MESSAGE_HANDLER(SBM_SETRANGE, OnSetRange)
	MESSAGE_HANDLER(WM_SETFONT, OnSetFont)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnEditKeydown)
END_MSG_MAP()
*/

#if 0
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), EN_KILLFOCUS), (LPARAM)m_hWnd);
		return 0;
	}

	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if ((uMsg == WM_KILLFOCUS) ||
			(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
		{
			TCHAR buf[64];
			m_edit.GetWindowText(buf, sizeof(buf));
			m_value = atof(buf)*65536;

			::SendMessage(GetParent(), NM_SETNUMBER, 0, m_value);

			::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetWindowLong(GWL_ID), EN_KILLFOCUS), (LPARAM)m_hWnd);

			//if (uMsg == WM_KEYDOWN)
				return 0;
		}

		return m_edit.DefWindowProc(uMsg, wParam, lParam);
	}

	LRESULT OnSetFont(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_edit.SendMessage(WM_SETFONT, wParam, lParam);
	}

	LRESULT OnSetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_minValue = wParam;
		m_maxValue = lParam;
		return 0;
	}

	LRESULT OnSetPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_value = wParam;

		TCHAR buf[32];
		sprintf(buf, "%g", m_value/65536.0);
		m_edit.SetWindowText(buf);

		return 0;
	}
#endif

#if 0
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_edit.Create(m_hWnd, &CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER);
		return 0;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect client;
		GetClientRect(&client);

		m_edit.MoveWindow(0, 0, client.right-16, client.bottom);

		return 0;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);

		CRect client;
		GetClientRect(&client);

		DrawPopupArrow(dc.m_hDC, client.right-8, (client.bottom-4)/2, 4);

		return 0;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPoint point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

		CRect client;
		GetClientRect(&client);

		if (point.x > client.right-16)
		{
			CPoint scrpt;
			scrpt.x = point.x;//client.right;
			//scrpt.x = m_splitx;
			scrpt.y = client.bottom;//point.y;
			ClientToScreen(&scrpt);

			/*double value = */m_slider.GetValue(m_hWnd,
				m_minValue/65536.0,
				m_maxValue/65536.0,
				m_value/65536.0,
				scrpt.x, scrpt.y, 100);

			/*m_value = value*65536;*/

			/*
			TCHAR buf[32];
			sprintf(buf, "%g", m_value/65536.0);
			m_edit.SetWindowText(buf);
			*/
		}

		return 0;
	}
#endif
};

class CCSSProperty;

class CCSSPropertiesDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CCSSPropertiesDlg, &CLSID_CSSPropertiesDlg>,
//	public IDispatchImpl<ICSSPropertiesDlg, &IID_ICSSPropertiesDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,
//	public CUIDialogImpl<CCSSPropertiesDlg, CWindowImpl<CCSSPropertiesDlg> >,
//	public CUIEventHandlerImpl,
public UI::ProcessTargetCommands,	// ILDOMEventListener
//	public CMessageFilter,

	public Web::ICSSStyleDeclarationHandler

//	public IDispEventImpl<1, CCSSPropertiesDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
#if 0
	public IDispEventImpl<2, CCSSPropertiesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
//	public IDispEventImpl<3, CCSSPropertiesDlg, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>
{
public:
//	DECLARE_WND_CLASS_EX(NULL, CS_DBLCLKS, COLOR_BTNFACE)

	CCSSPropertiesDlg();

	int FinalConstruct();
	void FinalRelease();

//	int m_category;

	CView* m_view;
	ILXMLEditorApp* m_app;

//	CEditNumberWnd m_editNumberWnd;
//	CContainedWindow m_comboBoxWnd;
	UI::Control * m_wnd;
//	UI::Control* m_hWndEdit;
//	CContainedWindow m_wndEdit;

	//CButton m_newProperty;
//	CAxWindow m_axbuttonsCtl;
//	CComPtr<IUIToolbarButtons> m_buttonsCtl;
	LDraw::Bitmap* m_hButtonsBitmap;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;

//	CComPtr<ILDOMElement> m_element;

	IECSSSelection* m_viewGroup;

	Web::ICSSStyleDeclaration* m_style;

	LDraw::BBoxi m_areaRect;

//	int m_activeCategory;

	LDraw::Bitmap* m_expandedBitmap;

	int m_splitx;

	C2Obj* m_pTree;
	CCSSProperty* m_pActiveProperty;
	int m_activeIndex;

	bool m_bModal;

//	BOOL m_bTabbedView;

	void RebuildList();

	void EndEdit();
	void OnSize();

	void Apply();

	void SetPropertyValue(System::StringW* value);

	//virtual BOOL PreTranslateMessage(MSG* pMsg);

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCSSPropertiesDlg)
	COM_INTERFACE_ENTRY(ICSSPropertiesDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

	COM_INTERFACE_ENTRY(ILCSSStyleDeclarationHandler)
END_COM_MAP()
*/

//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);
//	void __stdcall OnVertScroll(long code, long pos);
	void __stdcall OnViewGroupSelectionChanged();
	void __stdcall OnToolbarButtonClick(long buttonid);

	/*
BEGIN_MSG_MAP(CCSSPropertiesDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)

	COMMAND_ID_HANDLER(IDOK, OnOK)

	COMMAND_HANDLER(1, EN_KILLFOCUS, OnKillFocus)

	COMMAND_HANDLER(2, CBN_KILLFOCUS, OnCbnKillFocus)
	COMMAND_HANDLER(2, CBN_SELENDOK, OnCbnSelendOk)

	COMMAND_HANDLER(3, EN_KILLFOCUS, OnEditNumberKillFocus)

	MESSAGE_HANDLER(NM_SETNUMBER, OnSetNumber)

	MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)

	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
		MESSAGE_HANDLER(EN_KILLFOCUS, OnEditKeydown)
//		MESSAGE_HANDLER(CBN_KILLFOCUS, OnEditKeydown)

	ALT_MSG_MAP(2)
		MESSAGE_HANDLER(WM_KEYDOWN, OnCbKeydown)
		MESSAGE_HANDLER(WM_GETDLGCODE, OnCbGetDlgCode)
END_MSG_MAP()
*/
	/*
	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCbKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCbGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	*/

	long OnOK(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	/*
	LRESULT OnKillFocus(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);

	LRESULT OnCbnKillFocus(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);
	LRESULT OnCbnSelendOk(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);

	LRESULT OnEditNumberKillFocus(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);

	LRESULT OnSetNumber(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	*/

DECLARE_CMD_MAP(CCSSPropertiesDlg)

//	LRESULT OnTabbedView(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);
//	void OnTabbedViewUpdate(long iid, IUICmdUpdate* pCmdUI);

// ICSSPropertiesDlg
public:
// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);

// ILCSSStyleDeclarationHandler
	ErrorCode handleCSSEvent(/*[in]*/ long type, /*[in]*/ System::StringW* propertyName);
};

}	// LXmlEdit
}

#endif //__CSSPROPERTIESDLG_H_
