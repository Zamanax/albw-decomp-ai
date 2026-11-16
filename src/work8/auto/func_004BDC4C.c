extern char data_00706E20[];
extern char ro_00693A4C[];
extern unsigned* func_005841A8(char* mgr, unsigned key, unsigned* from);

struct Self {
    char pad[0x950];
    unsigned m950;
};

void func_004BDC4C(struct Self* self) {
    if (self->m950 == 0) {
        char* mgr = *(char**)data_00706E20;
        if (mgr != 0) {
            unsigned* it = func_005841A8(mgr, *(unsigned*)ro_00693A4C, *(unsigned**)(mgr + 0x3dbc0));
            while (it != *(unsigned**)(mgr + 0x3dbc8)) {
                if (*it != 0) {
                    self->m950 = *(unsigned*)((char*)(*it) + 0x2cc);
                    return;
                }
                it = func_005841A8(mgr, *(unsigned*)ro_00693A4C, it + 1);
            }
        }
    }
}
