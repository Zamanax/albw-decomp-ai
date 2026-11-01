typedef unsigned char u8;
typedef unsigned short u16;

struct Obj708 {
    char pad[0x10];
    float m10;
    float m14;
    char pad18[0x1c - 0x18];
    float m1c;
    char pad20[0x2d - 0x20];
    u8 m2d;
    char pad2e[0x3c - 0x2e];
    int m3c;
};

struct Arg708 {
    Obj708* m0;
    char* m4;
    char pad8[4];
    float mC;
};

struct Self708 {
    char pad[0x14];
    void* m14;
};

float func_0056F3E4(Obj708* o);
float func_0069141C(Obj708* o);
void func_00178D58(void* p);
int func_002CB1A4(Self708* self, Arg708* arg, char* p);

int func_002CB3B0(Self708* self, int id, Arg708* arg) {
    switch (id) {
    case 10: {
        Obj708* o = arg->m0;
        float a = arg->mC;
        float d = func_0069141C(o);
        float v = o->m14;
        o->m10 = a;
        o->m14 = d + v;
        if (self->m14) func_00178D58(self->m14);
        return 3;
    }
    case 9: {
        Obj708* o = arg->m0;
        int n = o->m3c;
        if (n > 0) {
            float r = o->m2d ? o->m1c : func_0056F3E4(o);
            float k = (float)n * r;
            int i = (int)((o->m10 - arg->mC) / k) + 1;
            o->m10 = arg->mC + k * (float)i;
        }
        return 1;
    }
    default:
        break;
    }
    char* p = arg->m4 - 2;
    u16 cmd = *(u16*)p;
    char* v;
    if (cmd == 0xe) {
        v = p + 8 + *(u16*)(p + 6);
    } else if (cmd == 0xf) {
        v = p + 6;
    } else {
        arg->m4 = p;
        v = p;
    }
    if (cmd == 0xe || cmd == 0xf) {
        arg->m4 = v;
        if (p != 0) return func_002CB1A4(self, arg, p);
    }
    arg->m4 = v + 2;
    return 0;
}
