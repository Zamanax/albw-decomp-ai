typedef unsigned int u32;
typedef unsigned char u8;
extern char data_007142C8[];
extern char data_00711F50[];
extern char data_0070D858[];
extern char ro_006F5988[];
extern void func_0051B888(u32, u32);
extern void func_00297298(u32, u32);
extern void func_0010A464(void*);
extern void func_00587F74(u32, void*, void*);
extern void func_0025B7B0(void*, u32);
extern void func_00259354(u32, void*, u32);
extern void func_0025B84C(void*);
struct Name { void* vt; void* s; };
void func_00171D98(char* self)
{
    char obj[0x60];
    struct Name name;
    *(u8*)(self + 0x2ee) = 3;
    func_0051B888(*(u32*)data_007142C8, 0);
    func_00297298(*(u32*)data_00711F50, 0xf);
    func_0010A464(obj);
    struct Name* t2 = &name;
    t2->s = (void*)"SE_S_START";
    struct Name* t1 = t2;
    t1->vt = ro_006F5988;
    func_00587F74(*(u32*)data_00711F50, t2, obj);
    func_0025B7B0(obj, 0xf);
    u32 gm = *(u32*)(data_0070D858 + 8);
    struct Name* t0 = &name;
    t0->vt = ro_006F5988;
    t0->s = (void*)gm;
    func_00259354(*(u32*)data_00711F50, t0, 0x3c);
    func_0025B84C(obj);
}
