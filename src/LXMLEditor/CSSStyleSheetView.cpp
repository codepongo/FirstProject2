// CSSStyleSheetView.cpp : Implementation of CCSSStyleSheetView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "CSSStyleSheetView.h"

#include "ECSSViewGroup.h"
#include "ECSSDocument.h"
//#include "SourceView.h"	// TODO remove

#if 0

void GetParentRuleList(ILCSSRule* rule, ILCSSRuleList* *pVal);
int GetRuleIndex(ILCSSRuleList* ruleList, ILCSSRule* rule);

#define PANE_NAME			0
#define PANE_MEDIA		1
#define PANE_URL			2
#define PANE_SOURCE		3

/////////////////////////////////////////////////////////////////////////////
// CCSSStyleSheetView

int CCSSStyleSheetView::FinalConstruct()
{
	HRESULT hr;

//	hr = m_ctl.CoCreateInstance(CLSID_CSSStyleSheetViewCtl);
//	if (FAILED(hr)) return hr;

	return S_OK;
}

// ILElementBehavior
STDMETHODIMP CCSSStyleSheetView::Init(/*[in]*/ ILElementBehaviorSite* pBehaviorSite)
{
	ASSERT(0);
#if 0
	m_behaviorSite = pBehaviorSite;

	CComPtr<ILDOMElement> element;
	m_behaviorSite->GetElement(&element);

	CComPtr<ILDOMDocument> document;
	element->get_ownerDocument(&document);

	document->createElementNS(L"http://www.lerstad.com/2004/lxui", L"tree", (ILDOMElement**)&m_treeElement);
//	m_editObjectElement->setAttribute(L"classid", L"clsid:{94327EC1-8D79-4A8E-B9B7-ACCCE8C787EF}");
#if 0
	m_treeElement->setAttribute(L"style", L"-moz-box-flex: 1;");
#endif

//	document->createElementNS(L"http://www.lerstad.com/2004/lxui", L"p", (ILDOMElement**)&m_statusBarElement);
//	m_statusBarElement->put_textContent(L"");

//	element->appendChild(m_editObjectElement, NULL);
	element->appendChild(m_treeElement, NULL);

//	CComPtr<IUnknown> unk;
//	m_editObjectElement->get__object(&unk);

//	m_edit = CComQIPtr<IUIEdit>(unk);
//	if (m_edit == NULL) return E_FAIL;
#endif
	OnCreate();

	return S_OK;
}

STDMETHODIMP CCSSStyleSheetView::Detach()
{
	m_behaviorSite.Release();
	return S_OK;
}

STDMETHODIMP CCSSStyleSheetView::OnDragOut(IUIDockBar* dockBar)
{
	return S_OK;
}

#if 0
void CCSSStyleSheetView::PopulateRules(DWORD parentItem, ILCSSRuleList* ruleList)
{
	long nrules;
	ruleList->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule;
		ruleList->item(i, &rule);

		LCSSType type;
		rule->get_type(&type);

		switch (type)
		{
		case COMMENT_RULE:	// comment (this is an Extension to the CSS OM)
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"Comment", 4/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case STYLE_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, NULL, 1/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		// @rules

		case UNKNOWN_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@unknown", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case CHARSET_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@charset", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case IMPORT_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@import", 2/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case PAGE_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@page", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case FONT_FACE_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@fontface", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
			}
			break;

		case MEDIA_RULE:
			{
				DWORD newItem;
				m_treeCtl->InsertItem((DWORD)rule.p, parentItem, NULL, L"@media", 3/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

				CComQIPtr<ILCSSMediaRule> mediaRule = rule;

				CComPtr<ILCSSRuleList> ruleList;
				mediaRule->get_cssRules(&ruleList);

				PopulateRules(newItem, ruleList);	// Recurse
			}
			break;
		}
	}
}

