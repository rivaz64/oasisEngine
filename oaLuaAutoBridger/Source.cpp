#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>
#include "Compiler.h"

using oaEngineSDK::StringUtilities;
using oaEngineSDK::currentPath;
using oaEngineSDK::DirectoryIterator;
using oaEngineSDK::Path;
using oaEngineSDK::fstream;
using oaEngineSDK::ios;
using oaEngineSDK::String;
using oaEngineSDK::Vector;
using oaEngineSDK::int32;

bool 
isClass(String token, fstream& luaFile)
{
  bool ans = token == "class";
  return ans;
}

bool 
isLua(String token, fstream& luaFile)
{
  return token == "class";
}

void 
analizeFile(const Path& path, fstream& luaFile)
{
  fstream file(path,ios::in);

  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

  auto tokens = StringUtilities::split(str," \n");

  String keyWord = "class";

  Compiler compiler;

  for(auto& token : tokens){
    compiler.evaluateToken(token,luaFile);
  }

  file.close();
}

int main(){

  auto splited = StringUtilities::split("hello world"," ");

  auto path = currentPath().parent_path();
  auto luaPath = currentPath().parent_path();

  luaPath.append("oaCore");
  luaPath.append("oaLuaRegister.h");

  fstream luaFile(luaPath,ios::out);
  luaFile<<"#include \"oaLuaMacros.h\" "<<std::endl;
  DirectoryIterator projects(path);

  for(auto&  project : projects){
    auto projectPath = project.path();
    auto projectName = projectPath.filename().string();
    if(projectName[0] == 'o' && projectName[1] == 'a' && projectPath.extension().string() != ".sln"){
      oaEngineSDK::print(projectName);
      DirectoryIterator folders(projectPath);
      for(auto& folder : folders){
        auto folderPath = folder.path();
        auto folderName = folderPath.filename().string();
        if(folderName == "include"){
          DirectoryIterator files(folderPath);
          for(auto& file : files){
            auto fileName = file.path().filename().string();
            oaEngineSDK::print(fileName);
            if("oaVector2f.h" == fileName){
              int deug = 0;
            }
            analizeFile(file.path(),luaFile);
            oaEngineSDK::print("");
          }
        }
      }
      oaEngineSDK::print("");
      oaEngineSDK::print("");
    }
    
  }

  luaFile.close();

  return 0;

}