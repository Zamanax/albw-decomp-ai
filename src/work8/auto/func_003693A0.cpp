// 0x003693A0: look up two names and keep each found object when it is a node_00714C9C class;
// the second name is optional (skipped when empty).
#include "albw_types.h"
#include "sead_string.h"
#include "typenode.h"

extern const TypeNode data_00714C9C;

struct Child : TypeNodeObject {
    TYPENODE(data_00714C9C)
};

struct Finder {
    TypeNodeObject* func_005229AC(const SafeString& name);
};

struct X {
    u8 pad[0x2c];
    Child* m2C;
    Child* m30;
    void func_003693A0(Finder* finder, const SafeString& name, const SafeString& name2);
};

void X::func_003693A0(Finder* finder, const SafeString& name, const SafeString& name2) {
    if (!finder) return;
    m2C = typeNodeCast<Child*>(finder->func_005229AC(name.cstr()));
    if (name2.mStringTop[0] != '\0') {
        m30 = typeNodeCast<Child*>(finder->func_005229AC(name2.cstr()));
    }
}
