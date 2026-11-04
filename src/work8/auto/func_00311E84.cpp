typedef unsigned int u32;

struct Mgr;
extern Mgr* data_0070FB60;
u32 func_00194BFC(int i);
u32 func_0055696C(Mgr* m, u32 id);

bool func_00311E84() {
    u32 count = 0;
    for (int i = 0; i < 10; i++) {
        u32 id = func_00194BFC(i);
        if (id != 1) {
            if (func_0055696C(data_0070FB60, id) >= 2) count++;
        }
    }
    return count == 0;
}
