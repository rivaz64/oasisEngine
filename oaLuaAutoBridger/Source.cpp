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
analizeFile(const Path& path, fstream& luaFile,bool debug)
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

  

  Compiler compiler;

  compiler.debug = debug;

  for(auto& token : tokens){
    compiler.evaluateToken(token,luaFile);
  }
  compiler.end(luaFile);
  file.close();
}

int main(){

  auto separated = StringUtilities::extract("};",'}');

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
              analizeFile(file.path(),luaFile,true);
            }
            else
            analizeFile(file.path(),luaFile,false);
            //oaEngineSDK::print("");
          }
        }
      }
      //oaEngineSDK::print("");
      //oaEngineSDK::print("");
    }
    
  }

  luaFile.close();

  return 0;

}