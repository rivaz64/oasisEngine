#include "oaPlugInManager.h"
#include <Windows.h>
namespace oaEngineSDK
{

using Function = const void* (*)();

void PlugInManager::load(String DLL)
{
#if OA_PLATFORM == OA_PLATFORM_WIN32
  HINSTANCE hGetProcIDDLL = LoadLibrary(DLL.c_str());
  uint64 err = GetLastError();
  if(!hGetProcIDDLL)
  {
    print("Could not load " + DLL + " Dll");
    print(StringUtilities::intToString(err));
    return;
  }

  Function foundFunction = reinterpret_cast<Function>(GetProcAddress(hGetProcIDDLL, "initPlugIn"));
  if(!foundFunction())
  {
    print("Could not find function: "+DLL);
    return;
  }
  print("loaded "+ DLL);
#endif
}

}

