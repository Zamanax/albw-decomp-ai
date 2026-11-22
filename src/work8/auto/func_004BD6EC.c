extern char data_00706E20[];
extern char ro_006934CC[];
extern unsigned* func_005841A8(char* mgr, unsigned key, unsigned* from);

struct Self {
    char pad[0x814];
    unsigned m814;
};

void func_004BD6EC(struct Self* self) {
    if (self->m814 == 0) {
        char* mgr = *(char**)data_00706E20;
        if (mgr != 0) {
            unsigned* it = func_005841A8(mgr, *(unsigned*)ro_006934CC, *(unsigned**)(mgr + 0x3dbc0));
            while (it != *(unsigned**)(mgr + 0x3dbc8)) {
                if (*it != 0) {
                    self->m814 = *(unsigned*)((char*)(*it) + 0x2cc);
                    return;
                }
                it = func_005841A8(mgr, *(unsigned*)ro_006934CC, it + 1);
            }
        }
    }
}
