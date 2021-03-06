#include "stdafx.h"
#include "LFC.h"

namespace System
{

uint32 ToUInt32(uint64 value, bool* ok)
{
	if (ok == NULL) raise(ArgumentException());

	if (value > 0xFFFFFFFF)
	{
		*ok = false;
		return 0;
	}

	*ok = true;

	return (uint32)value;
}

uint32 ToUInt32(uint64 value) throw (SystemException*)
{
	if (value > 0xFFFFFFFF)
	{
		raise(SystemException("Cannot convert uint64 to uint32"));
	}

	return (uint32)value;
}

char digits[16] =
{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
};

char* WriteNumber(char* dst, uint num, uint base)
{
	typedef char T;

	T buffer[32];
	T* p = buffer+31;

	--p;
	*p = 0;

	do
	{
		uint digit = num % base;
		num /= base;

		--p;
		*p = digits[digit];
	}
	while (num > 0);

	while (p < buffer+32)
	{
		*dst++ = *p++;
	}

	return dst;
}

char* WriteNumber(char* dst, unsigned long num, uint base)
{
	typedef char T;

	T buffer[32];
	T* p = buffer+31;

	--p;
	*p = 0;

	do
	{
		uint digit = num % base;
		num /= base;

		--p;
		*p = digits[digit];
	}
	while (num > 0);

	while (p < buffer+32)
	{
		*dst++ = *p++;
	}

	return dst;
}

char* WriteNumber(char* dst, uint64 num, uint base)
{
	typedef char T;

	T buffer[32];
	T* p = buffer+31;

	--p;
	*p = 0;

	do
	{
		uint digit = num % base;
		num /= base;

		--p;
		*p = digits[digit];
	}
	while (num > 0);

	while (p < buffer+32)
	{
		*dst++ = *p++;
	}

	return dst;
}

namespace IO
{

Stream::Stream() : position(*this), m_state(0), m_refcount(0)
{
}

Stream::~Stream()
{
	VERIFY(m_refcount == 0);

	/*
	if (m_streamObject)
	{
		m_streamObject->DecRef();
	}
	*/
}

uint64 Stream::GetSize()
{
	raise(IOException("Size of stream unknown"));
	return ~0;
}

size_t Stream::DecRef()
{
	ASSERT(m_refcount > 0);
	size_t refcount = InterlockedDecrement(&m_refcount);
	if (refcount == 0)
	{
		Close();
	}
	return refcount;
}

uint32 Stream::GetSize32() throw (SystemException*)
{
	uint64 size = GetSize();
	if (size > 0xFFFFFFFF)
	{
		raise(SystemException("File size is larger than can fit in 32 bits"));
	}

	return (uint32)size;
}

#if 0
LFCEXT IO::TextWriter& operator << (IO::TextWriter& stream, const Fmt& fmt)
{
	String::const_iterator<WCHAR> it = fmt.m_fmt.begin();

	tiny_uint count[20] = {0};

	while (*it)
	{
		WCHAR c = *it++;

		if (c == '{')
		{
			c = *it++;
			ASSERT(isdigit(c));
			int num = c - '0';
			c = *it++;
			ASSERT(c == '}');

			ubyte type = fmt.m_types[num];

			switch (num)
			{
				/*
			case 1:
				{
					bool value;
					value = (*pvalue) & 1;

					stream << value;
				}
				break;

			case 2:
				{
					char value;
					value = (*pvalue);

					stream << value;
				}
				break;

			case 3:
				{
					signed char value;
					value = (*pvalue);

					stream << value;
				}
				break;

			case 4:
				{
					unsigned char value;
					value = (*pvalue);

					stream << value;
				}
				break;

			case 5:
				{
					wchar_t value;
					value = (*pvalue);
					value |= (*pvalue)<<8;

					stream << value;
				}
				break;

			case 6:
				{
					short value;
					value = (*pvalue);
					value |= (*pvalue)<<8;

					stream << value;
				}
				break;

			case 7:
				{
					unsigned short value;
					value = (*pvalue);
					value |= (*pvalue)<<8;

					stream << value;
				}
				break;
				*/

			case 8:
				{
					int value = fmt.m_values32[num].intVal;
					stream << value;
				}
				break;

			case 9:
				{
					unsigned int value = fmt.m_values32[num].uintVal;
					stream << value;
				}
				break;

				/*
			case 10:
				{
					long value = m_values32[num].longVal;
					stream << value;
				}
				break;

			case 11:
				{
					unsigned long value = m_values32[num].ulongVal;
					stream << value;
				}
				break;
				*/

			case 14:
				{
					float value = fmt.m_values32[num].floatVal;
					stream << value;
				}
				break;

				/*
			case 13:
				{
					double value = m_values32[num].floatVal;
					stream << value;
				}
				break;
				*/

			case 16:
				{
					String value = fmt.m_strvalues[num];
					stream << value;
				}
				break;
			}
		}
		else
		{
			stream << c;
		}
	}

	return stream;
}
#endif

Stream& Stream::operator << (const array<sbyte>& data)
{
	Write(data.begin(), data.size());
	return *this;
}

Stream& Stream::operator << (const array<ubyte>& data)
{
	Write(data.begin(), data.size());
	return *this;
}

Stream& Stream::operator << (const vector<sbyte>& data)
{
	Write(data.begin(), data.size());
	return *this;
}

Stream& Stream::operator << (const vector<ubyte>& data)
{
	Write(data.begin(), data.size());
	return *this;
}

/*
Stream& Stream::operator << (const StringVariant& str)
{
	if (str.m_stringObject)
	{
		str.m_stringObject->Write(this);
	}
	else if (str.m_cstr)
	{
	}

	return *this;
}
*/

template<uint nbits, class T = unsigned int> class bitfield
{
public:

	static uint bitlength()
	{
		return nbits;
	}

	operator T () const
	{
		return m_value;
	}

	T m_value;
};

size_t Stream::WriteChars(const char* p, size_t len)
{
	return _WriteChars(p, len);
}

size_t Stream::WriteChars(const wchar_t* p, size_t len)
{
	return _WriteChars(p, len);
}

size_t Stream::_WriteChars(const char* p, size_t len)
{
	ASSERT(0);
	raise(Exception("not implemented"));
	return 0;
}

size_t Stream::_WriteChars(const wchar_t* p, size_t len)
{
	ASSERT(0);
	raise(Exception("not implemented"));
	return 0;
}

size_t Stream::ReadChars(char* p, size_t len)
{
	ASSERT(0);
	raise(Exception("not implemented"));
	return 0;
}

size_t Stream::ReadChars(wchar_t* p, size_t len)
{
	ASSERT(0);
	raise(Exception("not implemented"));
	return 0;
}

Stream& Stream::operator << (sbyte ch)
{
	Write(&ch, sizeof(ch));
	return *this;
}

Stream& Stream::operator << (ubyte ch)
{
	Write(&ch, sizeof(ch));
	return *this;
}

Stream& Stream::operator >> (sbyte& ch)
{
	Read(&ch, sizeof(ch));
	return *this;
}

Stream& Stream::operator >> (ubyte& ch)
{
	Read(&ch, sizeof(ch));
	return *this;
}

}	// IO
}	// System
