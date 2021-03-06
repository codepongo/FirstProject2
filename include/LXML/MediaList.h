#ifndef __MEDIALIST_H_
#define __MEDIALIST_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class MediaList;

class WEBEXT MediaQuery : public Object
{
public:
	CTOR MediaQuery()
	{
		m_mediaText = nullptr;
//		m_bTextUpdated = true;
//		m_pListener = NULL;
	}

	~MediaQuery()
	{
//		ASSERT(m_pListener == NULL);
	}

//	int FinalConstruct();
//	void FinalRelease();

//	MediaListListener* m_pListener;

public:

	//const StringW& GetTextRef();

	String get_text();
	void set_text(StringIn text);

	String get_prefix();
	void set_prefix(StringIn prefix);

	String get_mediaType();
	void set_mediaType(StringIn mediaType);

	uint get_numberOfExpressions() const;
//	STDMETHOD(getExpression)(/*[in]*/ long index, /*[out,retval]*/ ILMediaExpression* *pVal);

protected:

	void UpdateCSSText();
	void ParseCSSText();

	String m_mediaText;
	String m_prefix;
	String m_mediaType;
	bool m_bTextUpdated;
};

interface IMediaListListener
{
	virtual void OnMediaListChanged(MediaList* pList) = 0;
};

class WEBEXT MediaList : public System::Object
{
public:
	CTOR MediaList()
	{
		m_bTextUpdated = true;
		m_pListener = nullptr;
	}

	~MediaList()
	{
		ASSERT(m_pListener == nullptr);
	}

	String get_mediaText();
	void set_mediaText(StringIn newVal);
	unsigned int get_length() const;
	MediaQuery* item(unsigned int index);
	void deleteMedium(StringIn oldMedium);
	void appendMedium(StringIn newMedium);

	IMediaListListener* m_pListener;

protected:

	void UpdateCSSText();
	void ParseCSSText();

	String m_mediaText;
	vector<MediaQuery*> m_items;
	bool m_bTextUpdated;
};

}	// Web
}	// System

#endif //__MEDIALIST_H_
