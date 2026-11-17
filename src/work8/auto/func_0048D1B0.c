extern char ro_006F52FC[];
extern char ro_006F5930[];
extern void func_00490C38();
extern unsigned func_004A1520(unsigned);
extern void func_0049FAD8(unsigned);

void func_0048D1B0(unsigned a0)
{
    unsigned r4 = a0 + 0x6c;
    *(unsigned *)a0 = (unsigned)ro_006F52FC;
    *(unsigned *)(a0 + 0x6c) = (unsigned)ro_006F5930;
    func_00490C38(r4, (unsigned)ro_006F5930);
    {
        unsigned t1 = func_004A1520(r4);
        func_0049FAD8(t1 - 0x6c);
    }
}
