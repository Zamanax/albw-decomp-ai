#include "sead_rtti.h"
struct A1 { SEAD_RTTI_BASE(A1) };
typedef const sead::RuntimeTypeInfo::Interface* TI;
bool func_00584E08(void* self, TI t) { return A1::getRuntimeTypeInfoStatic() == t; }
