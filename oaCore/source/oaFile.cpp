#include "oaFile.h"
#include <fstream>
#include <iostream>

#include "oaPath.h"
using std::fstream;



void oaEngineSDK::File::open(const Path& path, FILEFLAGS::E flags)
{
  file = new fstream;
  auto& tempFile = *static_cast<fstream*>(file);
  tempFile.open(path.getCompletePath(),std::ios::out);
  if(!tempFile){
    std::cout<<"error";
  }
  
}

void oaEngineSDK::File::close()
{
  auto& tempFile = *static_cast<fstream*>(file);
  tempFile.close();
  delete file;
}

void oaEngineSDK::File::write(const String& message)
{
  auto& tempFile = *static_cast<fstream*>(file);
  tempFile<<message<<std::endl;
}
