typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef int s32;

struct Obj { char pad[0xd9]; u8 b; };
struct GameState { char pad[0x18]; s8 k; char pad2[3]; s32 id; };

extern GameState* data_00709DF8;

bool func_00575EB4(Obj* self)
{
    s32 id = data_00709DF8->id;
    s8 k = data_00709DF8->k;
    if (k >= 2 && k <= 5) return false;
    if (k >= 22 && k <= 23) return false;
    if (k >= 24 && k <= 26) return false;
    if (k == 0) {
        if (id == 0x21 || id == 0x25) return false;
        if (id == 0x26 || id == 0x28) return false;
        if (id == 0x29 || id == 0x2a) return false;
        if (id == 0x2b || id == 0x2c) return false;
    } else if (k == 1) {
        if (id == 0x26) return false;
    }
    return self->b == 0;
}
