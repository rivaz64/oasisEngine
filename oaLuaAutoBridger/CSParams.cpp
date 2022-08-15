#include "CSParams.h"
#include "Compiler.h"
#include "oaStringUtilities.h"

using oaEngineSDK::StringUtilities;

void
CSParams::evaluateToken(Compiler* compiler, String& token)
{
  if(token == ")"){
    compiler->continueSearch();
    auto numOfTypes = types.size();
    compiler->fDefinitions<<"LUA_ASSERT_ARGS_NUM("<<StringUtilities::intToString(types.size()+1-compiler->isStatic)<<");"<<std::endl;
    int paramNum = 1;
    if(!compiler->isStatic){
      compiler->fDefinitions<<"LUA_CHECK_USER_PARAM("<<compiler->className<<","<<1<<");"<<std::endl;
      paramNum = 2;
    }
    for(auto& param : types){
      if(param == "int" || param == "int32" || param == "uint32" || param == "float" || param == "string"){
        compiler->fDefinitions<<"LUA_CHECK_PARAM("<<param<<","<<paramNum<<");"<<std::endl;
      }
      else{
        compiler->fDefinitions<<"LUA_CHECK_USER_PARAM("<<param<<","<<paramNum<<");"<<std::endl;
      }
      ++paramNum;
    }
    if(compiler->type != "void"){
      compiler->fDefinitions<<"auto ret = ";
    }
    if(!compiler->isStatic){
      compiler->fDefinitions<<"var1->"<<compiler->memberName<<"(";
      paramNum = 2;
    }
    else{
      compiler->fDefinitions<<compiler->className<<"::"<<compiler->memberName<<"(";
      paramNum = 1;
    }
    //oaEngineSDK::print(StringUtilities::intToString(paramNum));
    //oaEngineSDK::print(StringUtilities::intToString(numOfTypes));
    numOfTypes = numOfTypes+2-compiler->isStatic;
    for(;paramNum<numOfTypes; ++paramNum){
      auto& type = types[paramNum-2+compiler->isStatic];
      if(type == "int" || type == "float" || type == "string"){
        compiler->fDefinitions<<"var"<<paramNum;
      }
      else{
        compiler->fDefinitions<<"*var"<<paramNum;
      }
      if(paramNum+1 != numOfTypes){
        compiler->fDefinitions<<",";
      }
    }
    
    compiler->fDefinitions<<");"<<std::endl;
    
    if(compiler->type != "void"){
      if(compiler->type != "else"){
        compiler->fDefinitions<<"LUA_PUSH_PARAM("<<compiler->type<<","<<"ret)"<<std::endl;
      }
      else{
        compiler->fDefinitions<<"LUA_PUSH_USER_PARAM(ret)"<<std::endl;
      }
      compiler->fDefinitions<<"return 1;"<<std::endl;
    }
    else{
      compiler->fDefinitions<<"return 0;"<<std::endl;
    }

    compiler->fDefinitions<<"}"<<std::endl;
    forRegister = true;
    types.clear();
    compiler->isStatic = false;
    compiler->type = "else";
  }
  else if(token == ","){
    //compiler->continueSearch();
    forRegister = true;
  }
  else if(token == "const"){
  
  }
  else if(forRegister){
    types.push_back(token);
    forRegister = false;
  }
}
