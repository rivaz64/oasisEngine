#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>
#include "Compiler.h"

using oaEngineSDK::StringUtilities;
using oaEngineSDK::currentPath;
using oaEngineSDK::DirectoryIterator;
using oaEngineSDK::Path;
using oaEngineSDK::fstream;
using oaEngineSDK::ofstream;
using oaEngineSDK::ios;
using oaEngineSDK::String;
using oaEngineSDK::Vector;
using oaEngineSDK::int32;
using std::endl;
String 
eliminateComents(String code){
  if(code.size()==0) return code;
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
analizeFile(const Path& path, ofstream& metatables, ofstream& tables, ofstream& functions, ofstream& fDefinitions, ofstream& includes, ofstream& libs,bool debug)
{
  fstream file(path,ios::in);

  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

  str = eliminateComents(str);

  auto tokens = StringUtilities::split(str," \n");

  Vector<String> temTokens;

  for(auto& token : tokens){
    auto newTokens = StringUtilities::extract(token,"{}(),&;");
    temTokens.insert(temTokens.end(), newTokens.begin(), newTokens.end());
  }
  tokens = temTokens;
  //for(auto token : tokens){
  //  oaEngineSDK::print(token);
  //}
  Compiler compiler(metatables,tables,functions,fDefinitions,includes,libs);

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
  path.append("include");
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
  auto luaLibsPath = getPath("oaLua.h");

  ofstream luaMetatableFile(luaMetatablePath.generic_string());
  ofstream luaTableFile(luaTablePath);
  ofstream luaFunctionsFile(luaFunctionsPath);
  ofstream luaFDefinitionsFile(luaFDefinitionsPath);
  ofstream luaIncludesFile(luaIncludesPath);
  ofstream luaLibsFile(luaLibsPath);

  luaMetatableFile<<"#include \"oaLuaFunctions.h\" "<<endl;
  luaMetatableFile<<"namespace oaEngineSDK { "<<endl;
  luaTableFile<<"#include \"oaLuaFunctions.h\" "<<endl;
  luaTableFile<<"namespace oaEngineSDK { "<<endl;
  luaFunctionsFile<<"#pragma once"<<endl;
  luaFunctionsFile<<"#include \"oaLuaMacros.h\" "<<endl;
  luaFunctionsFile<<"#include \"oaPrerequisitesCore.h\" "<<endl;
  luaFunctionsFile<<"#include \"oaLuaIncludes.h\" "<<endl;
  luaFunctionsFile<<"extern \"C\" {"<<endl<<"#include <lua/lua.h>"<<endl<<"#include <lua/lualib.h>"<<endl<<"#include <lua/lauxlib.h>"<<endl<<"}"<<endl;
  luaFunctionsFile<<"namespace oaEngineSDK { "<<endl;
  luaFDefinitionsFile<<"#include \"oaLuaFunctions.h\" "<<endl;
  luaFDefinitionsFile<<"#include \"oaPrerequisitesCore.h\" "<<endl;
  luaFDefinitionsFile<<"#include \"oaLuaIncludes.h\" "<<endl;
  luaFDefinitionsFile<<"namespace oaEngineSDK { "<<endl;
  luaLibsFile<<"#pragma once"<<endl<<"#include \"oaPrerequisitesCore.h\""<<endl<<"#include \"oaLuaMetatables.h\""<<endl<<"#include \"oaLuaTable.h\""<<endl<<"class lua_State;"<<endl<<"namespace oaEngineSDK{"<<endl<<"FORCEINLINE void loadLuaOasisLib(lua_State *L)"<<endl<<"{"<<endl;
  
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
            //if("oaVector2f.h" == fileName){
            //  int deug = 0;
            //  analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,luaFDefinitionsFile,luaIncludesFile,luaLibs,true);
            //}
            //else
            analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,luaFDefinitionsFile,luaIncludesFile,luaLibsFile,false);
            //oaEngineSDK::print("");
          }
        }
      }
      //oaEngineSDK::print("");
      //oaEngineSDK::print("");
    }
    
  }

  luaMetatableFile<<"} "<<endl;
  luaTableFile<<"} "<<endl;
  luaFunctionsFile<<"} "<<endl;
  luaFDefinitionsFile<<"} "<<endl;
  luaLibsFile<<"} "<<endl<<"} "<<endl;
  luaMetatableFile.close();
  luaTableFile.close();
  luaFunctionsFile.close();
  luaFDefinitionsFile.close();
  luaIncludesFile.close();
  return 0;

}