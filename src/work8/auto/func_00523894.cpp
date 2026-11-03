#include "../../work7/ds6/ds6.h"

u32 func_00523894(char* self) {
    f32 t = (f32)*(u32*)(self + 0x2d8) * (1.0f / 60.0f);
    return (s16)(t * 100.0f) % 100;
}
