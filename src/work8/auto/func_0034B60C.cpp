#include "../../work7/gpt22/range.h"
struct SafeOpaque22{const char*text;SafeOpaque22(const char*p):text(p){}virtual~SafeOpaque22(){}virtual void assureTerminationImpl_()const;const char*cstr()const{assureTerminationImpl_();return text;}};
extern "C" void* func_0048E140(void*,FactoryArg22*,const char*);
extern "C" void* func_00491260(void*);
extern "C" char ro_006E3194[];
void* func_0034B60C(void*self,FactoryArg22*p){
  const char * t3 = SafeOpaque22("BootLoadFader").cstr();
  const char * t2 = t3;
  void * t1 = func_0048E140(self,p,t2);
  void*r=t1;
  *(void**)r=ro_006E3194;
  return (char*)((func_00491260((char*)r+0x1ec)))-0x1ec;
}
