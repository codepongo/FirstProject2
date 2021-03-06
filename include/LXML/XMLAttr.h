#ifndef __XMLATTR_H
#define __XMLATTR_H

#include "ValueType.h"

namespace System
{
namespace Web
{

//class Attr;
//class Element;

// Base class for XML attributes and CSS properties ?
class CATAttr : public Object
{
public:
	virtual CValueType* GetAnimVal() = 0;	// ??
};

class WEBEXT CATXMLAttr :
	public CATAttr,
	public CAttributeType	// ??
//	public ILSMILXMLAttr
{
public:
	CTOR CATXMLAttr()
	{
		m_reentrance = 0;
		m_pAttr = nullptr;
		m_specified = false;

		m_namespaceURI = nullptr;
		m_attributeName = nullptr;
		m_defaultValue = nullptr;
	}

	Element* m_animationTarget;
//	CAnimationTarget* m_animationTarget;

	long m_reentrance;

	bool m_specified;

	Attr* m_pAttr;

	String m_namespaceURI;
	String m_attributeName;

	String m_defaultValue;

	String get_name()
	{
		return m_attributeName;
	}

	String get_namespaceURI()
	{
		return m_namespaceURI;
	}

	virtual CValueType* GetBaseVal() = 0;	// ??

	void OnBaseValChanged();

	// Set element attribute from baseVal
	void SetAttribute(Element* element);

	// Set values of baseVal/animVal from attribute string
	void SetValues(Element* element);
};

// Non-animatable XML Attribute
template<class Type> class CXMLAttr2T :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public CATXMLAttr,
	public ISingleObjectListener
{
public:
	CTOR CXMLAttr2T()
	{
		m_animationTarget = NULL;
		m_value->m_value->m_pListener = this;
	}

	Type m_value;

	virtual CValueType* NewVal()
	{
		return NULL;
	}

	virtual CValueType* GetBaseVal()
	{
		return m_value;
	}

	virtual CValueType* GetAnimVal()
	{
		return NULL;
	}

	virtual void OnChanged(CSingleObject* pObject)
	{
		OnBaseValChanged();
	}
};

template<class T>
CATXMLAttr* NewNXMLAttr(T** pP, StringIn namespaceURI, StringIn attributeName, StringIn defaultValue = NULL)
{
	(*pP) = new T;
	(*pP)->m_namespaceURI = namespaceURI;
	(*pP)->m_attributeName = attributeName;
	(*pP)->m_defaultValue = defaultValue;

	return (*pP);
}

template <class Type> class CAnimatedClass :
	public ISingleObjectListener
{
public:
	Type* m_baseVal;
	Type* m_animVal;

	CTOR CAnimatedClass()
	{
		m_baseVal = new Type;
		m_animVal = new Type;
		m_baseVal->m_value->m_pListener = this;
	}

	~CAnimatedClass()
	{
		m_baseVal->m_value->m_pListener = NULL;
		delete m_baseVal;
		delete m_animVal;
	}

	CATXMLAttr* m_pAttr;

	/*
	CAnimatedClass* operator -> ()
	{
		return this;
	}
	*/

	virtual void OnChanged(CSingleObject* pObject)
	{
		m_pAttr->OnBaseValChanged();
	//	if (m_pListener) m_pListener->OnValueTypeChange(this);
	}
};

// Animatable XML Attribute
template<class AnimatedType, class Type> class CATXMLAttr2T :
	public CATXMLAttr
{
public:
	CTOR CATXMLAttr2T()
	{
		m_animationTarget = NULL;

		ASSERT(0);
		//m_animated->m_pAttr = this;
	}

	AnimatedType m_animated;

	/*
	operator AnimatedType* ()
	{
		return &m_animated;
	}
	*/

	virtual CValueType* NewVal()
	{
		return new Type;
	//	CComObject<Type>::CreateInstance(&value);
	//	value->AddRef();
	//	return value;

		//return (new Type);
	}

	virtual CValueType* GetBaseVal()
	{
		ASSERT(0);
		return NULL;
		//return m_animated->m_baseVal;
	}

	virtual CValueType* GetAnimVal()
	{
		ASSERT(0);
		return NULL;
	//	return m_animated->m_animVal;
	}

};

template<class T>
CATXMLAttr* NewXMLAttr(T** pP, StringIn namespaceURI, StringIn attributeName, StringIn defaultValue = NULL)
{
	ASSERT(0);

	/*
	(*pP) = new T;
	(*pP)->m_namespaceURI = namespaceURI;
	(*pP)->m_attributeName = attributeName;
	(*pP)->m_defaultValue = defaultValue;
*/
	return (*pP);
}

}	// Web
}

#endif
