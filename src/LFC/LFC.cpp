#include "stdafx.h"
#include "LFC.h"
#include <Psapi.h>
#include <Winternl.h>

typedef LONG    NTSTATUS;
typedef NTSTATUS (WINAPI *pNtQIT)(HANDLE, LONG, PVOID, ULONG, PULONG);

extern pNtQIT pfNtQueryInformationThread;

#if AMIGA
#include "../amiga_header.h"
#include <stdio.h>
#endif

//#include "Linker.h"
#include "NameMangler.h"
#include "VCMangler.h"

#include "CodeViewDebugInfo.h"
#include "coff.h"
//#include "../Include/AmigaHunkParser.h"

#include <algorithm>

LFCEXT void testnullptr(decltype(nullptr))
{
}

#if 0

class EventHandler
{
public:

	EventHandler(const type_info& typeinfo) : m_typeinfo(typeinfo)
	{
	}

	System::Object* m_me;
	const type_info& m_typeinfo;
};

template<class T> class EventHandlerT : public EventHandler
{
public:

	EventHandlerT(T* me, void (T::*handler)()) : EventHandler(typeid(T))
	{
		m_object = me;
		int size = sizeof(handler);
		m_handler = handler;
	}

	typedef T classtype;

	T* m_object;
	void (T::*m_handler)();
};

namespace Test
{

/*
template<class T> EventHandlerT<T> CreateEventHandler(T* me, void (T::*handler)())
{
	return EventHandlerT<T>(me, handler));
}
*/

	class Window
	{
	public:

		//class Event;

		/*
		template<class T> class Handler
		{
			typedef void (T::*handler)();
		}
		*/

		template<class arg_type> class Event
		{
		public:
			vector<EventHandler> m_handlers;

			/*
			template<class T> class EventHandler
			{
				typedef T handlerClass;
			};

			EventHandler
			*/

			/*
			template<class T> Event& operator = (void (T::*handler)())
			{
				return *this;
			}
			*/

			/*
			template<class T> Event& Add(void (T::*handler)())
			{
				return *this;
			}
			*/

			template<class T> Event& operator = (void (T::*handler)(arg_type))
			{
				//(handler.m_object->*handler.m_handler)();

			//	ft f = (ft)handler.m_handler;

				return *this;
			}

			template<class T> Event& operator += (EventHandler<arg_type> (T::*handler)(arg_type))
			{
				//(handler.m_object->*handler.m_handler)();

			//	ft f = (ft)handler.m_handler;

				return *this;
			}

#if 0
			template<class T> Event& operator = (EventHandlerT<T> handler)
			{
				//(handler.m_object->*handler.m_handler)();

			//	ft f = (ft)handler.m_handler;

				return *this;
			}
#endif

			/*
			template<class T> Event& operator = (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}

			template<class T> Event& operator += (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}

			template<class T> Event& operator -= (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}
			*/

			bool operator == (void* nullptr) const
			{
				return false;
			}

			bool operator != (void* nullptr) const
			{
				return false;
			}
			/*
			template<class T> Event& operator & (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}
			*/

			void operator () (arg_type arg)
			{
			}
		};

		template<class arg1_type, class arg2_type> class Event2
		{
		public:
			vector<EventHandler> m_handlers;

			/*
			template<class T> class EventHandler
			{
				typedef T handlerClass;
			};

			EventHandler
			*/

			/*
			template<class T> Event& operator = (void (T::*handler)())
			{
				return *this;
			}
			*/

			/*
			template<class T> Event& Add(void (T::*handler)())
			{
				return *this;
			}
			*/

			template<class T> Event& operator = (EventHandlerT<T> handler)
			{
				//(handler.m_object->*handler.m_handler)();

			//	ft f = (ft)handler.m_handler;

				return *this;
			}

			/*
			template<class T> Event& operator = (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}

			template<class T> Event& operator += (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}

			template<class T> Event& operator -= (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}
			*/

			bool operator == (void* nullptr) const
			{
				return false;
			}

			bool operator != (void* nullptr) const
			{
				return false;
			}
			/*
			template<class T> Event& operator & (EventHandlerT<T> handler)
			{
				(handler.m_object->*handler.m_handler)();

				return *this;
			}
			*/

			void operator () (arg1_type arg1, arg2_type arg2)
			{
			}
		};

		Event<System::Event*> mouseDown;

		void click()
		{
			mouseDown(new System::Event());
		}
	};
}

#endif

#if WIN32
#include "vc_typeinfo.h"
#endif

//DECLSPEC_DLLEXPORT long g_locked = 0;
//DECLSPEC_DLLEXPORT long g_locked2 = 0;

#if AMIGA

#undef getc

extern "C" int getc(FILE* fp)
{
	ASSERT(0);
	return 0;
}

#undef putc

extern "C" int putc(int, FILE*)
{
	ASSERT(0);
	return 0;
}
#endif

extern "C" int entrypoint_hook(unsigned char* address, char* str, int len);

//using namespace System;
//using namespace System::IO;

#if 0
DWORD load_offset;
#endif

//const type_info& uih = typeid(TestEnum);

#if AMIGA

__type_info2::~__type_info2()
{
}

class __class_type_info2 : public __type_info2
{
};

struct __base_class_type_info2
{
public:
	const __class_type_info2 *__base_type;
	long __offset_flags;
	
	enum __offset_flags_masks
	{
		__virtual_mask = 0x1,
		__public_mask = 0x2,
		__offset_shift = 8
	};
};

class __si_class_type_info2 : public __class_type_info2
{
public:
	const __class_type_info2 *__base_type;
};

class __vmi_class_type_info2 : public __class_type_info2
{
public:
	unsigned int __flags;
	unsigned int __base_count;
	__base_class_type_info2 __base_info[1];
	  
	enum __flags_masks
	{
		__non_diamond_repeat_mask = 0x1,
		__diamond_shaped_mask = 0x2
	};
};

extern "C" 
   void* __dynamic_cast ( const void *sub,
			  const __class_type_info2 *src,
			  const __class_type_info2 *dst,
			  ptrdiff_t src2dst_offset);
   /* sub: source address to be adjusted; nonnull, and since the
    *      source object is polymorphic, *(void**)sub is a virtual
    pointer.
    * src: static type of the source object.
    * dst: destination type (the "T" in "dynamic_cast<T>(v)").
    * src2dst_offset: a static hint about the location of the
    *    source subobject with respect to the complete object;
    *    special negative values are:
    *       -1: no hint
    *       -2: src is not a public base of dst
    *       -3: src is a multiple public base type but never a
    *           virtual base type
    *    otherwise, the src type is a unique public nonvirtual
    *    base type of dst at offset src2dst_offset from the
    *    origin of dst.
    */

/*
class Test
{
public:
	Test();

	int m_x;

	int get_Testing();
	void put_Testing(int x);
};
*/
#endif

#if WIN32

/*
#include "../LFC/vc_typeinfo.h"

System::Type* type_info::GetType() const
{
	TypeDescriptor* ti = (TypeDescriptor*)this;
//	return *(Type**)ti->rawname;
	ASSERT(ti->_m_data);
	return (System::Type*)ti->_m_data;
}
*/

#endif

#if AMIGA

/*
const char * std::type_info::name() const
{
	return ((NamedType*)ti->__type_name)
}
*/

System::Type* std::type_info::GetType() const
{
	__type_info2* ti = (__type_info2*)this;
#if 1
	return *(System::Type**)(ti->__type_name-4);
#else
	return (System::Type*)ti->__type_name;
#endif

#if 0
	TypeDescriptor* ti = (TypeDescriptor*)this;
//	return *(Type**)ti->rawname;
	ASSERT(ti->_m_data);
	return (Type*)ti->_m_data;
#endif
	return NULL;
}

#endif

#if 0

#if AMIGA
#include "C:/test.cpp"
#else
#include "C:/test.cpp"
#endif

namespace TestNamespace
{

Test::Test()
{
	m_x = 6;
	printf("Test ctor\n");
}

Test_2::Test_2()
{
	m_y = 9;
}

data::data()
{
	m_j = 6;
}

/*
data::~data()
{
}
*/

int Test::get_Testing()
{
	printf("get_Testing = %d\n", m_x);

	return m_x;
}

void Test::put_Testing(int x)
{
	printf("put_Testing: old_x(%d)\n", m_x);
	printf("put_Testing: new_x(%d)\n", x);
	m_x = x;
}

void Test::virt_func()
{
	printf("virt_func\n");
}

void Test::virt_func2()
{
	printf("virt_func\n");
}

void Test2::virt_func()
{
	printf("virt_func: %d\n", m_y);
}

void Test2::virt_func2(Test2* k)
{
	printf("virt_func2: %d\n", m_y);
}

void Test_2::virt_func3(int x, float y)
{
	printf("virt_func3: %d\n", m_y);
}

StringA Test2::GetString(StringA str)
{
	return StringA();
}

StringA Test2::GetString2(StringA & str)
{
	return StringA();
}

int Test2::GetString3(const StringA & str)
{
	return 0;
}

/*
data get_data()
{
	return data();
}
*/

void Test2::put_data(data d)
{
	printf("data.m_j = %d\n", d.m_j);
}

}
#endif

// ABI

/*
<builtin-type> ::= v	# void
		 ::= w	# wchar_t
		 ::= b	# bool
		 ::= c	# char
		 ::= a	# signed char
		 ::= h	# unsigned char
		 ::= s	# short
		 ::= t	# unsigned short
		 ::= i	# int
		 ::= j	# unsigned int
		 ::= l	# long
		 ::= m	# unsigned long
		 ::= x	# long long, __int64
		 ::= y	# unsigned long long, __int64
		 ::= n	# __int128
		 ::= o	# unsigned __int128
		 ::= f	# float
		 ::= d	# double
		 ::= e	# long double, __float80
		 ::= g	# __float128
		 ::= z	# ellipsis
		 ::= u <source-name>	# vendor extended type

*/

/*
void DemangleName(const char* mname)
{
	const char* p = NULL;

	if (*p == 'P')
	{
		Type* pType = new Type;
		pType->m_type = type_pointer;
	}
	else
	{
	}
}
*/

/*
<operator-name> ::= nw	# new           
		  ::= na	# new[]
		  ::= dl	# delete        
		  ::= da	# delete[]      
		  ::= ps # + (unary)
		  ::= ng	# - (unary)     
		  ::= ad	# & (unary)     
		  ::= de	# * (unary)     
		  ::= co	# ~             
		  ::= pl	# +             
		  ::= mi	# -             
		  ::= ml	# *             
		  ::= dv	# /             
		  ::= rm	# %             
		  ::= an	# &             
		  ::= or	# |             
		  ::= eo	# ^             
		  ::= aS	# =             
		  ::= pL	# +=            
		  ::= mI	# -=            
		  ::= mL	# *=            
		  ::= dV	# /=            
		  ::= rM	# %=            
		  ::= aN	# &=            
		  ::= oR	# |=            
		  ::= eO	# ^=            
		  ::= ls	# <<            
		  ::= rs	# >>            
		  ::= lS	# <<=           
		  ::= rS	# >>=           
		  ::= eq	# ==            
		  ::= ne	# !=            
		  ::= lt	# <             
		  ::= gt	# >             
		  ::= le	# <=            
		  ::= ge	# >=            
		  ::= nt	# !             
		  ::= aa	# &&            
		  ::= oo	# ||            
		  ::= pp	# ++            
		  ::= mm	# --            
		  ::= cm	# ,             
		  ::= pm	# ->*           
		  ::= pt	# ->            
		  ::= cl	# ()            
		  ::= ix	# []            
		  ::= qu	# ?             
		  ::= st	# sizeof (a type)
		  ::= sz	# sizeof (an expression)
		  ::= cv <type>	# (cast)        
		  ::= v <digit> <source-name>	# vendor extended operator
*/

/*
<builtin-type> ::= v	# void
		 ::= w	# wchar_t
		 ::= b	# bool
		 ::= c	# char
		 ::= a	# signed char
		 ::= h	# unsigned char
		 ::= s	# short
		 ::= t	# unsigned short
		 ::= i	# int
		 ::= j	# unsigned int
		 ::= l	# long
		 ::= m	# unsigned long
		 ::= x	# long long, __int64
		 ::= y	# unsigned long long, __int64
		 ::= n	# __int128
		 ::= o	# unsigned __int128
		 ::= f	# float
		 ::= d	# double
		 ::= e	# long double, __float80
		 ::= g	# __float128
		 ::= z	# ellipsis
		 ::= u <source-name>	# vendor extended type
*/

namespace System
{

String ToString(int n)
{
	char buf[32];
	sprintf_s(buf, "%d", n);

	return new ImmutableString<char>(string_copy(buf));
}

#if 0
StringA & operator << (StringA & str, int n)
{
	char buf[32];
	sprintf(buf, "%d", n);
	/*
	do
	{
		str += n;
		n /= 10;
	}
	while (n >= 0)
	*/

	str = str + buf;

	return str;
}
#endif

/*
template<class T> class deref
{
public:
	deref(T * p)
	{
		m_t = *p;
	}

	deref(deref & other)
	{
		m_t = p.m_t;
	}

	T* m_t;

	bool operator == (const T * other) const
	{
		return *m_t == *other;
	}

	bool operator < (const T * other) const
	{
		return *m_t < *other;
	}
};
*/

/*
class cstrn
{
public:
	cstrn(const char* str)
	{
		m_str = str;
		m_len = strlen(str);
	}

	bool operator == (cstrn& other) const
	{
		if (m_len != other.m_len) return false;
		return strncmp(m_str, other.m_str, m_len) == 0;
	}

	bool operator < (cstrn& other) const
	{
		if (m_len < other.m_len)
			return strncmp(m_str, other.m_str, m_len) < 0;
		else
			return strncmp(m_str, other.m_str, other.m_len) < 0;
	}

	const char* m_str;
	int m_len;
};
*/

class heap_allocator
{
public:

	CTOR heap_allocator(Heap* pHeap) : m_pHeap(pHeap)
	{
	}

	Heap* m_pHeap;

	void* allocate_object(size_t size)
	{
		ASSERT(0);
		return NULL;
		//return m_pHeap->allocate_object(size);
	}
};

void* grow_allocator::allocate_buffer(size_t size)
{
	uint8* p = m_buffer + m_next;
	size = (size+3) & ~3;
	m_next += size;
	if (!(m_next <= m_size))
	{
		std::printf("ASSERT\n");
		std::printf("%s\n", m_buffer);
		ASSERT(0);
		return NULL;
	}
	return p;
}

void* grow_allocator::reallocate_buffer(void* pv, size_t size)
{
	if (pv == NULL)
	{
		return allocate_buffer(size);
	}
	else
	{
		size = (size+3) & ~3;
		m_next = (uint8*)pv + size - m_buffer;
		if (!(m_next < m_size))
		{
			printf("ASSERT\n");
			printf("%s\n", m_buffer);
			ASSERT(0);
		}

		return pv;
	}
}

#if 0
void MangleName(Method* pMethod, IO::TextWriter& strbuilder)
{
//	printf("\n\n");

	strbuilder << "__ZN";

	//Heap* pHeap = new Heap(4096);

	Mangler mangler;

	FunctionType* pFunction = pMethod->m_decl->m_pType->GetFunction();

	if (pFunction->m_bVolatile) strbuilder << "V";
	if (pFunction->m_bConst) strbuilder << "K";

	mangler.MangleName(pMethod->AsClass()->m_pScope, strbuilder);

	if (pMethod->m_decl->m_name == pMethod->GetClass()->m_name)	// constructor
	{
		strbuilder << "C1";
	}
	else
	{
	//	char component[512];
	//	sprintf_s(component, "%d%s", , pMethod->m_decl->m_name->c_str());
		strbuilder << pMethod->m_decl->m_name.GetLength() << pMethod->m_decl->m_name;
	}

	strbuilder << "E";

	mangler.MangleFunctionParameters(pFunction->m_parameters, strbuilder);

	/*
	if (*pMethod->m_decl->m_name == "Button")
	{
		printf("my attempt: %s\n", mname);
	}
	*/

//	return strbuilder.DetachToString();

#if 0
	if (m_pFunction)
	{
		if (m_pFunction->m_parameters.size() == 0)
		{
			mname += "v";	// void
		}
		else
		{
			for (int i = 0; i < m_pFunction->m_parameters.size(); i++)
			{
				Type* pType = NULL;
			}
		}
	}
#endif
}
#endif

void MangleName(ClassType* pClass, Declarator* decl, IO::TextWriter& strbuilder)
{
//	printf("\n\n");

	strbuilder << "__ZN";

	//Heap* pHeap = new Heap(4096);

	Mangler mangler;

	FunctionType* pFunction = decl->m_pType->AsFunction();

	if (pFunction->m_bVolatile) strbuilder << "V";
	if (pFunction->m_bConst) strbuilder << "K";

	mangler.MangleName(pClass/*pMethod->GetClass()*/->m_pScope, strbuilder);

	if ( /*pMethod->m_ */decl->m_name == pClass/*pMethod->GetClass()*/->m_name)	// constructor
	{
		strbuilder << "C1";
	}
	else
	{
	//	char component[512];
	//	sprintf_s(component, "%d%s", /*pMethod->m_*/decl->m_name->Length(), /*pMethod->m_*/decl->m_name->c_str());
	//	strbuilder << component;
		strbuilder << decl->m_name.GetLength() << decl->m_name;
	}

	strbuilder << "E";

	mangler.MangleFunctionParameters(pFunction->m_parameters, strbuilder);

	/*
	if (*pMethod->m_decl->m_name == "Button")
	{
		printf("my attempt: %s\n", mname);
	}
	*/

//	return strbuilder.DetachToString();

#if 0
	if (m_pFunction)
	{
		if (m_pFunction->m_parameters.size() == 0)
		{
			mname += "v";	// void
		}
		else
		{
			for (int i = 0; i < m_pFunction->m_parameters.size(); i++)
			{
				Type* pType = NULL;
			}
		}
	}
#endif
}

//template LFCEXT void MangleName<char>(ClassType* pClass, CDeclarator* decl, StringBuilder<char>& strbuilder);
//template LFCEXT void MangleName<WCHAR>(ClassType* pClass, CDeclarator* decl, StringBuilder<WCHAR>& strbuilder);

}

LFCEXT int wcsncmp(const WCHAR* str, const WCHAR* str2, int len)
{
	while (len--)
	{
		int d = *str - *str2;

		if (*str == 0)
			return d;
		else if (*str2 == 0)
			return d;
		else if (d)
			return d;

		str++;
		str2++;
	}

	return 0;
}

