#include "stdafx.h"
#include "LXML2.h"

#pragma comment(lib, "LFC")
#pragma comment(lib, "XML")
#pragma comment(lib, "XPath")
#pragma comment(lib, "Networking")
#pragma comment(lib, "CSS")
#pragma comment(lib, "Graphics")
#pragma comment(lib, "GUI")
#pragma comment(lib, "EcmaScript")
#pragma comment(lib, "JSVM")

#if _WIN32

#pragma comment(lib, "wininet.lib")	// TODO, only using InternetCombineUrl, make that function myself

//#include <Usp10.h>
//#pragma comment(lib, "Usp10.lib")

#pragma comment(lib, "Mscms.lib")
//#pragma comment(lib, "icm32.lib")

#endif

namespace System
{
namespace Web
{

bool TypeInfo::isDerivedFrom(StringIn typeNamespaceArg, StringIn typeNameArg, unsigned int derivationMethod)
{
	ASSERT(0);
	return false;
}

}	// Web
}

#if 0
/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
   // return _Module.RegisterServer(TRUE);
	 return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
//    return _Module.UnregisterServer(TRUE);
	return S_OK;
}

#endif
