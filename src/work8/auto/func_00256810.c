typedef unsigned char u8;
typedef unsigned int u32;
struct Elem { char pad[0x34]; signed char f; char rest[3]; };
struct S { struct Elem e[20]; char pad[0x19c]; u32 v; };
extern void func_001164F4(void* p, u32 n);
extern u32 func_004A143C(void* p, u32 n);
void func_00256810(struct S *s)
{
    int i;
    func_001164F4(s, 0x600);
    for (i = 0; i < 20; i++) {
        s->e[i].f = -1;
    }
    s->v = func_004A143C(s, 0x5fc);
}