LFCEXT int wcsncmp(const WCHAR* str, const char* str2, int len)
{
	while (len--)
	{
		int d = *str - *str2;
		
		if (*str == 0)
			return d;
		else if (*str2 == 0)
			return d;
		else if (d)
			return d;

		str++;
		str2++;
	}

	return 0;
}

LFCEXT int wcsncmp(const char* str, const WCHAR* str2, int len)
{
	while (len--)
	{
		int d = *str - *str2;
		
		if (*str == 0)
			return d;
		else if (*str2 == 0)
			return d;
		else if (d)
			return d;

		str++;
		str2++;
	}

	return 0;
}

LFCEXT int wcsncmp(const char* str, const char* str2, int len)
{
	while (len--)
	{
		int d = *str - *str2;
		
		if (*str == 0)
			return d;
		else if (*str2 == 0)
			return d;
		else if (d)
			return d;

		str++;
		str2++;
	}

	return 0;
}

#if 0//WIN32

void* my___RTDynamicCast(void *p)
{
	void* vtable = *(void**)p;
	rtti_object_locator* p3 = ((rtti_object_locator**)vtable)[-1];
	uint8* e = (uint8*)p - p3->value;
	if (p3->offset_to_top == NULL)
		goto there;

	ASSERT(0);
there:

	return e;
}

const BaseClassDescriptor* my2_RTDynamicCast(void* p2, rtti_object_locator* p3, void* type0, void *e, TypeDescriptor* type1)
{
	BaseClassDescriptor** o = p3->m_classHierarchyDescriptor->m_baseClassArray;

	int count = p3->m_classHierarchyDescriptor->count;
	for (int i = 0; i < count; i++)
	{
		if ((*o)->typedesc == type1)
		{
			/*
			long v = o->value[4];
			if (v & 1)
			{
				ASSERT(0);
			}
			*/

			return *o;
		}
		else if (strcmp((*o)->typedesc->rawname, type1->rawname) == 0)
		{
			return *o;
		}

		o++;
	}

	return NULL;
}

int my3_RTDynamicCast(void* p2, const Sub* h)
{
	int k = 0;

	if (h->value1 < 0)
	{
		k += h->value0;
		return k;
	}
/*	if (((long*)h)[1] < 0)
	{
		k += ((long*)h)[0];
		return k;
	}
*/	else
		ASSERT(0);
	//*h
}

void* my__RTDynamicCast(void* p, int parm0/*??*/, void* type0, void* type1, int parm1/*??*/)
{
	uint8* p2 = (uint8*)my___RTDynamicCast((void*)p);
	void* vtable = *(void**)p;
	rtti_object_locator* p3 = ((rtti_object_locator**)vtable)[-1];
	uint8* e = (uint8*)p - parm0;
	p = e;
	e -= (long)p2;
	if (p3->m_classHierarchyDescriptor->value0 & 1)
	{
		ASSERT(0);
	}

	const BaseClassDescriptor* h = my2_RTDynamicCast(p2, p3, type0, e, (TypeDescriptor*)type1);
	if (h == NULL)
		ASSERT(0);
	//h += 8;

	int g = my3_RTDynamicCast(p2, &h->value2);
	p2 += g;

	int j = -1;

	return p2;
}

#endif // WIN32

#if 0
static void* _myalloc(size_t size)
{
//	if (size == 0) return NULL;
#if WIN32
//	return malloc(size);
	return HeapAlloc(GetProcessHeap(), 0, size);
#else
	return execAllocVec(*(struct ExecBase**)4, size, 0);
#endif
}

static void _myfree(void* p)
{
#if WIN32
	HeapFree(GetProcessHeap(), 0, p);
#else
	execFreeVec(*(struct ExecBase**)4, p);
#endif
}
#endif

namespace System
{

#if 0
static System::CriticalSection crit;

LFCEXT void* myalloc(size_t size)
{
	return allocate_buffer(size);

	if (size == 0) return NULL;	// ??

	void* p = _myalloc(size);
	if (p == NULL)
	{
		TRACE("Failed to allocate size=%d\n", size);
		THROW(std::bad_alloc());
	}
	return p;
}

LFCEXT void* myalloc(size_t size, const char* filename, long line)
{
	return allocate_buffer(size);

	if (size == 0) return NULL;	// ??

	void* p = _myalloc(size);
	if (p == NULL)
	{
		DebugTraceLn("Failed to allocate size=" << size << " in " << filename << paren(line));
		THROW(std::bad_alloc());
	}
	return p;

#if 0
	memnode* node = (memnode*)_myalloc(sizeof(memnode) + size + 12);
	if (node == NULL)
	{
		printf("Failed to allocate size: %d + 4\n", size);
		ASSERT(0);
		return NULL;
	}
	strcpy_s(node->filename, filename);
	node->line = line;
	node->size = size;
	node->pattern[0] = 0xFAB091CB;
	node->pattern[1] = 0x86A35625;
	node->pattern[2] = 0xFDC34565;

	uint8* after = ((uint8*)(node+1)) + size;
	std::memcpy(after, pattern_after, 12);

	// addtail
	crit.Lock();
	insert(&memlist, node, (node_t*)&memlist.head);
	crit.Unlock();
//	node->prev = memlist.tailpred;
//	node->next = (node_t*)&memlist.tail;
//	memlist.tailpred->next = node;
//	((node_t*)&memlist)->next = node;
	//memlist.tailpred = node;

//	s_memlist->next = node;
//	s_memlist = node;

	return (void*)(node+1);
#endif
}

LFCEXT void myfree(void* p)
{
	return;

	if (p == NULL)
		return;
	_myfree(p);
	return;

#if 0
	memnode* node = ((memnode*)p) - 1;

#if WIN32
	if (IsBadReadPtr(node, sizeof(memnode)))
	{
		ASSERT(0);
	}
#endif
	if (node->pattern[0] != 0xFAB091CB)
	{
		ASSERT(0);
	}

	if (node->pattern[1] != 0x86A35625)
	{
		ASSERT(0);
	}

	if (node->pattern[2] != 0xFDC34565)
	{
		ASSERT(0);
	}

	uint8* after = ((uint8*)(node+1)) + node->size;
	if (std::memcmp(after, pattern_after, 12) != 0)
	{
		ASSERT(0);
	}

	ASSERT(node->prev);
	ASSERT(node->next);

	crit.Lock();
	node->prev->next = node->next;
	node->next->prev = node->prev;
	crit.Unlock();

	_myfree(node);
#endif
}
#endif

#if WIN32

LFCEXT void* CreateThread(THREADSTARTPROC startproc, void* args)
{
	DWORD threadId;
	return ::CreateThread(NULL, NULL, startproc, args , 0, &threadId);
}

#endif

}

#if AMIGA

CriticalSection::CriticalSection()
{
	ASSERT(sizeof(m_private) >= sizeof(SignalSemaphore));

	ASSERT((SignalSemaphore*)&m_private == (SignalSemaphore*)m_private);

	InitSemaphore((SignalSemaphore*)m_private);
}

CriticalSection::~CriticalSection()
{
}

void CriticalSection::Lock()
{
	ObtainSemaphore((SignalSemaphore*)m_private);
}

void CriticalSection::Unlock()
{
	ReleaseSemaphore((SignalSemaphore*)m_private);
}

bool CriticalSection::Try()
{
	return AttemptSemaphore((SignalSemaphore*)m_private)? true: false;
}

typedef ULONG (*THREADSTARTPROC)(void* lpArgument);

struct THREADDATA
{
	THREADSTARTPROC startproc;
	void* args;
};

/*
extern "C" long __saveds ThreadEntryPoint(const char* str, int len)
{
	THREADDATA* pt;
	sscanf(str, "%x", &pt);

	THREADDATA t = *pt;

	FreeMem(pt, sizeof(THREADDATA));

	t.startproc(t.args);

#if 0//AMIGA
	Wait(0);	// Wait forever
#endif

	return 0;
}

__asm__("

	xdef __ThreadEntryPoint

__ThreadEntryPoint:
	move.l d0,-(a7)
	move.l a0,-(a7)
	jsr _ThreadEntryPoint
	adda.l #8,a7
	rts

	");
*/

extern "C" ULONG _ThreadEntryPoint();

extern "C" ULONG ThreadEntryPoint(const char* str, int len)
{
	struct THREADDATA* pt;
	struct THREADDATA t;

	pt = (struct THREADDATA*)str2int(str);

	t = *pt;

//	execFreeMem(*(struct ExecBase**)4, pt, sizeof(struct THREADDATA));

	return t.startproc(t.args);
}

void* CreateThread(THREADSTARTPROC startproc, void* args)
{
	THREADDATA* pt = (THREADDATA*)execAllocMem(SysBase, sizeof(THREADDATA), MEMF_PUBLIC);
	ASSERT(pt);
	if (pt == NULL) return NULL;

	pt->startproc = startproc;
	pt->args = args;

	char str[32];
	sprintf(str, "%ld", pt);

	Process* process = CreateNewProcTags(
		(NP_Entry), (ULONG)_ThreadEntryPoint,
		(NP_Arguments), (ULONG)str,
	//	(NP_Output), dosOpen(DOSBase, "CON:", MODE_NEWFILE),
		(NP_StackSize), 900000,
		(TAG_END));

	return process;
}

void _DebugBreak(const char* file, int line)
{
	printf("assertion at %s(%d)\n", file, line);
	Delay(50*10);
	exit(20);
}

int wcscmp(const WCHAR* s1, const WCHAR* s2)
{
	while (1)
	{
		int diff = *s1 - *s2;

		if (*s1 == 0) return diff;
		else if (*s2 == 0) return diff;
		else if (diff) return diff;

		s1++;
		s2++;
	}

	return 0;
}

WCHAR* wcschr(const WCHAR* str, WCHAR c)
{
	while (*str)
	{
		if (*str == c)
			return (WCHAR*)str;

		str++;
	}

	return NULL;
}

int wcsicmp(const WCHAR*, const WCHAR*)
{
	ASSERT(0);
	return 0;
}

int wcsnicmp(const WCHAR*, const WCHAR*, int)
{
	ASSERT(0);
	return 0;
}

WCHAR* wcscpy(WCHAR* dest, const WCHAR* src)
{
	WCHAR* p = dest;
	while (*src)
	{
		*p++ = *src++;
	}
	*p = 0;

	return dest;
}

WCHAR* wcsncpy(WCHAR* dest, const WCHAR* src, int len)
{
	ASSERT(0);
	return NULL;
}

int wcslen(const WCHAR* str)
{
	int count = 0;

	while (*str)
	{
		count++;
		str++;
	}
	return count;
}

#endif

#if WIN32

namespace System
{

void _AddPersistentLiveRoot(void** pp);

void NullType::Static_Init()
{
#undef new
	::new (&Types::type_null) NullType();
#define new _new
}

void PrimitiveType::Static_Init()
{
#undef new

	::new (&Types::type_void) PrimitiveType(System::type_void);
	::new (&Types::type_bool) PrimitiveType(System::type_bool);
	::new (&Types::type_char) PrimitiveType(System::type_char);
	::new (&Types::type_wchar) PrimitiveType(System::type_wchar);
	::new (&Types::type_signed_char) PrimitiveType(System::type_signed_char);
	::new (&Types::type_unsigned_char) PrimitiveType(System::type_unsigned_char);
	::new (&Types::type_int) PrimitiveType(System::type_int);
	::new (&Types::type_unsigned_int) PrimitiveType(System::type_unsigned_int);
	::new (&Types::type_short) PrimitiveType(System::type_short);
	::new (&Types::type_unsigned_short) PrimitiveType(System::type_unsigned_short);
	::new (&Types::type_long) PrimitiveType(System::type_long);
	::new (&Types::type_unsigned_long) PrimitiveType(System::type_unsigned_long);
	::new (&Types::type_long_long) PrimitiveType(System::type_long_long);
	::new (&Types::type_unsigned_long_long) PrimitiveType(System::type_unsigned_long_long);
	::new (&Types::type_float) PrimitiveType(System::type_float);
	::new (&Types::type_double) PrimitiveType(System::type_double);
	::new (&Types::type_long_double) PrimitiveType(System::type_long_double);
	::new (&Types::type_float128) PrimitiveType(System::type_float128);

#define new _new
}

// static
TypeDatabase* TypeDatabase::pD;

TypeDatabase::TypeDatabase() : m_debugInfo(NULL)
{
}

NamedType* TypeDatabase::LookupNamedType(StringIn name)
{
	map<String, NamedType*>::iterator it = m_namedTypes.find(name);
	if (it != m_namedTypes.end())
		return (*it).second;
	else
		return NULL;
}

Conv::Conv()
{
	pConv = NULL;

	ArgType = NULL;
	pMethod = NULL;
}

/*
Method::Method()
{
	m_class = NULL;
	m_decl = NULL;
//	m_func = 0;
}

Method::~Method()
{
}
*/

#if 0
Type_Info* Method::GetTypeInfo()
{
	return m_class->m_pTypeInfo;
}
#endif

/*
class some_other
{
public:
};

template<class T> class LFCEXT test_template
{
public:
	int x;
};

extern Heap* heap;
*/

#if 0

Type* ParseType(char* & p);

void getidentifier(char* name_buffer, char* & p)
{
	if (!isalpha(*p) && *p != '_')
	{
		THROW(-1);
		ASSERT(0);
	}

	char* pname = name_buffer;
	*pname++ = *p++;

	while (isalnum(*p) || *p == '_')
	{
		*pname++ = *p++;
	}
	*pname = 0;
}

Type* ParseType2(char* & p)
{
	if (!strncmp("bool", p, 4))
	{
		p += 4;
		return Types::type_bool;
	}
	else if (!strncmp("char", p, 4))
	{
		p += 4;
		return Types::type_char;
	}
	else if (!strncmp("unsigned char", p, 13))
	{
		p += 13;
		return Types::type_unsigned_char;
	}
	else if (!strncmp("int", p, 3))
	{
		p += 3;
		return Types::type_int;
	}
	else if (!strncmp("unsigned int", p, 12))
	{
		p += 12;
		return Types::type_unsigned_int;
	}
	else if (!strncmp("unsigned short", p, 14))
	{
		p += 14;
		return Types::type_unsigned_short_int;
	}
	else if (!strncmp("long", p, 4))
	{
		p += 4;
		return Types::type_long_int;
	}
	else if (!strncmp("unsigned long", p, 13))
	{
		p += 13;
		return Types::type_unsigned_long_int;
	}
	else if (!strncmp("float", p, 5))
	{
		p += 5;
		return Types::type_float;
	}
	else if (!strncmp("double", p, 6))
	{
		p += 6;
		return Types::type_double;
	}
	else
	{
		int open = 0;
		char name_buffer2[4096];
		char* pname2 = name_buffer2;
		char * p2 = p;
		while (*p2)
		{
			if (*p2 == '<')
			{
				*pname2++ = *p2++;
				open++;
			}
			else if (*p2 == '>')
			{
				if (open == 0)
					break;

				*pname2++ = *p2++;
				open--;
				if (open == 0)
					break;
			}
			else
			{
				if (open == 0)
				{
					if (isalnum(*p2) || *p2 == '_' || *p2 == ':')
					{
						*pname2++ = *p2++;
					}
					else
					{
						break;
					}
				}
				else
				{
					*pname2++ = *p2++;
				}
			}
		}
		*pname2 = 0;

		uint8* next = heap->m_next;
		StringA* str = new StringA(name_buffer2);
		NamedType* pType = pD->LookupNamedType(str);

		heap->m_next = next;

		//ASSERT(pType);

		while (1)
		{
			char name_buffer[4096];
			getidentifier(name_buffer, p);

			Scope* pScope;
			namespacemap::iterator it = pScope->m_namespaces.find(new StringA(name_buffer));
			if (it != end())
			{
				pScpe = (*it).second->m_pScope;
			}
			else
			{
				Namespace* pNamespace 
				m
			}

			if (*p == '<')	// template
			{
				ClassType* pClassType = new ClassType;
				pClassType->m_qname = new StringA(name_buffer);
				pClassType->m_kwType = pType->GetClass()->m_kwType;

				TemplatedClassType* pInst = new TemplatedClassType;
				pInst->m_pClass = pClassType;

				p++;
				while (1)
				{
				//	StringBuilderA strbuilder2;
					Type* pArgType = ParseType(p);
					if (pArgType == NULL)
						return NULL;

					pInst->m_templateArgs.push_back(pArgType);

					if (*p == '>')
						break;
					else if (*p == ',')
						p++;
					else
						ASSERT(0);
				}

				p++;

				if (*p == ':')
				{
					p++;
					VERIFY(*p == ':');
					p++;
				}
			}
			else
			{
				pD->LookupNamedType(
			}

			return pInst;
		}
		else
			return pType;
#if 0
		ASSERT(pType);

		/*str =*/ DecorateNameName(pType, strbuilder);
#endif
	}
}

Type* ParseType(char* & p)
{
	Type* pType = ParseType2(p);

	if (pType == NULL)
		return pType;

	ASSERT(pType);

	while (isspace(*p))
	{
		p++;
	}

	while (1)
	{
		if (*p == '*')
		{
			p++;
			pType = new PointerType(pType);
		}
		else if (*p == '&')
		{
			p++;
			pType = new ReferenceType(pType);
		}
		else if (!strncmp(p, "const", 5))
		{
			p += 5;
			// TODO
			//pType = new ModifierType(true, false, pType);
		}
		else
			break;

		while (isspace(*p))
		{
			p++;
		}
	}

	return pType;
}
#endif

//test_template<int> testing;

//void DecorateName(const char* & p, StringBuilderA& strbuilder)

#if 0
LFCEXT Type* DemangleName(const char* & p)
{
	if (*p == 'V')
	{
		p++;

		ASSERT(0);

		IO::StringWriter qname;
		while (*p)
		{
		}

		return NULL;
	}
	else if (*p == 'P')
	{
		p++;
		return new PointerType(DemangleName(p));
	}
	else if (*p == 'A')
	{
		p++;
		return new ReferenceType(DemangleName(p));
	}
	else
	{
		ASSERT(0);
		return NULL;
	}
}
#endif

#if 0
LFCEXT void MangleNameName(StringA* qname, StringBuilderA & strbuilder)
{
	char buffer[4096];
	strcpy(buffer, qname->c_str());

	vector<char*> parts;

	char* p = buffer;
	char* part = p;
//	int open = 0;
	while (*p)
	{
		/*
		if (*p == '<')
		{
		//	part.Append(*p++);
			open++;
			StringBuilderA strbuilder;
			DecorateName(p, strbuilder);
		}
		else if (*p == '>')
		{
			part.Append(*p++);
			open--;
		}
		else
		*/
		if (*p == ':')
		{
			*p = 0;

			p++;
			ASSERT(*p == ':');
			p++;

			parts.InsertAt(0, part);
			part = p;
		}
		else
		{
			p++;
		}
	}
	parts.InsertAt(0, part);

	//StringBuilderA decoratedName;

#if 0
	if (pType->GetKind() == type_class)
	{
		if (pType->GetClass()->m_kwType == CLASSKEY_CLASS)
			strbuilder << "AV";
		else // CLASSKEY_STRUCT
			strbuilder << "AU";
	}
	else
	{
		ASSERT(pType->GetKind() == type_enum);
		strbuilder << "AW4";
	}
#endif

	for (int i = 0; i < parts.GetSize(); i++)
	{
		strbuilder << parts[i];
		strbuilder << '@';
	}
	strbuilder << "@";
}
#endif


#if 0
LFCEXT StringA * DecorateName(NamedType* pType, const char* & p, int & open)
{
	StringBuilderA decoratedName;

	if (pType->GetKind() == type_class)
	{
		if (pType->GetClass()->m_kwType == CLASSKEY_CLASS)
			decoratedName = "V";
		else // CLASSKEY_STRUCT
			decoratedName = "U";
	}
	else
	{
		ASSERT(pType->GetKind() == type_enum);
		decoratedName = "W4";
	}

	StringBuilderA part;

	StringBuilderA part;
	while (*p)
	{
		if (*p == '<')
		{
			StringA* subname = DecoratedName(p);
			part.Append(*p++);
			open++;
		}
		else if (*p == '>')
		{
			part.Append(*p++);
			open--;
		}
		else if (*p == ':')
		{
			p++;
			ASSERT(*p == ':');
			p++;

			if (open == 0)
			{
				parts.InsertAt(0, part.DetachToString());
			}
			else
			{
				part.Append(*p++);
			}
		}
		else
		{
			part.Append(*p++);
		}
	}
	parts.InsertAt(0, part.DetachToString());

	return decoratedName->DetachToString();
}
#endif

#if 0
LFCEXT StringA * DecorateName(StringA* qname)
{
	char buffer[4096];
	strcpy(buffer, qname->c_str());

	char* p = buffer;
	Type* pType = ParseType(p);

	if (pType)
	{
		StringBuilderA strbuilder;
		strbuilder = "??_R0?A";	// `RTTI Type Descriptor'

		MangleType(pType, strbuilder);

		strbuilder << "@@8";

		return strbuilder.ToString();//DetachToString();
	}
	return NULL;
}
#endif

#ifdef _M_IX86

extern "C"
{

LFCEXT void void_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		call func
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT void void_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		call func
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT int32 int32_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
	int32 result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov	result, eax
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT void* pointer_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
	void* result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov	result, eax
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT int32 int32_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
	int32 result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov result, eax
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT int64 int64_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
	int32 result0;
	int32 result1;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov	result0, eax
		mov	result1, edx
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result0 | ((int64)result1<<32);
}

LFCEXT int64 int64_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
	int32 result0;
	int32 result1;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov	result0, eax
		mov	result1, edx
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result0 | ((int64)result1<<32);
}

LFCEXT float float_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
	float result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		fstp dword ptr [result]
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT float float_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
	float result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		fstp dword ptr [result]
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT double double_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
	double result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		fstp qword ptr [result]
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT double double_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz)
{
	double result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		fstp qword ptr [result]
	//	add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT void* pointer_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz)
{
	void* result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

	//	mov ecx,_this
		call func
		mov result, eax
		add esp,sz

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT void struct_invoke_function_cdecl(ULONG_PTR func, const void* args, uint32 sz, void* retaddress)
{
#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack
		mov ecx, retaddress       // return value
		push ecx

	//	mov ecx,_this
		call func
		add esp,sz
		add esp,4

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT void struct_invoke_function_stdcall(ULONG_PTR func, const void* args, uint32 sz, void* retaddress)
{
#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack
		mov ecx, retaddress       // return value
		push ecx

	//	mov ecx,_this
		call func
	//	add esp,sz
	//	add esp,4

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT void struct_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz, void* retaddress)
{
	ASSERT(func != 0);
	ASSERT(func != -1);

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov ecx, sz       // get size of buffer
		mov esi, args     // get buffer
		sub esp, ecx      // allocate stack space
		mov edi, esp      // start of destination stack frame
		shr ecx, 2        // make it dwords
		rep movsd         // copy params to real stack
		mov ecx, retaddress       // return value
		push ecx

		mov ecx,_this
		call func

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT void void_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz)
{
	ASSERT(func != 0);
	ASSERT(func != ~0);

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov ecx, sz       // get size of buffer
		mov esi, args     // get buffer
		sub esp, ecx      // allocate stack space
		mov edi, esp      // start of destination stack frame
		shr ecx, 2        // make it dwords
		rep movsd         // copy params to real stack

		mov ecx,_this
		call func

		pop edi
		pop esi
		pop ecx
	}
#endif
}

LFCEXT int32 int32_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz)
{
	int result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		mov ecx,_this
		call func
		mov	result, eax

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT int64 int64_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz)
{
	int32 result0;
	int32 result1;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		mov ecx,_this
		call func
		mov	result0, eax
		mov	result1, edx

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result0 | ((int64)result1<<32);
}

LFCEXT float float_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz)
{
	float result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		mov ecx,_this
		call func
		fstp dword ptr [result]

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

LFCEXT double double_invoke_method32(ULONG_PTR func, void* _this, const void* args, uint32 sz)
{
	double result;

#ifndef __LERSTAD__
	__asm
	{
		push ecx
		push esi
		push edi

		mov   ecx, sz       // get size of buffer
		mov   esi, args     // get buffer
		sub   esp, ecx      // allocate stack space
		mov   edi, esp      // start of destination stack frame
		shr   ecx, 2        // make it dwords
		rep   movsd         // copy params to real stack

		mov ecx,_this
		call func
		fstp qword ptr [result]

		pop edi
		pop esi
		pop ecx
	}
#endif

	return result;
}

}	// extern "C"

