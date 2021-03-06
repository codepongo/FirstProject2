#include "stdafx.h"
#include "XML.h"

#include "XmlData.h"
#include "XmlParser.h"

namespace System
{
namespace XmlData
{

///////////////////////
// Node

unsigned int Node::getPosition()
{
	return m_position;
}

XDM::IData* Node::getRoot()
{
	return get_ownerDocument();
}

String Node::getAttributeName(unsigned int index)
{
	NamedNodeMap* attributes = get_attributes();
	if (attributes)
	{
		return attributes->item(index)->get_nodeName();
	}
	return nullptr;
}

Variant Node::getAttributeValue(unsigned int index)
{
	NamedNodeMap* attributes = get_attributes();
	if (attributes)
	{
		return attributes->item(index);
	}
	return Variant();
}

String Node::getAttributeNamespaceURI(unsigned int index)
{
	NamedNodeMap* attributes = get_attributes();
	if (attributes)
	{
		return attributes->item(index)->get_namespaceURI();
	}
	return nullptr;
}

System::Type* Node::getAttributeType(unsigned int index)
{
	ASSERT(0);
	return nullptr;
	/*
	NamedNodeMap* attributes = get_attributes();
	if (attributes)
	{
		return attributes->item(index)->get_namespaceURI();
	}
	return System::Variant();
	*/
}

unsigned int Node::getChildCount()
{
	NodeList* childNodes = get_childNodes();
	if (childNodes)
		return childNodes->get_length();
	else
		return 0;
}

bool Node::IsChildText(unsigned int index)
{
	return get_childNodes()->item(index)->get_nodeType() == NODE_TEXT;
}

String Node::getChildName(unsigned int index)
{
	return get_childNodes()->item(index)->get_nodeName();
}

String Node::getChildNamespaceURI(unsigned int index)
{
	return get_childNodes()->item(index)->get_namespaceURI();
}

System::Type* Node::getChildType(unsigned int index)
{
	ASSERT(0);
	return get_childNodes()->item(index)->GetType();
}

XDM::IData* Node::getChildElement(unsigned int index)
{
	return get_childNodes()->item(index);
}

String Node::getChildText(unsigned int index)
{
	return get_childNodes()->item(index)->get_textContent();
}

NodeList* Node::get_childNodes()
{
	return m_childNodes;
}

NamedNodeMap* Node::get_attributes()
{
	return NULL;
}

Node* Node::insertNode(Node* newChild, Node* pBefore)
{
	Node* pPrevParent = newChild->get_parentNode();
	if (pPrevParent)
	{
		ASSERT(0);
		//pPrevParent->removeChild(newChild);
	}

	Node* pAfter;

	if (pBefore)
		pAfter = pBefore->get_previousSibling();
	else
		pAfter = m_lastChild;

	newChild->m_nextSibling = pBefore;
	newChild->m_previousSibling = pAfter;

	if (pAfter == NULL)
		m_firstChild = newChild;
	else
		pAfter->m_nextSibling = newChild;

	if (pBefore == NULL)
		m_lastChild = newChild;
	else
		pBefore->m_previousSibling = newChild;

	if (pBefore)
	{
		for (uint i = 0; i < m_childNodes->m_items.GetSize(); i++)
		{
			if (m_childNodes->m_items[i] == pBefore)
			{
				m_childNodes->m_items.InsertAt(i, newChild);
			//	m_childNodes->m_items.insert(&m_childNodes->m_items[i], newChild);
				break;
			}
		}
	}
	else
	{
		m_childNodes->m_items.Add(newChild);
	}

// Set new child node's parent to this element
	newChild->m_parentNode = this;

	return newChild;
}

///////////////////////////////////////////////
// Element

Element::Element()
{
	m_namespaceURI = nullptr;
	m_localName = nullptr;
	m_attributes = nullptr;

	m_childNodes = new NodeList;
}

Element::Element(NamedNodeMap* attributes) : m_attributes(attributes)
{
	m_namespaceURI = nullptr;
	m_localName = nullptr;

	m_childNodes = new NodeList;
}

Element::~Element()
{
	delete m_childNodes;
}

/////////////////////////////////////////////
// Attr

Attr::Attr()
{
	m_prefix = nullptr;
	m_childNodes = new NodeList;
}

Attr::~Attr()
{
//	delete m_childNodes;
}

NodeType Attr::get_nodeType() const
{
	return NODE_ATTRIBUTE;
}

String Attr::get_namespaceURI()
{
	return m_namespaceURI;
}

String Attr::get_name()
{
	return m_nodeName;
}

String Attr::get_nodeName()
{
	return m_nodeName;
}

String Attr::get_prefix()
{
	return m_prefix;
}

String Attr::get_localName()
{
	return m_localName;
}

String Attr::get_nodeValue()
{
	return get_value();
}

String Attr::get_value()
{
	return dynamic_cast<Text*>(m_childNodes->m_items[0])->get_data();
}

void Attr::set_value(StringIn newVal)
{
	if (m_childNodes->m_items.size() == 0)
	{
		m_childNodes->m_items.push_back(m_ownerDocument->createTextNode(newVal));
	}
	else
	{
		dynamic_cast<Text*>(m_childNodes->m_items[0])->set_data(newVal);
	}
}

Document::Document()
{
	m_documentElement = NULL;
	m_childNodes = new NodeList;
}

Document::~Document()
{
}

Node* Document::appendChild(Node* child)
{
	Element* element = dynamic_cast<Element*>(child);
	if (element)
	{
		if (m_documentElement)
		{
			raise(Exception(L"Can only have one root element"));	// Can only have one root element
		}
		m_documentElement = element;
	}	// else, it's a comment etc. node

	return Node::appendChild(child);
}

bool Document::load(StringIn url)
{
	XMLParser parser;
	parser.m_document = this;
	return parser.load(url);
}

bool Document::load(IO::Stream* stream)
{
	XMLParser parser;
	parser.m_document = this;
	return parser.load(stream);
}

NodeType Document::get_nodeType() const
{
	return NODE_DOCUMENT;
}

String Document::s_nodeName(L"#document");

String Document::get_nodeName()
{
	return s_nodeName;
}

Element* Document::get_documentElement()
{
	return m_documentElement;
}

DocumentType* Document::get_doctype()
{
	return NULL;
}

Comment* Document::createComment(StringIn data)
{
	Comment* p = new Comment;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

Text* Document::createTextNode(StringIn data)
{
	Text* p = new Text;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

CDATASection* Document::createCDATASection(StringIn data)
{
	CDATASection* p = new CDATASection;
	p->m_data = data;
	p->set_ownerDocument(this);
	return p;
}

ProcessingInstruction* Document::createProcessingInstruction(StringIn target, StringIn data)
{
	ProcessingInstruction* pi = new ProcessingInstruction(this, target, data);
	return pi;
}

EntityReference* Document::createEntityReference(StringIn name)
{
	return NULL;
}

Attr* Document::createAttributeNS(StringIn namespaceURI, StringIn qualifiedName)
{
	Attr* p = new Attr;

	size_t ncolon = qualifiedName.find(':');
	if (ncolon != String::npos)
	{
		p->m_prefix = qualifiedName.LeftOf(ncolon);
		p->m_localName = qualifiedName.RightOf(ncolon+1);
	}
	else
	{
		if (qualifiedName == L"xmlns")
		{
			p->m_prefix = qualifiedName;
		//	p->m_localName = NULL;
		}
		else
		{
			p->m_localName = qualifiedName;
		}
	}

	p->m_namespaceURI = namespaceURI;
	p->m_nodeName = qualifiedName;

	p->set_ownerDocument(this);
	return p;
}

Element* Document::createElementNS(StringIn namespaceURI, StringIn qualifiedName)
{
	Element* pElement;

	pElement = new Element;
	pElement->m_namespaceURI = namespaceURI;
	pElement->m_nodeName = qualifiedName;
	pElement->m_localName = qualifiedName;	// TODO

	pElement->set_ownerDocument(this);

	return pElement;
}

Element* Document::createElementNS(StringIn namespaceURI, StringIn qualifiedName, StringIn localName)
{
	Element* pElement = new Element;

	pElement->m_namespaceURI = namespaceURI;
	pElement->m_nodeName = qualifiedName;
	pElement->m_localName = localName;

	size_t ncolon = qualifiedName.find(':');
	if (ncolon != String::npos)
	{
		pElement->m_prefix = qualifiedName.LeftOf(ncolon);
	}

	pElement->set_ownerDocument(this);

	return pElement;
}

unsigned int NodeList::get_length() const
{
	return m_items.GetSize();
}

Node* NodeList::item(unsigned int index) const
{
	return m_items[index];
}

unsigned int NamedNodeMap::get_length() const
{
	return m_items.size();
}

Node* NamedNodeMap::item(unsigned int index) const
{
	return m_items[index];
}

Node* NamedNodeMap::getNamedItemNS(StringIn namespaceURI, StringIn localName) const
{
//	map<System::StringW*, Node*, Ref_Less<System::StringW>, System::__gc_allocator>::iterator

	for (uint i = 0; i < m_items.GetSize(); i++)
	{
		if (namespaceURI == m_items[i]->get_namespaceURI() &&
			localName == m_items[i]->get_localName())
		{
			return m_items[i];
		}
	}

	return NULL;
}

/////////////////////////////

Node::Node()
{
	m_childNodes = NULL;
	m_firstChild = NULL;
	m_lastChild = NULL;
	m_nextSibling = NULL;
	m_previousSibling = NULL;
	m_parentNode = NULL;
	m_ownerDocument = NULL;
}

Node::~Node()
{
}

String Node::get_textContent()
{
	return nullptr;
}

Document* Node::get_ownerDocument()
{
	return m_ownerDocument;
}

void Node::set_ownerDocument(Document* newVal)
{
	m_ownerDocument = newVal;
}

void Node::setUserData(StringIn key, Object* data)
{
	m_userdata.insert(tyuserdatamap::value_type(key, data));
}

Object* Node::getUserData(StringIn key) const
{
	tyuserdatamap::const_iterator it = m_userdata.find(key);
	if (it != m_userdata.end())
	{
		return (*it).second;
	}
	else
		return NULL;
}

Node* Node::get_parentNode() const
{
	return m_parentNode;
}

Node* Node::get_firstChild() const
{
	return m_firstChild;
}

Node* Node::get_lastChild() const
{
	return m_lastChild;
}

Node* Node::get_nextSibling() const
{
	return m_nextSibling;
}

Node* Node::get_previousSibling() const
{
	return m_previousSibling;
}

long Node::getTextOffset(long which) const
{
	ASSERT(which >= 0 && which < 10);
	return m_textOffset[which];
}

void Node::setTextOffset(long which, long offset)
{
	ASSERT(which >= 0 && which < 10);
	m_textOffset[which] = offset;
}

Node* Node::appendChild(Node* child)
{
	if (m_childNodes)
	{
		return insertNode(child, NULL);
	}
	else
		throw new Exception(L"Cannot append child here");
	return NULL;
}

Node* Node::insertBefore(Node* child, Node* before)
{
	if (m_childNodes)
	{
		return insertNode(child, before);
	}
	else
		throw new Exception(L"Cannot insert child here");

	return NULL;
}

///

DocumentType::DocumentType()
{
}

NodeType DocumentType::get_nodeType() const
{
	return NODE_DOCUMENT_TYPE;
}

String DocumentType::get_nodeName()
{
	return get_name();
}

String DocumentType::get_name()
{
	return m_name;
}

///////

ProcessingInstruction::ProcessingInstruction()
{
}

NodeType ProcessingInstruction::get_nodeType() const
{
	return NODE_PROCESSING_INSTRUCTION;
}

String ProcessingInstruction::get_nodeName()
{
	return m_target;
}

String ProcessingInstruction::get_nodeValue()
{
	return m_data;
}

////////

CDATASection::CDATASection()
{
}

NodeType CDATASection::get_nodeType() const
{
	return NODE_CDATA_SECTION;
}

String CDATASection::s_nodeName(L"#cdata-section");

String CDATASection::get_nodeName()
{
	return s_nodeName;//WSTR("#cdata-section");
}

//////////////

Text::Text()
{
}

NodeType Text::get_nodeType() const
{
	return NODE_TEXT;
}

String Text::s_nodeName(L"#text");

String Text::get_nodeName()
{
	return s_nodeName;//WSTR("#text");
}


////////

Comment::Comment()
{
}

NodeType Comment::get_nodeType() const
{
	return NODE_COMMENT;
}

String Comment::s_nodeName(L"#comment");

String Comment::get_nodeName()
{
	return s_nodeName;//WSTR("#comment");
}


//////

EntityReference::EntityReference()
{
}

NodeType EntityReference::get_nodeType() const
{
	return NODE_ENTITY_REFERENCE;
}

String EntityReference::get_nodeName()
{
	return L"#";
}

/////////////////////////////////////////////////////////////////
// CharacterData

String CharacterData::get_nodeValue()
{
	return get_data();
}

unsigned int CharacterData::get_length() const
{
	return m_data.GetLength();
}

String CharacterData::get_data()
{
	return m_data;
}

String CharacterData::get_textContent()
{
	return m_data;
}

void CharacterData::set_data(StringIn data)
{
	m_data = data;

#if 0
	MutationEvent* evt = new MutationEvent;
	evt->initEvent(OLESTR("TextChanged"), true, false);
	dispatchEvent(evt);
#endif
}

/*
const StringW& CharacterData::get_dataref() const
{
	return m_data;
}
*/

void CharacterData::deleteData(unsigned int offset, unsigned int count)
{
// TODO, improve this
	ASSERT(0);
#if 0
	StringW* data = new StringW(true, m_data->c_str(), offset);
	*data += m_data->c_str()+offset+count;
	m_data = data;
#endif

#if 0
	MutationEvent* evt = new MutationEvent;
	evt->m_offset = offset;
	evt->m_len = count;
	evt->initEvent(OLESTR("TextDeleted"), true, false);
	dispatchEvent(evt);
#endif
}

void CharacterData::insertData(unsigned int offset, StringIn arg)
{
	String data = m_data.Insert(arg, offset);
	m_data = data;

#if 0
// TODO, improve this
	StringW * data = new StringW(true, m_data->c_str(), offset);
	*data += *arg;
	*data += m_data->c_str()+offset;
	m_data = data;
#endif

#if 0
	MutationEvent* evt = new MutationEvent;
	evt->m_offset = offset;
	evt->m_len = arg.length();
	evt->initEvent(OLESTR("TextInserted"), true, false);
	dispatchEvent(evt);
#endif
}

String CharacterData::substringData(unsigned int offset, unsigned int count) const
{
	if (offset+count > m_data.GetLength())
	{
		ASSERT(0);
		raise(ArgumentOutOfRangeException());
	}

	if (offset == 0)
	{
		if (count == m_data.GetLength())	// Exactly the same
			return m_data;
//		else
//			return m_data.Mid(offset, count);
	}

	return m_data.m_stringObject->SubString(offset, count);
//	return new StringW(string_copy(m_data->c_str() + offset, count));
}

////////////////////////////////////////////
//

NodeType Element::get_nodeType() const
{
	return NODE_ELEMENT;
}

String Element::get_tagName()
{
	return m_nodeName;
}

String Element::get_nodeName()
{
	return m_nodeName;
}

String Element::get_localName()
{
	return m_localName;
}

String Element::get_namespaceURI()
{
	return m_namespaceURI;
}

NamedNodeMap* Element::get_attributes()
{
	return m_attributes;
}

void Element::set_attributes(NamedNodeMap* attributes)
{
	ASSERT(this);
	m_attributes = attributes;
}

String Element::getAttribute(StringIn name)
{
	Node* node = m_attributes->getNamedItemNS(nullptr, name);
	if (node)
		return static_cast<Attr*>(node)->get_value();
	else
		return nullptr;
}

String Element::getAttributeNS(StringIn namespaceURI, StringIn localName)
{
	Node* node = m_attributes->getNamedItemNS(namespaceURI, localName);
	if (node)
		return static_cast<Attr*>(node)->get_value();
	else
		return nullptr;
}

void Element::setAttribute(StringIn name, StringIn value)
{
	if (m_attributes == NULL)
	{
		m_attributes = new NamedNodeMap();
	}

	Attr* attr = (Attr*)m_attributes->getNamedItemNS(nullptr, name);
	ASSERT(attr == NULL);
	attr = m_ownerDocument->createAttributeNS(nullptr, name);
	attr->set_value(value);

	m_attributes->m_items.push_back(attr);
}

Element* Element::getElementByTagNameNS(StringIn namespaceURI, StringIn localName)
{
	for (uint i = 0; i < m_childNodes->m_items.size(); ++i)
	{
		if (m_childNodes->m_items[i]->get_nodeType() == NODE_ELEMENT)
		{
			Element* element = static_cast<Element*>(m_childNodes->m_items[i]);

			if (element->get_namespaceURI() == namespaceURI &&
				element->get_localName() == localName)
			{
				return element;
			}
		}
	}

	return NULL;
}

String CDATASection::ToString()
{
	String str;
	str = L"<![CDATA[";
	str += get_data();
	str += L"]]>";

	return str;
}

String Comment::ToString()
{
	String str;
	str = L"<!--";
	str += get_data();
	str += L"-->";

	return str;
}

String Attr::ToString()
{
	String str;
	str = get_name();
	str += L"=";
	str += L"\"";
	str += get_value();
	str += L"\"";

	return str;
}

String Element::ToString()
{
	String str;
	str = L"<";
	str += get_tagName();

	if (m_attributes)
	{
		for (uint i = 0; i < m_attributes->m_items.size(); ++i)
		{
			Node* node = m_attributes->m_items[i];

			str += L" ";
			str += node->ToString();
		}
	}

	if (m_childNodes->m_items.size() == 0)
	{
		str += L"/>";
	}
	else
	{
		str += L">\n";

		for (uint i = 0; i < m_childNodes->m_items.size(); ++i)
		{
			Node* node = m_childNodes->m_items[i];
		
			str += node->ToString();
			str += L"\n";
		}

		str += L"</";
		str += get_tagName();
		str += L">";
	}

	return str;
}

String Document::ToString()
{
	String str;

	if (true)
	{
		str += L"<?xml version=\"1.0\" ?>";
		str += L"\n";
	}

	for (uint i = 0; i < m_childNodes->m_items.size(); ++i)
	{
		Node* node = m_childNodes->m_items[i];
	
		str += node->ToString();
		str += L"\n";
	}

	return str;
}

}	// XmlData
}
