// Start.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <tchar.h>
#include "Start.h"

#include <cguid.h>

#include <sapi.h>
#pragma comment(lib, "sapi")

#include "CodeComp/cpp_translate.h"

#include "LVOC/VOCLoader.h"
#pragma comment(lib, "LVOC.lib")

#include "PSD/PSD.h"
#pragma comment(lib, "PSD")

//#include "GUI/wmf.h"

#include "DXFile/DXFile.h"
#pragma comment(lib, "DXFile")

#include "JSVM/JSVM.h"

/*
// Direct3D 10
#ifdef _DEBUG
//#pragma comment(lib, "d3d10d")
#pragma comment(lib, "d3d10_1")
#pragma comment(lib, "d3dx10d")
#else
#pragma comment(lib, "d3d10_1")
#pragma comment(lib, "d3dx10")
#endif
*/

#pragma comment(lib, "EcmaScript")
#pragma comment(lib, "JSVM")
#pragma comment(lib, "CSS")
#pragma comment(lib, "CodeComp")
#pragma comment(lib, "Expressive")

//#include "GUI/physics.h"

namespace System
{

DECLSPEC_DLLIMPORT JSVM::StackFrame* g_frame;

namespace cpp
{
namespace ast
{
CodeCompExt Expression* parse_expression(StringIn str);
CodeCompExt Expression* parse_expression(CGlobal* pGlobal, StringIn str);
CodeCompExt DeclarationList* parse_translation_unit(CGlobal* pGlobal, StringIn str);
}

CodeCompExt void CalcClass(CGlobal* pGlobal, ClassType* pClass, unsigned int alignment);

}	// ast
}	// cpp

extern "C"
{
//ExpressParser_expr_return Parse(wchar_t* str, unsigned int strlen);
}

//#include "antlr/parser.hpp"

#include <searchapi.h>
#pragma comment(lib, "SearchSDK")

#ifdef UNICODE
#define UnregisterClass UnregisterClassW
#else
#define UnregisterClass UnregisterClassA
#endif
#include <atlbase.h>
#include <atldbcli.h>
#undef UnregisterClass

namespace System
{

void Search(StringIn str)
{

	HRESULT hr;

	// Create ISearchManager instance
	ComPtr<ISearchManager> pSearchManager;
	hr = CoCreateInstance(CLSID_CSearchManager, nullptr, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&pSearchManager));		
//	Obtain an instance of ISearchCatalogManager using ISearchManager::GetCatalog. The name of the system catalog for Windows Search is SYSTEMINDEX. 

	// Create ISearchCatalogManager instance 
	ComPtr<ISearchCatalogManager> pSearchCatalogManager;
	// Call ISearchManager::GetCatalog for "SystemIndex" to access the catalog to the ISearchCatalogManager
	hr = pSearchManager->GetCatalog(L"SystemIndex", &pSearchCatalogManager);
			
//	Obtain an instance of ISearchQueryHelper using ISearchCatalogManager::GetQueryHelper. 
	// Call ISearchCatalogManager::GetQueryHelper to get the ISearchQueryHelper interface
	ComPtr<ISearchQueryHelper> pQueryHelper;
	hr = pSearchCatalogManager->GetQueryHelper(&pQueryHelper);
			
//	Once you have an instance of ISearchQueryHelper you must then receive the connection string used to connect to the Windows Search index OLE DB connector. 
	// Call get_ConnectionString to get the OLE DB connection string
	CoString pszConnectionString;
	hr = pQueryHelper->get_ConnectionString(&pszConnectionString);
	if (SUCCEEDED(hr))
	{
		CoString pszSQL;
		hr = pQueryHelper->GenerateSQLFromUserQuery(str.c_strw(), &pszSQL);
		if (SUCCEEDED(hr))
		{
			CDataSource cDataSource;
			hr = cDataSource.OpenFromInitializationString(pszConnectionString/*L"provider=Search.CollatorDSO.1;EXTENDED PROPERTIES=\"Application=Windows\""*/);

			if (SUCCEEDED(hr))
			{
				CSession cSession;
				hr = cSession.Open(cDataSource);

				if (SUCCEEDED(hr))
				{
					CCommand<CDynamicAccessor, CRowset> cCommand;
					hr = cCommand.Open(cSession, pszSQL);

					if (SUCCEEDED(hr))
					{
						size_t nrow = 0;
						for (hr = cCommand.MoveFirst(); hr == S_OK; hr = cCommand.MoveNext(), ++nrow)
						{
							for (DBORDINAL i = 1; i <= cCommand.GetColumnCount(); ++i)
							{
								if ((nrow % 20) == 0)
								{
									PCWSTR columnName = cCommand.GetColumnName(i);
									Std::get_Out() << "[" << columnName << "]";
								}
								DBTYPE type;
								cCommand.GetColumnType(i, &type);

								Variant v;

								switch (type)
								{
								case DBTYPE_STR:
									v = (CHAR*)cCommand.GetValue(i);
									break;

								case DBTYPE_WSTR:
									v = (WCHAR*)cCommand.GetValue(i);
									break;

								case DBTYPE_I4:
									v = *(int*)cCommand.GetValue(i);
									break;

								case DBTYPE_UI4:
									v = *(unsigned int*)cCommand.GetValue(i);
									break;

								case DBTYPE_I8:
									v = *(int64*)cCommand.GetValue(i);
									break;

								case DBTYPE_UI8:
									v = *(uint64*)cCommand.GetValue(i);
									break;

								case DBTYPE_BOOL:
									v = !! *(long*)cCommand.GetValue(i);
									break;

								default:
									v = *(long*)cCommand.GetValue(i);
								}

								Console::get_Out() << v;
								Console::get_Out() << endl;
							}
						}
						cCommand.Close();
					}
				}
			}
		}
	}
}

}	// System

namespace System
{

Module _Module;

LFCEXT void gc_Protect();
LFCEXT int EvalExcept(int code, _EXCEPTION_POINTERS*);

namespace Gui
{
extern GUIEXT IXAudio2* pXAudio2;
GUIEXT bool InitAudio();

//extern GUIEXT __live_object_ptr<StyleSheet> g_styleSheet;
extern GUIEXT StyleSheet* g_styleSheet;

//extern GUIEXT NxScene* g_gScene;
}

}

#pragma comment(lib, "d2d1")	// TODO, shouldn't be needed here

#pragma comment(lib, "LFC")
#pragma comment(lib, "GUI")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "Imaging")

#include "wmp.h"

//#pragma comment(lib, "LXML")
//#pragma comment(lib, "XSLT")

/*
#include "LXML/LXML.h"

#include "XSLT/XSLT.h"
*/

#include "LFC/NameMangler.h"

#define HAVE_SVG	0

#if HAVE_SVG
#pragma comment(lib, "LHTML")
#pragma comment(lib, "LSVG")
//#pragma comment(lib, "LXUI")	// TODO remove

#include "LSVG/LSVG.h"
#endif

//#include "x3d/x3d.h"
//#pragma comment(lib, "X3D")

namespace System
{

namespace Start
{

class Init
{
public:

	CTOR Init();
};

Init::Init()
{
	HMODULE hModule = GetModuleHandleW(nullptr);

	try
	{
		_Module.Init(hModule);
		_Module.SetHandle(hModule);
	}
	catch (Exception* e)
	{
		String reason = e->get_Reason();
		AllocConsole();
		Console::_In->SetFileHandle(GetStdHandle(STD_INPUT_HANDLE));
		Console::_Out->SetFileHandle(GetStdHandle(STD_OUTPUT_HANDLE));
		Console::_Err->SetFileHandle(GetStdHandle(STD_ERROR_HANDLE));

		Console::get_Out() << e;
	}
}

// Must have this before other statics that depend on Typeinfo
Init init;

using namespace Gui;

class type_info
{
public:
	virtual ~type_info()
	{
	}

	void *_m_data;
	char _m_d_name[1];
};

struct ITest;

class Listen : public Object
{
public:

	void OnSize(Window* windowVisual)
	{
		MessageBeep(-1);
	}
};

IMP_DEPENDENCY_PROPERTY(float, MyPage, BrushWidth, 20.0f)

DependencyClass* MyPage::get_Class()
{
//	ComPtr<ITest> hello;

	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BrushWidthProperty(),
	/*
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	*/
	};

	return &depclass;
}

void MyPage::OnMouseLeftButtonDown(MouseButtonEventArgs* args)
{
	CaptureMouse();

	gm::PointF pos = args->GetPosition(this);

	m_points.push_back(pos);
	InvalidateVisual();
}

void MyPage::OnMouseLeftButtonUp(MouseButtonEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		ReleaseMouseCapture();

		static Gui::strokeStyle myStrokeStyle(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND);

		m_geometry |= Gui::geometry::From(m_points).Widened(get_BrushWidth(), myStrokeStyle);
		m_points.clear();

		InvalidateVisual();
	}
}

void MyPage::OnMouseRightButtonDown(MouseButtonEventArgs* args)
{
	CaptureMouse();

	gm::PointF pos = args->GetPosition(this);

	m_points.push_back(pos);
	InvalidateVisual();
}

void MyPage::OnMouseRightButtonUp(MouseButtonEventArgs* args)
{
	if (get_IsMouseCaptured())
	{
		ReleaseMouseCapture();
		static Gui::strokeStyle myStrokeStyle(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND);

		m_geometry -= Gui::geometry::From(m_points).Widened(get_BrushWidth(), myStrokeStyle);
		m_points.clear();

		InvalidateVisual();
	}
}

void MyPage::OnMouseMove(MouseEventArgs* args)
{
	gm::PointF pos = args->GetPosition(this);

	if (get_IsMouseCaptured())
	{
		m_points.push_back(pos);
		InvalidateVisual();
	}

//	get_OwnerWindow()->set_TitleText(String("New Window Title"));
}

/*
class AnimationBinding : public Object, public IBinding
{
public:

	CTOR AnimationBinding(AnimationClock* animationClock) :
		m_animationClock(animationClock)
	{
	}

	virtual Object* GetOutput(IBinding* caller);
	virtual int SetOutput(IBinding* caller, Object* value);
	virtual int SetInput(IBinding* caller, Object* value);
	virtual void* Connect(IBinding* binding);

	AnimationClock* m_animationClock;
	list<IBinding*> m_outBindings;
};
*/

template<class propertyType> TypedAnimation<propertyType>* animate(propertyType from, propertyType to, double duration)
{
	TypedAnimation<propertyType>* timeline = new TypedAnimation<propertyType>();
	timeline->set_From(from);
	timeline->set_To(to);
	timeline->set_Duration(duration);

	return timeline;
};

class Graph
{
public:
	float from;
	float to;
	float step;
};