#elif AMIGA

__asm(

"					xdef		_invoke_function				\n"
"_invoke_function:											\n"
"					link		a5,#-4							\n"	// make room for saving register a6

// save register a6
"					move.l	a6,-4(a5)						\n"

"					move.l	16(a5),a6						\n"	// args
"					move.l	20(a5),d0						\n"	// sz
"					adda.l	d0,a6								\n"	// args += sz

// copy args to stack

"					lsr		#1,d0								\n"	// words
"					bra		loop_test0						\n"
"loop0:			move.w	-(a6),-(a7)						\n"
"loop_test0:	dbra		d0,loop0							\n"

"					move.l	8(a5),a6							\n"	// function
"					jsr		(a6)								\n"	// jsr function

// restore register a6
"					move.l	-4(a5),a6						\n"

"					unlk		a5									\n"
"					rts											\n"
);

__asm(

"					xdef		_invoke_method					\n"
"_invoke_method:												\n"
"					link		a5,#-4							\n"	// make room for saving register a6

// save register a6
"					move.l	a6,-4(a5)						\n"

"					move.l	16(a5),a6						\n"	// args
"					move.l	20(a5),d0						\n"	// sz
"					adda.l	d0,a6								\n"	// args += sz

// copy args to stack
"					lsr		#1,d0								\n"	// words
"					bra		loop_test1						\n"
"loop1:															\n"
"					move.w	-(a6),-(a7)						\n"
"loop_test1:													\n"
"					dbra		d0,loop1							\n"

"					move.l	12(a5),-(a7)					\n"	// push 'this' last on stack
"					move.l	8(a5),a6							\n"	// function
"					jsr		(a6)								\n"	// jsr function

// restore register a6
"					move.l	-4(a5),a6						\n"

"					unlk		a5									\n"
"					rts											\n"
);

#endif
#endif

//map<ClassType*, Dispatch* /*, Ref_Less<StringA>*/ > m_pDispatches;
namespace gm
{
template class LFCEXT vector3<int>;
template class LFCEXT vector3<float>;
template class LFCEXT vector3<double>;
}

LFCEXT Dispatch* GetDispatch(NamespaceType* pType)
{
	ASSERT(pType);

	if (pType->m_pDispatch == NULL)
	{
		pType->m_pDispatch = new Dispatch(pType);
	}
	return pType->m_pDispatch;
}

Conv* Convert(Type* pType, Type* ArgType, int level)
{
//	VERIFY(_this);
	VERIFY(pType != NULL);
	VERIFY(ArgType != NULL);
	VERIFY(ArgType->get_Kind() == type_class);

#if 1
	String className = ArgType->AsClass()->m_name;
#else
	const char* str = ArgType->GetClass()->m_name.c_str();
	while (const char* str2 = strstr(str, "::"))
	{
		str = str2 + 2;
	}
	StringA className = str;
#endif
	/*
#else
	StringA className = "C1";
#endif
	*/

	Dispatch* dispatch = GetDispatch(ArgType->AsClass());

	vector<Conv*> convs;

	// The constructors are the methods that have the same name as the class
	auto it = dispatch->m_methodnames.find(className);

	if (it != dispatch->m_methodnames.end())
	{
		do
		{
			auto pMethod = it->second;

			DebugTraceLn("ctor with " << pMethod->m_pType->AsFunction()->m_parameters.size() << "arguments");

			if (pMethod->m_pType->AsFunction()->m_parameters.m_parameters.size() == 1)
			{
				Type* pCtorType = pMethod->m_pType->AsFunction()->m_parameters.m_parameters[0].m_pType->GetStripped();

				String ctortypestring = pCtorType->ToString();
				DebugTraceLn("constructor with 1 arg " << ctortypestring);

				/*
						StringA str0 = pType->toString();
						//StringA str1 = ArgType->m_pPointerTo->m_pClasstoString();
						StringA str2 = pCtorType->toString();
						for (int i = 0; i < level; i++)
							TRACE("\t");
						TRACE("%s -> %s(%s)\n", str0.c_str(), className.c_str(), str2.c_str());
*/
				if (pType->IsOfType((Type*)pCtorType))	// Both types must be pointers for this to succeed
				{
					DebugTrace("converter found\n");

					Conv* cnv = new Conv;
					cnv->ArgType = ArgType;
					cnv->pMethod = pMethod;
				//	cnv->_this = _this;
					convs.Add(cnv);
				}
				else
				{
					if (pCtorType->get_Kind() == type_reference/* || pCtorType->m_type == type_pointer*/)
					{
						pCtorType = pCtorType->GetPointerTo()->GetStripped();

						if (!pCtorType->Equals(*(Type*)ArgType))	// Skip constructors like: someclass(someclass& object) in order to avoid infinite recursion
						{

							{
								if (pCtorType->get_Kind() == type_class)
								{
									Conv* conv2 = Convert(/*_this,*/ pType, pCtorType, level+1);
									if (conv2)
									{
										Conv* cnv = new Conv;
										cnv->ArgType = ArgType;
										cnv->pMethod = pMethod;
									//	cnv->_this = data2;
										cnv->pConv = conv2;
										convs.Add(cnv);
									}
								}
							}
						}
					}
					else
					{
						MessageBeep(-1);
					}
				}
			}

			++it;
		}
		while ((*it).first == className);
	}

	Conv* pConv = nullptr;

	if (convs.GetSize() > 1)
	{
		String typeString = pType->ToString();

		for (uint i = 0; i < convs.GetSize(); i++)
		{
			Conv* conv = convs[i];

			if (conv->pMethod->m_pType->AsFunction()->m_parameters[0].m_pType->ToString() == typeString)
			{
				pConv = conv;
				break;
			}
		}

		if (pConv == nullptr)
		{
			MessageBoxA(NULL, "ambiguity", "", MB_OK);
		}
	}
	else if (convs.GetSize() == 1)
	{
		pConv = convs[0];

		/*
		DWORD func = conv.pMethod->m_func;

		long size = ArgType->GetClass()->get_sizeof();
		uint8* data = new uint8[size];

		void* _this = conv._this;

		__asm
		{
			push ecx
			mov ecx,data
			push _this
			call func
			pop ecx
		}

				Type* pCtorType = conv.pMethod->m_decl->m_pType->m_pFunction->m_parameters[0]->m_pType->GetType();
						StringA str0 = pType->toString();
						//StringA str1 = ArgType->m_pPointerTo->m_pClasstoString();
						StringA str2 = pCtorType->toString();
						for (int i = 0; i < level; i++)
							TRACE("\t");
						TRACE("%s -> %s(%s)\n", str0.c_str(), className.c_str(), str2.c_str());

		//delete[] _this;

		return data;
		*/
	}

	return pConv;
}

LFCEXT void* newvoidobj(ClassType* pClass) throw (SystemException*)
{
	Dispatch* pDispatch = GetDispatch(pClass);
	if (pDispatch == NULL)
	{
		raise(SystemException(L"Class has no dispatch"));
		return nullptr;
	}

	String className = pClass->m_name;

	size_t size = pClass->get_sizeof();

	DebugTraceLn("newobj: " << pClass->m_qname << ", sizeof=" << size);

	if (size > 560000)	// Sanity check
	{
	//	WCHAR buffer[512];
	//	swprintf_s(buffer, L"sizeof(%S) was -1 (unknown) or > 560000", className->c_str());

		ASSERT(0);
		VERIFY(0);
		//throw new Exception(L"sizeof(" + className + ") was -1 (unknown) or > 560000");
	}

	// Find the constructor with no parameters
	auto it = pDispatch->m_methodnames.find(className);
	if (it != pDispatch->m_methodnames.end())
	{
		Declarator* pMethod = nullptr;
		do
		{
			ASSERT(it->second->m_pType != nullptr);
			ASSERT(it->second->m_pType->AsFunction() != nullptr);

			if (it->second->m_pType->AsFunction()->m_parameters.size() == 0)
			{
				pMethod = (*it).second;
				break;
			}
			++it;
		}
		while (it->first == className);

		if (pMethod == nullptr)
		{
			raise(SystemException(L"constructor that takes no parameters not found for " + className));
			return nullptr;
		}

#if 0
		ULONG_PTR func_address = pMethod->m_decl->GetAddress();
		if (func_address == 0 || func_address == ~0)
		{
			/*
			WCHAR buffer[512];
			swprintf_s(buffer, L"constructor function address was NULL for class %S", pClass->m_qname->c_str());

			throw new Exception(new StringW(string_copy(buffer)));
			*/
			ASSERT(0);
			VERIFY(0);
		}
#endif
		byte* object = (byte*)allocate_object(size);

		pMethod->void_invoke_method(object);

		return object;
		/*
#if WIN32
		__asm
		{
			push ecx
			mov ecx,_this
			call func
			pop ecx
		}
		return object;
#else
		ASSERT(0);
#endif
		*/
	}
	else
	{
		raise(SystemException("no constructor found for " + className));

/*
		BufferImp<char> buffer;
		StringBuilderA strbuilder = StringBuilderA(&buffer);
		strbuilder << "no constructor found for " << *className;
		MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);

		multimap<StringA*, Method*, Ref_Less<StringA>, __gc_allocator>::iterator it = pDispatch->m_methodnames.begin();
		while (it != pDispatch->m_methodnames.end())
		{
			printf("%s\n", (*it).first->c_str());
			++it;
		}
*/
		ASSERT(0);
		//delete object;
		return nullptr;
	}
}

LFCEXT Object* newobj(ClassType* pClass) throw (SystemException*)
{
	VerifyArgumentNotNull(pClass);

	if (!pClass->IsLeftMostDerivedFrom((ClassType*)typeid(Object).GetType()))
	{
		IO::StringWriter str;
		str << pClass->get_QName() << " is not (leftmost) derived from System::Object";
		raise(Exception(str.str()));
	}
	
	return (Object*)newvoidobj(pClass);
}

uint32 CharacterStream::GetChar()
{
	if (m_p == (uint8*)m_data + m_bytelength)
		return -1;

	switch (m_encoding)
	{
	case Latin:
		{
			uint8 c = *m_p++;
			return c;
		}
		break;

	case Utf16:
		{
			uint32 c;

			uint16 w1 = *(const uint16*)m_p;
			m_p += 2;

			if (w1 < 0xD800 || w1 > 0xDFFF)
			{
				c = w1;
				//n = 1;
			}
			else
			{
				if (/*w1 >= 0xD800 &&*/ w1 <= 0xDBFF)
				{
					if (!AtEnd())//m_p < len-1)
					{
						uint16 w2 = *(const uint16*)m_p;
						m_p += 2;

						if (w2 >= 0xDC00 && w2 <= 0xDFFF)
						{
						//	n = 2;

							c = (((w1 & 0x3FF)<<10) | (w2 & 0x3FF)) + 0x10000;
						}
						else
							return -1;	// Error
					}
					else
						return -1;	// Error
				}
				else
					return -1;	// Error
			}

			return c;
		}
		break;

	case Utf32:
		{
			uint32 c = *(const uint32*)m_p;
			m_p += 4;
			return c;
		}
		break;

	default:
		ASSERT(0);
		return 0;
	}
}

#if 0
StringA getpart(const char * & p)
{
	VERIFY(isdigit(*p));

	int n = 0;
	while (isdigit(*p))
	{
		n *= 10;
		n += (*p - '0');
		p++;
	}

	StringA name = StringA(p, n);

	/*
	while (n--)
	{
		name = name.Append(*p);
		p++;
	}
	*/
	p += n;

	return name;
}
#endif

#if 0

void getpart(StringBuilderA & stream, const char * & p)
{
	VERIFY(isdigit(*p));

	int n = 0;
	while (isdigit(*p))
	{
		n *= 10;
		n += (*p - '0');
		p++;
	}

	while (n--)
	{
		stream << *p;
		p++;
	}
}

LFCEXT StringA* getparts(const char * p)
{
	if (*p == 'N')
	{
		p++;

		StringBuilderA name;

		while (1)
		{
			getpart(name, p);
			if (*p == 'E') break;
			name << "::";
		}

		p++;

		return name.DetachToString();
	}
	else
	{
		StringBuilderA name;
		getpart(name, p);
		return name.DetachToString();
	}
}
#endif

