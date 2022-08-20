#include "CSPublic.h"
#include "Compiler.h"
#include <oaStringUtilities.h>

using oaEngineSDK::StringUtilities;
using std::endl;

void 
CSPublic::evaluateToken(Compiler* compiler, String& token)
{
  if("private:"  == token || "protected:"  == token){
    compiler->isPublic = false;
    compiler->setCurrentState(COMPILER_STATES::kNotPublic);
  }
  else if("(" == token){
    compiler->memberName = prevToken;
    if(compiler->memberName == compiler->className){
      compiler->setCurrentState(COMPILER_STATES::kConstructor);
    }
    else if('~' == compiler->memberName[0]){
    
    }
    else if(compiler->memberName.find("operator") != std::string::npos){
    
    }
    else{
      if(compiler->isStatic){
        compiler->tables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<compiler->memberName<<")"<<endl;
      }
      else{
        compiler->metatables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<compiler->memberName<<")"<<endl;
      }
      compiler->functions<<"static int LUA_FUNCTION("<<compiler->className<<","<<compiler->memberName<<"){"<<endl;
      //compiler->fDefinitions<<"int LUA_DEFINITION("<<compiler->className<<","<<compiler->memberName<<")"<<endl<<"{"<<endl;
      compiler->setCurrentState(COMPILER_STATES::kParams);
      
    }
  }
  else if(";" == token){
    if("override" != prevToken && "(" != prevToken && "template<class" != prevToken && "default" != prevToken && "}" != prevToken){
      //oaEngineSDK::print(compiler->className);
      //oaEngineSDK::print(prevToken);
      compiler->functions<<"LUA_GET_ATTRIBUTE("<<compiler->className<<","<<prevToken<<",";
      if("int" == compiler->type || "int32"  == compiler->type || "uint32"  == compiler->type || "float"  == compiler->type || "string"  == compiler->type || "void" == compiler->type || "bool" == compiler->type){
        compiler->functions<<"LUA_PUSH_PARAM("<<compiler->type<<",ret)";
      }
      else{
        compiler->functions<<"LUA_PUSH_USER_PARAM("<<prevToken<<")";
      }
      compiler->functions<<")"<<endl;

      compiler->metatables<<"LUA_REGISTER_MEMBER("<<compiler->className<<", get_"<<prevToken<<")"<<endl;
    }
    

  }
  else if("{" == token){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  else if("static" == token){
    compiler->isStatic = true;
  }
  else if("int" == token || "int32"  == token || "uint32"  == token || "float"  == token || "string"  == token || "void" == token || "bool" == token){
    compiler->type = token;
  }
  else if(token.find("template") != std::string::npos){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  
  prevToken = token;
}
