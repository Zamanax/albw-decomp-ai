typedef unsigned int u32;
typedef int s32;
extern void func_00167E04(void*, void*, s32);

void func_0043BD0C(char* p, u32 flag)
{
    switch (flag) {
    case 0:
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x80), 1);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x84), 0);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x88), 0);
        break;
    case 1:
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x80), 0);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x84), 1);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x88), 0);
        break;
    default:
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x80), 0);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x84), 0);
        func_00167E04(*(void**)(p + 0x1c), *(void**)(p + 0x88), 1);
        break;
    }
}
