struct Entry { unsigned short key; unsigned short pad; unsigned int val; };
extern struct Entry data_00722AD0[];

struct Entry* func_003DA0A0(unsigned int id) {
    int lo = 0;
    int hi = 0x575;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        unsigned short k = data_00722AD0[mid].key;
        if (k == id)
            return &data_00722AD0[mid];
        if (k > id)
            hi = mid - 1;
        else
            lo = mid + 1;
    }
    return 0;
}
