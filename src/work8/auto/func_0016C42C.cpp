typedef unsigned int u32;
typedef float f32;

struct Vec3 {
f32 x, y, z;
};
struct Sub {
u32 m0;
u32 m4;
void** m8;
};
struct Elem {
Sub* m0;
};
struct Mgr {
char pad[8];
Elem* arr[6];
};
struct This16 {
char pad[0xf74];
Mgr* mF74;
};

char* at(Sub*s,const u32&i){
if(s->m0>(u32)i)return (char*)s->m8[i];
return 0;
}
void func_0016C42C(This16* t, u32 idx, const Vec3& v) {
    Mgr* m = t->mF74;
    Elem** a = m->arr;
    u32 k = idx + 3;
    if (k < 6) a += k;
    if (*a == 0) return;
    Elem** b = m->arr;
    if (k < 6) b += k;
    Sub* s = (*b)->m0;
    if (s != 0) {
        char* o = at(s, 0);
        *(Vec3*)(o + 0x40) = v;
    }
}
