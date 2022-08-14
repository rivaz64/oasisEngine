#include <oaPrerequisitesUtilities.h>
#include <oaStringUtilities.h>

using oaEngineSDK::StringUtilities;
using oaEngineSDK::currentPath;
using oaEngineSDK::DirectoryIterator;
using oaEngineSDK::Path;
using oaEngineSDK::fstream;
using oaEngineSDK::ios;
using oaEngineSDK::String;
using oaEngineSDK::Vector;

void 
analizeFile(const Path& path)
{
  fstream file(path,ios::in);

  String str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

  auto tokens = StringUtilities::split(str," ");
  

  for(auto& token : tokens){
    if(token == "LUAEXPORT"){
      oaEngineSDK::print(str);
      break;
    }
    
  }

  file.close();
}

int main(){

  auto splited = StringUtilities::split("hello world"," ");

  auto path = currentPath().parent_path();

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
            analizeFile(file.path());
            oaEngineSDK::print("");
          }
        }
      }
      oaEngineSDK::print("");
      oaEngineSDK::print("");
    }
    
  }

  return 0;

}