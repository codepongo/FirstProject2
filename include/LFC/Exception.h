#ifdef __LERSTAD__
struct IErrorInfo;
#endif

namespace System
{

#ifndef __LERSTAD__
#define raise_(p)	do { auto _p = p; _p->m_filename.m_data.assign(__FILE__, strlen(__FILE__)); _p->m_line = __LINE__; throw _p; } while (0)
#define raise(x)	do { auto p = new x; raise_(p); } while (0)
#else
#define raise_(p)	do { Exception* _p = p; _p->m_filename.m_data.assign(__FILE__, strlen(__FILE__)); _p->m_line = __LINE__; throw _p; } while (0)
#define raise(x)	do { Exception* p = new x; raise_(p); } while (0)
#endif

#define _catch(ex_t, ex) catch (ex_t* ex)

#define _EXCEPTION	virtual __declspec(noreturn) void raiseme() { throw this; }

class LFCEXT Exception : public Object
{
public:

	CTOR Exception(StringIn reason = StringIn(), Exception* innerException = nullptr, HRESULT hr = E_FAIL);
	CTOR Exception(const Exception& e);	// copy constructor

#undef new

	void *operator new (size_t size)
	{
		return allocate_object(size);
	}

	void *operator new (size_t size, const char* filename, int line)
	{
		Exception* p = (Exception*)allocate_object(size, filename, line);
		if (p)
		{
			p->m_filename.m_data.assign(filename, strlen(filename));
			p->m_line = line;
		}
		return p;
	}

#define new _new

	Exception* get_innerException()
	{
		return m_innerException;
	}

	virtual String get_Reason();
	virtual String get_Source()
	{
		return m_source;
	}
	virtual String get_Filename();
	virtual int get_Line();
	virtual HRESULT get_HResult()
	{
		return m_HResult;
	}

	_EXCEPTION

	static Exception* FromHResult(HRESULT hr, IErrorInfo* errorinfo = nullptr);
	static Exception* FromHResult(StringIn str, HRESULT hr);
	static Exception* FromStdException(const std::exception& e);

	LFCEXT friend IO::TextWriter& WriteToStream(IO::TextWriter& stream, Exception* e);

	ImmutableString<char> m_filename;
	int m_line;

protected:

	Exception* m_innerException;
	String m_reason;
	String m_source;
	HRESULT m_HResult;
	IErrorInfo* m_errorInfo;

	void* m_backtraces[32];
	uint m_nframes;
	bool m_bFree;
};

inline IO::TextWriter& operator << (IO::TextWriter& stream, Exception& e)
{
	return WriteToStream(stream, &e);
}

}	// System
