#include "albw_types.h"
#include "sead_string.h"
struct FactoryArg22;
extern "C" void* func_003BC2F0(void*, FactoryArg22*, const SafeString&);
extern "C" void* func_00491260(void*);
extern "C" char ro_006E9EC4[];
extern "C" void* target(void* obj, FactoryArg22* p){
  void* r = func_003BC2F0(obj, p, SafeString("LoadingFaderBattleOut"));
  *(void**)r = ro_006E9EC4;
  char* q = (char*)func_00491260((char*)r + 0x210) - 0x210;
  *(u32*)(q + 0x2f8) = 0;
  return q;
}