void CCSSStyleSheetView::PopulateStyleSheets(DWORD parentItem, ILStyleSheetList* styleSheetList)
{
	long nstylesheets;
	styleSheetList->get_length(&nstylesheets);
	for (int i = 0; i < nstylesheets; i++)
	{
		CComPtr<ILCSSStyleSheet> styleSheet;
		m_styleSheetList->item(i, (ILStyleSheet**)&styleSheet);

		DWORD newItem;
		m_treeCtl->InsertItem((DWORD)styleSheet.p, parentItem, NULL, NULL, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

		styleSheet->addHandler(this);

		CComPtr<ILCSSRuleList> ruleList;
		styleSheet->get_cssRules(&ruleList);

		PopulateRules(newItem, ruleList);
	}
}

BOOL CCSSStyleSheetView::AnyLinkStyleChildren(ILDOMNode* parentNode)
{
	CComPtr<ILDOMNode> node;
	parentNode->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComQIPtr<ILLinkStyle> linkStyle = node;
			if (linkStyle)
			{
				return TRUE;
			}
			else
			{
				BOOL bAny = AnyLinkStyleChildren(element);
				if (bAny)
					return TRUE;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}

	return FALSE;
}

void CCSSStyleSheetView::PopulateStyleSheetElements(DWORD parentItem, ILDOMNode* parentNode)
{
	CComPtr<ILDOMNode> node;
	parentNode->get_firstChild(&node);

	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComQIPtr<ILLinkStyle> linkStyle = node;
			if (linkStyle)
			{
				CComPtr<ILStyleSheet> styleSheet;
				linkStyle->get_sheet(&styleSheet);

				if (styleSheet)
				{
					CComBSTR href;
					styleSheet->get_href(&href);

					CComBSTR tagName;
					element->get_tagName(&tagName);

					DWORD newItem;
					m_treeCtl->InsertItem((DWORD)styleSheet.p, parentItem, NULL, tagName, 0/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

					if (href.Length() == 0)	// Internal style sheet
					{
						CComQIPtr<ILCSSStyleSheet> cssStyleSheet = styleSheet;
						if (cssStyleSheet)
						{
							CComPtr<ILCSSRuleList> ruleList;
							cssStyleSheet->get_cssRules(&ruleList);

							PopulateRules(newItem, ruleList);
						}
					}
				}
			}
			else
			{
				BOOL bAny = AnyLinkStyleChildren(element);
				if (bAny)
				{
					CComBSTR tagName;
					element->get_tagName(&tagName);

					DWORD newItem;
					m_treeCtl->InsertItem((DWORD)element.p, parentItem, NULL, tagName, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

					PopulateStyleSheetElements(newItem, element);	// Recurse
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}
#endif

LRESULT CCSSStyleSheetView::OnCreate()
{
	m_treeElement->insertColumn(L"Name");
	/*
	m_treeElement->insertColumn(L"Media");
	m_treeElement->insertColumn(L"Url");
//	m_treeElement->insertColumn(L"Status");
//	m_treeElement->insertColumn(L"Size");
	m_treeElement->insertColumn(L"Source");
	*/

#if 0
#if 0
	IUnknown* p;

	CRect rc(0,0,0,0);
	m_axctl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axctl.AttachControl(m_ctl, &p);
#endif

	HRESULT hr;

	hr = IDispEventImpl<2, CCSSStyleSheetView, &DIID__ICSSStyleSheetViewCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_ctl);
	ASSERT(SUCCEEDED(hr));

	hr = IDispEventImpl<1, CCSSStyleSheetView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	ASSERT(SUCCEEDED(hr));

//	m_ctl->putref_styleSheet(m_styleSheet);

#if 0
	if (m_styleSheetList)
	{
		ASSERT(m_viewGroup);

		CComPtr<IEXMLDocument> eDocument;
		m_viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<ILDOMDocument> domDocument;
		eDocument->get_DOMDocument(&domDocument);

	//	CComPtr<ILDOMElement> documentElement;
	//	domDocument->get_documentElement(&documentElement);

		PopulateStyleSheetElements(NULL, domDocument);
		/*
		PopulateStyleSheets(NULL, m_styleSheetList);
		*/

		{

			CComQIPtr<ILDOMEventTarget> eventTarget = domDocument;
			eventTarget->addEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
			eventTarget->addEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
		}

		IDispEventImpl<1, CCSSStyleSheetView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup->GetUnknown());
	}
	else if (m_styleSheet)
	{
		CComPtr<ILCSSRuleList> ruleList;
		m_styleSheet->get_cssRules(&ruleList);

		PopulateRules(NULL, ruleList);
	}

//	m_treeCtl->put_hImageList((DWORD)m_hFileIcons);
#endif

	m_ctl->AddStyleSheet(NULL, m_viewGroup->m_pDocument->m_styleSheet);
#endif

	CComPtr<ILCSSRuleList> ruleList;
	m_viewGroup->m_pDocument->m_styleSheet->get_cssRules(&ruleList);

	CComPtr<ILXUITreeChildrenElement> treeChildrenElement;
	m_treeElement->get_treeChildren(&treeChildrenElement);

	PopulateRules(treeChildrenElement, ruleList);

	return 0;
}

LRESULT CCSSStyleSheetView::OnDestroy()
{
#if 0
	// Remove handlers on stylesheets
	{
		DWORD root;
		m_treeCtl->GetRootItem(&root);

		DWORD item;
		m_treeCtl->GetFirstChildItem(root, &item);
		while (item)
		{
			DWORD itemdata;
			m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

			CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
			if (styleSheet)
			{
				styleSheet->removeHandler(this);
			}

			m_treeCtl->GetNextSiblingItem(item, &item);
		}
	}

	{
		CComPtr<IEXMLDocument> eDocument;
		m_viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<ILDOMDocument> domDocument;
		eDocument->get_DOMDocument(&domDocument);

		CComQIPtr<ILDOMEventTarget> eventTarget = domDocument;
		eventTarget->removeEventListener(L"DOMNodeInserted", (ILDOMEventListener*)this, VARIANT_TRUE);
		eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", (ILDOMEventListener*)this, VARIANT_TRUE);
	}
#endif

	HRESULT hr;

	/*
	hr = IDispEventImpl<2, CCSSStyleSheetView, &DIID__ICSSStyleSheetViewCtlEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_ctl);
	ASSERT(SUCCEEDED(hr));
	*/

	hr = IDispEventImpl<1, CCSSStyleSheetView, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup->GetUnknown());
	ASSERT(SUCCEEDED(hr));

	return 0;
}

STDMETHODIMP CCSSStyleSheetView::GetItemText(ILCSSRule* itemdata, LONG column, BSTR * pVal)
{
	*pVal = NULL;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
//	CSiteItem* pNode = (CSiteItem*)itemdata;

	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSStyleRule> styleRule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSMediaRule> mediaRule = (IUnknown*)itemdata;
	CComQIPtr<ILCSSImportRule> importRule = (IUnknown*)itemdata;

	switch (column)
	{
	case PANE_NAME:
		/*
		if (styleSheet)
		{
			CComPtr<ILDOMNode> ownerNode;
			styleSheet->get_ownerNode(&ownerNode);

			if (ownerNode)
			{
				CComBSTR tagName;
				ownerNode->get_nodeName(&tagName);
				if (!wcscmp(tagName, L"style"))
				{
					*pVal = SysAllocString(L"Internal style");
				}
				else
				{
					BSTR bhref;
					styleSheet->get_href(&bhref);

					*pVal = bhref;
				}
			}
			else
			{
				BSTR bhref;
				styleSheet->get_href(&bhref);

				*pVal = bhref;
			}
		}
		else
			*/
			if (styleRule)
		{
			styleRule->get_selectorText(pVal);
		}
		break;

	case PANE_MEDIA:
		{
			if (styleSheet)
			{
				CComPtr<ILMediaList> media;
				styleSheet->get_media(&media);

				media->get_mediaText(pVal);
			}
			else if (mediaRule)
			{
				CComPtr<ILMediaList> media;
				mediaRule->get_media(&media);

				media->get_mediaText(pVal);
			}
		}
		break;

	case PANE_URL:
		{
			if (styleSheet)
			{
				styleSheet->get_href(pVal);
			}
			else if (importRule)
			{
				importRule->get_href(pVal);
			}
		}
		break;

	case PANE_SOURCE:
		{
			if (styleRule)
			{
				CComPtr<ILCSSStyleDeclaration> decl;
				styleRule->get_style(&decl);
				if (decl)
				{
					decl->get_cssText(pVal);
				}
			}
			else if (mediaRule)
			{
				*pVal = NULL;	// No text
			}
			else if (importRule)
			{
				*pVal = NULL;	// No text
			}
			else if (rule)
			{
				rule->get_cssText(pVal);
			}
		}
		break;
	}

	return S_OK;
}

void CCSSStyleSheetView::InsertRule(ILXUITreeChildrenElement* treeChildren, ILXUIElement* beforeItem, ILCSSRule* rule, ILXUITreeItemElement* *pVal)
{
	CComPtr<ILXUITreeItemElement> newItem;

	LCSSType type;
	rule->get_type(&type);

//	CComPtr<ILXUIDocument> document;
//	CComPtr<ILDOMElement> element;
//	document->createElementNS(L"http://www.lerstad.com/2004/lxui", &element);

	m_treeElement->createItem(&newItem);

	for (int i = 0; i < 1; i++)
	{
		CComBSTR text;
		GetItemText(rule, i, &text);

		newItem->setColumnText(i, _variant_t(text));
	}

#if 0
	switch (type)
	{
	case COMMENT_RULE:	// comment (this is an Extension to the CSS OM)
		{
		//	m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"Comment", 4/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case STYLE_RULE:
		{
			CComQIPtr<ILCSSStyleRule> styleRule = rule;
	
			CComBSTR text;
			styleRule->get_selectorText(&text);

			newItem->setColumnText(0, _variant_t(text));

//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, NULL, 1/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	// @rules

	case UNKNOWN_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@unknown", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case CHARSET_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@charset", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case IMPORT_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@import", 2/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case PAGE_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@page", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case FONT_FACE_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@font-face", 3/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case COLOR_PROFILE_RULE:
		{
//			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@color-profile", 5/*pNewItem->m_iIcon*/, 0/*pNewItem->m_cChildren*/, &newItem);
		}
		break;

	case MEDIA_RULE:
		{
#if 0
			m_treeCtl->InsertItem((DWORD)rule, parentItem, beforeItem, L"@media", 3/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

			CComQIPtr<ILCSSMediaRule> mediaRule = rule;

			CComPtr<ILCSSRuleList> ruleList;
			mediaRule->get_cssRules(&ruleList);

			PopulateRules(newItem, ruleList);	// Recurse
#endif
		}
		break;

	default:
		ASSERT(0);
	}
#endif

#if 0
	rule->setUserData(m_userDataKey, newItem, NULL);
#endif

	treeChildren->appendItem(newItem);

	*pVal = newItem;
	(*pVal)->AddRef();
}

void CCSSStyleSheetView::PopulateRules(ILXUITreeChildrenElement* parentItem, ILCSSRuleList* ruleList)
{
	long nrules;
	ruleList->get_length(&nrules);

	for (int i = 0; i < nrules; i++)
	{
		CComPtr<ILCSSRule> rule;
		ruleList->item(i, &rule);

		CComPtr<ILXUITreeItemElement> newItem;
		InsertRule(parentItem, NULL, rule, &newItem);
	}
}

#if 0
LRESULT CCSSStyleSheetView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axctl.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}
#endif

void __stdcall CCSSStyleSheetView::OnRuleStateChange(ILCSSRule* rule, long oldState, long newState)
{
	if ((oldState & 1) != (newState & 1))	// Toggle activate rule
	{
		m_bSelectingElement++;

		CComPtr<IESelectedRule> selectedRule;
		m_viewGroup->ActivateElement(rule, MK_SHIFT, &selectedRule);

		m_bSelectingElement--;
	}
}

void __stdcall CCSSStyleSheetView::OnViewGroupSelectionChanged()
{
	if (!m_bSelectingElement)
	{
		if (m_viewGroup->m_pActiveElement)
		{
			CComPtr<ILCSSRule> rule;
			m_viewGroup->m_pActiveElement->get_rule(&rule);

#if 0
			m_ctl->SelectRule(CComVariant(rule));
#endif
		}
		else
		{
#if 0
			m_ctl->SelectRule(CComVariant(NULL));
#endif
		}
	}
}

#if 0
STDMETHODIMP CCSSStyleSheetView::handleCSSEvent(ILCSSStyleSheet* styleSheet, long type)
{
	DWORD root;
	m_treeCtl->GetRootItem(&root);

	DWORD selecteditem;
	m_treeCtl->GetSelectedItem(&selecteditem);

	CComQIPtr<ILCSSRule> cssrule;
	if (selecteditem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(selecteditem, &itemdata, NULL, NULL);

		cssrule = (IUnknown*)itemdata;
	}

	DWORD item;
	m_treeCtl->GetFirstChildItem(root, &item);
	while (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet2 = (IUnknown*)itemdata;
		if (styleSheet2 == styleSheet)
		{
			m_treeCtl->ResetContent(item);

			CComPtr<ILCSSRuleList> ruleList;
			styleSheet->get_cssRules(&ruleList);

			PopulateRules(item, ruleList);

			DWORD parentitem = item;
			if (cssrule)	// Previously selected rule
			{
				// Search through and see if we can't reselect it
				DWORD item;
				m_treeCtl->GetFirstChildItem(parentitem, &item);
				while (item)
				{
					DWORD itemdata;
					m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

					CComQIPtr<ILCSSRule> cssrule2 = (IUnknown*)itemdata;
					if (cssrule2 == cssrule)
					{
						m_treeCtl->SetSelectedItem(item);
						break;
					}

					m_treeCtl->GetNextSiblingItem(item, &item);
				}
			}
			break;
		}

		m_treeCtl->GetNextSiblingItem(item, &item);
	}

	return S_OK;
}

// ILDOMEventListener
STDMETHODIMP CCSSStyleSheetView::handleEvent(ILDOMEvent* evt)
{
	CComBSTR type;
	evt->get_type(&type);

//	BOOL bUpdate = FALSE;

	if (!wcscmp(type, L"DOMNodeInserted"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			linkStyle->get_sheet((ILStyleSheet**)&styleSheet);

			styleSheet->addHandler(this);

			DWORD newItem;
			m_treeCtl->InsertItem((DWORD)styleSheet.p, NULL/*parentItem*/, NULL, NULL, 0/*pNewItem->m_iIcon*/, 1/*pNewItem->m_cChildren*/, &newItem);

			CComPtr<ILCSSRuleList> ruleList;
			styleSheet->get_cssRules(&ruleList);

			PopulateRules(newItem, ruleList);
		}
	}
	else if (!wcscmp(type, L"DOMNodeRemovedFromDocument"))
	{
		CComQIPtr<ILDOMMutationEvent> mut = evt;

		CComPtr<ILDOMEventTarget> target;
		mut->get_target(&target);
		CComQIPtr<ILDOMNode> node = target;

		CComQIPtr<ILLinkStyle> linkStyle = node;
		if (linkStyle)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			linkStyle->get_sheet((ILStyleSheet**)&styleSheet);

			DWORD root;
			m_treeCtl->GetRootItem(&root);

			DWORD item;
			m_treeCtl->GetFirstChildItem(root, &item);
			while (item)
			{
				DWORD itemdata;
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

				CComQIPtr<ILCSSStyleSheet> styleSheet2 = (IUnknown*)itemdata;
				if (styleSheet2 == styleSheet)
				{
					m_treeCtl->DeleteItem(item);
					break;
				}

				m_treeCtl->GetNextSiblingItem(item, &item);
			}
		}

		/*
		for (int i = 0; i < m_listView.m_items.GetSize(); i++)
		{
			if (m_listView.m_items[i]->m_element == node)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = m_listView.m_items[i]->m_element;
				eventTarget->removeEventListener(L"DOMNodeRemovedFromDocument", this, VARIANT_FALSE);

				m_listView.DeleteItem(i);
				break;
			}
		}
*/
	}

	return S_OK;
}
#endif

#if 0
void __stdcall CCSSStyleSheetView::OnItemClick(DWORD item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComPtr<ILDOMRange> range;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	if (styleSheet)
	{
		CComPtr<ILDOMNode> ownerNode;
		styleSheet->get_ownerNode(&ownerNode);
		if (ownerNode)
		{
			CComPtr<ILDOMDocument> ownerDocument;
			ownerNode->get_ownerDocument(&ownerDocument);

			CComQIPtr<ILDOMDocumentRange> documentRange = ownerDocument;
			if (documentRange)
			{
				documentRange->createRange(&range);
				if (range)
				{
					range->selectNode(ownerNode);
				}
			}

		// hmm... either the following should create the range or the
		// above should do the following (or not???)
			CComPtr<IEXMLDocument> eDocument;
			m_viewGroup->get_eXMLDocument(&eDocument);

			CComPtr<IEElement> eElement;
			eDocument->GetEElementFromDOMElement(CComQIPtr<ILDOMElement>(ownerNode), &eElement);
			if (eElement)
			{
				m_viewGroup->ActivateElement(eElement, 0, NULL);
			}
		}
	}
	else if (rule)
	{
		long startOffset;
		rule->getTextOffset(0, &startOffset);

		long endOffset;
		rule->getTextOffset(3, &endOffset);

		CComPtr<ILCSSStyleSheet> styleSheet;
		rule->get_parentStyleSheet(&styleSheet);
		ASSERT(styleSheet);

		CComPtr<ILDOMNode> ownerNode;
		styleSheet->get_ownerNode(&ownerNode);
		if (ownerNode)
		{
			CComPtr<ILDOMNode> firstChild;
			ownerNode->get_firstChild(&firstChild);

			CComPtr<ILDOMDocument> ownerDocument;
			ownerNode->get_ownerDocument(&ownerDocument);

			CComQIPtr<ILDOMCharacterData> charData = firstChild;
			if (charData)
			{
				CComQIPtr<ILDOMDocumentRange> documentRange = ownerDocument;
				if (documentRange)
				{
					documentRange->createRange(&range);
					if (range)
					{
						range->setStart(charData, startOffset);
						range->setEnd(charData, endOffset);
					}
				}
			}
		}
	}

	if (range)
	{
		CEXMLViewGroup* pViewGroup = m_viewGroup;

		for (int i = 0; i < pViewGroup->m_views.GetSize(); i++)
		{
			CComQIPtr<ISourceView> sourceView = pViewGroup->m_views[i];
			if (sourceView)
			{
				((CSourceView*)sourceView.p)->SetRange(range);
			}
		}
	}
}
#endif

#include "ECSSDocument.h"

#if 0
void __stdcall CCSSStyleSheetView::OnItemDblClick(DWORD item)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

	CComPtr<ILCSSStyleSheet> openStyleSheet;

	CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
	CComQIPtr<ILCSSRule> rule = (IUnknown*)itemdata;
	if (styleSheet)
	{
		CComBSTR href;
		styleSheet->get_href(&href);
		if (href.Length())
		{
			openStyleSheet = styleSheet;
		}
	}
	else if (rule)
	{
		CComQIPtr<ILCSSImportRule> importRule = rule;
		if (importRule)
		{
			importRule->get_styleSheet(&openStyleSheet);
		}
	}

	if (openStyleSheet)
	{
		CComObject<CECSSDocument>* pCSSDocument;
		CComObject<CECSSDocument>::CreateInstance(&pCSSDocument);
		if (pCSSDocument)
		{
			pCSSDocument->m_styleSheet = openStyleSheet;

			BSTR cssText;
			openStyleSheet->get_cssText(&cssText);
			pCSSDocument->m_textData->put_data(cssText);

#if 0
			AddDocument(pCSSDocument->GetUnknown(), NULL);
#endif
		}
	}
}

void __stdcall CCSSStyleSheetView::OnEndLabelEdit(long item, BSTR text)
{
	DWORD itemdata;
	m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
	if (itemdata)
	{
		CComQIPtr<ILCSSStyleRule> styleRule = (IUnknown*)itemdata;
		if (styleRule)
		{
			styleRule->put_selectorText(text);
		}
	}
	else
	{
		if (text && wcslen(text) > 0)
		{
			DWORD parentitem;
			m_treeCtl->GetParentItem(item, &parentitem);
			if (parentitem)
			{
				DWORD parentitemdata;
				m_treeCtl->GetItemInfo(parentitem, &parentitemdata, NULL, NULL);

				CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)parentitemdata;
				if (styleSheet)
				{
					CComPtr<ILCSSRuleList> cssRules;
					styleSheet->get_cssRules(&cssRules);

					long length;
					cssRules->get_length(&length);

					_bstr_t rule = text + _bstr_t(L" {}");

					long index;
					styleSheet->insertRule(rule, length, &index);

					CComPtr<ILCSSRule> cssrule;
					cssRules->item(index, &cssrule);

				// Select the newly inserted rule in the treeview
				// insertRule() will rebuild the parent list, so we need to do this
					{
						DWORD item;
						m_treeCtl->GetFirstChildItem(parentitem, &item);
						while (item)
						{
							DWORD itemdata;
							m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

							CComQIPtr<ILCSSRule> cssrule2 = (IUnknown*)itemdata;
							if (cssrule2 == cssrule)
							{
								m_treeCtl->SetSelectedItem(item);
								OnItemClick(item);	// hm.. maybe this should be called by the above
								break;
							}

							m_treeCtl->GetNextSiblingItem(item, &item);
						}
					}
				}
			}
		}
		else
		{
			m_treeCtl->DeleteItem(item);
		}
	}
}
#endif

#if 0
// ICommandTarget
STDMETHODIMP CCSSStyleSheetView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try viewgroup
	CComQIPtr<ICommandTarget> target = m_viewGroup;
	if (target)
	{
		target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
		if (*bHandled) return S_OK;
	}

	return S_OK;
}
#endif

