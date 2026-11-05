extern void func_0010961C(void *p);
extern void func_00109698(void *p);
typedef void (*Fn3)(void *obj, void *self, int v);

void func_0049B9D0(unsigned char *self, int flag)
{
    unsigned char *s = self + 0xbc;
    int v;
    void *p;
    Fn3 f;
    if (!flag) goto false_path;
    v = 1;
    func_0010961C(s);
    p = *(void **)(s + 0x48);
    if (!p) goto store;
call_obj:
    f = *(Fn3 *)*(void **)p;
    f(p, s, v);
    goto store;
false_path:
    v = 0;
    func_0010961C(s);
    p = *(void **)(s + 0x48);
    if (p) goto call_obj;
store:
    *(int *)(s + 0x44) = v;
    func_00109698(s);
}