void MyPage::RenderRetained(System::Gui::ManagedRetainedRenderContext renderContext)
{
	static Gui::SolidColorBrush* bgbrush = new Gui::SolidColorBrush(1, 1, 1);
	renderContext.FillRectangle(gm::RectF(0, 0, get_ActualWidth(), get_ActualHeight()), bgbrush);

	static Gui::strokeStyle myStrokeStyle(D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND);
	geometry g = pathgeometry::From(m_points).Widened(get_BrushWidth(), myStrokeStyle).Outline();

	static Gui::SolidColorBrush* brush = new Gui::SolidColorBrush(0, 0, 0);
	static Gui::SolidColorBrush* fbrush = new Gui::SolidColorBrush(1, 0, 0);

	renderContext.FillGeometry(this->m_geometry, fbrush);
	renderContext.StrokeGeometry(this->m_geometry, brush, 1);

	renderContext.FillGeometry(g, fbrush);
	renderContext.StrokeGeometry(g, brush, 1);

//	renderContext.RenderCond(_if(Window::Find(L"WMPlayerApp")

#if 0

	m_expression = Expressive::Math::sin(Expressive::typed_expression<float>(new Expressive::GetVariableExpression(String(L"x"))) * 0.2f) * 60.0f;

	Graph graph;
	graph.from = 0;
	graph.to = 400;
	graph.step = 1;

	if (graph.to > graph.from)
	{
		if (graph.step <= 0)
			raise(Exception());
	}
	else if (graph.to < graph.from)
	{
		if (graph.step >= 0)
			raise(Exception());
	}

	int count = (graph.to - graph.from) / graph.step;

	vector<float> values;
	values.resize(count);

	int i = 0;
	float x = graph.from;
	while (x < graph.to)
	{
		Expressive::EvalContext evalContext;
		evalContext.m_this = nullptr;
		evalContext.m_userObject = nullptr;
		evalContext.m_variables[String(L"x")] = box_cast(x);
		float y = ToFloat(m_expression->Evaluate(&evalContext));

		values[i] = y;

		x += graph.step;
		i += 1;
	}

	PathGeometry* geometry = new PathGeometry;
//	geometry->MoveTo(LDraw::PointF(0, values[0]));
	for (int i = 0; i < values.size(); i++)
	{
		geometry->LineTo(LDraw::PointF(i*1, values[i]));
	}

	renderContext.PushTransform(new TranslateTransform(_Mouse::screenposX(), _Mouse::screenposY()));
	renderContext.StrokeGeometry(geometry, new SolidColorBrush(0,0,0), 1);
	renderContext.Pop();
#endif

#if 0
	ActiveXHostVisual* activeX = new ActiveXHostVisual(L"TestATLControl.TestAX");

//	Window* window = Window::Find(L"WMPlayerApp");
	/*
	if (window)
	{
		renderContext.DrawVisual(window->GetVisual());
	}
	*/

	FloatAnimationClock* clock = new FloatAnimationClock(animate(float(-50), float(100), 20));
	clock->get_CurrentTimeBinding()->SetInputBinding(TimeManager::get_GlobalTime());

	renderContext.PushTransform(new TranslateTransform(Mouse::_Mouse::screenposX(), Mouse::_Mouse::screenposY()));
		renderContext.PushTransform(new TranslateTransform( - _Window(get_OwnerWindow()).getLeft(), - _Window(get_OwnerWindow()).getTop()));
			renderContext.PushTransform(new TranslateTransform( -50, - 50));

				renderContext.m_p->m_visuals->Add(new VisualInstance(activeX));
			/*
				renderContext.FillGeometry(
					new RoundedRectangleGeometry(
						0,
						0,
						200,
						80,
						10,
						10),
					new SolidColorBrush(0.75f, 0.75f, 0.85f));
*/
				renderContext.DrawLine(
					0, 0,
					Expressive::Math::cos(_Clock(clock).getCurrentTime()) * 120.0f,
					Expressive::Math::sin(_Clock(clock).getCurrentTime()) * 120.0f,
					new SolidColorBrush(1, 0, 1), 10);

			//	window->get_Icon()->SetRoot(GetRoot());	// TODO remove
			//	renderContext.DrawVisual(window->get_Icon()->GetVisual());

				renderContext.OutputText(WSTR("Button"), new SolidColorBrush(0, 0, 0), new FontFamily(WSTR("Arial")), 30.0f);
			renderContext.Pop();
		renderContext.Pop();
	renderContext.Pop();
#endif
}

#if 0

class DocumentData : public XDM::IData
{
public:

	DocumentData(XDM::IData* child, StringIn childName)
	{
		m_child = child;
		m_childName = childName;
	}

	virtual XDM::IData* getParent()
	{
		return nullptr;
	}

	virtual unsigned int getPosition()
	{
		return ~0;
	}

#if 0
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return nullptr;
		//return WSTR("#document");
	}
	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return nullptr;
	}
#endif

	virtual XDM::IData* getRoot()
	{
		return this;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}
	virtual System::Variant getAttributeValue(unsigned int index)
	{
		ASSERT(0);
		return Variant();
	}
	virtual String getAttributeName(unsigned int index)
	{
		ASSERT(0);
		return null;
	}

	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual System::Type* getChildType(unsigned int index)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual String getAttributeNamespaceURI(unsigned int index)
	{
		return null;
	}
	virtual unsigned int getChildCount()
	{
		return 1;
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}

	virtual String getChildName(unsigned int index)
	{
		return m_childName;
	}

	virtual String getChildNamespaceURI(unsigned int index)
	{
		return null;
	}
	virtual XDM::IData* getChildElement(unsigned int index)
	{
		ASSERT(index == 0);
		return m_child;
	}
	virtual String getChildText(unsigned int index)
	{
		return nullptr;
	}

	virtual Object* GetObject()
	{
		return nullptr;
	}

	XDM::IData* m_child;
	String m_childName;
};

map<Object*, XDM::IData*> objects;

class ObjectData;

class ComplexTypeData  : public XDM::IData
{
public:
	ComplexTypeData(XDM::IData* root, System::Object* object, XDM::IData* parent, unsigned int position);

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}
	virtual unsigned int getPosition()
	{
		return m_position;
	}

	/*
	virtual System::StringW* getName()
	{
		return 0;
	}

	virtual System::StringW* getNamespaceURI()
	{
		return 0;
	}
	*/
	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}

	virtual System::Variant getAttributeValue(unsigned int index)
	{
		return 0;
	}
	virtual String getAttributeName(unsigned int index)
	{
		return null;
	}
	virtual String getAttributeNamespaceURI(unsigned int index)
	{
		return null;
	}
	virtual System::Type* getAttributeType(unsigned int index)
	{
		return nullptr;
	}

	virtual unsigned int getChildCount()
	{
		return 1;
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}
	virtual String getChildName(unsigned int index)
	{
		ASSERT(index == 0);
		return m_object->GetType()->m_name;
	}
	virtual String getChildNamespaceURI(unsigned int index)
	{
		ASSERT(index == 0);
		return null;
	}
	virtual System::Type* getChildType(unsigned int index)
	{
		return m_object->GetType();
	}
	virtual XDM::IData* getChildElement(unsigned int index);

	virtual String getChildText(unsigned int index)
	{
		return null;
	}

	virtual System::Object* GetObject()
	{
		return m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
//	Property* m_parentProperty;
	Object* m_object;
//	ObjectData* m_content;
};

class CollectionData : public XDM::IData
{
public:
	CollectionData(XDM::IData* root, IObjectCollection* collection, XDM::IData* parent, unsigned int position)
	{
		m_root = root;
		m_collection = collection;
		m_parent = parent;
		m_position = position;
	//	m_parentProperty = parentProperty;
	}

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}
	virtual unsigned int getPosition()
	{
		return m_position;
	}

	/*
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return 0;
	}

	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return 0;
	}
	*/
	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}

	virtual System::Variant getAttributeValue(unsigned int index)
	{
		ASSERT(0);
		return 0;
	}
	virtual String getAttributeName(unsigned int index)
	{
		ASSERT(0);
		return null;
	}
	virtual String getAttributeNamespaceURI(unsigned int index)
	{
		ASSERT(0);
		return null;
	}
	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual unsigned int getChildCount()
	{
		return m_collection->GetCount();
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}
	virtual String getChildName(unsigned int index)
	{
		Object* child = m_collection->get_ObjectItem(index);
		return child->GetType()->get_Name();
	}
	virtual String getChildNamespaceURI(unsigned int index)
	{
		return null;
	}
	virtual System::Type* getChildType(unsigned int index)
	{
		Object* child = m_collection->get_ObjectItem(index);
		return child->GetType();
	}
	virtual XDM::IData* getChildElement(unsigned int index);

	virtual String getChildText(unsigned int index)
	{
		return null;
	}

	virtual System::Object* GetObject()
	{
		ASSERT(0);
		return nullptr;//m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
	IObjectCollection* m_collection;
//	Property* m_parentProperty;
};

class ObjectData : public XDM::IData
{
public:

	ObjectData(XDM::IData* root, Object* object, XDM::IData* parent, unsigned int position)
	{
		m_root = root;
		m_object = object;
		//m_parentProperty = parentProperty;
		m_parent = parent;
		m_position = position;
	}

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}

	virtual unsigned int getPosition()
	{
		return m_position;
	}

	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

#if 0
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return nullptr;
		/*
		ASSERT(m_parentProperty);

		//return m_object->GetType()->m_qname->ToStringW();
		return m_parentProperty->get_PropertyName()->ToStringW();
		*/
	}

	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return nullptr;
	}
