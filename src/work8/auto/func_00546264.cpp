typedef float f32;
typedef unsigned char u8;
struct Obj546264 { char pad[0x10]; f32 value; char gap[0x24]; u8 flag; };
extern "C" f32 func_00546264(Obj546264* p) {
    f32 seconds = p->flag ? 15.f : 10.f;
    f32 limit = seconds * 60.f;
    f32 v = p->value;
    f32 m = v > limit ? limit : v;
    f32 r = 1.f;
    return (r / limit) * m;
}
