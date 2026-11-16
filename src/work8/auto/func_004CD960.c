extern void* func_0049F634(void* list);
extern void* func_0049F688(void* list);

int func_004CD960(char* self) {
  void* obj;
  char* list;
  if (*(void**)(self + 0x44) != 0) return 0;
  if (*(int*)(self + 0x2c) > 0) {
    list = self + 0x24;
    obj = func_0049F634(list);
    if (obj != 0) obj = (char*)obj - *(unsigned int*)(list + 0xc);
    *(void**)(self + 0x44) = obj;
    (*(void(**)(void*))((char*)*(void**)obj + 0x18))(obj);
  } else {
    if (*(int*)(self + 0x1c) <= 0) return 1;
    list = self + 0x14;
    obj = func_0049F688(list);
    if (obj != 0) obj = (char*)obj - *(unsigned int*)(list + 0xc);
    *(void**)(self + 0x44) = obj;
    (*(void(**)(void*))((char*)*(void**)obj + 0x10))(obj);
  }
  obj = *(void**)(self + 0x44);
  if (obj != 0) {
    *(unsigned char*)(self + 0x10) = 1;
    (*(void(**)(void*))((char*)*(void**)obj + 0x1c))(obj);
    *(unsigned char*)(self + 0x10) = 0;
  }
  return 1;
}