#endif

	virtual unsigned int getAttributeCount()
	{
		if (IObjectCollection* collection = dynamic_cast<IObjectCollection*>(m_object))
		{
			return 0;
		}
		else
		{
			ClassType* pClass = m_object->GetType();

			unsigned int count = 0;

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (IsSimple(pProperty))
				{
					++count;
				}

				++it;
			}

			return count;
		}
	}

	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return nullptr;
	}

	virtual System::Type* getChildType(unsigned int index)
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return child->GetType();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					index--;
				}

				if ((int)index == -1)
					break;

				++it;
			}

			Object* object = pClass->m_pDispatch->Object_Invoke(m_object, (*it).second->get_GetMethod(), nullptr, 0);

			ASSERT(object != nullptr);	// TODO

			return object->GetType();

		//	return (*it).second->get_GetType();
		}
	}

	virtual Variant getAttributeValue(unsigned int index)
	{
		ClassType* pClass = m_object->GetType();

		Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
		Dispatch::propertymap_t::iterator it = properties.begin();

		while (it != properties.end())
		{
			Property* pProperty = (*it).second;

			if (IsSimple(pProperty))
			{
				index--;
			}

			if ((int)index == -1)
				break;

			++it;
		}

		ASSERT(it != properties.end());

		Property* pProperty = (*it).second;

		switch (pProperty->get_GetType()->get_Kind())
		{
		case type_bool:
			{
				bool result = pClass->m_pDispatch->bool_Invoke(m_object, pProperty->get_GetMethod(), nullptr, 0);
				return Variant(result);
			}
			break;

		case type_enum:
			{
				int32 result = pClass->m_pDispatch->int32_Invoke(m_object, pProperty->get_GetMethod(), nullptr, 0);
				return Variant((int)result);
			}
			break;

		case type_int:
		case type_unsigned_int:
			{
				int32 result = pClass->m_pDispatch->int32_Invoke(m_object, pProperty->get_GetMethod(), nullptr, 0);
				return Variant((int)result);
			}
			break;

		case type_long_int:
		case type_unsigned_long_int:
			{
				int32 result = pClass->m_pDispatch->int32_Invoke(m_object, pProperty->get_GetMethod(), nullptr, 0);
				return Variant((unsigned int)result);
			}
			break;

		case type_class:
			{
				String result = pClass->m_pDispatch->String_Invoke(m_object, pProperty->get_GetMethod(), nullptr, 0);
				return Variant(result);
			}
			break;

		default:
			ASSERT(0);
		}

			/*
		if (pProperty->get_GetType()->get_Kind() == type_enum)
		{
			return Variant((int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_bool)
		{
			return Variant((bool)(result & 1));
		}
		else if (pProperty->get_GetType()->get_Kind() == type_char ||
					pProperty->get_GetType()->get_Kind() == type_signed_char)
		{
			return Variant((signed char)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_char)
		{
			return Variant((unsigned char)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_short_int)
		{
			return Variant((short)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_short_int)
		{
			return Variant((unsigned short)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_int)
		{
			return Variant((int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_int)
		{
			return Variant((unsigned int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_class &&
				pProperty->get_GetType()->GetClass() == typeid(String).GetType())
		{
			return Variant((StringObject*)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_pointer &&
				pProperty->get_GetType()->GetPointerTo() == typeid(StringA).GetType())
		{
			return Variant((StringA*)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_pointer &&
				pProperty->get_GetType()->GetPointerTo() == typeid(StringW).GetType())
		{
			return Variant((StringW*)result);
		}
		else
			ASSERT(0);
		*/
	}

	virtual String getAttributeName(unsigned int index)
	{
		ClassType* pClass = m_object->GetType();

		Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
		Dispatch::propertymap_t::iterator it = properties.begin();

		while (it != properties.end())
		{
			Property* pProperty = (*it).second;

			if (IsSimple(pProperty))
			{
				index--;
			}

			if ((int)index == -1)
				break;

			++it;
		}

		return (*it).second->get_PropertyName();
	}

	virtual String getChildName(unsigned int index)
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return child->GetType()->get_Name()->ToStringW();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					index--;
				}

				if ((int)index == -1)
					break;

				++it;
			}

			return (*it).second->get_PropertyName();
		}
	}

	virtual String getAttributeNamespaceURI(unsigned int index)
	{
		return nullptr;
	}

	virtual String getChildNamespaceURI(unsigned int index)
	{
		return nullptr;
	}

	virtual unsigned int getChildCount()
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			return collection->GetCount();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			unsigned int count = 0;

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					++count;
				}

				++it;
			}

			return count;
		}
	}

	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}

	virtual XDM::IData* getChildElement(unsigned int index)
	{
#if 0
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return new ObjectData(child, nullptr/*(*it).second*/, this, index);
		}
		else
#endif
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			int i = index;
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					i--;
				}

				if (i == -1)
					break;

				++it;
			}

			ASSERT(it != properties.end());

			Object* object = pClass->m_pDispatch->Object_Invoke(m_object, (*it).second->get_GetMethod(), nullptr, 0);
			if (object != 0)
			{
				/*
				map<Object*, XDM::IData*>::iterator oit = objects.find(object);
				if (oit != objects.end())
				{
					return (*oit).second;
				}
				else
					*/
				{
				//	ObjectData* p = new ObjectData(object, (*it).second, this, index);
				//	ObjectData* p = new ObjectData(object, this);
				//	objects.insert(map<Object*, XDM::IData*>::value_type(object, p));

					if (IObjectCollection* collection = dynamic_cast<IObjectCollection*>(object))
					{
						return new CollectionData(m_root, collection, /*(*it).second,*/ this, index);
					}
					else
					{
						return new ComplexTypeData(m_root, object, this, index);
					}

					//return p;
				}
			}
			else
				return nullptr;
		}
	}

	virtual String getChildText(unsigned int index)
	{
		return null;
	}

	static bool IsSimple(Property* pProperty)
	{
		Type* pReturnType = pProperty->get_GetType();

		if (pReturnType->get_Kind() == type_class &&
			(pReturnType->GetClass() == typeid(String).GetType()))
		{
			return true;
		}
		else if (pReturnType->get_Kind() == type_pointer &&

			(pReturnType->GetPointerTo() == typeid(StringA).GetType() ||
			pReturnType->GetPointerTo() == typeid(StringW).GetType()))
		{
			return true;
		}
		else
		{
			switch (pReturnType->get_Kind())
			{
			case type_bool:
			case type_char:
			case type_signed_char:
			case type_unsigned_char:
			case type_int:
			case type_short_int:
			case type_long_int:
			case type_unsigned_int:
			case type_unsigned_short_int:
			case type_unsigned_long_int:

			case type_enum:
				return true;
			}
		}

		return false;
	}

	virtual Object* GetObject()
	{
		return m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
	//Property* m_parentProperty;
	Object* m_object;
};

XDM::IData* CollectionData::getChildElement(unsigned int index)
{
	Object* child = m_collection->get_ObjectItem(index);
//	return new ComplexTypeData(child, nullptr/*m_parentProperty*/, this, index);
	return new ObjectData(m_root, child, this, index);
}

ComplexTypeData::ComplexTypeData(XDM::IData* root, Object* object, /*Property* parentProperty,*/ XDM::IData* parent, unsigned int position)
{
	m_root = root;
	m_parent = parent;
	m_position = position;

	m_object = object;

//	m_content = new ObjectData(m_object, this, 0);
}

XDM::IData* ComplexTypeData::getChildElement(unsigned int index)
{
	ASSERT(index == 0);

	return new ObjectData(m_root, m_object, this, 0);
}

Web::Element* ToElement(Web::Document* ownerDocument, XDM::IData* data, int elementpos, int level)
{
	if (level > 10)
		return nullptr;

	String name = data->getChildName(elementpos);

	Web::Element* element = ownerDocument->createElement(name);

	XDM::IData* childdata = data->getChildElement(elementpos);
	if (childdata)
	{
		XDM::IData* parent = data;

		/*
		while (parent)
		{
			if (parent->GetObject() == childdata->GetObject())
				break;

			parent = parent->getParent();
		}

		if (parent)
		{
			return nullptr;
		}
		*/

		{
			unsigned int nattributes = childdata->getAttributeCount();
			for (int i = 0; i < nattributes; i++)
			{
				String name = childdata->getAttributeName(i);
				ASSERT(name);

				String data = childdata->getAttributeValue(i);
				if (data)
				{
					element->setAttribute(name, data);
				}
			}
		}

		{
			unsigned int nchildren = childdata->getChildCount();
			for (int i = 0; i < nchildren; i++)
			{
			//	StringW* name = childdata->getChildName(i);

				/*
				XDM::IData* parent = data;

				while (parent)
				{
					if (parent->GetObject() == childdata->GetObject())
						break;

					parent = parent->getParent();
				}

				if (parent == nullptr)
					*/
				{
					Web::Element* childelement = ToElement(ownerDocument, childdata, i, level+1);
					if (childelement)
					{
						element->appendChild(childelement);
					}
				}
			}
		}
	}

	return element;
}
#endif

String GetFilename(Type* pType)
{
	IO::StringWriter strbuilder;
	Mangler mangler(true/*bPreserveTypedefs*/);
	mangler.MangleType(pType, strbuilder);
	strbuilder << L".html";
	return strbuilder.str();
}

/*
template<class TYPE> Stream& write(Stream& stream, TYPE object)
{
	Type* pType = typeid(object).GetType();

	switch (pType->get_Kind())
	{
		case type_class:
		{
			ClassType* pClassType = pType->GetClass();
		}
		break;

	case type_enum:
		{
		}
		break;
	}

	return stream;
}
*/

template<class TYPE, class ARRAY_TYPE> IO::TextWriter& write(IO::TextWriter& stream, Vector<TYPE, ARRAY_TYPE>* items)
{

	size_t count = items->GetCount();
	for (size_t i = 0; i < count; i++)
	{
		if (i > 0) stream << ", ";
		TYPE item = items->get_Item(i);

		stream << item;
	}

	return stream;
}

/*
foreach(decl in declarators)
{
	if (decl is member of pointer type)
	{
		out converttoindex(decl)
	}
	else
		out << decl;

}
*/

//Gui::Application* Gui::Application::s_Current = new PaintApp;

class Exp : public Object
{
public:
	virtual int Evaluate() const = 0;
};

class ConstExp : public Exp
{
public:
};

template<class T>
class TypedConstExp : public ConstExp
{
public:

	CTOR TypedConstExp(T value) : m_value(value)
	{
	}

	virtual int Evaluate() const
	{
		return m_value;
	}

	T m_value;
};

typedef TypedConstExp<int> ConstInt;
typedef TypedConstExp<double> ConstDouble;
typedef TypedConstExp<String> ConstString;

class UnopExp : public Exp
{
public:

	CTOR UnopExp(Exp* exp, char op) : m_exp(exp), m_op(op)
	{
	}

	CTOR UnopExp(vector<Object*>& objs)
	{
		m_op = dynamic_cast<UByteObject*>(objs[0])->GetValue();
		m_exp = dynamic_cast<Exp*>(objs[1]);
	}

	virtual int Evaluate() const
	{
		return -m_exp->Evaluate();
	}

	Exp* m_exp;
	char m_op;
};

class BinopExp : public Exp
{
public:

	CTOR BinopExp(char op, Object* left, Object* right)
	{
		m_left = dynamic_cast<Exp*>(left);
		m_right = dynamic_cast<Exp*>(right);
		m_op = op;
	}

	virtual int Evaluate() const
	{
		int left = m_left->Evaluate();
		int right = m_right->Evaluate();

		switch (m_op)
		{
		case '+':
			return left + right;

		case '-':
			return left - right;

		case '*':
			return left * right;

		case '/':
			return left / right;

		default:
			ASSERT(0);
		}
	}

	Exp* m_left;
	Exp* m_right;
	char m_op;
};

class RuleItemObject : public Object
{
public:

	virtual Object* Parse(const char* & stream) = 0;
};

template<class T>
class ConstTerminalObject : public RuleItemObject
{
public:

	CTOR ConstTerminalObject()
	{
	}

	CTOR ConstTerminalObject(T value) : m_value(value)
	{
	}

	virtual const Type_Info& _Type()
	{
		return typeid(T);
	}

	virtual Object* Parse(const char* & stream)
	{
		if (*stream == m_value)
		{
			++stream;
			return UByteObject::GetObject(m_value);
		}

		return nullptr;
	}

	T m_value;
};

template<class T>
class TerminalObject : public RuleItemObject
{
public:

	CTOR TerminalObject()
	{
	}

	virtual const Type_Info& _Type()
	{
		return typeid(T);
	}

	virtual T* Parse(const char* & stream)
	{
		if (isdigit(*stream))
		{
			int number = *stream - '0';
			++stream;
			T* p = new T(number);
			return p;
		}

		return nullptr;
	}
};

typedef char Token;
int stream_offset;

class ChoiceObject : public RuleItemObject
{
public:
	virtual const Type_Info& _Type()
	{
		return typeid(void);
	}

	Object* Parse(const char* & stream)
	{
	//	Token tok = *stream;
	//	++stream;

		const char* stream2 = stream;

		Object* obj = nullptr;

		list<RuleItemObject*>::iterator it = m_list.begin();
		while (it != m_list.end())
		{
			RuleItemObject* p = *it;

			const char* stream3 = stream;
			Object* res = p->Parse(stream);
			if (res)
			{
				ASSERT(stream3 != stream);
				obj = res;
				break;
			}

			stream = stream2;

			++it;
		}

		return obj;
	}

