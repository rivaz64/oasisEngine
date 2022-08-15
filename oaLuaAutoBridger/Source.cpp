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
analizeFile(const Path& path, fstream& metatables, fstream& tables, fstream& functions,bool debug)
{
  fstream file(path,ios::in);

  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

  str = eliminateComents(str);

  auto tokens = StringUtilities::split(str," \n");

  Vector<String> temTokens;

  for(auto& token : tokens){
    auto newTokens = StringUtilities::extract(token,'{');
    temTokens.insert(temTokens.end(), newTokens.begin(), newTokens.end());
  }
  tokens = temTokens;
  temTokens.clear();
  if(debug){
    for(auto& token : tokens){
      oaEngineSDK::print(token);
    }
  }
  for(auto& token : tokens){
    auto newTokens = StringUtilities::extract(token,'}');
    temTokens.insert(temTokens.end(), newTokens.begin(), newTokens.end());
  }
  tokens = temTokens;

  Compiler compiler(metatables,tables,functions);

  compiler.debug = debug;

  for(auto& token : tokens){
    compiler.evaluateToken(token);
  }
  compiler.end();
  file.close();
}

int main(){

  auto separated = StringUtilities::extract("};",'}');

  auto path = currentPath().parent_path();
  auto luaMetatablePath = currentPath().parent_path();
  auto luaTablePath = currentPath().parent_path();
  auto luaFunctionsPath = currentPath().parent_path();

  luaMetatablePath.append("oaCore");
  luaTablePath.append("oaCore");
  luaFunctionsPath.append("oaCore");
  luaMetatablePath.append("oaLuaMetatables.h");
  luaTablePath.append("oaLuaTable.h");
  luaFunctionsPath.append("oaLuaFunctions.h");

  fstream luaMetatableFile(luaMetatablePath,ios::out);
  fstream luaTableFile(luaTablePath,ios::out);
  fstream luaFunctionsFile(luaFunctionsPath,ios::out);
  luaMetatableFile<<"#include \"oaLuaFunctions.h\" "<<std::endl;
  luaMetatableFile<<"namespace oaEngineSDK { "<<std::endl;
  luaTableFile<<"#include \"oaLuaFunctions.h\" "<<std::endl;
  luaTableFile<<"namespace oaEngineSDK { "<<std::endl;
  luaFunctionsFile<<"#include \"oaLuaMacros.h\" "<<std::endl;
  luaFunctionsFile<<"extern \"C\" {"<<std::endl<<"#include <lua/lua.h>"<<std::endl<<"#include <lua/lualib.h>"<<std::endl<<"#include <lua/lauxlib.h>"<<std::endl<<"}"<<std::endl;
  luaFunctionsFile<<"namespace oaEngineSDK { "<<std::endl;
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
              analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,true);
            }
            else
            analizeFile(file.path(),luaMetatableFile,luaTableFile,luaFunctionsFile,false);
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

  luaMetatableFile.close();
  luaTableFile.close();
  luaFunctionsFile.close();
  return 0;

}