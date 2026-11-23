#include "sead_string.h"

extern char ro_006F5988[];
extern char ro_00695184[];
extern char ro_0069519C[];
extern char ro_006951DC[];
extern char ro_006951B0[];
extern char ro_006951C8[];
extern "C" void func_0014DBF4(void* a, void* b, unsigned int c, unsigned int d);

extern "C" void func_004F9880(unsigned int kind, void* p, unsigned int x, unsigned int flag) {
  if (flag) {
    if (kind == 9) {
      SafeString s((const char*)ro_0069519C);
      func_0014DBF4(p, &s, x, 0);
    } else if (kind == 10) {
      SafeString s((const char*)ro_00695184);
      func_0014DBF4(p, &s, x, 0);
    }
    return;
  }
  switch (kind) {
    case 8: {
      SafeString s((const char*)ro_006951B0);
      func_0014DBF4(p, &s, x, 0);
      return;
    }
    case 5: {
      SafeString s((const char*)ro_006951C8);
      func_0014DBF4(p, &s, x, 0);
      return;
    }
    case 14: {
      SafeString s((const char*)ro_006951DC);
      func_0014DBF4(p, &s, x, 0);
      return;
    }
    default:
      return;
  }
}
