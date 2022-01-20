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
  OPENFILENAME ofn;
  char fileName[MAX_PATH] = "";
  ZeroMemory(&ofn, sizeof(ofn));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = nullptr;
  ofn.lpstrFilter =  "All Files (*.*)\0*.*\0";
  ofn.lpstrFile = fileName;
  ofn.nMaxFile = MAX_PATH;
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.lpstrDefExt = "";

  if (GetOpenFileName(&ofn))

  completePath = fileName;

  if(completePath.size()==0){
    return false;
  }

  _splitpath_s(fileName, 
               drive, 
               _MAX_DRIVE,
               direction, 
               _MAX_DIR,
               name , 
               _MAX_FNAME, 
               extencion, 
               _MAX_EXT);

  return true;
}
void Path::setCompletePath(String path)
{
  _splitpath_s(path.c_str(), 
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

}

