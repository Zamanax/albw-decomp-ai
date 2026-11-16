struct Sub { char pad0[0x78]; float m78; char pad1[4]; float m80; };
struct T { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual float* v30(); char p0[0x3dc - 4]; float a3dc; char p1[0x3e4 - 0x3e0]; float b3e4; char p2[0x400 - 0x3e8]; Sub sub; };
int func_00555CFC(T* self) {
  Sub* q = &self->sub;
  if (self->a3dc > 0.0f) {
    if (self->v30()[0] < q->m78) return 0;
  } else if (self->a3dc < 0.0f) {
    if (self->v30()[0] > q->m78) return 0;
  }
  if (self->b3e4 > 0.0f) {
    if (self->v30()[2] < q->m80) return 0;
    return 1;
  }
  if (self->b3e4 < 0.0f) {
    if (self->v30()[2] > q->m80) return 0;
  }
  return 1;
}
