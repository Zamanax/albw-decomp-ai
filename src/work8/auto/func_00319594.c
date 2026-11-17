extern char data_00706E20[];
extern char ro_006934CC[];
extern void func_00318BBC(char* self, unsigned v);
extern unsigned* func_005841A8(char* mgr, unsigned key, unsigned* from);

void func_00319594(char* self) {
  func_00318BBC(self, 1);
  char* mgr = *(char**)data_00706E20;
  if (mgr == 0) return;
  unsigned* it = func_005841A8(mgr, *(unsigned*)ro_006934CC, *(unsigned**)(mgr + 0x3dbc0));
  unsigned** endp = (unsigned**)(mgr + 0x3dbc8);
  if (it == *endp) return;
  for (;;) {
    char* node = (char*)*it;
    if (node != 0) {
      *(unsigned*)(self + 0x4c4) = *(unsigned*)(node + 0x2cc);
      return;
    }
    it = func_005841A8(mgr, *(unsigned*)ro_006934CC, it + 1);
    if (it == *endp) return;
  }
}