	list<RuleItemObject*> m_list;
};

template<class T>
class RuleListObject : public RuleItemObject
{
public:

	CTOR RuleListObject()
	{
	}

	virtual const Type_Info& _Type()
	{
		return typeid(T);
	}

	T* Parse(const char* & stream)
	{
	//	Token tok = *stream;
	//	++stream;

		const char* stream2 = stream;

		vector<Object*> objs;

		list<RuleItemObject*>::iterator it = m_list.begin();
		while (it != m_list.end())
		{
			RuleItemObject* p = *it;

			const char* stream3 = stream;
			Object* res = p->Parse(stream);
			if (res == nullptr)
			{
				stream = stream2;
				return nullptr;
			}
			ASSERT(stream3 != stream);

			objs.push_back(res);

			/*
			if (m_op)	// Choice, break at first successfull
			{
				break;
			}*/

			++it;
		}

		T* p = Create(objs);

		return p;
	}

	T* Create(vector<Object*>& objs) const
	{
		T* p = new T(objs);
		return p;
	}

	list<RuleItemObject*> m_list;
};

template<class T>
class BinopRuleObject : public RuleItemObject
{
public:

	CTOR BinopRuleObject(char op, RuleItemObject* exp) : m_op(op), m_exp(exp)
	{
	}

	Object* Parse(const char* & stream)
	{
		Object* exp = m_exp->Parse(stream);

		while (*stream == m_op)
		{
			++stream;

			Object* right = m_exp->Parse(stream);

			exp = new T(m_op, exp, right);
		}

		return exp;
	}

	RuleItemObject* m_exp;
	char m_op;
};

/*
template<class T>
class UnopRuleObject : public RuleItemObject
{
public:
	virtual const Type_Info& _Type()
	{
		return typeid(T);
	}

	T* Parse(const char* & stream)
	{
		if (
		Object* left = m_left->Parse(stream);

		while (*stream == m_op)
		{
			Object* right = m_right->Parse(stream);

			left = new BinopExp(m_op, left, right);
		}

		return p;
	}

	char m_op;
};
*/

#if 0
//template<class T>
class Rule
{
public:

	CTOR Rule()
	{
		m_p = nullptr;//new RuleObject<T>;
	}

	CTOR Rule(RuleItemObject* p) : m_p(p)
	{
	}

	/*
	typedef T t_type;
	*/

	Object* parse(const char* stream)
	{
		return m_p->Parse(stream);
	}

	/*
	T* create()
	{
		return m_p->Create();
	}
	*/

	/*
	template<class T2>
	Rule& operator << (const Terminal<T2>& rule)
	{
		m_p->m_list.push_back(rule.m_p);
		return *this;
	}

	template<class T2>
	Rule& operator << (const Rule<T2>& rule)
	{
		m_p->m_list.push_back(rule.m_p);
		return *this;
	}
	*/

	RuleItemObject* m_p;

	/*
	Rule& operator << (int terminal)
	{
		ASSERT(0);
		return *this;
	}

	Rule& operator << (float terminal)
	{
		ASSERT(0);
		return *this;
	}

	Rule& operator << (double terminal)
	{
		ASSERT(0);
		return *this;
	}

	Rule& operator << (const char* terminal)
	{
		ConstStringTerminal* p = new ConstStringTerminal;
		p->m_str = terminal;
		m_p->m_list.push_back(p);
		return *this;
	}

	Rule& operator << (const Rule& non_terminal)
	{
		m_p->m_list.push_back(non_terminal.m_p);
		return *this;
	}

	read(

	RuleObject* m_p;
	*/
};

template<class T>
class BinopRule : public Rule
{
public:
	CTOR BinopRule() : Rule(nullptr)
	{
	}

	CTOR BinopRule(char op, RuleItemObject* ch) : Rule(new BinopRuleObject<T>(op, ch))
	{
	}
};

template<class T>
class Terminal
{
public:
	CTOR Terminal() : m_p(new TerminalObject<T>)
	{
	}

	TerminalObject<T>* m_p;
};

class Choice
{
public:

	CTOR Choice() : m_p(new ChoiceObject)
	{
	}

	Object* parse(const char* & stream)
	{
		return m_p->Parse(stream);
	}

	ChoiceObject* m_p;
};

Choice operator | (const Rule& r1, const Rule& r2)
{
	Choice c;
	c.m_p->m_list.push_back(r1.m_p);
	c.m_p->m_list.push_back(r2.m_p);
	return c;
}

/*
template<class T, class T2> Choice operator | (const Rule<T>& r1, const Terminal<T2>& r2)
{
	Choice c;
	c.m_p->m_list.push_back(r1.m_p);
	c.m_p->m_list.push_back(r2.m_p);
	return c;
}

template<class T> Choice& operator | (Choice& c, const Rule<T>& r)
{
	c.m_p->m_list.push_back(r.m_p);
	return c;
}

template<class T> Choice& operator | (Choice& c, Terminal<T>& r)
{
	c.m_p->m_list.push_back(r.m_p);
	return c;
}

template<class T, class T2> Rule<T>& operator << (Rule<T>& r, const Terminal<T2>& t)
{
	r.m_p->m_list.push_back(t.m_p);
	return r;
}

template<class T, class T2> Rule<T>& operator << (Rule<T>& r, const Rule<T2>& t)
{
	r.m_p->m_list.push_back(t.m_p);
	return r;
}

template<class T> Rule<T>& operator << (Rule<T>& r, const Choice& c)
{
	r.m_p->m_list.push_back(c.m_p);
	return r;
}

template<class T> Rule<T>& operator << (Rule<T>& r, char ch)
{
	r.m_p->m_list.push_back(new ConstTerminalObject<char>(ch));
	return r;
}
*/

/*
class Token
{
};

class TokenStream
{
public:
};
*/
#endif

/*
int Execute(StringIn cmd)
{
//	return system("\"C:\\Program Files (x86)\\Microsoft Visual Studio 9.0\\VC\\bin\\cl.exe\"");

	return system(CString(cmd).c_str());
}
*/

class PSDCallback : public PSD::ILayeredImageCallback
{
public:
};

class DirectoryChange
{
public:
};

class VariableBinding : public Object, public Gui::IBinding
{
public:
	virtual Variant GetOutput(IBinding* caller) override;
	virtual int SetOutput(IBinding* caller, const Variant& value) override;
	virtual int SetInput(IBinding* caller, const Variant& value) override;
	virtual void* Connect(IInputBinding* binding) override;
};

Variant VariableBinding::GetOutput(IBinding* caller)
{
	return nullptr;
}

int VariableBinding::SetOutput(IBinding* caller, const Variant& value)
{
	return 0;
}

int VariableBinding::SetInput(IBinding* caller, const Variant& value)
{
	return 0;
}
//	virtual Object* GetIn() = 0;

void* VariableBinding::Connect(IInputBinding* binding)
{
	return nullptr;
}

Window* g_window;

void Load(StringIn filename)
{
	String code;

	{
		IO::FileStream fs(filename, IO::FileMode_Open, IO::FileAccess_Read);
		do
		{
			byte ch;
			if (fs.state())
				break;
			fs >> ch;
			code += (char)ch;
		}
		while (!fs.state());
	}

	ecma::ScriptCode scriptcode;
	scriptcode.AddText(code);

	JSVM::ScriptFunction fun;
	fun.m_codeData = scriptcode.m_code.begin();
	fun.m_codeLength = scriptcode.m_code.size();
	fun.m_pContext = scriptcode.m_as_context;

	scriptcode.m_code.Detach();

	JSVM::VM vm;
	vm.m_gui_threadId = gui_threadId;

//	frame->m_variables[String("this")] = g_window;

	fun.dispatch(&vm, g_frame, 0);
}

Exception* lastException;

Exception* GetLastException()
{
	return lastException;
}

// TODO, do this differently

map<String, IBinding*> m_bindings;

void CreateBinding(StringIn varname, IBinding* binding)
{
	dynamic_cast<PropertyValue*>(binding)->m_localValue = undefined;//&PropertyValue::UnsetValue;
	m_bindings.insert(map<String, IBinding*>::value_type(varname, binding));
}

void OnSetVariable(JSVM::StackFrame* frame, StringIn varname, const Variant& value)
{
	IBinding* binding = m_bindings.find(varname)->second;
	if (binding)
	{
		Object* ob = FloatObject::GetObject(value.ToFloat());

		dynamic_cast<PropertyValue*>(binding)->m_localValue = Variant();//&PropertyValue::UnsetValue;
		binding->SetInput(nullptr, ob);
	}
}

void Speak(StringIn str)
{
	HRESULT hr;

	ComPtr<ISpVoice> voice;
	hr = voice.CoCreateInstance(CLSID_SpVoice, nullptr, CLSCTX_ALL);

	ULONG streamNumber;
	hr = voice->Speak(str.c_strw(), 0, &streamNumber);

	Std::Out << "done" << endl;
}

struct Result
{
	uint8* buf;
	long size;
};

long eval(T_Exp* e, PlatformProcess hProcess);

void eval(T_Stm* s, PlatformProcess hProcess)
{
	switch (s->kind)
	{
	case T_Stm::T_MOVE:
		{
			long v = eval(s->move.right, hProcess);

			ASSERT(s->move.left->kind == T_Exp::T_MEM);

			switch (s->move.left->mem.size)
			{
			case 1:
				*(byte*)(s->move.left->mem.mem->const_int.int32Val) = (byte)v;
				break;

			case 2:
				*(int16*)(s->move.left->mem.mem->const_int.int32Val) = (int16)v;
				break;

			case 4:
				*(int32*)(s->move.left->mem.mem->const_int.int32Val) = v;
				break;

			case 8:
				*(int64*)(s->move.left->mem.mem->const_int.int64Val) = v;
				break;
			}
		}
		break;

	case T_Stm::T_CJUMP:
		{
			switch (s->cjump.relop)
			{
			case '<':
				break;
			case '>':
				break;
				
				ASSERT(0);
			}
		}
		break;

	case T_Stm::T_EXP:
		{
			eval(s->exp, hProcess);
		}
		break;

	default:
		ASSERT(0);
	}
}

