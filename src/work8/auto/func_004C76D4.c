typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct TypeInfo { const void* vt; } TypeInfo;
extern const char ro_006F5D74[];
extern TypeInfo data_007261E8;
extern u32 data_007261E4;
extern u8* data_00711DE8;
extern u8* data_0070B728;
extern void* func_005215DC(void* p);
extern int func_00100174(u32* g);
extern void func_00100184(u32* g);

void func_004C76D4(u8* self)
{
    u8* r4 = self + 0x500;
    u32 a = self[0x59c];
    if (a == 0) {
        a = r4[0x9d];
    }
    if (a != 0) return;
    if (r4[0x9e] == 0) {
        if (r4[0x9f] != 0) return;
    } else {
        return;
    }
    if (r4[0xa0] != 0) return;
    if (self[0x5a4] != 1) return;
    if (data_00711DE8 != 0) {
        if (*(u32*)(data_00711DE8 + 0x9c0) > 1) return;
    }
    if (func_005215DC(*(void**)(self + 0x518)) == 0) return;
    {
        u8* g = data_0070B728;
        if (g != 0) {
            u8* ev = *(u8**)(g + 0x44);
            if (ev != 0) {
                if (!(data_007261E4 & 1)) {
                    if (func_00100174(&data_007261E4)) {
                        { TypeInfo* ti = &data_007261E8; ti->vt = ro_006F5D74; }
                        func_00100184(&data_007261E4);
                    }
                }
                {
                    void* vt = *(void**)ev;
                    int (*fp)(void*, const void*) = *(int (**)(void*, const void*))((u8*)vt + 8);
                    if (fp(ev, &data_007261E8) != 0) return;
                }
            }
        }
    }
    *(u16*)(r4 + 0xa2) = 0x3c;
}
