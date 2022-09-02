#include "CSRegister.h"
#include "Compiler.h"
using std::endl;
void 
CSRegister::evaluateToken(Compiler* compiler, String& token)
{
  compiler->metatables<<"LUA_METATABLE_REGISTER("<<token<<")"<<endl;
  compiler->tables<<"LUA_TABLE_REGISTER("<<token<<")"<<endl;
  compiler->includes<<"#include \"oa"<<token<<".h\" "<<endl;
  compiler->libs<<"LUA_CLASS_REGISTER("<<token<<");"<<endl;
  compiler->functions<<"LUA_CONSTRUCTOR("<<token<<")"<<endl;
  compiler->className = token;
  compiler->setCurrentState(COMPILER_STATES::kNotPublic);
}
