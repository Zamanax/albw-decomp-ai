int func_0052FD14(int *self, int *f)
{
    int count = 0;
    int **p = (int **)self[1];
    if ((int **)self[3] != p) {
        do {
            int *e = *p;
            if (e != 0 && *(char *)((char *)e + 0x2d7) == 0) {
                if (((int (*)(int *, int *))((int **)f)[0][0])(f, e) != 0) {
                    count++;
                }
            }
            p = p + 1;
        } while ((int **)self[3] != p);
    }
    return count;
}