BEGIN_CMD_MAP(CCSSStyleSheetView)
// Edit
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)
	CMD_UPDATE(ID_EDIT_CLEAR, OnEditClearUpdate)

// CSS
	CMD_HANDLER(ID_CSS_NEWIMPORTRULE, OnNewImportRule)
	CMD_UPDATE(ID_CSS_NEWIMPORTRULE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_NEWCLASSSTYLE, OnNewStyleRule)
	CMD_UPDATE(ID_CSS_NEWCLASSSTYLE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_NEWMEDIARULE, OnNewMediaRule)
	CMD_UPDATE(ID_CSS_NEWMEDIARULE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_NEWCOLORPROFILE, OnNewColorProfile)
	CMD_UPDATE(ID_CSS_NEWCOLORPROFILE, OnNewRuleUpdate)

	CMD_HANDLER(ID_CSS_DISABLEDSTYLESHEET, OnDisabledStylesheet)
	CMD_UPDATE(ID_CSS_DISABLEDSTYLESHEET, OnDisabledStylesheetUpdate)
END_CMD_MAP()

LRESULT CCSSStyleSheetView::OnDisabledStylesheet(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	DWORD activeitem;
	m_ctl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(activeitem, &itemdata, NULL, NULL);

		CComQIPtr<ILStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet)
		{
			VARIANT_BOOL disabled;
			styleSheet->get_disabled(&disabled);

		// Toggle
			styleSheet->put_disabled(~disabled);
		}
	}
