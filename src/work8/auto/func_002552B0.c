int func_002552B0(int *a, int r1) {
    if (a[0x70/4] == 2 && a[0xdc/4] == r1) r1 = 0x12;
    else if (a[0x74/4] == 2 && a[0xe0/4] == r1) r1 = 0x13;
    else if (a[0x78/4] == 2 && a[0xe4/4] == r1) r1 = 0x14;
    else if (a[0x7c/4] == 2 && a[0xe8/4] == r1) r1 = 0x15;
    else if (a[0x80/4] == 2 && a[0xec/4] == r1) r1 = 0x16;
    else return 0;
    if ((unsigned)(r1 - 0x12) <= 4) { int *s = a + r1; int v = s[10]; if (v) { int ret = 1; s[37] = 0; return ret; } return 0; }
    return 0; }
