// Run-time type nodes: the game's own class-tree RTTI (not sead::RuntimeTypeInfo, see sead_rtti.h).
//
// Every class of a tree owns one static 4-byte node. The node's only word points at the node of
// the direct base class (null for a root); the owning unit's static initializer stores it, e.g.
// func_005C3EA0 writes 0x00714C9C into node 0x0070B880 and 0x00714C90 into node 0x0070B884, and
// func_005AEB6C writes 0x00714C8C into node 0x00714C9C. An object hands out the node of its class
// through vtable slot 2 (+0x08, after the two destructor slots): 0x0053AB58 is
// `return &node_0070B884` and 0x00569560 `return &node_00714C9C`.
//
// typeNodeCast<T*>(obj) is the inlined down-cast that 50 game functions contain (0x002327BC,
// 0x002326C0, 0x00368300, ...):
//
//     movs  rO, obj              ; null object: result null
//     ldr   rT, =node_of_T       ; target node, loaded before the null test
//     mov   rZ, #0               ; the null result, kept in a callee-saved register
//     beq   null
//     ldr r0,[rO]; ldr r1,[r0,#8]; mov r0,rO; blx r1     ; obj->getTypeNode()
//   loop: cmp r0, rT; beq found; ldr r0,[r0]; cmp r0,#0; bne loop
//   null: mov rO, rZ
//   found:
//
// The spelling below is the one the bytes need (measured on 0x00368300, armcc 4.1 -O3):
//   * the target node is fetched into a local BEFORE the null test (that is what loads rT ahead of
//     the virtual call and keeps it in a callee-saved register);
//   * the walk is a bool member of the node, a pre-tested `while` from `this` (the compiler drops
//     the first test: the node a virtual call returns is not null);
//   * `false` and the null result are the same constant 0: armcc materialises it once, at entry,
//     in a callee-saved register (rZ), and later zero stores of the caller reuse that register.
// A class names its node with TYPENODE(node), where node is the address-named global.

#ifndef ALBW_TYPENODE_H
#define ALBW_TYPENODE_H

struct TypeNode {
    const TypeNode* parent;  // +0x00: node of the direct base class, null for a root

    explicit TypeNode(const TypeNode* base) : parent(base) {}

    bool isDerivedFrom(const TypeNode* node) const {
        const TypeNode* self = this;
        while (self) {
            if (self == node) return true;
            self = self->parent;
        }
        return false;
    }
};

// Root of a node-carrying class tree: slot 0/1 destructors, slot 2 the node of the dynamic class.
class TypeNodeObject {
public:
    virtual ~TypeNodeObject();
    virtual const TypeNode* getTypeNode() const;
};

// Inside a class body: the class's static node is the global NODE (an address-named extern).
#define TYPENODE(NODE) \
    static const TypeNode* typeNode() { return &NODE; }

template <typename T>
inline const TypeNode* typeNodeOfPtr(T* /* only the type */) {
    return T::typeNode();
}

// obj as a TPtr (a pointer type) when obj's class is that class or derives from it, else null.
template <typename TPtr, typename TFrom>
inline TPtr typeNodeCast(TFrom* obj) {
    const TypeNode* node = typeNodeOfPtr(TPtr(0));
    if (obj && obj->getTypeNode()->isDerivedFrom(node)) {
        return static_cast<TPtr>(obj);
    }
    return 0;
}

#endif  // ALBW_TYPENODE_H
