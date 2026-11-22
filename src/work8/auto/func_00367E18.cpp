// 0x00367E18: like 0x00368300, the found object cast twice: to the node_00714C9C class, then to
// its node_0070B880 subclass.
#include "albw_types.h"
#include "sead_string.h"
#include "typenode.h"

extern const TypeNode data_00714C9C;
extern const TypeNode data_0070B880;

struct Base : TypeNodeObject {
    TYPENODE(data_00714C9C)
};

struct Derived : Base {
    TYPENODE(data_0070B880)
};

struct Finder {
    TypeNodeObject* func_005229AC(const SafeString& name);
};

struct X {
    u8 pad[0x38];
    Derived* m38;
    void func_00367E18(Finder* finder, const SafeString& name);
};

void X::func_00367E18(Finder* finder, const SafeString& name) {
    if (!finder) return;
    m38 = typeNodeCast<Derived*>(typeNodeCast<Base*>(finder->func_005229AC(name.cstr())));
}
