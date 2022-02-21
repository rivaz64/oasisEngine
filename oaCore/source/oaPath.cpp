/**
* @file oaPath.cpp
* @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
* @date 1/15/2022
*/

#include "oaPath.h"
#include <Windows.h>

namespace oaEngineSDK{

bool Path::searchForPath()
{
  OPENFILENAMEW ofn;
  UNICHAR fileName[MAX_PATH] = L"";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = nullptr;
  ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = L"";

  if (!GetOpenFileNameW(&ofn)){
    return false;
  }

  completePath = fileName;

  if (completePath.size()==0){
    return false;
  }

  setCompletePath(fileName);

  return true;
}

void 
Path::setCompletePath(WString path)
{
  _wsplitpath_s(path.c_str(), 
               drive, 
               _MAX_DRIVE,
               direction, 
               _MAX_DIR,
               name , 
               _MAX_FNAME, 
               extencion, 
               _MAX_EXT);
  completePath = path;
}

void 
Path::setCompletePath(String path)
{
  completePath = StringUtilities::toWString(path);
  _wsplitpath_s(completePath.c_str(), 
               drive, 
               _MAX_DRIVE,
               direction, 
               _MAX_DIR,
               name , 
               _MAX_FNAME, 
               extencion, 
               _MAX_EXT);
  
}

}

