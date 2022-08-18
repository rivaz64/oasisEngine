#include "CSPublic.h"
#include "Compiler.h"
#include <oaStringUtilities.h>

using oaEngineSDK::StringUtilities;

void 
CSPublic::evaluateToken(Compiler* compiler, String& token)
{
  if(token == "private:" || token == "protected:"){
    compiler->isPublic = false;
    compiler->setCurrentState(COMPILER_STATES::kNotPublic);
  }
  else if(token == "("){
    compiler->memberName = prevToken;
    if(compiler->memberName == compiler->className){
      compiler->setCurrentState(COMPILER_STATES::kConstructor);
    }
    else if(compiler->memberName[0] == '~'){
    
    }
    else if(compiler->memberName.find("operator") != std::string::npos){
    
    }
    else{
      if(compiler->isStatic){
        compiler->tables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<compiler->memberName<<")"<<std::endl;
      }
      else{
        compiler->metatables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<compiler->memberName<<")"<<std::endl;
      }
      compiler->functions<<"static int LUA_FUNCTION("<<compiler->className<<","<<compiler->memberName<<"){"<<std::endl;
      //compiler->fDefinitions<<"int LUA_DEFINITION("<<compiler->className<<","<<compiler->memberName<<")"<<std::endl<<"{"<<std::endl;
      compiler->setCurrentState(COMPILER_STATES::kParams);
      
    }
  }
  else if(token == "{"){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  else if(token == "static"){
    compiler->isStatic = true;
  }
  else if(token == "int" || token == "int32" || token == "uint32" || token == "float" || token == "string" || token == "void" || token == "bool"){
    compiler->type = token;
  }
  else if(token.find("template") != std::string::npos){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  
  prevToken = token;
}