#endif

	return 0;
}

void CCSSStyleSheetView::OnDisabledStylesheetUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;
	BOOL bCheck = FALSE;

	DWORD activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(activeitem, &itemdata, NULL, NULL);

		CComQIPtr<ILStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet)
		{
			VARIANT_BOOL disabled;
			styleSheet->get_disabled(&disabled);

			bCheck = disabled;
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
	pCmdUI->SetCheck(bCheck);
#endif
}

LRESULT CCSSStyleSheetView::OnEditClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_ctl->DeleteSelection();
#endif
	return 0;
}

void CCSSStyleSheetView::OnEditClearUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;

	DWORD activeitem;
	m_treeCtl->GetSelectedItem(&activeitem);

	if (activeitem)
	{
		bEnable = TRUE;
	}

	pCmdUI->Enable(bEnable);
#endif
	pCmdUI->Enable(TRUE);
}

LRESULT CCSSStyleSheetView::OnNewStyleRule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILCSSRule> rule;
	m_viewGroup->m_pActiveElement->get_rule(&rule);

	CComPtr<ILCSSRuleList> ruleList;
	GetParentRuleList(rule, &ruleList);

	int index = GetRuleIndex(ruleList, rule);

	_bstr_t cssRule = L"{}\n";// + _bstr_t(sbuffer);

	m_viewGroup->m_pDocument->m_styleSheet->insertRule(cssRule, index, NULL);