long eval(T_Exp* e, PlatformProcess hProcess)
{
	switch (e->kind)
	{
	case T_Exp::T_ESEQ:
		{
			eval(e->eseq.s, hProcess);
			return eval(e->eseq.e, hProcess);
		}
		break;

	case T_Exp::T_MEM:
		{
			//printf("mem(");
			long addr = eval(e->mem.mem, hProcess);
			//printf(")size(%d)", e->mem.size);

			uint8* buf = (uint8*)_alloca(e->mem.size);

			if (hProcess == (PlatformProcess)-1)
			{
				memcpy(buf, (LPVOID)addr, e->mem.size);
			}
			else
			{
				SIZE_T nRead;
				ReadProcessMemory(hProcess, (LPVOID)addr, buf, e->mem.size, &nRead);
			}

			if (e->mem.size == 1)
				return *(char*)buf;
			else if (e->mem.size == 2)
				return *(short*)buf;
			else if (e->mem.size == 4)
				return *(int32*)buf;
			/*
			else if (e->mem_size == 8)
				return *(char*)buf;
				*/
			else
				ASSERT(0);
		}
		break;

	case T_Exp::T_CONST:
		{
			//printf("%d", e->const_int.int32);
			return e->const_int.int32Val;
		}
		break;

	case T_Exp::T_BINOP:
		{
			//printf("binop(");
			long e1 = eval(e->binop.left, hProcess);
			//printf(",");
			long e2 = eval(e->binop.right, hProcess);
			//printf(",");

			switch (e->binop.op)
			{
			case '+':
				{
					return e1+e2;
				}
				break;

			case '-':
				{
					return e1-e2;
				}
				break;

			case '*':
				{
					return e1 * e2;
				}
				break;

			case '/':
				{
					if (e2 == 0) raise(Exception("division by zero"));
					return e1 / e2;
				}
				break;

			case '%':
				{
					if (e2 == 0) raise(Exception("division by zero"));
					return e1 % e2;
				}
				break;

			case '|':
				{
					return e1 | e2;
				}
				break;

			case '&':
				{
					return e1 & e2;
				}
				break;

			case '^':
				{
					return e1 ^ e2;
				}
				break;

			case '<':
				{
					return e1 < e2;
				}
				break;

			case '>':
				{
					return e1 > e2;
				}
				break;

			case '<=':
				{
					return e1 <= e2;
				}
				break;

			case '>=':
				{
					return e1 >= e2;
				}
				break;

			case '==':
				{
					return e1 == e2;
				}
				break;

			case '!=':
				{
					return e1 != e2;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	case T_Exp::T_TEMP:
		{
			ASSERT(0);
#if 0

			if ((*e->temp)->getn() == 5)
			{
#if WIN32
				return g_pt->m_context.Ebp;
#elif AMIGA
			//	printf("%X", regs[8+5]);
				return debugger_regs[8+5];
#elif __APPLE__
				// TODO
				return 0;
#endif
			}
			else
				ASSERT(0);
#endif
		}
		break;

		/*
	case T_Exp::T_ESEQ:
		{
			ATLASSERT(0);
			//e->eseq.
		}
		break;
		*/

	case T_Exp::T_NAME:
		{
		//	printf("%d", e->name.label->m_spOffset);
			return e->name.label->m_spOffset;
		}
		break;

	default:
		ASSERT(0);
	}

	return 0;
}

int MyThreadProc(Object* param)
{

//	Std::Out << (Fmt("Hello {0} There {0} {1}") << 5 << 7);

//	::CoInitializeEx(nullptr);
	::CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	g_frame = new JSVM::StackFrame;

	cpp::CGlobal* pGlobal = new cpp::CGlobal;
	pGlobal->m_options = new cpp::Options();
	pGlobal->m_namespace = TypeDatabase::pD->m_globalNamespace;

	int mode = 0;

	String str;
	do
	{
		Console::get_Out() << ">";

		Console::get_In() >> str;

		String str2 = str.SubString(0, str.GetLength()-2);

		if (str2.GetLength() == 0) continue;

		try
		{
			if (str2 == ".")
			{
				mode = 3;
			}
			else if (str2 == "cpp")
			{
				mode = 1;
			}
			else if (str2 == "js")
			{
				mode = 0;
			}
			else
			{
				if (mode == 0)	// js
				{
					ecma::ScriptCode scriptcode;
					scriptcode.AddText(str2);

					JSVM::ScriptFunction fun;
					fun.m_codeData = scriptcode.m_code.begin();
					fun.m_codeLength = scriptcode.m_code.size();
					fun.m_pContext = scriptcode.m_as_context;

					scriptcode.m_code.Detach();	// hm.. or copy in DefineFunction?

			//		m_pFun->m_args.push_back(String(L"event"));

					JSVM::VM vm;
					vm.OnSetVariable = OnSetVariable;
					vm.m_gui_threadId = gui_threadId;
				//	vm.m_global = m_element;

				//	frame->m_variables[String("this")] = m_element;

				//	frame->m_variables[String("this")] = g_window;
				//	frame->m_variables[String("Scene")] = g_scene;

					fun.dispatch(&vm, g_frame, 0);

					if (vm.m_stack.size())
					{
						Variant retval = vm.pop();
						if (!retval.IsUndefined())
						{
							if (retval.IsPtrObject())
							{
								Object* obj = retval.GetObject();
								if (obj)
								{
									Console::get_Out() << obj->ToString() << " : " << retval.GetType()->ToString();
								}
								else
								{
									Console::get_Out() << "null" << " : " << retval.GetType()->ToString();
								}
							}
							else
							{
								Console::get_Out() << retval.ToString() << " : " << retval.GetType()->ToString();
							}

							Console::get_Out() << endl;
						}
					}

					/*
					if (retval.m_variant.kind == VARKIND_BOOL &&
						retval.m_variant.u.bool_val == m_preventDefaultOnReturnValue)
					{
						evt->preventDefault();
					}
					*/
				}
				else if (mode == 1)	// cpp
				{
					cpp::ast::DeclarationList* dlist = cpp::ast::parse_translation_unit(pGlobal, str2);
					if (dlist)
					{
						for (size_t i = 0; i < pGlobal->m_alltypes.size(); ++i)
						{
							NamedType* pType = pGlobal->m_alltypes[i];

							if (pType->get_Kind() == type_class)
							{
								ClassType* pClass = (ClassType*)pType;

								if (pClass->m_pTemplateParams == nullptr)
								{
									int default_alignment = 8;
									cpp::CalcClass(pGlobal, pClass, default_alignment);

									IO::StringWriter strbuilder;
									pType->Write(strbuilder);
									String str = strbuilder.str();
								}
							}

							ASSERT(pType->m_qname.GetLength());
							TypeDatabase::pD->m_namedTypes.insert(map<String, NamedType*>::value_type(pType->m_qname, pType));
							TypeDatabase::pD->m_namedTypesM.insert(multimap<String, NamedType*>::value_type(pType->m_name, pType));
						}

						for (size_t i = 0; i < pGlobal->m_globals.size(); ++i)
						{
							Declarator* decl = pGlobal->m_globals[i];

							decl->SetAddress(new byte[decl->m_pType->get_sizeof()]);
						}
					}
					else
					{
						cpp::ast::Expression* exp = cpp::ast::parse_expression(pGlobal, str2);
						if (exp)
						{
							Tr_Exp* texp = cpp::TransExpression(nullptr/*T_Declarator* frame*/, exp, pGlobal, pGlobal->m_namespace->m_pScope);

							HANDLE hProcess = GetCurrentProcess();

							if (texp)
							{
								Type* pType = texp->m_pType;

								IO::StringWriter valuestr;

								if (pType->get_Kind() != type_class)
								{
									T_Exp* exp = unEx(texp);

									long value = eval(exp, hProcess);

									Console::get_Out() << Variant(value, pType);
									Console::get_Out() << endl;
								}
							}
							else
							{
								Console::get_Out() << "err" << endl;
							}
						}
						else
						{
							Console::get_Out() << "err" << endl;
						}
					}
				}
				else if (mode == 3)
				{
					Expressive::AExpression* aexp = Expressive::Parser::ExpressionFromString(str2);

					Expressive::Translator translator(nullptr);
					Expressive::Expression* exp = translator.TranslateExpression(aexp, g_frame);
					ASSERT(exp->m_pType);

					Expressive::EvalContext context;

					if (exp->m_pType == typeid(bool))
					{
						bool value = exp->EvaluateBool(&context);
						Console::get_Out() << value;
					}
					else if (exp->m_pType == typeid(int))
					{
						int value = exp->EvaluateInt(&context);
						Console::get_Out() << value;
					}
					else if (exp->m_pType == typeid(float))
					{
						float value = exp->EvaluateFloat(&context);
						Console::get_Out() << value;
					}
					else if (exp->m_pType == typeid(double))
					{
						double value = exp->EvaluateDouble(&context);
						Console::get_Out() << value;
					}
					else
					{
						Object* obj = exp->Evaluate(&context);
						Console::get_Out() << (obj? obj->ToString(): "nil");
					}

					Console::get_Out() << " : " << exp->m_pType->ToString();
					Console::get_Out() << endl;
				}
			}
		}
		catch (Exception* e)
		{
			lastException = e;
			Console::get_Out() << e << endl;
		}
		catch (std::exception& e)
		{
			Console::get_Out() << e.what() << endl;

			// TODO, more specific
			lastException = new Exception(e.what());
		}
		catch (...)
		{
			Console::get_Out() << "... exception" << endl;
		}

		if (!Console::s_open)
		{
			break;
		}
 	}
	while (str != "q");

	::CoUninitialize();

	return 0;
}

class Test
{
public:
	void Handle(UIElement* element)
	{
	}
};

void ValidateCheck()
{
	Type* pType = typeid(Visual).GetType();
	if (pType == nullptr)
	{
		raise(SystemException(L"Main - Visual Type = nullptr"));
	}
	size_t s1 = sizeof(Visual);
	size_t s2 = pType->get_sizeof();
	VERIFY(s1 == s2);

	pType = typeid(UIElement).GetType();
	s1 = sizeof(UIElement);
	s2 = pType->get_sizeof();
	VERIFY(s1 == s2);

	VERIFY(sizeof(Geometry) == typeid(Geometry).GetType()->get_sizeof());

	VERIFY(sizeof(UIElement) == typeid(UIElement).GetType()->get_sizeof());
	VERIFY(sizeof(Window) == typeid(Window).GetType()->get_sizeof());

//	VERIFY(sizeof(WindowVisual) == typeid(WindowVisual).GetType()->get_sizeof());

//	VERIFY(sizeof(Event) == typeid(Event).GetType()->get_sizeof());
}

void StartupInfoMessage()
{
	if (true)
	{
		Console::get_Out() << "Platform - ";
#ifdef _M_X64
		Console::get_Out() << "x64";
#elif _M_IX86
		Console::get_Out() << "x86";
#else
		#error "Unknown platform"
#endif

#ifdef _DEBUG
const char* ConfigurationName = "Debug";
#else
const char* ConfigurationName = "Release";
#endif

		Console::get_Out() << " " << ConfigurationName;

		Console::get_Out() << endl;
	}
}

FilePath currentdir()
{
	wchar_t fullpath[1024];
	_wfullpath(fullpath, L".", _countof(fullpath));
	return fullpath;
}

const char* FeatureLevelString(D3D10_FEATURE_LEVEL1 featureLevel)
{
	switch (featureLevel)
	{
	case D3D10_FEATURE_LEVEL_10_1:
		return "10_1";

	case D3D10_FEATURE_LEVEL_10_0:
		return "10_0";

	case D3D10_FEATURE_LEVEL_9_3:
		return "9_3";

	case D3D10_FEATURE_LEVEL_9_2:
		return "9_2";

	case D3D10_FEATURE_LEVEL_9_1:
		return "9_1";
	}

	return nullptr;
}

/*
bool StartApp::DdeExecute(StringIn command)
{
	if (command.LeftOf(4) == "Open")
	{
		//StringIn::iterator
		Std::Out << command << "\n";
		return true;
	}
	
	return false;
}
*/

int StartApp::Main(StringIn cmdline)
{

#if 0
	if (false)
	{
		AllocConsole();
		Std::In->SetFileHandle(GetStdHandle(STD_INPUT_HANDLE));
		Std::Out->SetFileHandle(GetStdHandle(STD_OUTPUT_HANDLE));
		Std::Err->SetFileHandle(GetStdHandle(STD_ERROR_HANDLE));

	//	UnopRule negative_exp;
		BinopRule<BinopExp> additive_exp;
		BinopRule<BinopExp> multiplicative_exp;
		
	//	exp = Terminal<ConstInt>();
	//	negative_exp = UnopRule('-', exp);
		multiplicative_exp = BinopRule<BinopExp>('*', Terminal<ConstInt>().m_p);
		additive_exp = BinopRule<BinopExp>('+', multiplicative_exp.m_p);

		BinopRule<BinopExp> exp = additive_exp;

		String inexp;
		Std::In >> inexp;

		//const char* str = "4+5*2";

		Exp* pExp = (Exp*)exp.parse(CString(inexp).c_str());

		int value = pExp->Evaluate();

		Std::Out << value;
		Std::In >> inexp;

		return 0;
	}
#endif

	/*
	Choice unop;

	Choice exp;
	exp = (binop | Terminal<ConstInt>());

	binop << unop << '+' << unop;
	unop = exp | (Rule<UnopExp>() << '-' << exp);

	const char* str = "-4+5";

	Exp* pExp = (Exp*)exp.parse(str);

	int value = pExp->Evaluate();

	Std::Out << value;
	*/

	Console::Open();
	Console::_In->SetFileHandle(GetStdHandle(STD_INPUT_HANDLE));
	Console::_Out->SetFileHandle(GetStdHandle(STD_OUTPUT_HANDLE));
	Console::_Err->SetFileHandle(GetStdHandle(STD_ERROR_HANDLE));

#if 0
	{
		if (true)
		{
		//	TypeArchive ar(TypeArchive::Mode_Load, L"D:/Users/Sigurd/Documents/VSProjects/MMStudio/bin/Win32/Debug/LFC.typeinfo");
			TypeArchive ar(TypeArchive::Mode_Load, "D:/Users/Sigurd/Documents/VSProjects/MMStudio/bin/Win32/Debug/GUI.typeinfo");
			ar.m_pGlobalNamespace = new Namespace;
			ar.m_typestuff = new TypeStuff;///pD->m_typestuff;
			TypeLib* typelib = new TypeLib;
			ar.m_typelib = typelib;

			ar.ReadHeader();
			ar.MapObject(typelib);
			typelib->Load(ar);

		//	vector<NamedType*, __gc_allocator> types;
		//	types.reserve(ntypes);

			/*
			{
				for (int i = 0; i < typelib->m_types.size(); i++)
				{
					types.push_back(pType);
				}
			}
			*/

			if (false)
			{
				// Namespace/Class Hierarchy

				Web::Document* stylesheet = new Web::GenericDocument;
				stylesheet->set_async(false);
				stylesheet->load(WSTR("D:/Users/Sigurd/Documents/VSProjects/MMStudio/NamespaceHierarchy.xsl"));

				XSLT::Document transformer(stylesheet);

				Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

				//CollectionObject<Array<NamedType*>, NamedType>* collection = new CollectionObject<Array<NamedType*>, NamedType>(types);

				DocumentData* documentData = new DocumentData(nullptr, WSTR("Root"));
				ObjectData* pData = new ObjectData(documentData, pD->m_globalNamespace, documentData, 0);
				documentData->m_child = pData;

				Web::Document* resultDocument = new Web::GenericDocument;

				/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

				resultDocument->save(WSTR("D:/Users/Sigurd/Documents/LerstadSite2/Documentation/NamespaceHierarchy.html"));
			}
			else if (false)
			{
				// Class Hierarchy

				Web::Document* stylesheet = new Web::GenericDocument;
				stylesheet->set_async(false);
				stylesheet->load(WSTR("D:/Users/Sigurd/Documents/LerstadSite2/ClassHierarchy.xsl"));

				XSLT::Document transformer(stylesheet);

				Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

				Vector<NamedType*>* collection = new Vector<NamedType*>(typelib->m_types);

				DocumentData* documentData = new DocumentData(nullptr, WSTR("Root"));
				CollectionData* pData = new CollectionData(documentData, collection, documentData, 0);
				documentData->m_child = pData;

				Web::Document* resultDocument = new Web::GenericDocument;

				/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

				resultDocument->save(WSTR("D:/Users/Sigurd/Documents/VSProjects/MMStudio/Documentation/ClassHierarchy.html"));
			}
			else
			{
				Web::Document* stylesheet = new Web::GenericDocument;
				stylesheet->set_async(false);
				stylesheet->load(WSTR("D:/Users/Sigurd/Documents/VSProjects/MMStudio/stylesheet.xsl"));

				XSLT::Document transformer(stylesheet);

				Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

				DocumentData* documentData = new DocumentData(nullptr, S("Root"));

				{
					uint start = 0;
					uint end = 8000;
					if (end > typelib->m_types.size()) end = typelib->m_types.size();

				//	int count = 0;

					for (uint i = start; i < end; ++i)
					{
						NamedType* pType = typelib->m_types[i];

						if (	pType->get_Kind() == type_class ||
								pType->get_Kind() == type_enum ||
								pType->get_Kind() == type_typedef)
						{
							NamedType* pClass = (NamedType*)pType;

							String filename = GetFilename(pType);//buffer.DetachToString();

							WCHAR fullname[600];
							swprintf_s(fullname, L"D:/Users/Sigurd/Documents/LerstadSite2/Documentation/%s", CStringw(filename).c_str());

							XDM::IData* pData = new ComplexTypeData(documentData/*root*/, pClass, documentData/*parent*/, 0/*position*/);
							documentData->m_child = pData;

							if (false)
							{
								Web::Document* document = new Web::GenericDocument;

								Web::Element* element = ToElement(document, documentData, 0, 0/*level*/);

								document->appendChild(element);

								document->save(WSTR("c:/mmstudio/todoc.xml"));

							}

							Web::Document* resultDocument = new Web::GenericDocument;

							/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

							resultDocument->save(fullname);

							/*
							count++;
							if (count == 3000)
								exit(0);
								*/
						}
					}
				}
			}

			exit(0);
		}
	}
#endif

	HRESULT hr;
	hr = ::OleInitialize(nullptr);
	if (FAILED(hr))
	{
		Console::get_Out() << "Failed: OleInitialize() : hr = " << hr << endl;
		return EXIT_FAILURE;
	}

	MessageWindow::Init();

//	HINSTANCE hinst;

	DdeInstance ddeInstance;
	UINT ddeError = ddeInstance.Initialize(
		(PFNCALLBACK) Application::DdeCallback, // pointer to callback function 
	/*	CBF_FAIL_EXECUTES |        // filter XTYPE_EXECUTE 
		CBF_SKIP_ALLNOTIFICATIONS, // filter notifications 
		*/
		APPCLASS_STANDARD);
	if (ddeError != DMLERR_NO_ERROR)
	{
		Console::get_Out() << "DDE error";
		return EXIT_FAILURE;
	}
	Application::g_ddeInst = &ddeInstance;

	Application::dde_system = ddeInstance.CreateStringHandle(SZDDESYS_TOPIC);
//	HDDEDATA systemService = ddeInstance.NameService(dde_system, DNS_FILTEROFF);

	Application::dde_service_name = ddeInstance.CreateStringHandle(L"Start");
	HDDEDATA startService = ddeInstance.NameService(dde_service_name, DNS_FILTEROFF);

	StartupInfoMessage();

	try
	{
		// TODO, not here
		if (!Graphics::Direct10::s.Init())
		{
			Console::get_Out() << "Failed to init D3DDevice 10, hr = " << Graphics::Direct10::s.m_hr << "\n";

		//	raise_(Exception::FromHResult(GL::Direct10::s.m_hr));
		}
		/*
		else if (Graphics::Direct10::get_D3DDevice1() == nullptr)
		{
			Std::get_Out() <<	"Failed to init D3DDevice 10_1, using D3DDevice 10\n" <<
								"Direct2D and DWrite will not be available\n";

		//	raise_(Exception::FromHResult(GL::Direct10::s.m_hr));
		}
		*/
	}
	catch (Exception* e)
	{
		Console::get_Out() << e;
	}

	if (Graphics::Direct10::get_D3DDevice1())
	{
		Console::get_Out() << "Direct3D" << FeatureLevelString(Graphics::Direct10::get_D3DDevice1()->GetFeatureLevel()) << endl;
	}
	else
	{
		Console::get_Out() << "Direct3D 10_0";
	}

#if 1
	Gui::InitPhysics();
	if (Gui::gPhysics)
	{
		Console::get_Out() << "NVIDIA PhysX" << endl;
	}
#endif

	/*
	const char test[] = "Hello";
	std::remove_extent<decltype(test)>::type hello = 4;
//	std::remove_extent<std::remove_reference<decltype("hello")> >::type hello2 = 4;
	std::remove_reference<decltype("hello")>::type hello2 = "hello";
	decltype("hello") hello3 = "hello";
	std::remove_extent<std::remove_reference<decltype("hello")>>::type hello4;

	string_char<decltype("hello")>::type c = 'h';
	string_char<decltype(L"hello")>::type c1 = L'h';
	*/

	/*
	for (int i = 0; i < 10; ++i)
	{
		String str = S("Hello0");
		Console::get_Out() << str << " " << (long)str.m_stringObject << endl;

		String str2 = S(L"Hello1");
		Console::get_Out() << str2 << " " << (long)str2.m_stringObject << endl;
	}
	*/

#if 0
	if (Graphics::Direct10::get_D3DDevice() == nullptr)
	{
		Std::get_Out() << "Failed to init D3DDevice 10, hr = " << Graphics::Direct10::s.m_hr << "\n";
	}
	else if (Graphics::Direct10::get_D3DDevice1() == nullptr)
	{
		Std::get_Out() <<	"Failed to init D3DDevice 10_1, using D3DDevice 10\n" <<
							"Direct2D and DWrite will not be available\n";

		//	raise_(Exception::FromHResult(GL::Direct10::s.m_hr));
	}
#endif

	if (!Gui::InitAudio())
	{
		Console::get_Out() << "Failed to init X3DAudio\n";
	}

	/*
	{
		testclass tc;

		Variant v(tc);

		bool b = v;
		//String str = v;

		Console::get_Out() << b << endl;
	}
	*/

#if 0
	PSDCallback psdcallback;

	Panel* panel = new Panel();

	if (false)
	{
		IO::FileByteStream file(L"D:\\Users\\Sigurd\\Documents\\Test.psd");
		PSD::PSDLoader loader(&psdcallback);
		loader.Load(&file);
		for (int i = 0; i < loader.GetNumLayers(); i++)
		{
			PSD::ILayer* layer = loader.GetNLayer(i);

			PSD::LAYERINFO layerinfo;
			layer->GetLayerInfo(&layerinfo);

			PSD::LAYERINFO2 layerinfo2;
			layer->GetLayerInfo2(&layerinfo2);

			LDraw::D3D10Texture2D texture;
			texture.Create(GL::Direct10::get_D3DDevice(), layerinfo.rect.GetWidth(), layerinfo.rect.GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM);

			D3D10_MAPPED_TEXTURE2D mapped;
			texture.m_d3d10_texture->Map(D3D10CalcSubresource(0,0,0), D3D10_MAP_WRITE_DISCARD, 0, &mapped);

			int colBytes = 4;
			if (layerinfo.channels == 4)
			{
				layer->ReadPSDLayerChannel(-1, mapped.RowPitch, colBytes, (byte*)mapped.pData + 3);
			}
			else
			{
				//layer->ReadPSDLayerChannel(-1, mapped.RowPitch, colBytes, (byte*)mapped.pData + 3);
			}

			layer->ReadPSDLayerChannel(0, mapped.RowPitch, colBytes, (byte*)mapped.pData + 0);
			layer->ReadPSDLayerChannel(1, mapped.RowPitch, colBytes, (byte*)mapped.pData + 1);
			layer->ReadPSDLayerChannel(2, mapped.RowPitch, colBytes, (byte*)mapped.pData + 2);

			texture.m_d3d10_texture->Unmap(D3D10CalcSubresource(0,0,0));

			BitmapSource* bitmap = new BitmapSource;
			bitmap->m_bitmap = new LDraw::Bitmap(GL::Direct10::get_D3DDevice(), texture);

			BitmapElement* bitmapElement = new BitmapElement();
			bitmapElement->set_Bitmap(bitmap);

			panel->AddChild(bitmapElement);
		}
	}

	Viewbox* viewbox = new Viewbox;

	if (false)
	{
		MetafileLoader wmfloader;
		IO::FileByteStream file(L"C:\\Program Files (x86)\\Microsoft Office\\CLIPART\\PUB60COR\\PE00014_.WMF");
		wmfloader.Load(&file);

		//panel->AddChild(new VisualElement(wmfloader.pCommands));
		//wmfloader.m_rect.GetLeft();

		viewbox->set_Child(new VisualElement(wmfloader.pCommands));

		viewbox->m_rect = wmfloader.GetRect();
	}
#endif

#if 0
	Media3D::Object3DVisual* visual3d;

	Media3D::PerspectiveCamera* camera = new Media3D::PerspectiveCamera();
	camera->LookAt(LDraw::vector3f(1, -1, -2), LDraw::vector3f(0, 0, 0), LDraw::vector3f(0, 1, 0));
//	camera->set_Eye(new Vector3_F(Expressive::Math::cos(_Mouse::screenposX() / 300.0f)*10.0f, Expressive::Math::sin(_Mouse::screenposX() / 300.0f)*10.0f, -10.f));
//	camera->set_Eye(new Vector3_F(_Mouse::screenposX() / 300.0f, 6.0f, 7.f));
	camera->set_Eye(new Vector3_F(0, 5, -10));

	visual3d = new Media3D::Object3DVisual;
	visual3d->set_Camera(camera);

//	Media3D::Mesh::Init();

	if (false)
	{
		DX::xfileparser standard_templates;
		{
			FilePath filepath(_Module.GetFilename());
			filepath.set_Filename(L"standard_templates.x");

			IO::FileByteStream* stream = new IO::FileByteStream(filepath.get_FullPath());
			standard_templates.ParseX(stream);
			stream->Close();
		}

		if (true)
		{
		//	UI::Media3D::C3DSLoader* loader = new UI::Media3D::C3DSLoader;
		//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/tiny.x"));
		//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/spaceship 2.x"));
		//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/airplane 2.x"));
		//	FileByteStream* stream = new FileByteStream(WSTR("C:/DXSDK/Samples/Media/tiger.x"));

			IO::FileByteStream* stream = new IO::FileByteStream(WSTR("../../../Scenes/Test.x"));

			DX::xfileparser parser;
			parser.m_templates = standard_templates.m_templates;
			parser.ParseX(stream);
			stream->Close();

		//	Media3D::Convert(parse.m_objects);

			Media3D::Document3D* document3d = new Media3D::Document3D;

			Media3D::Group* group = new Media3D::Group;
			//UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;

			Media3D::convert(document3d, parser.m_objects, group);

			visual3d->set_Object3D(group);

			/*
			for (int i = 0; i < document3d->m_references.size(); i++)
			{
				document3d->m_references[i]->m_object = document3d->m_namedObjects[document3d->m_references[i]->m_name];
				document3d->m_references[i]->m_object->m_references.Add(document3d->m_references[i]);
			}
			*/

			/*
			group = new UI::Media3D::Group;
			UI::Media3D::Object3DCollection* children = new UI::Media3D::Object3DCollection;

			UI::Media3D::convert(document3d, parser.m_objects, children);
			*/
		}
	}
#endif

#if 0
	byte* audioData = nullptr;

	if (false)
	{
		MediaShow::VOCLoader loader;
		loader.Open(&IO::FileByteStream(WSTR("D:\\Taylor Swift - Our Song.voc")));

		loader.ReadFormatSignature();
		loader.ReadHeader();

		ULONG audioBytes = loader.m_nSamples * loader.m_wfx.nBlockAlign;

		WAVEFORMATEX wfx = loader.m_wfx;
		wfx.cbSize = sizeof(WAVEFORMATEX);

		IXAudio2SourceVoice* pSourceVoice = nullptr;
		pXAudio2->CreateSourceVoice( &pSourceVoice, (WAVEFORMATEX*)&wfx,
									 0, XAUDIO2_DEFAULT_FREQ_RATIO, nullptr, nullptr, nullptr );

		audioData = new byte[audioBytes];
		loader.ReadSamples(audioData, loader.m_nSamples);

		ASSERT(audioBytes <= XAUDIO2_MAX_BUFFER_BYTES);

		XAUDIO2_BUFFER buffer;
		buffer.AudioBytes = audioBytes;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopBegin = 0;
		buffer.LoopCount = 0;
		buffer.LoopLength = 0;
		buffer.pAudioData = audioData;
		buffer.pContext = nullptr;
		buffer.PlayBegin = 0;
		buffer.PlayLength = 0;

		pSourceVoice->SubmitSourceBuffer(&buffer);
		pSourceVoice->Start(0, XAUDIO2_COMMIT_NOW);
//		PlayWave(loader.m_wfx, waveData);
	}
#endif

	Thread* thread = new Thread();
	thread->RunProc(MyThreadProc, nullptr);

	try
	{
//		FilePath path(currentdir());

		IO::FileStream file(IO::Path::Combine(IO::Path::GetDirectoryName(_Module.GetFullPath()), L"../../../TestFiles/Gui.css"), IO::FileMode_Open, IO::FileAccess_Read);
		Style::CSSStream cssparser(new IO::StreamReader(&file));

		StyleSheet* stylesheet = new StyleSheet();
		g_styleSheet = stylesheet;

		cssparser.Parse(stylesheet);
	}
	catch (Exception* e)
	{
		Console::get_Out() << e;
	}

	Variant v(new Gui::Window());
	Console::get_Out() << v.GetType() << endl;

	/*
	{
		Gui::Loader loader(FileStream("D:\\object0.gui", 1));
		loader.adv();
		loader.lex();
		Object* obj = loader.LoadObject();
	}
	*/

	/*
	Gui::Window* window = new Gui::Window();

	g_window = window;
*/

#if 0
	if (true)
	{
		ClassType* pType = typeid(TypeSerializable).GetType()->GetClass();

		Vector<ClassType*, vector<ClassType*>&>* derived = pType->get_DerivedClasses();
		Std::Out << window;
	}

//	Std::Out << "#define WGL_WGLEXT_VERSION " << WGL_WGLEXT_VERSION;

	window->set_Icon(new LineElement(0, 0, 32, 32, new SolidColorBrush(1, 0, 0), 3));
	window->set_TitleText(WSTR("Some Window Title"));
#endif
#if 0
	Gui::RectangleVisual* rectVisual = new Gui::RectangleVisual();
	/*
	rectVisual->m_rect.X = 0;
	rectVisual->m_rect.Y = 0;
	rectVisual->m_rect.Width = 600;
	rectVisual->m_rect.Height = 60;
	rectVisual->m_radius.X = 10;
	rectVisual->m_radius.Y = 10;
	*/
	//rectVisual->m_brush = new Gui::SolidColorBrush(0.8f, 0.8f, 0.85f);

	Gui::TextVisual* textVisual = new Gui::TextVisual();
	textVisual->m_text = new StringW(false, L"Hello World using DirectWrite!");
	//textVisual->m_textLength = wcslen(textVisual->m_textStr);
	textVisual->m_brush = new Gui::SolidColorBrush();
	textVisual->m_fontFamily = new Gui::FontFamily(StringW(false, L"Gabriola"));
	textVisual->set_Size(30.0f);
//	textVisual->m_layoutRect = rectVisual->m_rect;
	textVisual->m_layoutRect.Inflate(-10, -10);
	textVisual->m_transformMatrix = D2D1::Matrix3x2F::Rotation(45, D2D1::Point2F(0, 0));

	Gui::LineVisual* lineVisual = new Gui::LineVisual();
	lineVisual->m_start = LDraw::PointF(10, 10);
	lineVisual->m_end = LDraw::PointF(200, 200);
	lineVisual->m_pen = new Gui::Pen(new Gui::SolidColorBrush(1.0f, 0.0f, 0.0f), 10);

	/*
	Gui::ImageVisual* image = new Gui::ImageVisual;
	image->m_effect = new Gui::Effect(
		new Gui::GaussianBlurEffect(
			new Gui::VisualEffect(image), 5, 5));

	image->m_rect = LDraw::RectF(200, 0, 300, 300);
	Imaging::BitmapLoader loader;
	loader.Load(WSTR("../../../TestFiles/iron_man_5.bmp"));
	image->m_bitmap = loader.GetBitmap();

	Gui::GroupVisual* rootVisual = new Gui::GroupVisual;
	rootVisual->m_children.push_back(rectVisual);
	rootVisual->m_children.push_back(textVisual);
//	rootVisual->m_children.push_back(lineVisual);
	rootVisual->m_children.push_back(image);

	//window->SetVisualRoot(rootVisual);

	Gui::Button* button = new Gui::Button;
	/*
	{
		Gui::ObjectTemplate* pObjectTemplate = new Gui::ObjectTemplate(typeid(Gui::RectangleVisual));

		Gui::Template* pTemplate = new Gui::Template;
		pTemplate->m_object = pObjectTemplate;

		button->set_Width(100);
		button->set_Height(50);
		button->set_Content(WSTR("Hello"));
		button->set_Template(pTemplate);
	}
	*/

//	window->set_Content(rootVisual);
	window->set_Content(button);
#endif

#if 0
	x3d::SceneVisual3D* x3dVisual = nullptr;

	if (true)
	{
		x3d::VRMLLoader loader;
//		x3d::Scene* pScene = pLoader->Load(WSTR("C:/mmstudio/Scenes/test2.wrl"));
//		x3d::Scene* pScene = pLoader->Load(WSTR("C:/Files/VRML/RedSphereBlueBox.x3dv"));
		x3d::Scene* scene = loader.Load(WSTR("../../../TestFiles/RedSphereBlueBox.x3dv"));
		g_scene = scene;

	//	X3DViewer* v = new X3DViewer;
	//	v->m_pWindow->m_pControl->SetScene(pScene);
	//	x3d::COGLSceneRenderer* pViewer = new x3d::COGLSceneRenderer;
	//	pViewer->SetScene(pScene);

		x3dVisual = new x3d::SceneVisual3D;
		x3dVisual->set_Scene(scene);

//		scene->addRoute(new x3d::Route(new ExpressionBinding(nullptr, _Mouse::screenposX() / 200), scene->getDEFName("light")->getField("location")));

		scene->addRoute(new x3d::Route(new ExpressionBinding(nullptr, _Mouse::screenposX() / 200 - 8.0f), scene->getDEFName("body2")->getField("position")));

		MediaClock* pClock = new MediaClock;

		scene->m_clock = pClock;

	//	Ev::Event1<Visual*> OnTick;

	//	Test test;

	//	OnTick.Connect(Ev::EventHandler(&test, &Test::Handle));
	//	OnTick.Connect(Ev::EventHandler(scene, &x3d::Scene::OnTick));
		TimeManager::manager.OnTick.Connect(EventHandler(scene, &x3d::Scene::OnTick));

	//	Control* c = nullptr;
	//	OnTick(c);

		visual3d->set_Object3D(x3dVisual);
//		rootVisual->m_children.push_back(x3dVisual);
	}

	MyPage* page = new MyPage;

	window->m_animate = true;
//	window->set_Opacity(1.0f);
	window->set_Width(600);
	window->set_Height(500);
//	window->set_Content(new Button(WSTR("Hello")));

//	window->set_Content(page);

//	window->set_Content(panel);
//	window->set_Content(viewbox);
	window->set_Content(visual3d);
#endif

#if 0
	{

		/*
		Clock* clock = new Clock;

		FloatAnimation* animation = new Animation;
		animation->set_From( = 

		animation->m_clock = clock;
*/
		Refs refs;

		Window::_Window _templateOwner(&TemplateOwnerExpression::only);

		window->set_Template
		(
			tTemplate(refs,
				tObjectTemplate<WindowVisual>(refs.def(0),
				(
					tProperty(WindowVisual::LeftProperty) = _templateOwner.getLeft(),
					tProperty(WindowVisual::TopProperty) = _templateOwner.getTop(),
					tProperty(WindowVisual::WidthProperty) = _templateOwner.getWidth(),
					tProperty(WindowVisual::HeightProperty) = _templateOwner.getHeight(),
					tProperty(WindowVisual::TitleTextProperty) = _templateOwner.getTitleText(),
					tProperty(WindowVisual::OpacityProperty) = _templateOwner.getOpacity(),
					tProperty(WindowVisual::TopmostProperty) = _templateOwner.getTopmost(),
					//tProperty(WindowVisual::ClipProperty) = refs.use(1).getProperty(WindowVisual::ClipProperty),

					tProperty(WindowVisual::ChildProperty) = tObjectTemplate<TransformVisual>
					((
						tProperty(TransformVisual::TransformProperty) = new RotateTransform(0.5),
						tProperty(TransformVisual::ChildProperty) = tObjectTemplate<GroupVisual>
						((
							tProperty(GroupVisual::ChildrenProperty) = tCollectionObjectTemplate
							((
								tObjectTemplate<StrokeGeometryVisual>(refs.def(1),
								(
									tProperty(StrokeGeometryVisual::BrushProperty) = new SolidColorBrush(1.0f, 0.0f, 0.0f),
									tProperty(StrokeGeometryVisual::WidthProperty) = 10,

									tProperty(StrokeGeometryVisual::GeometryProperty) = tObjectTemplate<RectangleGeometry>(refs.def(2),
									(
										tProperty(RectangleGeometry::XProperty) = Mouse::_Mouse::screenposX() - refs.useAs<WindowVisual::_WindowVisual>(0).getLeft() - refs.useAs<WindowVisual::_WindowVisual>(0).getClientLeft(),
										tProperty(RectangleGeometry::YProperty) = Mouse::_Mouse::screenposY() - refs.useAs<WindowVisual::_WindowVisual>(0).getTop() - refs.useAs<WindowVisual::_WindowVisual>(0).getClientTop(),
										tProperty(RectangleGeometry::WidthProperty) = refs.useAs<TextVisual::_TextVisual>(3).getWidth(),
										tProperty(RectangleGeometry::HeightProperty) = refs.useAs<TextVisual::_TextVisual>(3).getHeight()
									))
								)),
								tObjectTemplate<TextVisual>(refs.def(3),
								(
									tProperty(TextVisual::TextProperty) = WSTR("Hello there, how are you?"),
									tProperty(TextVisual::FontSizeProperty) = 30,
									tProperty(TextVisual::FontFamilyProperty) = new FontFamily(WSTR("Arial")),
									tProperty(TextVisual::LayoutRectProperty) = refs.use(2)
								))
							))
						))
					))
				))
			)
		);
	}
#endif

#if HAVE_SVG
	Web::CHTMLWindow* svgwindow;
	if (false)
	{
		SVGVisual* svgVisual = new SVGVisual();

		svgwindow = new Web::CHTMLWindow;
		svgwindow->m_ownerVisual = svgVisual;

		Web::SVGDocument* svgdocument = new Web::SVGDocument();
		svgdocument->m_pWindow = svgwindow;

	//	svgdocument->load(WSTR("../../../TestFiles/image.svg"));
		svgdocument->load(WSTR("D:/Users/Sigurd/Documents/VSProjects/MMStudio/TestFiles/image.svg"));

		Web::SVGSVGElement* svgelement = dynamic_cast<Web::SVGSVGElement*>(svgdocument->get_documentElement());
		Web::PSVGSVGElement* psvgelement = dynamic_cast<Web::PSVGSVGElement*>(svgelement->m_pNode);

		/*
		for (int i = 0; i < svgelement->get_childNodes()->get_length(); i++)
		{
			w3c::Node* child = svgelement->get_childNodes()->item(i);
			psvgelement->m_rchildList.push_back(child->m_pNode);
		}
		*/

		psvgelement->GetCSSPropertiesAndChildren();
	//	psvgelement->BuildRenderableChildren();
		psvgelement->CalculateBoundsAndChildren();

		svgVisual->m_window = svgwindow;
		svgVisual->m_document = svgdocument;
		svgVisual->m_svgelement = svgelement;
		svgVisual->m_psvgelement = psvgelement;

		/*
		Gui::GroupVisual* groupVisual = new Gui::GroupVisual();

		Gui::PathVisual* pathVisual = new Gui::PathVisual();
		pathVisual->m_brush = new Gui::SolidColorBrush(0.0f, 1.0f, 1.0f);

		pathVisual->m_pathData = new Gui::PathData();
		pathVisual->m_pathData->m_segments.push_back(new Gui::MoveToPathSegment(LDraw::PointF(10, 10)));
		pathVisual->m_pathData->m_segments.push_back(new Gui::CubicBezierToPathSegment(
			LDraw::PointF(70, 10),
			LDraw::PointF(140, 120),
			LDraw::PointF(140, 200)));

		groupVisual->m_children.push_back(svgVisual);
		groupVisual->m_children.push_back(pathVisual);

		/*
		Gui::Window* window2 = new Gui::Window();

		Gui::CompoundGeometry* geom = new Gui::CompoundGeometry();
		geom->m_children.push_back(new Gui::EllipseGeometry(200, 200, 200, 200));
		geom->m_children.push_back(new Gui::RectangleGeometry(LDraw::RectF(20, 20, 100, 100)));
		geom->m_combineOp = Gui::CompoundGeometry::CombineOp_Union;

		//window2->set_Clip(geom);
		//window2->set_Opacity(0.75f);
		window2->set_Width(300);
		window2->set_Height(260);
	//	window2->SetVisualRoot(groupVisual);
		window2->set_Owner(window);
		*/
		window->set_Content(svgVisual);
	}
#endif

#if 0
	window->Show();

	if (false)
	{

	//	ComBSTR versionInfo; // Contains the version string.
	//	ComPtr<IWMPPlayer> spPlayer;  // Smart pointer to IWMPPlayer interface.

	//	hr = spPlayer.CoCreateInstance( __uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER);
	//	hr = spPlayer->get_versionInfo(&versionInfo);

		OleContainer* container = new OleContainer;
		container->AddRef();
		container->m_window = dynamic_cast<Gui::WindowVisual*>(window->get_ShadowTree());

		OleControlSite* ctl = new OleControlSite;
		ctl->m_container = container;

	//	ctl->CoCreateInstance(__uuidof(WindowsMediaPlayer), 0, CLSCTX_INPROC_SERVER);
		ctl->CoCreateInstance(L"TestATLControl.TestAX", 0, CLSCTX_INPROC_SERVER);

		ctl->m_rcPos.left = 0;
		ctl->m_rcPos.top = 0;
		ctl->m_rcPos.right = 800;
		ctl->m_rcPos.bottom = 600;

		ctl->InPlaceActivate();
		//ctl->UIActivate();

		ComPtr<IWMPPlayer> wmPlayer;
		ctl->m_spOleObject.QueryInterface(&wmPlayer);

		ComBSTR url(L"D:\\XXX\\x.nudist.dvd\\01 nudist beach handjob (1.34min).avi");

		wmPlayer->put_URL(url);

		//ComPtr<IWMPPlayer> spPlayer = ctl;  // Smart pointer to IWMPPlayer interface.

	//	Std::Out << versionInfo;

		/*
		String str;

		Std::In >> str;
		Std::Out << str;
		*/
	}
#endif
//	Listen* listen = new Listen;
//	dynamic_cast<WindowVisual*>(window->GetVisual())->OnSize.Connect(EventHandler(listen, &Listen::OnSize));

	// Main message loop:
	int ret = MessageLoop();

	/*
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	*/

	return ret;
}

int APIENTRY wWinMain2(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow)
{
	Gui::Application::s_Current = new StartApp;
	gui_threadId = GetCurrentThreadId();

	int ret;
	
	try
	{
		ret = StartApp::Main(lpCmdLine);
	}
	catch (Exception* e)
	{
		AllocConsole();
		Console::_In->SetFileHandle(GetStdHandle(STD_INPUT_HANDLE));
		Console::_Out->SetFileHandle(GetStdHandle(STD_OUTPUT_HANDLE));
		Console::_Err->SetFileHandle(GetStdHandle(STD_ERROR_HANDLE));

		Console::get_Out() << e;

		char ch;
		Console::get_In() >> ch;

		return EXIT_FAILURE;
	}
	catch (std::exception& e)
	{
		AllocConsole();
		Console::_In->SetFileHandle(GetStdHandle(STD_INPUT_HANDLE));
		Console::_Out->SetFileHandle(GetStdHandle(STD_OUTPUT_HANDLE));
		Console::_Err->SetFileHandle(GetStdHandle(STD_ERROR_HANDLE));

		Console::get_Out() << e.what();

		char ch;
		Console::get_In() >> ch;

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

extern "C" int APIENTRY wWinMain(HINSTANCE hInstance,
				HINSTANCE hPrevInstance,
				LPWSTR    lpCmdLine,
				int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	Environment::ParseCommandLineArgs(lpCmdLine);

//	_Module.SetHandle(hInstance);

	ValidateCheck();

	if (false)
	{
		gc_Protect();

		__try
		{
			return wWinMain2(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		}
		__except (EvalExcept(GetExceptionCode(), GetExceptionInformation()))
		{
			;
		}
	}
	else
	{
		return wWinMain2(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}

	return 0;
}

}	// Start
}	// System