struct Memblock
{
#if defined(_M_X64) && defined(_MSC_VER)
	unsigned int m_nextfree : 26;
	unsigned int m_kind : 1, m_allocated : 1, m_marked : 1;
	unsigned int m_magic : 3;

	unsigned int m_pad;
#else

	unsigned int m_nextfree : 26;
	unsigned int m_kind : 1, m_allocated : 1, m_marked : 1;
	unsigned int m_magic : 3;

	void* m_extra;

#endif
};

#define BLOCK_MAGIC 0x5

extern byte* data;
extern byte* enddata;

bool Module::WithinManaged(ULONG_PTR address)
{
//	Module module;
//	module.m_hModule = (HMODULE)address;
	auto it = std::lower_bound(TypeDatabase::pD->m_hmodules.begin(), TypeDatabase::pD->m_hmodules.end(), address,
		[](Module* x, ULONG_PTR y)
		{
			return (ULONG_PTR)x->m_hModule < y;
		}
	);

	if (it != TypeDatabase::pD->m_hmodules.end())
	{
		return ((*it)->Contains(address));
	}
	else
		return false;
}

#if 0
// static
void Module::BuildRanges()
{
	ASSERT(0);
	/*
	for (auto it = TypeDatabase::pD->m_hmodules.begin(); it != TypeDatabase::pD->m_hmodules.end(); ++it)
	{
		Module* pModule = (*it);

		(ULONG_PTR)pModule->m_hModule;
		pModule->m_sizeOfImage;

		m_ranges.push_back();
	}
	*/

#if 0
	HANDLE hProcess = GetCurrentProcess();

	HMODULE hModules[1024];
	DWORD cbBytes;
	EnumProcessModules(hProcess, hModules, 1024*sizeof(HMODULE), &cbBytes);

	uint count = cbBytes / sizeof(HMODULE);

//	ULONG_PTR address;
	bool lastfound = false;

	for (size_t n = 0; n < count; ++n)
	{
		MODULEINFO mi;
		GetModuleInformation(hProcess, hModules[n], &mi, sizeof(mi));

		Module module;
		module.m_hModule = (HMODULE)mi.lpBaseOfDll;

		bool found = std::binary_search(TypeDatabase::pD->m_hmodules.begin(), TypeDatabase::pD->m_hmodules.end(),
			&module,
			[](Module* x, Module* y)
			{
				return x->GetHandle() < y->GetHandle();
			}
		);

		if (found != lastfound)
		{
			lastfound = found;
			s_ranges.push_back((ULONG_PTR)mi.lpBaseOfDll);

			if (n == 0)
			{
				m_managedfirst = true;
			}
		}
	}
#endif
}
#endif

LFCEXT ClassType* GetType(const void* obj, bool nothrow)
{
	VERIFY(obj);

#if _WIN64

	const ObjectLocator& locator = ObjectLocator::From(obj);

	ASSERT(locator.signature == 1);
	ubyte* imageBase = (ubyte*)&locator - locator->self;

	DWORD* table = (DWORD*)(imageBase + ((ClassHierarchyDescriptor*)(imageBase + locator->m_classHierarchyDescriptor))->pBaseClassArray);

	TypeDescriptor* typedesc = (TypeDescriptor*)(imageBase + ((BaseClassDescriptor*)(imageBase + table[0]))->typedesc);
	ClassType* pType = (ClassType*)(typedesc)->_m_data;
	if (pType == nullptr)
	{
		if (nothrow) return nullptr;

		Module* pModule = Module::FromHandle((HMODULE)imageBase);

		IO::StringWriter str;
		str << "In module: " << pModule->GetFullPath() << ", Type = NULL for " << typedesc->rawname;

		raise(Exception(str.str()));
	}

#elif WIN32

	const ObjectLocator& locator = ObjectLocator::From(obj);

	ASSERT(locator.signature == 0);

	ClassType* pType = (ClassType*)locator.hierarchy->pBaseClassArray[0]->typedesc->_m_data;
	if (pType == nullptr)
	{
		if (nothrow) return nullptr;

		Module* pModule = Module::FromAddress(&locator);

		IO::StringWriter str;
		str << "In module: " << pModule->GetFullPath() << ", Type = NULL for " << locator.hierarchy->pBaseClassArray[0]->typedesc->rawname;

		raise(Exception(str.str()));
	}

#elif __GNUC__

	void *vtable = *((void**)object);
	__type_info2* ti = (__type_info2*)((void**)vtable)[-1];

	ClassType* pType = *(ClassType**)(ti->__type_name - 4);
	if (pType == nullptr)
	{
		if (nothrow) return nullptr;

		ASSERT(0);
	}

#else
#error "unknown OS"
#endif

	ASSERT(pType->get_Kind() == type_class);
	return pType;
}

LFCEXT void* LeftMost(void* obj, ClassType** ppClass)
{
	if (obj == nullptr)
	{
		if (ppClass) *ppClass = nullptr;
		return nullptr;
	}

#if _WIN64

	void* vtable = *(void**)obj;
	rtti_object_locator* locator = ((rtti_object_locator**)vtable)[-1];

	ASSERT(locator->signature == 1);
	ubyte* imageBase = (ubyte*)locator - locator->self;

	ASSERT(0);
	return nullptr;

#elif _WIN32

	void* vtable = *(void**)obj;
	ObjectLocator* locator = ((ObjectLocator**)vtable)[-1];

	BaseClassDescriptor** table = locator->hierarchy->pBaseClassArray;
	ClassType* pMostDerivedType = *(ClassType**)&table[0]->typedesc->_m_data;
	if (pMostDerivedType == nullptr)
	{
		raise(Exception(String(L"LeftMost failed for ") + table[0]->typedesc->raw_name()));
	}

	if (ppClass) *ppClass = pMostDerivedType;

	return (uint8*)obj - locator->offset_to_top;
#endif

}

LFCEXT void* DynamicCast(void* obj, ClassType* /*type*/, ClassType* totype)
{
	VERIFY(totype != nullptr);

	ASSERT(totype->get_Kind() == type_class);

#if _WIN64

	ClassType* pClass = static_cast<ClassType*>(totype);

	void* vtable = *(void**)obj;
	rtti_object_locator* locator = ((rtti_object_locator**)vtable)[-1];

	ASSERT(locator->signature == 1);
	ubyte* imageBase = (ubyte*)locator - locator->self;

	/*
	if ((byte*)obj > data && (byte*)obj < enddata)
	{
		Memblock* block = (Memblock*)obj - 1;
		VERIFY(block->m_magic == BLOCK_MAGIC);
		if (block->m_imageBase == nullptr)
		{
			void* p;
			block->m_imageBase = (ubyte*)RtlPcToFileHeader(locator, &p);
		}
		imageBase = block->m_imageBase;
	}
	
	if (imageBase == nullptr)
	{
		void* p;
		imageBase = (ubyte*)RtlPcToFileHeader(locator, &p);
	}
	*/

	DWORD* table = (DWORD*)(imageBase + ((ClassHierarchyDescriptor*)(imageBase + locator->m_classHierarchyDescriptor))->pBaseClassArray);

	TypeDescriptor* typedesc = (TypeDescriptor*)(imageBase + ((BaseClassDescriptor*)(imageBase + table[0]))->typedesc);
	ClassType* pMostDerivedType = (ClassType*)(typedesc)->_m_data;
	if (pMostDerivedType == pClass)
	{
		return (uint8*)obj - locator->offset_to_top;
	}
	else
	{
		int offset = pMostDerivedType->GetOffset(pClass);
		if (offset == -1) return nullptr;

		return (uint8*)obj - locator->offset_to_top + offset;
	}

#elif _WIN32

	ClassType* pClass = static_cast<ClassType*>(totype);

	/*
	{
		Class* srctype = GetType(obj);
		ASSERT(srctype->m_qname == ((Class*)type)->m_qname);
	}
	*/

	void* vtable = *(void**)obj;
	ObjectLocator* locator = ((ObjectLocator**)vtable)[-1];
	BaseClassDescriptor** table = locator->hierarchy->pBaseClassArray;
	ClassType* pMostDerivedType = (ClassType*)table[0]->typedesc->_m_data;
	if (pMostDerivedType == nullptr)
	{
		raise(Exception(String(L"DynamicCast failed for ") + table[0]->typedesc->rawname));
	}

	if (pMostDerivedType == pClass)
	{
		return (uint8*)obj - locator->offset_to_top;
	}
	else
	{
		int offset = pMostDerivedType->GetOffset(pClass);
		if (offset == -1) return nullptr;

		return (uint8*)obj - locator->offset_to_top + offset;
	}
#if 0
	Type_Info* srctypeinfo = ((ClassType*)type)->m_pTypeInfo;
	Type_Info* dsttypeinfo = ((ClassType*)totype)->m_pTypeInfo;

	ASSERT(srctypeinfo != 0);
	ASSERT(dsttypeinfo != 0);

	void* cobj = __RTDynamicCast(obj, 0, (void*)srctypeinfo, (void*)dsttypeinfo, 0);

	if (type == totype)
	{
		ASSERT(cobj == obj);
	}

	return cobj;
#endif

#else

	ClassType* pClass = static_cast<ClassType*>(totype);

	void *vtable = *((void**)obj);
	ptrdiff_t offset_to_top = ((ptrdiff_t*)vtable)[-2];
	__type_info2* ti = (__type_info2*)((void**)vtable)[-1];
	ASSERT(offset_to_top <= 0);

	ClassType* pMostDerivedType = *(ClassType**)(ti->__type_name - 4);

	if (pMostDerivedType == pClass)
	{
		return (uint8*)obj + offset_to_top;
	}
	else
	{
		int offset = pMostDerivedType->GetOffset(pClass);
		if (offset == -1) return NULL;

		return (uint8*)obj + offset_to_top + offset;
	}

	/*
	const char* p = ti->__type_name;

	for (int i = 0; i < pMostDerivedType->m_bases.size(); i++)
	{
		if (pMostDerivedType->m_bases[i].m_pClass->GetClass() == pClass)

	}
	*/

#endif
}

}	// System

namespace System
{

extern Heap * heap;
//extern ClassType * m_pObjectClass;

#define _WSTR2(size, x)	#size x
#define _WSTR(x)	_WSTR2(sizeof(x), x)

LFCEXT void InitTypes_no_gc()
{
	return;
#if 0
	printf("InitTypes_no_gc()\n");

	/*
	{
	char* x = _WSTR("Hello");
	}
	*/

	ASSERT(pD == NULL);
	pD = new TypeDatabase;
	pD->m_debugInfo = new CVR;
	pD->m_typestuff = new TypeStuff;
	pD->m_globalNamespace = new Namespace;

	/*
	map<DWORD,DWORD> x;

	x.insert(map<DWORD,DWORD>::value_type(0, 0));
	*/
//	typeid(*x.begin());

#if WIN32

	HMODULE hModules[512];
	DWORD cbBytes;
	EnumProcessModules(GetCurrentProcess(), hModules, 512*sizeof(HMODULE), &cbBytes);

	uint count = cbBytes / sizeof(HMODULE);

	for (uint n = 0; n < count; ++n)
	{
		WCHAR filename[512];
	//	GetModuleFileName(_Module.m_hInstance, filename, 256);
		GetModuleFileNameW(hModules[n], filename, 512);

		TRACE("%S - 0x%X\n", filename, hModules[n]);

		pD->m_hmodules.push_back(hModules[n]);

		if (false)
		{
			FileStream file(filename, 1);

			COFFParser* pImage = new COFFParser;
			pImage->m_loadAddress = (ULONG)hModules[n];
			if (pImage->Read(file) >= 0)
			{
				Scope* pGlobalScope = new Scope;
				CodeViewDebugInfo* pDebugInfo = (CodeViewDebugInfo*)pImage->GetDebugInfo(NULL/*pGlobalScope*/);
				if (pDebugInfo)
				{
					/*
					TRACE("DebugInfo for %s...", filename);

					fprintf(stdout, "DebugInfo for %s...", filename);
					fflush(stdout);
					*/

					pDebugInfo->Parse(pImage, pD->m_debugInfo, n);
					pDebugInfo->Release();
				}

				//DebugSymbol* pSymbol = pDebugInfo->LookupSymbol("__imp_?get_ActualSize@Visual@UI@@UBE?AVSizeD@LDraw@@XZ");
			//	DebugSymbol* pSymbol = pDebugInfo->LookupSymbol("?get_Viewable@TextEditView@@UAEPAV_Object@@XZ");

	#if 0
				if (false)
				{
					Type* pType = pD->LookupNamedType("MetafileLoader");
					CDeclaratorReference* method = pType->m_pClass->GetDeclarator("GetRect");

					Scope* pScope = pD->LookupProc("MetafileLoader::GetRect");


					{
						DWORD func = pScope->m_startAddress;//pSymbol->m_address;
						__asm {
							call func
						}
					}
				}
	#endif
	#if 0
				pModule->size = ctx->m_pImage->windowsHeader->SizeOfImage;

				codeBase = ctx->m_pImage->windowsHeader->ImageBase + ctx->m_pImage->SectionHeader[0].VirtualAddress;

				for (int i = 0; i < ctx->m_pImage->NumberOfNameSymbols; i++)
				{
					COFFParser::SYMBOL* pSymbol = &ctx->m_pImage->NameSymbols[i];
					if (pSymbol->is->SectionNumber > 0)
					{
						IMAGE_SECTION_HEADER *pSection = &ctx->m_pImage->SectionHeader[pSymbol->is->SectionNumber-1];
						DWORD address = pSymbol->is->Value /*- pSection->VirtualAddress*/ + ctx->m_pImage->windowsHeader->ImageBase + pSection->VirtualAddress/* + pSection->Misc.PhysicalAddress*/;

						DebugSymbol* pDebugSymbol = new DebugSymbol(pSymbol->name, address);

						pModule->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));

						ctx->m_pDebugInfo->symbols.insert(tysymbolmap_address::value_type(pDebugSymbol->m_address, pDebugSymbol));
						ctx->m_pDebugInfo->symbols_name.insert(tysymbolmap_name::value_type(pDebugSymbol->m_name, pDebugSymbol));

					//	TRACE("%s - %X\n", pSymbol->name, address);

						if (!strcmp(pSymbol->name, ".text"))
						{
						//	MessageBeep(-1);
						}
					}
				}
	#endif

				/*
				int numberOfSymbols = pImage->GetNumberOfSymbols();

				for (int i = 0; i  < numberOfSymbols; i++)
				{
				}
				*/
		//		nlist* stab = NULL;
		//		int nstabs = 0;
		//		char* stabstr = NULL;
			
			//	FromStab(ctx);
			//	FromCV(ctx);
			}
			delete pImage;
		}
	}
#endif // WIN32

	return;

#if 0
	Linker linker;
#if WIN32
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/ncrt0.o"));
	//linker.m_files.push_back(new StringA("C:/MMStudio/Amiga68k/main.o"));
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/OBJ/Browser/Browser.o"));
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/libui.a"));
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/libdraw.a"));
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/libxmlparse.a"));
	linker.m_files.push_back(ASTR("C:/MMStudio/Amiga68k/liblfc.a"));
	linker.m_files.push_back(ASTR("C:/cygwin/usr/local/amiga/lib/gcc/m68k-amigaos/3.4.0/libgcc.a"));
	linker.m_files.push_back(ASTR("C:/cygwin/usr/local/amiga/m68k-amigaos/lib/libstdc++.a"));
	linker.m_files.push_back(ASTR("C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnix.a"));
	linker.m_files.push_back(ASTR("C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnixmain.a"));
	linker.m_files.push_back(ASTR("C:/cygwin/home/Sigurd Lerstad/lib/libnix/libstubs.a"));
#else
	linker.m_files.push_back(new StringA("WinHD_C:/MMStudio/Amiga68k/ncrt0.o"));
	linker.m_files.push_back(new StringA("WINHD_C:/MMStudio/Amiga68k/main.o"));
	linker.m_files.push_back(new StringA("WINHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnix.a"));
	linker.m_files.push_back(new StringA("WINHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libnixmain.a"));
	linker.m_files.push_back(new StringA("WinHD_C:/cygwin/home/Sigurd Lerstad/lib/libnix/libstubs.a"));
#endif

	linker.pass1();

/*
	GlobalSymbol* pSymbol = linker.m_globsyms[new StringA("_main")];
	pSymbol->m_defined = true;
	pSymbol->ResolvedValue = (DWORD)MyMain;
*/
//	linker.AddSymbol(new StringA("_main"), (DWORD)MyMain);

#if 0
	linker.LoadObjectFile(linker.m_objectFiles[0]);

	TRACE("\n\n");
	{
		for (int i = 0; i < linker.m_loadedObjectFiles.size(); i++)
		{
			OFile2* ofile = linker.m_loadedObjectFiles[i];

			if (ofile->m_afilename)
				TRACE("%s:%s\n", ofile->m_afilename->c_str(), ofile->m_ofilename->c_str());
			else
				TRACE("%s\n", ofile->m_ofilename->c_str());
		}
	}
#endif

	linker.sets();

	OFile* pOFile = linker.LoadObjectFile2(linker.m_objectFiles[0]);
