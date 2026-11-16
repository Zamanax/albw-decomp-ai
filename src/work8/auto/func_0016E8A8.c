typedef unsigned int u32;
typedef unsigned short u16;
extern char data_00709DF8[];
extern char data_0070C8E0[];

void func_0016E8A8(char *self) {
    u32 k = (u32)(*(signed char *)(*(char **)data_00709DF8 + 0x18));
    if (k - 9 > 12) return;
    u32 idx = *(u16 *)(self + 0x5a);
    char *gm = *(char **)(*(char **)data_0070C8E0 + 0x40);
    u32 *slot = (u32 *)(gm + 0x15c);
    slot = slot + (idx >> 5);
    *slot = *slot | (1u << (idx & 31));
}
