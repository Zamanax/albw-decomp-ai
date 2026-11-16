struct Obj0040E4DC { char pad[8]; float m8; };

void func_0040E4DC(struct Obj0040E4DC* p, int v) {
    float r;
    if (v == 0x7f) {
        r = 65535.0f;
    } else if (v == 0x7e) {
        r = 24.0f;
    } else if (v < 0x32) {
        r = (float)(2 * v + 1) * 0.0078125f * 0.2f;
    } else {
        r = 60.0f / (float)(0x7e - v) * 0.2f;
    }
    p->m8 = r;
}
