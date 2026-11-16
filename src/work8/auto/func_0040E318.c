typedef struct Ent {
    char pad[0xc];
    float m0c;
} Ent;

void func_0040E318(Ent* e, int a) {
    float f;
    if (a == 0x7f) {
        f = 65535.0f;
    } else if (a == 0x7e) {
        f = 24.0f;
    } else if (a < 0x32) {
        f = (float)(2 * a + 1) * 0.0078125f * 0.2f;
    } else {
        f = (60.0f / (float)(0x7e - a)) * 0.2f;
    }
    e->m0c = f;
}
