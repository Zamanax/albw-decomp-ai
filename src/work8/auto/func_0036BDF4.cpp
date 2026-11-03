typedef unsigned int u32;
extern "C" void func_0036B708(void*);
extern "C" void func_00665670(void*, int);
extern "C" void func_0036BE48(void*);
struct S3 { char pad[0x59c]; u32 m59C; char pad2[0xc60 - 0x5a0]; u32 mC60; };
void func_0036BDF4(S3* self) {
    if (self->mC60 == 0) goto done;
    if (--self->mC60 == 0) {
        u32 v = self->m59C; self->m59C = v | 0x30;
        func_0036B708((char*)self + 0xaa0);
        func_00665670((char*)self + 0xba8, 6);
    }
done:
    func_0036BE48((char*)self + 0xaa0);
}
