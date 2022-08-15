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
  else if(token.find("(") != std::string::npos){
    auto memberName = StringUtilities::split(token,"(")[0];
    if(memberName == compiler->className){
      compiler->setCurrentState(COMPILER_STATES::kConstructor);
    }
    else if(memberName[0] == '~'){
    
    }
    else if(memberName.find("operator") != std::string::npos){
    
    }
    else{
      if(isStatic){
        compiler->tables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<memberName<<")"<<std::endl;
        isStatic = false;
      }
      else{
        compiler->metatables<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<memberName<<")"<<std::endl;
      }
      compiler->functions<<"int LUA_FUNCTION("<<compiler->className<<","<<memberName<<") {}"<<std::endl;
    }
  }
  else if(token == "{"){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  else if(token == "static"){
    isStatic = true;
  }
  
}
