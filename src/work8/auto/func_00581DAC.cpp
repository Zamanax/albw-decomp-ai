typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;
struct X { char pad[0x38]; s32 m38; };
extern s16 data_00015B40[];
s32 f(X* p){
    s32 i = p->m38;
    if (i) {
        s32 v = *(s16*)((char*)data_00015B40 + i);
        if (v >= 0) {
            char* q = (char*)(i + v * 0x143 * 4 + 0x183C);
            if (q) return *(s8*)(q + 0x3ff);
        }
    }
    return 0;
}