/*
	{
		GlobalSymbol* psym = linker.m_globsyms[new StringA("_DOSBase")];
		int x = *(long*)psym->ResolvedValue;
	}
*/
	printf("done\n");

	if (linker.m_undefinedReferenceCount)
	{
		printf("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
		TRACE("undefined reference count: %d\n", linker.m_undefinedReferenceCount);
	}
	else
	{
	#if AMIGA

		printf("Calling");

		char* line = strdup("programname parameter0 parameter1");
		entrypoint_hook(pOFile->m_textdata, line, strlen(line));
	#endif
	}

#if 1

#if 0
	{
		AOutParser* pParser = new AOutParser;
		FileByteStream* file = new FileByteStream(new StringA("C:/MMStudio/Amiga68k/obj/Browser/Browser.o"));
		pParser->Read(file);
		file->Close();
	}

	AmigaHunkParser* pHunkParser = new AmigaHunkParser;
	{
		FileByteStream* file = new FileByteStream(new StringA("C:/MMStudio/Amiga68k/Browser"));
		pHunkParser->Read(file);
		file->Close();
	}

	map<StringA*, DWORD, Ref_Less<StringA> > symbols;

	int nsymbols = pHunkParser->GetNumberOfSymbols();

	for (int i = 0; i < nsymbols; i++)
	{
		ObjectSymbol* pSymbol = pHunkParser->GetSymbol(i);

		if (strstr(pSymbol->n_name, "System") && strstr(pSymbol->n_name, "Object"))
		{
		//	MessageBeep(-1);
		}

		if (strstr(pSymbol->n_name, "red_black_node"))
		{
		//	MessageBeep(-1);
		}

		symbols.insert(map<StringA*,DWORD, Ref_Less<StringA> >::value_type(new StringA(pSymbol->n_name), pSymbol->n_value));

	//	TRACE("%s %d\n", pSymbol->n_name, pSymbol->n_value);
	}
#endif

//	map<StringA,DWORD>::iterator it = symbols.find("__ZN4TestC1Ev");
	/*
	map<StringA*,DWORD>::iterator it = symbols.find("__Z9InitTypesv");

	load_offset = (DWORD)InitTypes - (*it).second;

	if (it != symbols.end())
	{
		printf("yopp\n");
	}
	else
	{
		printf("nope\n");
	}
	*/

#if 0
	if (pHunkParser->stab)
	{
		Scope* pGlobalScope = new Scope;

		StabDebugInfo* pDebugInfo = (StabDebugInfo*)pHunkParser->GetDebugInfo(pGlobalScope);
		if (pDebugInfo)
		{
			pDebugInfo->FromStab(0/*offaddr*/, pHunkParser->stab, pHunkParser->nstabs, pD);
			pDebugInfo->Release();
		}
	}
#endif

#if 0
	if (false)
	{
		TypeArchive* ar = new TypeArchive(TypeArchive::Mode_Load, new FileByteStream(new StringA("C:/mmstudio/win32/bin/test.typeinfo"), FileMode_Read));

		int ntypes;
		*ar >> ntypes;

		printf("%d\n", ntypes);

		for (int i = 0; i < ntypes; i++)
		{
			NamedType* pType;
			*ar >> pType;

			{
				StringBuilderA strbuilder;
				pType->Write(strbuilder);
				pType->m_qname = strbuilder.DetachToString();

				if (strstr(pType->m_qname->c_str(), "StringT"))
				{
				//	MessageBeep(-1);
				}
			}

			if (pType->m_qname)
			{
				BufferImp<char> buffer;
				StringBuilderA strbuilder = StringBuilderA(&buffer);
				strbuilder = "__Z";

				strbuilder << "TI";	// type info

				Mangler mangler;
				mangler.MangleType(pType, strbuilder);

				StringA* name = buffer.DetachToString();

				gsymmap_t::iterator it2 = linker.m_globsyms.find(name);
				//map<StringA*, DWORD, Ref_Less<StringA> >::iterator it2 = symbols.find(name);
				if (it2 != linker.m_globsyms.end())
				{
					TRACE("\n");

#if AMIGA
						/*
						__type_info2* ti = (*it).second;
						int len = strlen(ti->__type_name);
						char* newname = malloc(len+1+4);
						strcpy(newname+4, ti->__type_name);
						ti->__type_name = newname+4;
						*(Type**)newname = pType;
						*/
#endif
#if 0
					TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;

					//VERIFY(typedesc->_m_data == NULL);

					if (pType->GetKind() == type_class)
					{
						((ClassType*)pType)->m_typedesc = (Type_Info*)typedesc;
					}
					else if (pType->GetKind() == type_enum)
					{
						((EnumType*)pType)->m_typedesc = (Type_Info*)typedesc;
					}

					typedesc->_m_data = pType2;

					AddPersistentLiveRoot((Object**)&typedesc->_m_data);
#endif
				}
				else
				{
				//	TRACE("not found %s\n", name->c_str());
				}
			}
		}

//		map<StringA,DWORD>::iterator it = symbols.find("__some_name");

		{
			multimap<StringA*, DWORD, Ref_Less<StringA>, __gc_allocator>::iterator it = pD->m_symbols.find(new StringA("__ZN6System9InitTypesEv"));
			if (it == pD->m_symbols.end())
			{
				printf("__Z6System9InitTypesv not found in symbols\n");
				exit(10);
			}

#if 0
			load_offset = (DWORD)InitTypes - (*it).second;

			printf("load_offset=%d\n", load_offset);
#endif
		}
	}
#endif
		/*
	//	map<StringA,DWORD>::iterator it = symbols.find("__ZN4TestC1Ev");
		map<StringA,DWORD>::iterator it = symbols.find("__Z5TestFv");
		if (it != symbols.end())
		{
			DWORD address = load_offset + (*it).second;

			long result;

			__asm("\tjsr		(%1)\n"
					"\tmove.l	d0,%0\n"

					: "=r"(result)
					: "a"(address)
					: "d0","d1","a0","a1"
					);

			printf("result: %d", result);
		}
		else
		{
			printf("nope\n");
		}
		*/

#if 0
		{
			ClassType* pClass = pD->LookupNamedType("TestNamespace::Test2")->GetClass();
			ASSERT(pClass);
			Dispatch* pdisp = GetDispatch(pClass);

			//Test* test = (Test*)newobj(pClass);
			TestNamespace::Test2* test = new TestNamespace::Test2;

			/*
			void *vtable = *((void**)test);

			ptrdiff_t offset_to_top = ((ptrdiff_t*)vtable)[-2];
			__type_info2* ti = (__type_info2*)((void**)vtable)[-1];

			printf("%d, %s\n", offset_to_top, ti->__type_name);
			*/

		//	__dynamic_cast(NULL, NULL, NULL, -1/*no hint*/);

			/*
			{
				Class* pClass = GetType(test);

				printf("%s\n", pClass->m_name.c_str());
			}

			printf("%d\n", pClass->get_sizeof());

			printf("%d\n", sizeof(TestNamespace::Test2));
			*/


			/*
			{
				propertymap_t properties;
				GetProperties(*pdisp, properties);

				Property* pProperty = properties.find("Testing")->second;

				int value[4] = {75};
				pdisp->Invoke(test, pProperty->put_method, value, 4*4);

				pdisp->Invoke(test, pProperty->get_method, NULL, 0);
			}
			*/

			{
				propertymap_t properties;
				GetProperties(*pdisp, properties);

				Property* pProperty = properties.find("data")->second;

				TestNamespace::data dat;
				pdisp->Invoke(test, pProperty->put_method, &dat, sizeof(TestNamespace::data));

			//	pdisp->Invoke(test, pProperty->get_method, NULL, 0);
			}

			/*
			{
				const Method* method = pdisp->GetMethod("virt_func3");
				ASSERT(method);
				printf("%d\n", method->m_decl->m_offset);
				printf("%s\n", method->m_class->m_name.c_str());

				pdisp->Invoke(test, method, NULL, 0);
			}
			*/

			/*
			{
				const Method* method = pdisp->GetMethod("virt_func3");
				ASSERT(method);
				printf("%d\n", method->m_class->m_name);
				printf("%d\n", method->m_decl->m_offset);

				pdisp->Invoke(test, method, NULL, 0);
			}
			*/

		//	DynamicCast

		//	propertymap_t::iterator propertyit = properties.find("virt_func");
		//	ASSERT(propertyit != properties.end());

			/*
			int param = 7;
			pdisp->Invoke(test, (*propertyit).second->put_method, &param, 4);

			pdisp->Invoke(test, (*propertyit).second->get_method, NULL, 0);
			*/
		}
#endif
#endif
#endif
#endif
}

//#undef new

int CountBases(ClassType* pType)
{
	int n = 0;

	n += pType->m_bases.size();

	for (uint i = 0; i < pType->m_bases.size(); ++i)
	{
		BaseClass* baseclass = pType->m_bases[i];

		n += CountBases(baseclass->m_pClass->AsClass());
	}

	return n;
}

/*
LFCEXT char* strcpy(char* d, String str)
{
	CString(d, str);
	return d;
}

LFCEXT WCHAR* strcpy(WCHAR* d, String str)
{
	CStringw(d, str);

	return d;
}
*/

map<Type*,TypeDescriptor*> g_typeTypeInfo;

TypeDescriptor* CreateTypeInfo(ClassType* pType)
{
	IO::StringWriter strbuilder;
//	strbuilder << "??_R0?A";	// `RTTI Type Descriptor'

	strbuilder << ".?A";

	VCMangler mangler;
	mangler.m_n++;
	mangler.MangleType(pType, strbuilder);
	//strbuilder << "@8";

	String str = strbuilder.str();

	TypeDescriptor* ti = (TypeDescriptor*)new uint8[sizeof(TypeDescriptor) + str.GetLength()+1];
//	new (ti) type_info;
	ti->vtable = NULL;	// TODO
	ti->_m_data = pType;
	ASSERT(0);
//	CString(ti->rawname, str.GetLength()+1) = str;

	return ti;
}

TypeDescriptor* GetTypeInfo(ClassType* pType)
{
	TypeDescriptor* ti = g_typeTypeInfo[pType];
	if (ti == NULL)
	{
		ti = CreateTypeInfo(pType);
		g_typeTypeInfo[pType] = ti;
	}

	return ti;
}

void fillbase(BaseClassDescriptor** & p, ClassType* pType, long offset)
{
	(*p) = new BaseClassDescriptor;

#ifdef _WIN64
	ASSERT(0);
#else
	(*p)->typedesc = GetTypeInfo(pType);
#endif
	(*p)->base_offset = offset;
	(*p)->nbases = CountBases(pType);
//	(*p)->flags = -1;	// ??
	++p;

	for (uint i = 0; i < pType->m_bases.size(); ++i)
	{
		BaseClass* baseclass = pType->m_bases[i];

		//p = new BaseClassDescriptor;
		fillbase(p, baseclass->m_pClass->AsClass(), offset + baseclass->m_offset);

		/*
		ASSERT(baseclass->m_pClass->GetClass()->m_pTypeInfo);
		base->typedesc = (TypeDescriptor*)baseclass->m_pClass->GetClass()->m_pTypeInfo;
		base->base_offset = baseclass->m_offset;
		base->num_bases = baseclass->m_pClass->GetClass()->m_bases.size();	// TODO all or just direct ??
		base->flags = -1;	// ??
		base->unknown0 = 0;	// ??
		base->unknown1 = 0;	// ??

		hier_descr->m_baseClassArray[i] = base;
		*/
	}

}

#if 0
LFCEXT rtti_object_locator* Build_rtti(ClassType* pType)
{
	TypeDescriptor* ti = GetTypeInfo(pType);

	ClassHierarchyDescriptor* hier_descr = new ClassHierarchyDescriptor;
	hier_descr->signature = 0;
	hier_descr->attributes = 0;
	hier_descr->count = 1 + CountBases(pType);

	// Primary vtable
	rtti_object_locator* objloc = new rtti_object_locator;
	objloc->signature = 0;
	objloc->offset_to_top = 0;
	objloc->cdOffset = 0;
	objloc->typeinfo = ti;
	objloc->m_classHierarchyDescriptor = hier_descr;

	hier_descr->m_baseClassArray = new BaseClassDescriptor*[hier_descr->count];

	BaseClassDescriptor** p = hier_descr->m_baseClassArray;
	fillbase(p, pType, 0);
	/*
	for (int i = 0; i < pType->m_bases.size(); i++)
	{
		BaseClass* baseclass = pType->m_bases[i];

		BaseClassDescriptor* base = new BaseClassDescriptor;

		ASSERT(baseclass->m_pClass->GetClass()->m_pTypeInfo);
		base->typedesc = (TypeDescriptor*)baseclass->m_pClass->GetClass()->m_pTypeInfo;
		base->base_offset = baseclass->m_offset;
		base->num_bases = baseclass->m_pClass->GetClass()->m_bases.size();	// TODO all or just direct ??
		base->flags = -1;	// ??
		base->unknown0 = 0;	// ??
		base->unknown1 = 0;	// ??

		hier_descr->m_baseClassArray[i] = base;
	}
	*/

	for (uint i = 0; i < pType->m_bases.size(); ++i)
	{
		// TODO, some of these share vtable

		rtti_object_locator objloc;
		objloc.offset_to_top = pType->m_bases[i]->m_offset;
		objloc.typeinfo = ti;
		objloc.m_classHierarchyDescriptor = hier_descr;

		//ClassType* pBaseClass
	}

	/*
	void** vtable = new void*[pType->m_virtualSize/4];

	vtable[-1] = objloc;

	//obj

	return vtable;
	*/

	return objloc;
}
#endif

/*
class polymorphic2
{
public:
	virtual int method(char* arg);
};
*/

extern"C" int __cdecl cdecl_method_this(void* _this, Declarator* method, char* args);

#ifndef _M_X64

static void __declspec(naked) cdecl_method()
{
	__asm
	{
	//	lea eax,dword ptr[esp+8]
	//	push eax

		lea eax,dword ptr[esp+4]
		push eax

		push 0x80000000	// placeholder for method (force dword)
		push ecx	// this
		mov eax,cdecl_method_this
		call eax
		ret
	}
}

template<int stacksize> static void __declspec(naked) stdcall_method()
{
	__asm
	{
		lea eax,dword ptr[esp+12]
		push eax
		push 0x80000000	// placeholder for method (force dword)
		push ecx	// this
		mov eax,cdecl_method_this
		call eax
		add esp,stacksize+4
		ret
	}
}

#endif

LFCEXT void** build_proxy_vtable(ClassType* pType)
{
	void** vtable_ = new void*[pType->m_virtualSize/sizeof(void*) + 1];

	void** vtable = &vtable_[1];

	//uint8* code = VirtualAlloc(

	Dispatch* pDispatch = GetDispatch(pType);

	auto it = pDispatch->m_methodnames.begin();
	while (it != pDispatch->m_methodnames.end())
	{
		Declarator* pMethod = (*it).second;
		++it;

		if (pMethod->m_virtual)
		{
			int size = 64;	// TODO
			uint8* function = (uint8*)GlobalAlloc(0, size);
			//void* src = cdecl_method;
			ASSERT(0);
			//memcpy(function, cdecl_method, size);
		//	*(Method**)(function+1) = pMethod;
			*(Declarator**)(function+6) = pMethod;

			LONG_PTR offset = pMethod->m_offset/sizeof(void*);

			vtable[offset] = function;
		}
	}

	return vtable;
}

struct polymorphic_object
{
	void** vtable;
};

#if 0
class TestObject : public System::Object
{
public:

	virtual void handleMouseEvent(System::Event* evt);
};

void TestObject::handleMouseEvent(System::Event* evt)
{
	MessageBeep(-1);
}
#endif

