typedef unsigned char u8; typedef unsigned int u32; typedef signed int s32;
struct Npc {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual s32 v42();
    virtual void request(u8, s32);
    char pad0[0x818 - 4];
    s32 target818;
    char pad1[0x854 - 0x81c];
    u8 request854;
    char pad2[0x861 - 0x855];
    u8 flag861;
};
void func_0060C038(Npc* p) {
p->target818 = p->v42();
    if (p->flag861) { Npc* q = p; q->request(q->request854, -1); }
    p->v38();
}
