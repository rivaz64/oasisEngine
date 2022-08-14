#include "CSPublic.h"
#include "Compiler.h"
#include <oaStringUtilities.h>

using oaEngineSDK::StringUtilities;

void 
CSPublic::evaluateToken(Compiler* compiler, String& token, fstream& luaFile)
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
    else{
      luaFile<<"LUA_REGISTER_MEMBER("<<compiler->className<<","<<memberName<<")"<<std::endl;
    }
  }
  else if(token == "{"){
    compiler->setCurrentState(COMPILER_STATES::kCodeBlock);
  }
  
}
