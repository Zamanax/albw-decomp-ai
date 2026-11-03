typedef unsigned char u8; typedef unsigned int u32; typedef int s32;
template<class T> struct ResourceEntry16 { T* object; u32 reserved[3]; };
struct Elem4 { u8 b[4]; };
struct Obj { s32 count; Elem4 elements[1]; };
struct S { u8 pad0[0xc]; ResourceEntry16<Obj>* entries; u8 pad10[4]; s32 index; };
u8* element(Obj* o, s32 i, u32 offset) { u32 displacement = offset + i * 4; return (u8*)((u32)o + displacement); }
s32 func_0011E7CC(S* p, s32 i, u8* out) {
    if (p->index == -1) return -5;
    Obj* obj = p->entries[p->index].object;
    if (obj->count <= i) return -1;
    u8* src = element(obj, i, 4);
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    out[3] = src[3];
    return 0;
}
