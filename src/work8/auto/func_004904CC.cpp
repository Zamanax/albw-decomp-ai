typedef unsigned int u32;
typedef float f32;

u32 func_004905E0(f32 ratio);

u32 func_004904CC(f32 x, f32 y) {
    if (y == 0.0f && x == 0.0f) return 0;
    if (y >= 0.0f) {
        if (x >= 0.0f) {
            if (y >= x) return func_004905E0(x / y);
            return 0x40000000 - func_004905E0(y / x);
        } else {
            f32 nx = -x;
            if (y >= nx) return 0 - func_004905E0(nx / y);
            return 0xC0000000 + func_004905E0(y / nx);
        }
    } else {
        if (x >= 0.0f) {
            f32 ny = -y;
            if (ny >= x) return 0x80000000 - func_004905E0(x / ny);
            return 0x40000000 + func_004905E0(ny / x);
        } else {
            if (y <= x) return 0x80000000 + func_004905E0(x / y);
            return 0xC0000000 - func_004905E0(y / x);
        }
    }
}
