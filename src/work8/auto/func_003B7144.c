typedef struct {
    unsigned int key;
    unsigned int a;
    unsigned int b;
    unsigned char c;
    unsigned char pad[3];
} Element_003AF244_16;

extern Element_003AF244_16 data_00709FC8[29];

unsigned int func_003B7144(unsigned int x) {
    unsigned int r = 0;
    if (x < 0x80) {
        int i;
        int n = 29;
        for (i = 0; i < n; i++) {
            Element_003AF244_16* t0 = &data_00709FC8[i];
            if (t0->key == x) {
                unsigned char t2 = data_00709FC8[i].c;
                unsigned char t1 = t2;
                r = t1;
                break;
            }
        }
    }
    return r;
}
