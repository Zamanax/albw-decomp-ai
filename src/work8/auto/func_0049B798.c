typedef unsigned char u8;
typedef unsigned int u32;

typedef void (*VFn3)(void *obj, void *self, u32 flag);

extern void func_0010961C(void *self);
extern void func_00109698(void *self);

void func_0048FBE0(u8 *this_, u32 flag)
{
    u8 *p = this_ + 0x6c;
    u32 v;
    void *obj;

    if (flag == 0) {
        goto else_arm;
    }
    v = 3;
    func_0010961C(p);
    obj = *(void **)(p + 0x48);
    if (obj == 0) {
        goto done;
    }
call:
    (*(VFn3 *)(*(void **)obj))(obj, p, v);
    goto done;
else_arm:
    v = 0;
    func_0010961C(p);
    obj = *(void **)(p + 0x48);
    if (obj != 0) {
        goto call;
    }
done:
    *(u32 *)(p + 0x44) = v;
    func_00109698(p);
}
