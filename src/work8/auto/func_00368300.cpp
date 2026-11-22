// 0x00368300: X::setChild(finder, name): look the name up and keep it when it is a node_00714C9C class.
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
    u8 pad[0x34];
    Child* m34;
    void func_00368300(Finder* finder, const SafeString& name);
};

void X::func_00368300(Finder* finder, const SafeString& name) {
    if (!finder) return;
    m34 = typeNodeCast<Child*>(finder->func_005229AC(name.cstr()));
}