#if 0
	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			DWORD newItem;
			m_treeCtl->InsertItem((DWORD)NULL, item, NULL, NULL, 1/*pNewItem->m_iIcon*/, -1/*pNewItem->m_cChildren*/, &newItem);

			CComPtr<IUIEdit> edit;
			m_treeCtl->EditLabel(newItem, &edit);
		}
	}
#endif

	return 0;
}

LRESULT CCSSStyleSheetView::OnNewImportRule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILCSSRule> rule;
	m_viewGroup->m_pActiveElement->get_rule(&rule);

	CComPtr<ILCSSRuleList> ruleList;
	GetParentRuleList(rule, &ruleList);

	int index = GetRuleIndex(ruleList, rule);

	_bstr_t cssRule = L"@import url()\n";// + _bstr_t(sbuffer);

	m_viewGroup->m_pDocument->m_styleSheet->insertRule(cssRule, index, NULL);


#if 0
	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
														"CSS Stylesheets (*.css)\0*.css\0"
														);

			TCHAR sbuffer[4096];
			strcpy(sbuffer, "");	// Initial filename
			
			TCHAR curdir[MAX_PATH];
			GetCurrentDirectory(sizeof(curdir), curdir);

			OPENFILENAME	ofn = {0};
			ofn.lStructSize = sizeof(OPENFILENAME);
			ASSERT(0);
			ofn.hwndOwner = NULL;//GetMainHwnd();
			ofn.hInstance = _Module.m_hInst;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrFile = sbuffer;
			ofn.nMaxFile = sizeof(sbuffer);
			ofn.lpstrInitialDir = curdir;
			ofn.lpstrFilter = FilesFilter;
			ofn.nFilterIndex = 2;
			
			if (GetOpenFileName(&ofn))
			{
				_bstr_t rule = L"@import" + _bstr_t(sbuffer);

			//	insertRule(in DOMString rule, index);
			}
		}
	}
