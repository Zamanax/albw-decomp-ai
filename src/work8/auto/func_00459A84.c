extern void func_00459280(unsigned char *);
extern void *func_005229AC(void *, void *);
extern void func_00450178(void *, void *);
extern void func_0045E4AC(void *, unsigned char);
extern void func_002DFB78(void *);
extern void *data_007142B0;
extern char data_00713A08[];

void func_00459A84(unsigned char *self, unsigned idx) {
  unsigned char **slot;
  unsigned char *obj;
  func_00459280(self);
  slot = (unsigned char **)(self + 0x1e4);
  if (idx < 3)
    slot = slot + idx;
  obj = *slot;
  func_00450178(data_007142B0, func_005229AC(*(void **)(obj + 0x1c), data_00713A08));
  if (obj[0xcc] == 0)
    func_0045E4AC(data_007142B0, obj[0xf8]);
  *(unsigned *)(self + 0x210) = idx;
  func_002DFB78(data_007142B0);
}
