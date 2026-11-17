struct BitSet58 { char pad[0x58]; unsigned int lo; unsigned int mid; unsigned int hi; };

void func_00259CC4(struct BitSet58 *p, int bit)
{
    unsigned int *w;
    if (bit == -1) {
        p->lo = 0xFFFFFFFFu;
        p->mid = 0xFFFFFFFFu;
        p->hi = 0xFFFFFFFFu;
        return;
    }
    if ((unsigned int)bit < 0x40u) {
        w = &p->lo;
    } else {
        return;
    }
    if (bit >= 0x40) {
        *w = p->hi;
        bit -= 0x40;
    } else {
        if (bit >= 0x20) {
            *w = p->mid;
            bit -= 0x20;
        }
    }
    {
        unsigned int m = 1u;
        unsigned int v = *w;
        *w = v | (m << bit);
    }
}
