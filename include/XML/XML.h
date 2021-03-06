#ifndef XMLData_h
#define XMLData_h

#ifdef __LERSTAD__
#import "LFC/LFC.h"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "XPath/XPath.h"
#else
#include "XPath/XPath.h"
#endif

#ifndef XMLEXT
#define XMLEXT DECLSPEC_DLLIMPORT
#endif

#include "XmlData.h"
#include "XmlSchema.h"
#include "SAXParser.h"

namespace System
{

interface IXmlWriter
{
	virtual void BeginDocument() abstract;
	virtual void BeginElement(StringIn name) abstract;
	virtual void EndElement() abstract;
	virtual void Attribute(StringIn name, StringIn value) abstract;
};

namespace XmlData
{

class XMLEXT XmlWriter : public Object, public IXmlWriter
{
public:

	virtual void BeginDocument() override
	{
		m_document = new Document;
		m_parent = m_document;
	}

	virtual void BeginElement(StringIn name) override
	{
		Element* element = m_document->createElementNS(nullptr, name);

		m_element = element;
		m_parent->appendChild(element);
		m_parent = element;
	}

	virtual void EndElement() override
	{
		ASSERT(m_parent);
		m_parent = m_parent->get_parentNode();
		m_element = nullptr;	// Can no longer access it, not even add attributes
	}

	virtual void Attribute(StringIn name, StringIn value) override
	{
	//	Attr* attr = m_document->createAttributeNS(NULL, name, value);

		m_element->setAttribute(name, value);
	}

	Document* m_document;
	Element* m_element;
	Node* m_parent;
};

}	// XmlData
}	// System

#endif // XMLData_h
