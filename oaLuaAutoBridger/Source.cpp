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

String 
eliminateComents(String code){
  String ans;
  bool inComent = false;
  auto codeSize = code.size();
  for(int32 i = 0; i<codeSize-1; ++i){
    if(!inComent){
      if(code[i] == '/' && code[i+1] == '*'){
        inComent = true;
        ++i;
      }
      else{
        ans.push_back(code[i]);
      }
    }
    else{
      if(code[i] == '*' && code[i+1] == '/'){
        inComent = false;
        ++i;
      }
    }
  }
  return ans;
}

void 
analizeFile(const Path& path, fstream& metatables, fstream& tables, fstream& functions, fstream& fDefinitions, fstream& includes,bool debug)
{
  fstream file(path,ios::in);

  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

  str = eliminateComents(str);

  auto tokens = StringUtilities::split(str," \n");

  Vector<String> temTokens;

  for(auto& token : tokens){
    auto newTokens = StringUtilities::extract(token,"{}(),&");
    temTokens.insert(temTokens.end(), newTokens.begin(), newTokens.end());
  }
  tokens = temTokens;
  //for(auto token : tokens){
  //  oaEngineSDK::print(token);
  //}
  Compiler compiler(metatables,tables,functions,fDefinitions,includes);

  compiler.debug = debug;

  for(auto& token : tokens){
    compiler.evaluateToken(token);
  }

  compiler.end();
  file.close();
}

Path getPath(String&& file){
  auto path = currentPath().parent_path();
  path.append("oaCore");
  path.append(file);
  return path;
}

int main(){
  auto path = currentPath().parent_path();
  auto luaMetatablePath = getPath("oaLuaMetatables.h");
  auto luaTablePath = getPath("oaLuaTable.h");
  auto luaFunctionsPath = getPath("oaLuaFunctions.h");
  auto luaFDefinitionsPath = getPath("oaLuaFunctions.cpp");
  auto luaIncludesPath = getPath("oaLuaIncludes.cpp");

  fstream luaMetatableFile(luaMetatablePath,ios::out);
  fstream luaTableFile(luaTablePath,ios::out);
  fstream luaFunctionsFile(luaFunctionsPath,ios::out);
  fstream luaFDefinitionsFile(luaFDefinitionsPath,ios::out);
  fstream luaIncludesFile(luaIncludesPath,ios::out);

  luaMetatableFile<<"#include \"oaLuaFunctions.h\" "<<std::endl;
  luaMetatableFile<<"namespace oaEngineSDK { "<<std::endl;
  luaTableFile<<"#include \"oaLuaFunctions.h\" "<<std::endl;
  luaTableFile<<"namespace oaEngineSDK { "<<std::endl;
  luaFunctionsFile<<"#include \"oaLuaMacros.h\" "<<std::endl;
  luaFunctionsFile<<"extern \"C\" {"<<std::endl<<"#include <lua/lua.h>"<<std::endl<<"#include <lua/lualib.h>"<<std::endl<<"#include <lua/lauxlib.h>"<<std::endl<<"}"<<std::endl;
  luaFunctionsFile<<"namespace oaEngineSDK { "<<std::endl;
  luaFDefinitionsFile<<"#include \"oaLuaFunctions.h\" "<<std::endl;
  luaFDefinitionsFile<<"#include \"oaPrerequisitesCore.h\" "<<std::endl;
  luaFDefinitionsFile<<"#include \"oaLuaIncludes.h\" "<<std::endl;
  luaFDefinitionsFile<<"namespace oaEngineSDK { "<<std::endl;

  DirectoryIterator projects(path);

  for(auto&  project : projects){
    auto projectPath = project.path();
    auto projectName = projectPath.filename().string();
    if(projectName[0] == 'o' && projectName[1] == 'a' && projectPath.extension().string() != ".sln"){
      //oaEngineSDK::print(projectName);
      DirectoryIterator folders(projectPath);
      for(auto& folder : folders){
        auto folderPath = folder.path();
        auto folderName = folderPath.filename().string();
        if(folderName == "include"){
          DirectoryIterator files(folderPath);
          for(auto& file : files){
            auto fileName = file.path().filename().string();
            //oaEngineSDK::print(fileName);
            if("oaVector2f.h" == fileName){
              int deug = 0;
              analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,luaFDefinitionsFile,luaIncludesFile,true);
            }
            else
            analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,luaFDefinitionsFile,luaIncludesFile,false);
            //oaEngineSDK::print("");
          }
        }
      }
      //oaEngineSDK::print("");
      //oaEngineSDK::print("");
    }
    
  }

  luaMetatableFile<<"} "<<std::endl;
  luaTableFile<<"} "<<std::endl;
  luaFunctionsFile<<"} "<<std::endl;
  luaFDefinitionsFile<<"} "<<std::endl;

  luaMetatableFile.close();
  luaTableFile.close();
  luaFunctionsFile.close();
  luaFDefinitionsFile.close();
  luaIncludesFile.close();
  return 0;

}