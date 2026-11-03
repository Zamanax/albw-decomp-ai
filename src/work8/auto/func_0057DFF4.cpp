#include "sead_rtti.h"
struct A1 { SEAD_RTTI_BASE(A1) };
typedef const sead::RuntimeTypeInfo::Interface* TI;
bool func_0057DFF4(void* self, TI t) { return A1::getRuntimeTypeInfoStatic() == t; }