LFCEXT void InitTypes()
{
	return;
#if 0
#if 0
	{
		TestObject* me = new TestObject;

		Test::Window* window = new Test::Window;
		window->mouseDown += EventHandler<System::Event*>(me, me->handleMouseEvent);	// set event handler
	//	window->mouseDown = EventHandlerT<TestObject>(me, me->handleMouseEvent);	// set event handler
	//	window->mouseDownEvent += EventHandlerT<TestObject>(me, me->handleMouseEvent);	// add event handler
	//	window->mouseDownEvent -= EventHandlerT<TestObject>(me, me->handleMouseEvent);	// remove event handler
		//window->mouseDownEvent & EventHandlerT<TestObject>(me, me->handleMouseEvent);	// is event handler registered

		if (window->mouseDown == NULL)	// Is empty
		{
		}

		if (window->mouseDown != NULL)	// Is not empty
		{
		}
	}
#endif

	DebugTrace("InitTypes()\n");
	InitTypes_no_gc();

	if (true)
	{
	//	TypeStuff* typestuff = new TypeStuff;
	//	Namespace* pGlobalNamespace = new Namespace;

		for (uint i = 0; i < pD->m_hmodules.size(); i++)
		{
			HINSTANCE hModule = pD->m_hmodules[i];

			LoadTypes(&_Module, hModule);

#if 0
				FILE* fp = fopen(adfilename, "rb");
				if (fp)
				{
					uint ntypelibs;
					ar >> ntypelibs;
					{
						for (uint i = 0; i < ntypelibs; i++)
						{
							TypeLibImport* typelib;
							ar >> typelib;
						}
					}

					Namespace* pGlobalNamespace;
					ar >> pGlobalNamespace;

					int ntypes;
					ar >> ntypes;

				//	vector<NamedType*> alltypes;
				//	alltypes.resize(ntypes);

					for (int i = 0; i < ntypes; i++)
					{
						NamedType* pType;
						ar >> pType;

						map<StringA*, NamedType*, Ref_Less<StringA>, __gc_allocator>::iterator it = pD->m_namedTypes.find(pType->m_qname);
						if (it == pD->m_namedTypes.end())
						{
							pD->m_namedTypes.insert(map<StringA*, NamedType*, Ref_Less<StringA>, __gc_allocator>::value_type(pType->m_qname, pType));
						}
						else
						{
							pType = (*it).second;
						}

						/*
						if (*pType->m_qname == "System::UI::Brush")
						{
							MessageBeep(-1);
						}
						*/

					//	alltypes[i] = pType;

						ULONG_PTR rtti_address;
						fread(&rtti_address, 1, sizeof(ULONG_PTR), fp);

						if (pType->get_Kind() == type_typedef)
						{
							pType->m_pTypeInfo = ((Typedef*)pType)->m_pType->m_pTypeInfo;
						}
						else
						{
							if (rtti_address != 0)
							{
								TypeDescriptor* typedesc = (TypeDescriptor*)((ULONG_PTR)hModule + rtti_address);

								pType->m_pTypeInfo = (Type_Info*)typedesc;
								typedesc->_m_data = pType;
								AddPersistentLiveRoot((Object**)&typedesc->_m_data);
							}
						}
					}

					/*
					{
						for (int i = 0; i < ntypes; i++)
						{
							ULONG_PTR rtti_address;
							ar >> rtti_address;

							if (rtti_address != 0)
							{
								TypeDescriptor* typdesc = (TypeDescriptor*)((ULONG_PTR)_Module.m_hInstance + rtti_address);
							}
						}
					}
					*/
					fclose(fp);
				}
#endif
		}
	}

#if WIN32
	if (false)
	{
		multimap<String, ULONG_PTR>::iterator it2 = pD->m_debugInfo->m_symbols.begin();
		//d(new StringA("TestEnum"));
		while (it2 != pD->m_debugInfo->m_symbols.end())
		{
			String str = (*it2).first;

		//	if (strstr(str->c_str(), ".?AVtype_info@@"))
		//	if (strstr(str->c_str(), "AVtype_info"))

#if 0
		//	if (strstr(str->c_str(), "AVDependencyProperty@UI@System@@"
			if (strstr(str->c_str(), "AVDependencyProperty@UI@System"))

		//	if (strstr(str->c_str(), "IAddChild"))
		//	if (strstr(str->c_str(), "IAddChild"))
		//	if (strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "StringA") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "StringT") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "red_black_node") && !strstr(str->c_str(), "NamedType") && strstr(str->c_str(), "StringT") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "FontFamilyStyles") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "list_node") && strstr(str->c_str(), "TreeItem") && strstr(str->c_str(), "??_R0?"))

		//	if (strstr(str->c_str(), "TestInner") && strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "Type") && strstr(str->c_str(), "PointerType") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "red_black_nodetest2") && strstr(str->c_str(), "Type") && strstr(str->c_str(), "PointerType") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "Type") && strstr(str->c_str(), "PointerType") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "FontFamilyStyles") && strstr(str->c_str(), "??_R0?"))
		//	if (strstr(str->c_str(), "ArrayBase") && strstr(str->c_str(), "?0"))
		//	if (strstr(str->c_str(), "NewObject") && strstr(str->c_str(), "JNINativeInterface"))
		//	if (strstr(str->c_str(), "NewDocument") && strstr(str->c_str(), "CEDocument"))
		//	if (strstr(str->c_str(), "GetModified") && strstr(str->c_str(), "CEDocument"))
		//	if (strstr(str->c_str(), "WndProc") && strstr(str->c_str(), "WindowImpl") && strstr(str->c_str(), "Hwnd"))
		//	if (strstr(str->c_str(), "??0Object") && strstr(str->c_str(), "Object@System") && !strstr(str->c_str(), "vector"))
		//	if (strstr(str->c_str(), "?set_Name") && strstr(str->c_str(), "Visual"))
			{
				void* k = (void*)(*it2).second;

//+	m_str	0x11cd3948 "?set_Name@Visual@UI@System@@QAEXPAV?$StringT@GV__gc_allocator@System@@@3@@Z"

//+	m_str	0x10d04ee8 "??0Object@System@@QAE@ABV01@@Z"

//+	m_str	0x119c6da0 "?WndProc@WindowImpl@MSWindows@System@@KGJVHwnd@23@IIJ@Z"

//+	m_str	0x123f23d0 "?NewDocument@CEDocument@@QAGJXZ"

// +	m_str	0x120cf350 "?NewObject@JNINativeInterface@JavaVM@System@@UAAPAXPAXJZZ"

// +	m_str	0x10ca4660 "??0ArrayBase@@QAE@XZ"

// +	m_str	0x10cb01b8 "?GetSize@ArrayBase@@QBEIXZ"


// +	m_str	0x1127c6b8 "??_R0?AV?$red_black_node@PAV?$StringT@GV__gc_allocator@System@@@System@@PAVFontFamilyStyles@LDraw@2@@System@@@8"

// +	m_str	0x118f2020 "??_R0?AV?$red_black_nodetest2@PAVType@System@@PAVPointerType@2@@@@8"

// + m_str	0x118c4198 "??_R0?AV?$red_black_node@PAVType@System@@PAVPointerType@2@@System@@@8"

// +	m_str	0x1253c09c "??_R0?AV?$red_black_nodePAVStringA@System@@PA12@@@8"

// +	m_str	0x11506d74 "??_R0?AV?$red_black_node@PAVStringA@System@@PAV12@@@@8"

// +	m_str	0x02a55d8c "??_R0?AV?$babbla@V?$babt@D@@V1@@@@8"
//+	m_str	0x02a453a4 "??_R0?AV?$babbla@V?$babt@D@@V?$babt@H@@V1@@@@8"
//+	m_str	0x02a2c278 "??_R0?AV?$babbla@VObject@System@@V?$babt@D@@V3@@@@8"
//+	m_str	0x02a69d78 "??_R0?AV?$babbla@PAV?$StringT@DV__gc_allocator@System@@@System@@V?$babt@D@@PAV12@@@@8"
				TypeDescriptor* typdesc = (TypeDescriptor*)k;
			//	MessageBeep(-1);
			}
#endif
			++it2;
		}
	}
#endif

#if WIN32

	{
#if 1
		ULONG heapsize = heap->m_next - (heap->m_data);
#else
		gc();
		ULONG heapsize = heap->m_next - (heap->m_data+heap->m_size);
#endif

		if (false)
		{
		char buf[256];
		sprintf_s(buf, "heapsize: %f MB", heapsize / (1024.0*1024));
		MessageBoxA(NULL, buf, "", MB_OK);
		}
	}

	vector<NamedType*> alltypes;
	alltypes.reserve(pD->m_namedTypes.size());

	{
		map<String, NamedType*>::iterator it = pD->m_namedTypes.begin();
		while (it != pD->m_namedTypes.end())
		{
			/*
			const char* str = (*it).first->c_str();
			if (strstr(str, "vector"))
			{
				MessageBeep(-1);
			}
			*/
			alltypes.push_back((*it).second);
			++it;
		}
	}

		TRACE("************************************\n\n\n");

		FILE* tfile;
		fopen_s(&tfile, "C:/mmstudio/Template.html", "r");

		{
#if 0
		//	TypeArchive ar(TypeArchive::Mode_Load, new System::IO::FileByteStream(new StringA("C:/mmstudio/win32/bin/test.typeinfo"), System::IO::FileMode_Read));
			TypeArchive ar(TypeArchive::Mode_Load, new System::IO::FileByteStream(new StringA("C:/mmstudio/win32/bin/Debug/Browser.typeinfo"), System::IO::FileMode_Read));

			uint ntypelibs;
			ar >> ntypelibs;
			{
				for (uint i = 0; i < ntypelibs; i++)
				{
					TypeLib* typelib;
					ar >> typelib;
				}
			}

			Namespace* pGlobalNamespace;
			ar >> pGlobalNamespace;

			uint ntypes;
			ar >> ntypes;

	//		doc = new XmlData::Document;

			vector<NamedType*> alltypes;

			alltypes.reserve(ntypes);

			printf("%d\n", ntypes);

			for (uint i = 0; i < ntypes; i++)
			{
				NamedType* pType;
				ar >> pType;

				alltypes.push_back(pType);

				// TODO, this is not necessary
				{
					BufferImp<char> buffer;
					StringBuilderA strbuilder = StringBuilderA(&buffer);
					pType->Write(strbuilder);
					StringA* qname = buffer.DetachToString();
					ASSERT(*pType->m_qname == *qname);

					TRACE("%s", pType->m_qname->c_str());

					TRACE("\n");
				}

				if (pType->m_qname)
				{
	#if 0
					TRACE("%s\n", pType->m_qname->c_str());

					if (strstr(pType->m_qname->c_str(), "red_black_node")/* &&
						strstr(pType->m_qname->c_str(), "ClassType")*/)
					{
						MessageBeep(-1);
					}

					if (!strcmp(pType->m_qname->c_str(), "red_black_node<System::StringA *,System::StringA *>"))
					{
						MessageBeep(-1);
					}

					if (strstr(pType->m_qname->c_str(), "DockEnum"))
					{
						MessageBeep(-1);
					}
	#endif
		#if 0
					if (pType->get_Kind() == type_class)
					{
						ClassType* pClass = pType->GetClass();
						MakeGCMembers(pClass/*most derived*/, pClass, 0);
					}
		#endif
	// "red_black_node<System::StringT<char,System::__gc_allocator> *,System::NamedType *>"

						BufferImp<char> buffer;
						StringBuilderA strbuilder = StringBuilderA(&buffer);
						strbuilder << "??_R0?A";	// `RTTI Type Descriptor'

						/*
						if (strstr(pType->GetQName()->c_str(), "red_black_node") &&
							strstr(pType->GetQName()->c_str(), "FontFamilyStyles"))
						{
	// "??_R0?AV?$red_black_node@PAV?$StringT@GV__gc_allocator@System@@@System@@PAVFontFamilyStyles@LDraw@@@@@8"

							MessageBeep(-1);
						}
						*/

#if 0
					if (strstr(pType->m_qname->c_str(), "type_info"))
					{
						MessageBeep(-1);
					}

					if (strstr(pType->m_qname->c_str(), "red_black_nodetest2") &&
						strstr(pType->m_qname->c_str(), "Type") &&
						strstr(pType->m_qname->c_str(), "PointerType"))
					{
						MessageBeep(-1);
					}

					if (strstr(pType->m_qname->c_str(), "red_black_node") &&
						strstr(pType->m_qname->c_str(), "FontFamilyStyles")/* &&
						strstr(pType->m_qname->c_str(), "StringT")*/)
					{
						MessageBeep(-1);
					}
#endif
// +	m_str	0x12907420 "System::map<System::StringT<unsigned short,System::__gc_allocator> *,System::LDraw::FontFamilyStyles *,System::Ref_Less<System::StringT<unsigned short,System::__gc_allocator> >,System::__gc_allocator>"

// +	p3	0x102e107c const System::red_black_node<class System::StringT<unsigned short,class System::__gc_allocator> *,class System::LDraw::FontFamilyStyles *>::`RTTI Complete Object Locator'

					VCMangler mangler;
					mangler.m_n++;

					mangler.MangleType(pType, strbuilder);
					strbuilder << "@8";

#if 0
					map<StringA*, NamedType*, Ref_Less<StringA> >::iterator it = pD->m_namedTypes.find(pType->get_QName());

					if (it != pD->m_namedTypes.end())
					{
						NamedType* pType2 = (*it).second;

						/*
						if (!pType2->Equals(*pType))
						{
							MessageBeep(-1);
							pType2->Equals(*pType);
						}
						*/

						(*it).second = pType;
					}
					else
					{
						pD->m_namedTypes.insert(map<StringA*, NamedType*, Ref_Less<StringA> >::value_type(pType->get_QName(), pType));
					}
#endif

					/*
					NamedType* pType2 = pD->LookupNamedType(pType->get_QName());
					if (pType2)
					{
					}
					*/

					NamedType* pType2 = pType;
#if 0
					pType2 = pType;

						/*
						*/

					pType2->m_name = pType->m_name;
					pType2->m_pOwnerScope = pType->m_pOwnerScope;
					if (pType2->GetClass())
					{
						pType2->GetClass()->m_pInstantiatedFromClass = pType->GetClass()->m_pInstantiatedFromClass;
						pType2->GetClass()->m_pInstantiatedFrom = pType->AsClass()->m_pInstantiatedFrom;
						pType2->GetClass()->m_pScope->m_pParentScope = pType->GetClass()->m_pOwnerScope;
					}
#endif

					/*
					StringBuilderA strbuilder;
					strbuilder = "??_R0?A";	// `RTTI Type Descriptor'

					VCMangler mangler;
					mangler.MangleType(pType, strbuilder);
					strbuilder << "@8";
					*/

					StringA* name = buffer.DetachToString();

			//		TRACE("%s", pType->get_QName()->c_str());

					if (pType->get_Kind() != type_typedef)
					{	// +	m_str	0x12913da8 "??_R0?AV?$red_black_node@PAV?$StringT@GV__gc_allocator@System@@@System@@PAVFontFamilyStyles@LDraw@1@@System@@@8"
						multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::iterator it2 = pD->m_symbols.find(name);
						if (it2 != pD->m_symbols.end())
						{
							TRACE("-------------- %s", name->c_str());

							do
							{
								TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;

								// done above
								if (false)
								{
									pType2->m_pTypeInfo = (Type_Info*)typedesc;
									typedesc->_m_data = pType2;
									AddPersistentLiveRoot((Object**)&typedesc->_m_data);
								}

								++it2;
							}
							while (*(*it2).first == *name);
						}
					}
					else //if (pType->get_Kind() == type_typedef)
					{
						Typedef* pTypedef = (Typedef*)pType;

						// done above
						if (false)
						{
						//	ASSERT(pTypedef->m_pType->m_pTypeInfo);
							pTypedef->m_pTypeInfo = pTypedef->m_pType->m_pTypeInfo;
						}
					}

					TRACE("\n");
				}
				else
				{
					//TRACE("%s not found\n", pType->GetQName()->c_str());
				}

				/*
				if (pType->m_qname->Length())
				{
				//	pD->OnType(pType->m_qname, pType, 0);
				}
				*/
				
			}
#endif

			if (false)
			{
				ULONG heapsize = heap->m_next - (heap->m_data);
				char buf[256];
				sprintf_s(buf, "heapsize: %f MB", heapsize / (1024.0*1024));
				MessageBoxA(NULL, buf, "", MB_OK);
			}

			if (pD->m_debugInfo)
			{
				CVR* debugInfo = pD->m_debugInfo;
				for (uint i = 0; i < alltypes.size(); ++i)
				{
					NamedType* pType = alltypes[i];
					if (pType->GetStripped() == NULL)
					{
						continue;	// hmm..
					}

					if (pType->get_sizeof() != -1)
					{
						map<String, NamedType*>::iterator it = debugInfo->m_namedTypes.find(pType->get_QName());

						if (it != debugInfo->m_namedTypes.end())
						{
							NamedType* pType2 = (*it).second;

						//NamedType* pType2 = pD->LookupNamedType(pType->get_QName());
						//if (pType2)
							ASSERT(0);
#if 0
							if (!pType2->Equals(*pType))
							{
								MessageBeep(-1);
								pType2->Equals(*pType);
							}
#endif
						//	(*it).second = pType;
						}
						/*
						else
						{
							pD->m_namedTypes.insert(map<StringA*, NamedType*, Ref_Less<StringA> >::value_type(pType->get_QName(), pType));
						}
						*/
					}
				}
			}
		}

		if (false)
		{
			map<String, NamedType*>::iterator it = pD->m_namedTypes.begin();
			while (it != pD->m_namedTypes.end())
			{
				NamedType* pType = (*it).second;//.m_p->GetType();

				ASSERT((uint8*)pType >= heap->m_data);
				ASSERT((uint8*)pType < heap->m_data + heap->m_size);

				if (pType->get_Kind() == type_class)
				{
					ClassType* pClass = pType->GetClass();
					/*
					if (*pClass->m_qname == "System::LDraw::Matrix3f")
					{
						MessageBeep(-1);
					}
					*/

					if (pClass->m_def && pClass->m_pTemplateParams == NULL)
					{
						size_t count = 0;
						size_t innercount = 0;
						size_t arraycount = 0;
						CalcGCMembers(pClass/*most derived*/, pClass, count, innercount, arraycount);

						ASSERT(count < 2000);
						ASSERT(innercount < 2000);
						ASSERT(arraycount < 2000);

						pClass->m_gcMembers.assign(new GCMember[count], count);
						pClass->m_gcInnerMembers.assign(new GCMember[innercount], innercount);
						pClass->m_gcArrayMembers.assign(new GCArrayMember[arraycount], arraycount);

						count = 0;
						innercount = 0;
						arraycount = 0;

						/*
						pClass->m_gcMembers.reserve(count);
						pClass->m_gcInnerMembers.reserve(innercount);
						pClass->m_gcArrayMembers.reserve(arraycount);
						*/

						MakeGCMembers(pClass/*most derived*/, pClass, 0, count, innercount, arraycount);

						GetDispatch(pClass);
					}
				}

				//Sleep(0);

				++it;
			}
		}

#if 1
		ULONG heapsize = heap->m_next - (heap->m_data);
#else
		gc();
		ULONG heapsize = heap->m_next - (heap->m_data+heap->m_size);
#endif

		if (false)
		{
		char buf[256];
		sprintf_s(buf, "heapsize: %f MB", heapsize / (1024.0*1024));
		MessageBoxA(NULL, buf, "", MB_OK);
		}

	//	heap = new Heap(48 * 1024*1024);

#endif

#if 0//WIN32
	{

		{
			const type_info& ti = typeid(pair<StringA*, bool>);
			const char* str = ti.raw_name();

			printf("%s\n", str);
		}

#if 1
		{
			{
				test_template<int>* k = new test_template<int>;
			}

			{
				test_template<float>* k = new test_template<float>;
			}

			TRACE("%s\n", typeid(test_template<int>).name());
			TRACE("%s\n", typeid(test_template<some_other>).name());

			multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::iterator it2 = pD->m_symbols.begin();
			//d(new StringA("TestEnum"));
			while (it2 != pD->m_symbols.end())
			{
				StringA* str = (*it2).first;

				if (strstr(str->c_str(), "red_black_node") && strstr(str->c_str(), "Comparable"))
			//	if (strstr(str->c_str(), "Tag") && strstr(str->c_str(), "ASN"))
				{
					void* k = (void*)(*it2).second;

					TypeDescriptor* typdesc = (TypeDescriptor*)k;
					MessageBeep(-1);
				}

				if (strstr(str->c_str(), "test_template"))
				{
					void* k = (void*)(*it2).second;

					MessageBeep(-1);
				}

				++it2;
			}

		}
#endif

		//vector<StringA*> decs;

		map<StringA*, NamedType*, Ref_Less<StringA>, __gc_allocator>::iterator it = pD->m_namedTypes.begin();
		while (it != pD->m_namedTypes.end())
		{
			NamedType* pType = (*it).second;//.m_p->GetType();

			ASSERT((uint8*)pType >= heap->m_data);
			ASSERT((uint8*)pType < heap->m_data + heap->m_size);

			if (pType->get_Kind() == type_class)
			{
				ClassType* pClass = pType->AsClass();

				MakeGCMembers(pClass/*most derived*/, pClass, 0);

				MakeGCMembers(pClass/*most derived*/, pClass, 0);
			}

#if 0
//			StringA* dname = DecorateName((*it).first);
			StringA* dname = NULL;
			//if (pType->m_type == type_class)
			dname = DecorateName(pType->m_qname/*, (*it).first*/);
			//else if (pType->m_type == type_enum)
			//	dname = DecorateEnumName((*it).first);

			if (dname)
			{
				if (strstr(dname->c_str(), "red_black_node") && strstr(dname->c_str(), "pair") == NULL)
				{
					MessageBeep(-1);
				}

	// +	m_str	0x01b29b30 "??_R0?AV?$red_black_node@VComparable@@PAVTreeItemChildren@UI@@@@@8"

				multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::iterator it2 = pD->m_symbols.find(dname);
				if (it2 != pD->m_symbols.end())
				{
					do
					{
						TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;

						VERIFY(typedesc->_m_data == NULL);

						/*
						int len = strlen(typedesc->rawname);
						ASSERT(len >= 3);
						printf("%s --- %s\n", dname->c_str(), typedesc->rawname);
						*/

						if (pType->get_Kind() == type_class)
						{
							((ClassType*)pType)->m_typedesc = (Type_Info*)typedesc;
						}
						else if (pType->get_Kind() == type_enum)
						{
							((EnumType*)pType)->m_typedesc = (Type_Info*)typedesc;
						}

						//*(NamedType**)&typedesc->rawname = pType;
						*(NamedType**)&typedesc->_m_data = pType;

						++it2;
					}
					while (*(*it2).first == *dname);
				}
				else
				{
					MessageBeep(-1);
				}
			}
#endif

			++it;
		}

		int nstrings = pD->m_strings.size();

		gc();

#if _DEBUG
		heap->ClearGarbage();
#endif

		/*
		const type_info& ti = typeid(TestEnum);
		const char* name = ti.raw_name();
*/

#if 0
		it = pD->m_namedTypes.begin();
		while (it != pD->m_namedTypes.end())
		{
			NamedType* pType = (*it).second;//.m_p->GetType();

			StringA* dname = NULL;
		//	if (pType->m_type == type_class)
				dname = DecorateName(pType->m_qname/*, (*it).first*/);
		//	else if (pType->m_type == type_enum)
		//		dname = DecorateEnumName((*it).first);

			multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::iterator it2 = pD->m_symbols.find(dname);
			if (it2 != pD->m_symbols.end())
			{
				do
				{
					TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;
					*(NamedType**)&typedesc->_m_data = pType;
					AddPersistentLiveRoot((Object**)&typedesc->_m_data);

					++it2;
				}
				while (*(*it2).first == *dname);
			}

			++it;
		}
#endif

#if _DEBUG
		heap->ClearGarbage();
#endif

#if 1
		gc();
		ULONG heapsize = heap->m_next - (heap->m_data);
#else
		ULONG heapsize = heap->m_next - (heap->m_data+heap->m_size);
#endif

		if (false)
		{
		char buf[256];
		sprintf(buf, "heapsize: %f MB", heapsize / (1024.0*1024));
		MessageBoxA(NULL, buf, "", MB_OK);
		}

		heap = new Heap;
	}
#endif

#if 0
	// Dynamically build rtti / vtable info
	if (false)
	{
		rtti_object_locator* p3;
		{
			testrtti_derived1 obj;
			void* vtable = *(void**)&obj;
			p3 = ((rtti_object_locator**)vtable)[-1];
		}

		const type_info& ti2 = typeid(testrtti_derived1);

		ClassType* pType = (ClassType*)typeid(testrtti_derived1).GetType();

		void* vtable[1];
		rtti_object_locator* p4 = Build_rtti(pType);
		vtable[0] = p4;
		polymorphic_object object;
		object.vtable = &vtable[1];

		const type_info& ti = typeid(*(Object*)&object);

		testrtti_base3* testv = dynamic_cast<testrtti_base3*>((Object*)&object);
	}
#endif
#endif
}

