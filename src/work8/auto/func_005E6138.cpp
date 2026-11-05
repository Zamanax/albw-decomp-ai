// static initializer, 0x005E6138: globals with dynamic init, in declaration order
typedef long long s64; typedef float f32;

#include "sead_string.h"

struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
struct Vec2 { f32 x, y; Vec2(f32 a, f32 b) : x(a), y(b) {} };
s64 data_0070BD48 = Id64().v;
Pair data_0070BD50;
SafeString data_0074FAB0[4] = { "N_ArrowT_00", "N_ArrowB_00", "N_ArrowL_00", "N_ArrowR_00" };
SafeString data_0074FAD0[2] = { "Continue", "Exit" };
Vec2 data_0070BD58(90.0f, 28.0f);
Vec2 data_0070BD60(155.0f, 138.0f);
