unsigned int func_003E30DC(unsigned int n) {
    unsigned int i;
    if (n <= 3) return 3;
    if (n <= 19) return n | 1;
    for (i = 0; i < 100; i++) {
        unsigned int x = n + i;
        if ((x & 1) == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0 ||
            x % 11 == 0 || x % 13 == 0 || x % 17 == 0)
            continue;
        return x;
    }
    return n | 1;
}