#if AMIGA

EXTERN_C
int
MessageBoxA(
    IN HWND hWnd,
    IN const TCHAR * lpText,
    IN const TCHAR * lpCaption,
    IN UINT uType)
{
	printf("%s\n", lpText);
	return MB_OK;
}

EXTERN_C WINBOOL MessageBeep(UINT)
{
	return true;
}

#endif

#if AMIGA
#include "../LFC/Linker.h"

System::Linker* plinker;
#endif

void load_t2()
{
	ASSERT(0);
#if 0
	{
#if WIN32
		TypeArchive ar(TypeArchive::Mode_Load, new IO::FileByteStream(L"C:/mmstudio/amiga68k/test.typeinfo", IO::FileMode_Read), 0);
//		TypeArchive* ar = new TypeArchive(TypeArchive::Mode_Load, new FileByteStream(new StringA("C:/test.typeinfo"), FileMode_Read));
		pD = new TypeDatabase;
		pD->m_debugInfo = new CVR;
#else
		TypeArchive ar(TypeArchive::Mode_Load, new IO::FileByteStream(new StringA("WinHD_C:/mmstudio/amiga68k/test.typeinfo"), IO::FileMode_Read));
#endif

		/*
		printf("%s\n", typeid(vector<list<UI::DependencyObject*> >).name());

		printf("%s\n", typeid(vector<System::Object*, System::__gc_allocator>).name());

		printf("%s\n", typeid(vector<System::ClassType*, System::__gc_allocator>).name());

		printf("%s\n", typeid(vector<red_black_node_base**, std_allocator>).name());

		printf("%s\n", typeid(vector<red_black_node<unsigned long, unsigned char*>*, std_allocator>).name());

		printf("%s\n", typeid(vector<System::StringT<wchar_t, System::__gc_allocator>, std_allocator>).name());

		printf("%s\n", typeid(babbla<System::StringA*, babt<char>, System::StringA* >).name());
		*/

		Namespace* pNamespace;
		ar >> pNamespace;

		int ntypes;
		ar >> ntypes;

		printf("ntypes: %d\n", ntypes);

		char buf[1024];

		for (int i = 0; i < ntypes; i++)
		{
			printf("%d\n", i);

			NamedType* pType;
			ar >> pType;

			if (pType->m_name)
			{
				{
					BufferImp<char> buffer;
					StringBuilderA strbuilder(&buffer);
					pType->Write(strbuilder);
					pType->m_qname = buffer.DetachToString();
				}

				if (pType->m_qname)
				{
				//	printf("%d, qname: %s\n", pType->GetKind(), pType->m_qname->c_str());

					ASSERT(pD->m_namedTypes.find(pType->m_qname) == pD->m_namedTypes.end());

					{
						pD->m_namedTypes.insert(map<StringA*, NamedType*, Ref_Less<StringA>, __gc_allocator>::value_type(pType->m_qname, pType));
					}
				}
				else
					ASSERT(0);
			}

			/*
			if (pType->GetKind() == type_class)
			{
				GetDispatch((ClassType*)pType);
			}
			*/
		//	ASSERT((uint8*)pType >= heap->m_data);
		//	ASSERT((uint8*)pType < heap->m_data + heap->m_size);

#if AMIGA
			if (pType->get_Kind() == type_class)
			{
				ClassType* pClass = pType->GetClass();
				size_t count = 0;
				size_t innercount = 0;
				size_t arraycount = 0;
				CalcGCMembers(pClass/*most derived*/, pClass, count, innercount, arraycount);
				pClass->m_gcMembers.reserve(count);
				pClass->m_gcInnerMembers.reserve(innercount);
				pClass->m_gcArrayMembers.reserve(arraycount);

				MakeGCMembers(pClass/*most derived*/, pClass, 0);

				GetDispatch(pClass);
			}
#endif

			if (pType->get_Kind() != type_typedef)
			{
				if (pType->m_name)
				{
					BufferImp<char, grow_allocator> buffer(grow_allocator(buf+4, 1024-4));
					StringBuilderA strbuilder(&buffer);

					strbuilder << "__ZTI";	// type info

#if 0
					if (strstr(pType->m_qname->c_str(), "babbla")/* &&
						strstr(pType->m_qname->c_str(), "list") &&
						strstr(pType->m_qname->c_str(), "DependencyObject")*/)
					{
						//printf("%s\n%s\n", pType->m_qname->c_str(), name2.c_str());
						MessageBeep(-1);
					}
#endif
					Mangler<char> mangler;
					mangler.MangleType(pType, strbuilder);

					// null terminate
					char z = 0;
					buffer.Write(&z, 1);

					StringA name2;
				//	name2.m_len = buffer.m_len-1;
					*(ULONG*)buf = buffer.m_len;
					ASSERT(0);
#if 0
					name2.m_str = buffer.m_str;
#endif

	#if WIN32
					TRACE("%s\n%s\n\n", pType->m_qname->c_str(), name2.c_str());
	#endif

	#if AMIGA
					gsymmap_t::iterator it2 = plinker->m_globsyms.find(&name2);
					//map<StringA*, DWORD, Ref_Less<StringA> >::iterator it2 = symbols.find(name);
					if (it2 != plinker->m_globsyms.end())
					{
						GlobalSymbol* globsym = (*it2).second;

						//printf("%s\n", name->c_str());

						for (int j = 0; j < globsym->m_syms.size(); j++)
						{
							Symbol* sym = globsym->m_syms[j];

							if (sym->ResolvedValue)
							{
								__type_info2* typedesc = (__type_info2*)sym->ResolvedValue;
							//	printf("%s\n", typedesc->__type_name);

								/*
								if (strstr(sym->globm_name->c_str(), "IAddChild"))
								{
									printf("found: %s at %x\n", sym->m_name->c_str(), typedesc);
								}
								*/

							//	int len = strlen(ti->__type_name);
			#if AMIGA
									/*
									char* newname = malloc(len+1+4);
									strcpy(newname+4, ti->__type_name);
									ti->__type_name = newname+4;
									*(Type**)newname = pType;
									*/
			#endif
								//TypeDescriptor* typedesc = (TypeDescriptor*)(*it2).second;

								//VERIFY(typedesc->_m_data == NULL);

								pType->m_pTypeInfo = (Type_Info*)typedesc;

								/*
								if (pType->GetKind() == type_class)
								{
									((ClassType*)pType)->m_typedesc = (Type_Info*)typedesc;
								}
								else if (pType->GetKind() == type_enum)
								{
									((EnumType*)pType)->m_typedesc = (Type_Info*)typedesc;
								}
								*/

								/*
								printf("%p - ", typedesc);

								const char* p = typedesc->__type_name;
								while (isalnum(*p) || *p == '_')
								{
									fprintf(stdout, "%c", *p);
									p++;
								}
								printf(" -> %s\n", pType->m_qname->c_str());
								*/

#if 1
								int len = strlen(typedesc->__type_name);

								char* p = (char*)malloc(4 + len+1);
								strcpy(p+4, typedesc->__type_name);
								*(Type**)p = pType;
								AddPersistentLiveRoot((Object**)p);

								typedesc->__type_name = p+4;
#else
								//typedesc->_m_data = pType2;
								typedesc->__type_name = (char*)pType;
								//*(Type**)&typedesc->__type_name = pType;
								AddPersistentLiveRoot((Object**)&typedesc->__type_name);
	#endif
							}
							else
							{
								printf("unloaded %s", globsym->m_name->c_str());
								/*
								if (sym->m_pOFile)
								{
									printf("(%s)\n", sym->m_pOFile->m_ofilename->c_str());
								}
								else
								{
									printf("(unknown.o)\n");
								}
								*/
							}
						}
					}
					else
					{
						if (strstr(pType->m_qname->c_str(), "babbla")/* &&
							strstr(pType->m_qname->c_str(), "list") &&
							strstr(pType->m_qname->c_str(), "DependencyObject")*/)
						{
							printf("not found: %s\n%s\n\n", pType->m_qname->c_str(), name2.c_str());
						}

						{
						//	printf("                              %s\n", name2.c_str());
						}
					}
#endif
				}
			}
			else
			{
				Typedef* pTypedef = (Typedef*)pType;

			//	ASSERT(pTypedef->m_pType->m_pTypeInfo);
#if 0
				pTypedef->m_pTypeInfo = pTypedef->m_pType->m_pTypeInfo;
#endif
			}
		}

		printf("sizeof(System::Object) = %d\n", sizeof(System::Object));
		printf("Calced: %d\n\n", typeid(System::Object).GetType()->get_sizeof());

		printf("sizeof(System::BoolObject) = %d\n", sizeof(System::BoolObject));
		printf("Calced: %d\n\n", typeid(System::BoolObject).GetType()->get_sizeof());

		printf("sizeof(System::StringT<char>) = %d\n", sizeof(System::StringT<char>));
		printf("Calced: %d\n\n", typeid(System::StringT<char>).GetType()->get_sizeof());

		printf("sizeof(System::StringT<WCHAR>) = %d\n", sizeof(System::StringT<WCHAR>));
		printf("Calced: %d\n\n", typeid(System::StringT<WCHAR>).GetType()->get_sizeof());


		ASSERT(sizeof(System::__gc_allocator) == typeid(System::__gc_allocator).GetType()->get_sizeof());
		ASSERT(sizeof(System::Object) == typeid(System::Object).GetType()->get_sizeof());
		ASSERT(sizeof(System::BoolObject) == typeid(System::BoolObject).GetType()->get_sizeof());
		ASSERT(sizeof(System::IntObject) == typeid(System::IntObject).GetType()->get_sizeof());
		ASSERT(sizeof(System::DoubleObject) == typeid(System::DoubleObject).GetType()->get_sizeof());
		ASSERT(sizeof(System::StringT<char>) == typeid(System::StringT<char>).GetType()->get_sizeof());
		ASSERT(sizeof(System::StringT<WCHAR>) == typeid(System::StringT<WCHAR>).GetType()->get_sizeof());
		ASSERT(sizeof(System::Type) == typeid(System::Type).GetType()->get_sizeof());
		ASSERT(sizeof(System::PrimitiveType) == typeid(System::PrimitiveType).GetType()->get_sizeof());
		ASSERT(sizeof(System::PointerType) == typeid(System::PointerType).GetType()->get_sizeof());
		ASSERT(sizeof(System::ReferenceType) == typeid(System::ReferenceType).GetType()->get_sizeof());
		ASSERT(sizeof(System::ModifierType) == typeid(System::ModifierType).GetType()->get_sizeof());
		ASSERT(sizeof(System::FunctionType) == typeid(System::FunctionType).GetType()->get_sizeof());
		ASSERT(sizeof(System::NamedType) == typeid(System::NamedType).GetType()->get_sizeof());
		ASSERT(sizeof(System::Typedef) == typeid(System::Typedef).GetType()->get_sizeof());
		ASSERT(sizeof(System::ClassType) == typeid(System::ClassType).GetType()->get_sizeof());
		ASSERT(sizeof(System::EnumType) == typeid(System::EnumType).GetType()->get_sizeof());
		ASSERT(sizeof(System::EnumDef) == typeid(System::EnumDef).GetType()->get_sizeof());
		ASSERT(sizeof(System::Scope) == typeid(System::Scope).GetType()->get_sizeof());
		ASSERT(sizeof(System::Namespace) == typeid(System::Namespace).GetType()->get_sizeof());
		ASSERT(sizeof(System::_TemplateArgType) == typeid(System::_TemplateArgType).GetType()->get_sizeof());
		ASSERT(sizeof(System::TemplatedClassArg) == typeid(System::TemplatedClassArg).GetType()->get_sizeof());
		ASSERT(sizeof(System::TemplatedClassArgs) == typeid(System::TemplatedClassArgs).GetType()->get_sizeof());
		ASSERT(sizeof(System::TemplateParameter) == typeid(System::TemplateParameter).GetType()->get_sizeof());
		ASSERT(sizeof(System::TemplateParams) == typeid(System::TemplateParams).GetType()->get_sizeof());
		ASSERT(sizeof(System::CDeclarator) == typeid(System::CDeclarator).GetType()->get_sizeof());
		ASSERT(sizeof(System::HeapRecord) == typeid(System::HeapRecord).GetType()->get_sizeof());
	//	ASSERT(sizeof(System::IEventTarget) == typeid(System::IEventTarget).GetType()->get_sizeof());
		ASSERT(sizeof(System::Dispatch) == typeid(System::Dispatch).GetType()->get_sizeof());
		ASSERT(sizeof(cstr_less) == typeid(cstr_less).GetType()->get_sizeof());
		ASSERT(offsetof(System::ClassType, m_virtualSize) == typeid(System::ClassType).GetType()->GetClass()->GetDeclarator(ASTR("m_virtualSize"))->m_offset);
		ASSERT(offsetof(System::NamedType, m_ownerScope) == typeid(System::NamedType).GetType()->GetClass()->GetDeclarator(ASTR("m_ownerScope"))->m_offset);


		//ASSERT(offsetof(UI::Control, m_ControlTemplate) == 

		/*
		{
			printf("************************\n");

			ClassType* pType = (ClassType*)typeid(UI::Border).GetType();
			ASSERT(pType);
			Dispatch* pDispatch = GetDispatch(pType);
			ASSERT(pDispatch);

			multimap<StringA*, Method*, Ref_Less<StringA>, __gc_allocator>::iterator it = pDispatch->m_methodnames.begin();
			while (it != pDispatch->m_methodnames.end())
			{
				printf("%s\n", (*it).first->c_str());
				++it;
			}

			printf("************************\n");
		}
		*/
	}
#endif
}

LFCEXT String MakeFilePath(Module& module, WCHAR* relpath)
{
	WCHAR modulefilename[1024];
	GetModuleFileNameW(module.GetModuleInstance(), modulefilename, 511);

	WCHAR* p;
	p = modulefilename;
	while (*p)
	{
		if (*p == '\\') *p = '/';
		p++;
	}
	
	p = modulefilename + wcslen(modulefilename);

	while (p[-1] != '/')
		p--;

	*p = 0;

	wcscat_s(modulefilename, relpath);
	return string_copy(modulefilename);
}

template class DECLSPEC_DLLEXPORT Map<String, CppSourceFile*, map<String, CppSourceFile*>&>;

LFCEXT IEnumerable<CppSourceFile*>* GetSourceFiles()
{
	static Map<String, CppSourceFile*, map<String, CppSourceFile*>&>* sourcefiles = new Map<String, CppSourceFile*, map<String, CppSourceFile*>&>(TypeDatabase::pD->m_typestuff->m_sourcefiles);
	return sourcefiles;
}

LFCEXT IEnumerable<FilePart*>* GetFiles(StringIn part)
{
	TypedMultiMapCollection<
		String,
		FilePart*,
		multimap<String, FilePart*>&>*
	
		files = new TypedMultiMapCollection<String, FilePart*, multimap<String, FilePart*>&>
		(TypeDatabase::pD->m_typestuff->m_fileparts);

	files->m_key = part;
	files->m_begin = TypeDatabase::pD->m_typestuff->m_fileparts.find(part);

	return files;
}

ULONG RefCountedObject::AddRef()
{
	++m_refcount;
	return m_refcount;
}

ULONG RefCountedObject::Release()
{
	ASSERT(m_refcount > 0);

	--m_refcount;
	return m_refcount;
}

