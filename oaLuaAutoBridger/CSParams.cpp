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
    compiler->functions<<"LUA_ASSERT_ARGS_NUM("<<StringUtilities::intToString(types.size()+1-compiler->isStatic)<<");"<<std::endl;
    int paramNum = 1;
    if(!compiler->isStatic){
      compiler->functions<<"LUA_CHECK_USER_PARAM("<<compiler->className<<","<<1<<");"<<std::endl;
      paramNum = 2;
    }
    for(auto& param : types){
      if(param == "int" || param == "int32" || param == "uint32" || param == "float" || param == "string"){
        compiler->functions<<"LUA_CHECK_PARAM("<<param<<","<<paramNum<<");"<<std::endl;
      }
      else{
        compiler->functions<<"LUA_CHECK_USER_PARAM("<<param<<","<<paramNum<<");"<<std::endl;
      }
      ++paramNum;
    }
    if(compiler->type != "void"){
      compiler->functions<<"auto ret = ";
    }
    if(!compiler->isStatic){
      compiler->functions<<"var1->"<<compiler->memberName<<"(";
      paramNum = 2;
    }
    else{
      compiler->functions<<compiler->className<<"::"<<compiler->memberName<<"(";
      paramNum = 1;
    }
    //oaEngineSDK::print(StringUtilities::intToString(paramNum));
    //oaEngineSDK::print(StringUtilities::intToString(numOfTypes));
    numOfTypes = numOfTypes+2-compiler->isStatic;
    for(;paramNum<numOfTypes; ++paramNum){
      auto& type = types[paramNum-2+compiler->isStatic];
      if(type == "int" || type == "float" || type == "string"){
        compiler->functions<<"var"<<paramNum;
      }
      else{
        compiler->functions<<"*var"<<paramNum;
      }
      if(paramNum+1 != numOfTypes){
        compiler->functions<<",";
      }
    }
    
    compiler->functions<<");"<<std::endl;
    
    if(compiler->type != "void"){
      if(compiler->type != "else"){
        compiler->functions<<"LUA_PUSH_PARAM("<<compiler->type<<","<<"ret)"<<std::endl;
      }
      else{
        compiler->functions<<"LUA_PUSH_USER_PARAM(ret)"<<std::endl;
      }
      compiler->functions<<"return 1;"<<std::endl;
    }
    else{
      compiler->functions<<"return 0;"<<std::endl;
    }

    compiler->functions<<"}"<<std::endl;
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
