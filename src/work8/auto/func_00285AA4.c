typedef unsigned int u32;
typedef unsigned char u8;
typedef struct Mgr { u8 pad0[0x3dbc0]; void* m3DBC0; } Mgr;
typedef struct Self { u8 pad0[0x99c]; u8 m99c; } Self;
typedef struct Obj { u8 pad0[0x488]; u8 m488; } Obj;

extern char* data_00706E20;
extern const u32 ro_00693220;
extern void** func_005841A8(Mgr* mgr, u32 k, void* p);

u32 func_00285AA4(Self* self)
{
    Mgr* mgr = (Mgr*)data_00706E20;
    u32 k = ro_00693220;
    void** p = func_005841A8(mgr, k, mgr->m3DBC0);
    void** end = *(void***)((char*)data_00706E20 + 0x3dbc8);
    if (p == end) return 0;
    for (;;) {
        Obj* o = (Obj*)*p;
        if (o != 0 && o->m488 == 4) {
            self->m99c = 1;
            return 1;
        }
        p = func_005841A8((Mgr*)data_00706E20, ro_00693220, p + 1);
        if (p == end) return 0;
    }
}
