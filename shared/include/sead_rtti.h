// Run-time type information for sead-style class trees (ALBW stand-in).
//
// A tree has one root, declared with SEAD_RTTI_BASE. Every other class declares
// SEAD_RTTI_OVERRIDE and names its direct parent. Each class hands out a
// function-local static type-info object. Subtype tests walk the parent chain
// through isDerived(), so a check is a pointer comparison per level.
//
//   struct Actor { SEAD_RTTI_BASE(Actor) };
//   struct Enemy : Actor { SEAD_RTTI_OVERRIDE(Enemy, Actor) };
//
// The engine stores one 4-byte type-info node per class. The matched sources spell that node two
// ways; both are provided here and describe the same object (a source uses one spelling, never both):
//   * the class form above (sead::RuntimeTypeInfo::Interface, virtual isDerived check), and
//   * the raw form below, TypeInfo { const void* vt; }, used by sources that call the object's
//     check through a vtable stand-in instead of a C++ virtual method.
// The node's single word is written by the guarded initializer of the class's
// getRuntimeTypeInfoStatic(): in func_0011F324 (0x11F324) guard 0x726364, node 0x726368,
// vtable 0x6F5D5C; in func_0058F4B4 guard 0x7268B8, node 0x7268BC, vtable 0x6F6500.

#ifndef ALBW_SEAD_RTTI_STANDIN_H
#define ALBW_SEAD_RTTI_STANDIN_H

#ifdef __cplusplus

namespace sead {
namespace RuntimeTypeInfo {

// Abstract node of the type-info graph.
struct Interface {
    virtual bool isDerived(Interface const* ti) const = 0;
};

// Type-info of a tree root: it matches only itself.
struct Root : Interface {
    Root() : Interface() {}
    virtual bool isDerived(Interface const* ti) const { return ti == this; }
};

// Type-info of a class whose direct parent is Parent.
template <typename Parent>
struct Derive : Interface {
    Derive() : Interface() {}
    virtual bool isDerived(Interface const* ti) const {
        if (ti == this) return true;
        return Parent::getRuntimeTypeInfoStatic()->isDerived(ti);
    }
};

}
}

// Raw type-info node: the same 4-byte object as the class-form node above, spelled as plain data
// for sources that inline the guarded initializer themselves. The word is the node's vtable pointer;
// four sources store the parent node pointer instead and name the member `parent` (same layout and
// same store), so those need `parent` renamed to `vt` when they migrate. Only the guarded
// getRuntimeTypeInfoStatic() sequence ever writes it.
struct TypeInfo {
    const void* vt;
};

// Stand-in for an object vtable whose only modelled slot is the RTTI check. The 68 C sources that
// spell the check at vtable offset 0 write exactly this type as `ObjVt` and call
// `a->vt->checkDerived(a, ti)`; a C++ object spells the same slot as a virtual member and calls
// `a->checkDerived(ti)`. Both lower to the same vptr load, slot-0 load and call.
template <typename Obj>
struct ObjVt {
    int (*checkDerived)(Obj* a, TypeInfo const* ti);
};

// Root of a tree. OWNER is the class being declared.
#define SEAD_RTTI_BASE(OWNER) \
public: \
    static sead::RuntimeTypeInfo::Interface const* getRuntimeTypeInfoStatic() { \
        static sead::RuntimeTypeInfo::Root const info; \
        return &info; \
    } \
    static bool checkDerivedRuntimeTypeInfoStatic(sead::RuntimeTypeInfo::Interface const* ti) { \
        return OWNER::getRuntimeTypeInfoStatic() == ti; \
    } \
    virtual bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const* ti) const { \
        return checkDerivedRuntimeTypeInfoStatic(ti); \
    } \
    virtual sead::RuntimeTypeInfo::Interface const* getRuntimeTypeInfo() const { \
        return OWNER::getRuntimeTypeInfoStatic(); \
    }

// Non-root class. OWNER is the class being declared, SUPER its direct parent.
#define SEAD_RTTI_OVERRIDE(OWNER, SUPER) \
public: \
    static sead::RuntimeTypeInfo::Interface const* getRuntimeTypeInfoStatic() { \
        static sead::RuntimeTypeInfo::Derive<SUPER> const info; \
        return &info; \
    } \
    static bool checkDerivedRuntimeTypeInfoStatic(sead::RuntimeTypeInfo::Interface const* ti) { \
        return OWNER::getRuntimeTypeInfoStatic() == ti ? true : SUPER::checkDerivedRuntimeTypeInfoStatic(ti); \
    } \
    virtual bool checkDerivedRuntimeTypeInfo(sead::RuntimeTypeInfo::Interface const* ti) const { \
        return checkDerivedRuntimeTypeInfoStatic(ti); \
    } \
    virtual sead::RuntimeTypeInfo::Interface const* getRuntimeTypeInfo() const { \
        return OWNER::getRuntimeTypeInfoStatic(); \
    }

#else  /* !__cplusplus */

/* C spelling of the same type-info node and vtable stand-in, for the C sources that model the
 * engine's RTTI check directly. 81 matched C sources declare a local TypeInfo: 77 name its word
 * `vt`, 4 `parent`, and 68 declare the slot-0 check vtable exactly as ObjVt below (other sources
 * add leading vtable slots and keep their own type). The object tag stays with the source: it owns
 * the layout, and the check is called as `a->vt->checkDerived(a, ti)`. */
typedef struct TypeInfo { const void* vt; } TypeInfo;

struct Obj;
typedef struct ObjVt {
    int (*checkDerived)(struct Obj* a, const TypeInfo* ti);
} ObjVt;

#endif  /* __cplusplus */

#endif  // ALBW_SEAD_RTTI_STANDIN_H