#endif

	return 0;
}

LRESULT CCSSStyleSheetView::OnNewMediaRule(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILCSSRule> rule;
	m_viewGroup->m_pActiveElement->get_rule(&rule);

	CComPtr<ILCSSRuleList> ruleList;
	GetParentRuleList(rule, &ruleList);

	int index = GetRuleIndex(ruleList, rule);

	_bstr_t cssRule = L"@media {}\n";

	m_viewGroup->m_pDocument->m_styleSheet->insertRule(cssRule, index, NULL);

	return 0;
}

LRESULT CCSSStyleSheetView::OnNewColorProfile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CComPtr<ILCSSRule> rule;
	m_viewGroup->m_pActiveElement->get_rule(&rule);

	CComPtr<ILCSSRuleList> ruleList;
	GetParentRuleList(rule, &ruleList);

	int index = GetRuleIndex(ruleList, rule);

	_bstr_t cssRule = L"@color-profile {}\n";

	m_viewGroup->m_pDocument->m_styleSheet->insertRule(cssRule, index, NULL);

	return 0;
}

void CCSSStyleSheetView::OnNewRuleUpdate(long iid, IUICmdUpdate* pCmdUI)
{
#if 0
	BOOL bEnable = FALSE;

	DWORD item;
	m_treeCtl->GetSelectedItem(&item);
	if (item)
	{
		DWORD itemdata;
		m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);

		CComQIPtr<ILCSSStyleSheet> styleSheet = (IUnknown*)itemdata;
		if (styleSheet == NULL)	// Try parent item
		{
			m_treeCtl->GetParentItem(item, &item);
			if (item)
			{
				m_treeCtl->GetItemInfo(item, &itemdata, NULL, NULL);
				styleSheet = (IUnknown*)itemdata;
			}
		}

		if (styleSheet)
		{
			bEnable = TRUE;
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

#endif