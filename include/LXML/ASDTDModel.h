#ifndef __ASDTDMODEL_H_
#define __ASDTDMODEL_H_

//#include "resource.h"       // main symbols

#include "ASDTDNamedObjectMap.h"
#include "ASDTDObjectImpl.h"

namespace System
{
namespace Web
{

class DTDDocument;
class CASDTDContentModel;
class CCPChoiceSeq;

class WEBEXT CDTDASObjectList : public Object,
	public IASObjectList
{
public:
	~CDTDASObjectList()
	{
		for (size_t i = 0; i < m_items.GetSize(); i++)
		{
//			m_items[i]->Release();
		}
	}

	vector<IASObject*> m_items;

	size_t get_length() const
	{
		return m_items.GetSize();
	}

	IASObject* item(size_t index) const
	{
		if (/*index >= 0 && */ index < m_items.GetSize())
		{
			return m_items[index];
		}
		else
			return NULL;
	}
};

class WEBEXT ASDTDModel : public IASModel//CASDTDObject
{
public:
	CTOR ASDTDModel();
	~ASDTDModel();

	String m_url;

	CASDTDContentModel* BuildCM(CCPChoiceSeq* cp);

	IDOMErrorHandler* m_errorHandler;
#if 0
	CComQIPtr<ITextData, &IID_ITextData> m_textDoc;
#endif

	CDTDASNamedObjectMap* m_entityDeclarations;
	CDTDASNamedObjectMap* m_elementDeclarations;
	CDTDASNamedObjectMap* m_attributeDeclarations;

	void BuildFromDTDDocument(DTDDocument* dtd);

#if 0
	STDMETHOD(FireModelChanged)();
	STDMETHOD(saveAsText)(/*[out,retval]*/ BSTR* pVal);
	STDMETHOD(parse)(/*[out,retval]*/ bool* pSuccess);
	STDMETHOD(get_sourceTextDoc)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(set_sourceTextDoc)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(get_errorHandler)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(set_errorHandler)(/*[in]*/ IUnknown* newVal);
	STDMETHOD(load)(/*[in]*/ BSTR pathName, /*[out,retval]*/ bool* pSuccess);
#endif

// IASModel
	IASNamedObjectMap* get_contentModelDeclarations();
	IASNamedObjectMap* get_entityDeclarations();
	IASNamedObjectMap* get_notationDeclarations();
	IASNamedObjectMap* get_attributeDeclarations();
	IASNamedObjectMap* get_elementDeclarations();
	bool get_isNamespaceAware() const;

#if 0
	STDMETHOD(createASContentModel)(/*[in]*/ unsigned long minOccurs, /*[in]*/ unsigned long maxOccurs, /*[in]*/ ASContentModelTypeOp Operator, /*[out,retval]*/ IASContentModel** pVal);
	STDMETHOD(createASEntityDeclaration)(/*[in]*/ BSTR name, /*[out,retval]*/ IASEntityDeclaration** pVal);
	STDMETHOD(createASNotationDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[in]*/ BSTR systemId, /*[in]*/ BSTR publicId, /*[out,retval]*/ IASNotationDeclaration** pVal);
	STDMETHOD(createASAttributeDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASAttributeDeclaration** pVal);
	STDMETHOD(createASElementDeclaration)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR name, /*[out,retval]*/ IASElementDeclaration** pVal);
	STDMETHOD(getASModels)(/*[out,retval]*/ IASObjectList* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;//m_asModels;
		//(*pVal)->AddRef();
		return S_OK;
	}
#endif

// IASObject
	ASObjectType get_asNodeType() const
	{
		return AS_MODEL;
	}

	void set_ownerASModel(/*[in]*/ IASModel* newVal)
	{
		VERIFY(0);
	}

	IASObject* cloneASObject(bool deep) const
	{
		ASSERT(0);
		return nullptr;
	}

#if 0
	StringW get_localName()
	{
		THROW(-1);
		return NULL;
	}
	
	STDMETHOD(set_localName)(const StringW& newVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return E_FAIL;
	}
	
	STDMETHOD(set_prefix)(/*[in]*/ BSTR newVal)
	{
		return E_FAIL;
	}
#endif

	String get_nodeName()
	{
		THROW(-1);
		return nullptr;
	}
	
	void set_nodeName(StringIn newVal)
	{
		VERIFY(0);
	}
	Element* GetElement()
	{
		return nullptr;
	}
	void SetElement(/*[in]*/ Element* newVal)
	{
	}
	
// IDOMErrorHandler
	ErrorCode warn(IDOMLocator * where, StringIn how, StringIn why)
	{
		return Success;
	}
	ErrorCode fatalError(IDOMLocator * where, StringIn how, StringIn why)
	{
		//MessageBox(NULL, _bstr_t(why), "DTD", MB_OK);
		THROW(new Exception(why));
		return Success;
	}
	ErrorCode error(IDOMLocator * where, StringIn how, StringIn why)
	{
		return Success;
	}
};

}	// Web
}

#endif //__ASDTDMODEL_H_