bool DynamicDynamicCast(FunctionType* pFrom, FunctionType* pFunSig)
{
	if (pFrom->m_parameters.m_parameters.size() != pFunSig->m_parameters.m_parameters.size())
	{
		return false;
	}

	Type* pReturnType = pFrom->get_ReturnType()->GetStripped();
	Type* pReturnType2 = pFunSig->get_ReturnType()->GetStripped();

	if (pReturnType->get_Kind() != pReturnType2->get_Kind())
	{
		return false;
	}

	if (pReturnType->get_Kind() == type_class)
	{
		if (!pReturnType->AsClass()->IsDerivedFrom(pReturnType2->AsClass()))
		{
			return false;
		}
	}

	for (uint i = 0; i < pFrom->m_parameters.m_parameters.size(); ++i)
	{
		Type* pType = pFrom->m_parameters.m_parameters[i].m_pType->GetStripped();
		Type* pType2 = pFunSig->m_parameters.m_parameters[i].m_pType->GetStripped();

		if (pType->get_Kind() != pType2->get_Kind())
		{
			return false;
		}

		if (pType->get_Kind() == type_class)
		{
			if (!pType->AsClass()->IsDerivedFrom(pType2->AsClass()))
			{
				return false;
			}
		}
	}

	return true;
}

Declarator* DynamicDynamicCast(void* pObject, FunctionType* pFunSig)
{
	// TODO, many possible functions ?

	ClassType* pClass = GetType(pObject);
	for (uint i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pClass->m_pScope->m_orderedDecls[i];

		if (!decl->get_IsStatic())
		{
			Type* pType = decl->m_pType->GetStripped();

			if (pType->get_Kind() == type_function)
			{
				if (DynamicDynamicCast(pType->AsFunction(), pFunSig))
				{
					return decl;
				}
			}
		}
	}

	return nullptr;
}

void* DynamicDynamicCast(void* pObject, ClassType* pInterface)
{
	for (size_t i = 0; i < pInterface->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pInterface->m_pScope->m_orderedDecls[i];

		if (!decl->get_IsStatic())
		{
			Type* pType = decl->m_pType->GetStripped();

			if (pType->get_Kind() == type_function)
			{
				Declarator* decl2 = DynamicDynamicCast(pObject, pType->AsFunction());
				if (decl2 == NULL)
				{
					return nullptr;
				}
			}
		}
	}

	ASSERT(0);
	return nullptr;
}

#if 0
LFCEXT void Print(Stream& stream, ClassType* pClass, void* data)
{
	uint offset = 0;
	for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); ++i)
	{
		Declarator* decl = pClass->m_pScope->m_orderedDecls[i];
		Type* pType = decl->m_pType->GetStripped();
		if (!decl->get_IsStatic() && pType->get_Kind() != type_function)
		{
			/*
			if (offset < decl->m_offset)
			{
				stream << (decl->m_offset - offset) << " padding bytes\n";
			}
			*/

			offset = decl->m_offset;
			stream << decl->m_name << "\n";

			byte* p = ((byte*)data + offset);

			switch (pType->get_Kind())
			{
			case type_char:
				stream << *(char*)p;
				break;

			case type_signed_char:
				stream << *(signed char*)p;
				break;

			case type_unsigned_char:
				stream << *(unsigned char*)p;
				break;

			case type_short_int:
				stream << *(short*)p;
				break;

			case type_unsigned_short_int:
				stream << *(unsigned short*)p;
				break;

			case type_int:
				stream << *(int*)p;
				break;

			case type_unsigned_int:
				stream << *(unsigned int*)p;
				break;

			case type_class:
				{
					Print(stream, pType->GetClass(), p);
				}
				break;
			}

			offset += pType->get_sizeof();
		}
	}
}
#endif

/*
char* month[] =
{
	NULL,
	"Jan",
	"Feb",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
	"Jan",
}
*/

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, const SYSTEMTIME& systemtime)
{
	stream << systemtime.wDay << ".";
	stream << systemtime.wMonth << ".";
	stream << systemtime.wYear;

	stream << " ";
	stream << systemtime.wHour << ":";
	stream << systemtime.wMinute << ":";
	stream << systemtime.wSecond;

	return stream;
}

/*
LFCEXT IO::TextReader& WriteToStream(IO::TextReader& stream, SYSTEMTIME& systemtime)
{
	stream >> systemtime.wDay >> ".";
	stream >> systemtime.wMonth >> ".";
	stream >> systemtime.wYear;

	stream >> " ";
	stream >> systemtime.wHour >> ":";
	stream >> systemtime.wMinute >> ":";
	stream >> systemtime.wSecond;

	return stream;
}
*/

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& stream, const FILETIME& filetime)
{
	SYSTEMTIME systemtime;
	FileTimeToSystemTime(&filetime, &systemtime);
	stream << systemtime;
	return stream;
}

LFCEXT IO::TextWriter& PrintValue(IO::TextWriter& stream, Type* pType, byte* p, StringIn sep)
{
	pType = pType->GetStripped();

	switch (pType->get_Kind())
	{
	case type_class:
		{
			ClassType* pClassType = static_cast<ClassType*>(pType);

			if (pClassType == typeid(String))
			{
				stream << "\"" << *(String*)p << "\"";
			}
			else
			{
				bool bAny = false;

				for (size_t i = 0; i < pClassType->m_pScope->m_orderedDecls.size(); ++i)
				{
					Declarator* decl = pClassType->m_pScope->m_orderedDecls[i];

					if (decl->m_pType && decl->m_pType->get_Kind() != type_function &&
						!decl->get_IsStatic())
					{
						if (bAny) stream << sep;
						bAny = true;

						stream << decl->m_name << ": ";
						PrintValue(stream, decl->m_pType, p + decl->m_offset, sep);
					}
				}
			}
		}
		break;

	case type_pointer:
		{
			PointerType* pPointerType = static_cast<PointerType*>(pType);
			byte* p2 = *(byte**)p;

			stream << "ptr";
			//PrintValue(stream, pPointerType->GetPointerTo(), p2, sep);
		}
		break;

	case type_array:
		{
			ArrayType* pArrayType = static_cast<ArrayType*>(pType);
			size_t count = pArrayType->get_ElemCount();
			Type* pElemType = pArrayType->get_ElemType();

			stream << "[";

			for (size_t i = 0; i < count; ++i)
			{
				if (i > 0) stream << sep;
				PrintValue(stream, pElemType, p + pElemType->get_sizeof()*i, sep);
			}

			stream << "]";
		}
		break;

	case type_bool:
		{
			stream << *(bool*)p;
		}
		break;

	case type_char:
		{
			stream << *(char*)p;
		}
		break;

	case type_wchar_t:
		{
			stream << *(wchar_t*)p;
		}
		break;

	case type_signed_char:
		{
			stream << *(signed char*)p;
		}
		break;

	case type_unsigned_char:
		{
			stream << *(unsigned char*)p;
		}
		break;

	case type_short:
		{
			stream << *(short*)p;
		}
		break;

	case type_unsigned_short:
		{
			stream << *(unsigned short*)p;
		}
		break;

	case type_int:
		{
			stream << *(int*)p;
		}
		break;

	case type_unsigned_int:
		{
			stream << *(unsigned int*)p;
		}
		break;

	case type_long:
		{
			stream << *(long*)p;
		}
		break;

	case type_unsigned_long:
		{
			stream << *(unsigned long*)p;
		}
		break;

	case type_long_long:
		{
			stream << *(long long*)p;
		}
		break;

	case type_unsigned_long_long:
		{
			stream << *(unsigned long long*)p;
		}
		break;

	case type_float:
		{
			stream << *(float*)p;
		}
		break;

	case type_double:
		{
			stream << *(double*)p;
		}
		break;

	case type_long_double:
		{
			stream << *(long double*)p;
		}
		break;

	default:
		// TODO
		stream << "(err)";
	//	ASSERT(0);
	}

	return stream;
}

//

LFCEXT String toString(bool value)
{
	static ImmutableString<WCHAR> true_str(L"true");
	static ImmutableString<WCHAR> false_str(L"false");

	return value? &true_str: &false_str;
//	StringStream str;
//	str << value;
//	return str;
}

LFCEXT String toString(char value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(unsigned char value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(wchar_t value)
{
	IO::StringWriter str;
	str << value;
	return str;
}

LFCEXT String toString(int value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(unsigned int value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(int64 value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(uint64 value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(float value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(double value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(long double value)
{
	return String::FromNumber(value);
}

LFCEXT String toString(Object* obj)
{
	return obj->ToString();
}

LFCEXT String toString(const String& str)
{
	return str;
}

LFCEXT String toString(const StringVariant& str)
{
	return str;
}

//
LFCEXT float toFloat(int value)
{
	return float(value);
}

LFCEXT float toFloat(double value)
{
	return float(value);
}

LFCEXT float toFloat(String value)
{
	// TODO
	return str2int(CStringw(value));
}

//
LFCEXT double toDouble(int value)
{
	return value;
}

LFCEXT double toDouble(float value)
{
	return value;
}

int Real::floor(float value)
{
	return (int)::floor(value);
}

int Real::ceil(float value)
{
	return (int)::ceil(value);
}

/*
LFCEXT Stream& PrintValue(Stream& stream, Type* pType, byte* p, String sep)
{
	map<void*,int> defs;
	return PrintValue2(stream, pType, p, sep, defs);
}
*/

LFCEXT Object* GetUserData(Object* obj, Object* key)
{
	IHasUserData* userdata = dynamic_cast<IHasUserData*>(obj);
	if (userdata)
	{
		return userdata->GetUserData(key);
	}
	else
		;//ASSERT(0);
	return NULL;
}

LFCEXT void SetUserData(Object* obj, Object* key, Object* value)
{
	IHasUserData* userdata = dynamic_cast<IHasUserData*>(obj);
	if (userdata)
	{
		userdata->SetUserData(key, value);
	}
	else
		;//ASSERT(0);
}

LFCEXT String CurrentDir()
{
	WCHAR buffer[512];
	GetCurrentDirectory(512, buffer);
	return String(string_copy(buffer));
}

LFCEXT bool ChangeDir(StringIn path)
{
//	WCHAR* buffer = _alloca((path.GetLength()+1)*sizeof(WCHAR)));

	return SetCurrentDirectory(CStringw(path).c_str()) != FALSE;
}

LFCEXT ProcessInformation Execute(StringIn commandLine)
{
	return Execute(nullptr, commandLine);
}

LFCEXT ProcessInformation Execute(StringIn applicationName, StringIn commandLine)
{
	STARTUPINFO si = { si.cb = sizeof(si)};

	PROCESS_INFORMATION pi;
	BOOL success = CreateProcessW(applicationName.c_strw(), wcsdup(commandLine.c_strw()), nullptr, nullptr,
		FALSE,	// bInheritHandles
		0,	// dwCreationFlags,
		nullptr,	// lpEnvironment
		nullptr,	// lpCurrentDirectory
		&si, // lpStartupInfo
		&pi);

	if (!success) raise(SystemException("Couldn't create process"));

	return ProcessInformation(pi);
}

LFCEXT void WaitFor(const ProcessInformation& process)
{
//	if (IsGUIThread(FALSE))
//	MsgWaitForMultipleObjects(1, &process.processHandle.m_h, FALSE, INFINITE, QS_ALLEVENTS);

	DWORD result = WaitForSingleObject(process.processHandle, INFINITE);
	if (result == WAIT_FAILED) raise(Exception());
}

LFCEXT WaitResult WaitFor(const ProcessInformation& process, DWORD milliseconds)
{
	DWORD result = WaitForSingleObject(process.processHandle, milliseconds);
	if (result == WAIT_FAILED) raise(Exception());
	return result == WAIT_TIMEOUT? WaitResult_Timeout: WaitResult_Ok;
}

#define ThreadQuerySetWin32StartAddress 9

ULONG_PTR ProcessThread::get_StartAddress()
{
	ULONG_PTR startAddress = 0;
	if (pfNtQueryInformationThread)
	{
		HANDLE hDupHandle;
		HANDLE hCurrentProcess = GetCurrentProcess();
		if (!DuplicateHandle(hCurrentProcess, m_h, hCurrentProcess, &hDupHandle, THREAD_QUERY_INFORMATION, FALSE, 0))
		{
			throw new SystemException("DuplicateHandle");
		//	SetLastError(ERROR_ACCESS_DENIED);
		//	return 0;
		}

		pfNtQueryInformationThread(hDupHandle, ThreadQuerySetWin32StartAddress, &startAddress, sizeof(ULONG_PTR), nullptr);

		CloseHandle(hDupHandle);
	}
	return startAddress;
}

LFCEXT float dot(gm::vector2f v1, gm::vector2f v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

LFCEXT gm::vector2f proj(gm::vector2f a, gm::vector2f u)
{
	return dot(a, u)/u.lengthSquared() * u;
}

LFCEXT gm::vector3f proj(gm::vector3f a, gm::vector3f u)
{
	return dot(a, u)/u.lengthSquared() * u;
}

namespace gm
{
template class LFCEXT Point<int>;
template class LFCEXT Point<float>;
template class LFCEXT Point<double>;
}

namespace gm
{
template class LFCEXT vector2<int>;
template class LFCEXT vector2<float>;
template class LFCEXT vector2<double>;
}

LFCEXT List<String>* FindFiles(StringIn filename)
{
	List<String>* l = new List<String>;

	WIN32_FIND_DATAW wfd;
	HANDLE hFile = FindFirstFileW(CStringw(filename), &wfd);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			l->Add(wfd.cFileName);
		}
		while (FindNextFileW(hFile, &wfd));

		FindClose(hFile);
	}

	return l;
}

namespace IO
{

// TODO
// PathCanonicalize

// static
String Path::GetFullPath(StringIn path)
{


	if (path.GetCharSize() == 1)
	{
		char full[512];
		_fullpath(full, path.c_str(), _countof(full));
		return full;
	}
	else
	{
		wchar_t full[512];
		_wfullpath(full, path.c_strw(), _countof(full));
		return full;
	}
}

// static
bool Path::IsPathRooted(StringIn path)
{
	if (path.GetLength() > 1 && path.At(1) == ':')
		return true;
	else
		return false;
}

// static
String Path::Combine(StringIn path1, StringIn path2)
{
	if (IsPathRooted(path2))
	{
		return path2;
	}
	else
	{
		if (path1.At(path1.GetLength()-1) == '\\' ||
			path1.At(path1.GetLength()-1) == '/')
		{
			return GetFullPath(path1 + path2);
		}
		else
		{
			return GetFullPath(path1 + "\\" + path2);
		}
	}
}

// static
String Path::Combine(StringIn path1, StringIn path2, StringIn path3)
{
	return Combine(Combine(path1, path2), path3);
}

// static
String Path::Combine(StringIn path1, StringIn path2, StringIn path3, StringIn path4)
{
	return Combine(Combine(Combine(path1, path2), path3), path4);
}

// static
String Path::Combine(const vector<String>& paths)
{
	ASSERT(0);
	return nullptr;
}

// static
String Path::GetDirectoryName(StringIn path)
{
	auto x = path.rfind('\\');
	if (x != String::npos) return path.LeftOf(x);

	x = path.rfind('/');
	if (x != String::npos) return path.LeftOf(x);

	return nullptr;
}

// static
String Path::GetFileName(StringIn path)
{
	size_t x = path.rfind('\\');
	if (x != String::npos) return path.RightOf(x+1);

	x = path.rfind('/');
	if (x != String::npos) return path.RightOf(x+1);

	return nullptr;
}

// static
String Path::GetFileNameWithoutExtension(StringIn path)
{
	size_t dot = path.rfind('.');
//	if (dot == String::npos) String::get_Empty();

	auto slash = path.rfind('\\');
	if (slash != String::npos) return path.substr(slash+1, dot-(slash+1));

	slash = path.rfind('/');
	if (slash != String::npos) return path.substr(slash+1, dot-(slash+1));

	return nullptr;
}

// static
String Path::GetPathNameWithoutExtension(StringIn path)
{
	size_t dot = path.rfind('.');
	return path.substr(0, dot);
}

// static
String Path::GetExtension(StringIn path)
{
	if (path == nullptr) return nullptr;

	size_t dot = path.rfind('.');
	if (dot == String::npos) return String::get_Empty();

	return path.substr(dot);
}

// static
bool Path::HasExtension(StringIn path)
{
	if (path == nullptr) return false;
	return path.rfind('.') != String::npos;
}

// static
String Path::ChangeExtension(StringIn path, StringIn extension)
{
	size_t extpos = path.rfind('.');

	if (extension == nullptr)	// Remove extension
	{
		return path.substr(0, extpos);
	}

	if (extension.At(0) == '.')
		return path.substr(0, extpos) + extension;
	else
		return path.substr(0, extpos) + "." + extension;
}

// static
String Path::GetPathRoot(StringIn path)
{
	size_t colon = path.find(':');
	if (colon == String::npos) return nullptr;
	return path.LeftOf(colon+1);
}

/*
BinaryReader& BinaryReader::operator << (int number)
{
	if (m_bufferpos + 4 >= m_bufferlen)
	{
		m_baseStream.Read(&number, sizeof(number));
	}

	if (m_endianess == Endianess_Big) number = BigEndian32(number);

	size_t nRead = m_baseStream->Read(&number, sizeof(number));
	if (nRead < sizeof(number))
	{
		raise(EndOfStreamException());
	}

	return *this;
}
*/

}

uint g_appLockCount = 0;

LFCEXT uint GetAppLockCount()
{
	return g_appLockCount;
}

LFCEXT uint IncAppLockCount()
{
	return InterlockedIncrement(&g_appLockCount);
}

LFCEXT uint DecAppLockCount()
{
	return InterlockedDecrement(&g_appLockCount);
}

Object UndefinedValue::undefinedObject;

LFCEXT UndefinedValue undefined;


}	// System

namespace System
{

// static
ATOM HWindow::m_class;

// static
void HWindow::RegisterClass()
{
	if (m_class == 0)
	{
		WCHAR classname[512];
		swprintf_s(classname, L"HWindow_class");

		WNDCLASSW wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = NULL;
		wc.hIcon = NULL;
		wc.hInstance = _Module.GetHandle();
		wc.lpfnWndProc = WndProc;
		wc.lpszClassName = classname;
		wc.lpszMenuName = NULL;
		wc.style = 0;

		m_class = ::RegisterClassW(&wc);
	}
}

// static
LRESULT CALLBACK HWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		{
		}
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LFCEXT DWORD gui_threadId;

LFCEXT Type* ToType(Type* p)
{
	return p;
}

}	// System

#include <crtdbg.h>

/*
namespace System
{
	namespace MSWindows
	{
		extern "C"
		{
WINBASEAPI VOID WINAPI DebugBreak();
		}
	}
}
*/

extern "C" void _Break(const char* filename, int line)
{
	ASSERT(0);
	MessageBoxA(NULL, filename, NULL, MB_OK);
	//_DebugBreak(filename, line);
	//_CrtDbgBreak();
	DebugBreak();
}