typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct { void* vt; const char* s; } StrLocal;

extern char ro_006F5988[];
extern char ro_006A5748[];
extern void func_002317C0(void* control, float value);
extern void func_0012C718(void* self);
extern void func_00533078(void* self, void* str, u32 flags);
extern void func_0066D168(void* p, u32 v);

void func_00454298(void* self) {
    u8* p = (u8*)self;
    u8* o = *(u8**)(p + 0x9c);
    u16 fl = *(u16*)(*(u8**)(o + 0x14) + 0x16);
    if (fl & 4) {
        if (p[0xd] == 3 && p[0xe] == 3) {
            u16 k = 3;
            u16 z = 0;
            u32 v = *(u32*)(p + 0x1c);
            *(u32*)(p + 0xb8) = v;
            *(u16*)(p + 0xb2) = k;
            u8* c = p + 0xb0;
            *(u16*)c = z;
            func_002317C0(c, 1.0f);
            func_0012C718(self);
            o = *(u8**)(p + 0x9c);
            if (o[0xd] == 3 && o[0xe] == 3) func_0012C718(o);
            {
                StrLocal t;
                t.vt = ro_006F5988;
                t.s = ro_006A5748;
                StrLocal* tp = &t;
                func_00533078(self, tp, 0);
            }
        }
    } else if (*(u16*)(*(u8**)(p + 0x14) + 0x16) & 0x80) {
        func_0066D168(p + 0x74, 2);
        {
            StrLocal t;
            t.vt = ro_006F5988;
            t.s = "SE_S_DECIDE_S";
            StrLocal* tp = &t;
                func_00533078(self, tp, 0);
        }
    }
}
