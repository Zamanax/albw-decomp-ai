// sead heap and the allocation entry points.
//
// The game allocates everything through sead::Heap: `operator new(size, heap, align)` at
// 0x0010BAB4 and the array form `operator new[](size, heap, align)` at 0x0010CEE0. Both fall back to
// the current heap when the heap argument is null: 0x0010CEE0 does `movs r0,r1` /
// `ldr r0,=data_00715210` / vtable slot +0x18 `alloc(size, align)`, i.e. the arguments are
// (u32 size, sead::Heap* heap, s32 align) with align = 4 at every call site of the string tables.
//
// Allocation tag (126 matched sources carried a private copy, under two spellings): it is one byte
// and has a user-declared constructor. armcc materialises a tag of any other shape: a 4-byte tag
// changes the generated code (3/14 words), and the same happens for a one-byte type *with a data
// member*. The two spellings below are the same type because the game has a single `operator new`
// overload taking it (0x0010BAB4 ignores r1), and the sources use both `new (NoThrow()) T` and
// `new (std::nothrow) T`.
//
// Array allocation: `new (heap, 4) T[n]` on a class with a destructor makes armcc inline the
// {element size, count} cookie, call operator new[] and then the vector constructor, which is what
// the game does for the state-name tables (cookie 0x24 at 0x002072B4, allocator 0x0010CEE0, ctor
// 0x0010BDF0 through __aeabi_vec_ctor). A plain `new T[n]` would go through the C++ library's
// __aeabi_vec_new_cookie instead, so sources that need the game's allocator pass the arguments
// explicitly; the defaults below are the two constants those call sites pass (`mov r1,#0` /
// `mov r2,#4`).

#ifndef SEAD_HEAP_H
#define SEAD_HEAP_H

#include "albw_types.h"

namespace sead {
// The allocation interface. Its layout is only known per class that derives from it, so this header
// declares the type and the entry points, not the virtual table.
class Heap;
}  // namespace sead

using sead::Heap;

// Allocation tag for the non-throwing operator new: one byte, no data members.
class NoThrow {
public:
    NoThrow() {}
};

namespace std {
// Same argument type as the game's std::nothrow_t: one `operator new` (0x0010BAB4) serves both
// spellings, so this is an alias rather than a second, distinct type.
typedef ::NoThrow nothrow_t;
extern const nothrow_t nothrow;
}  // namespace std

// Engine allocators.
void* operator new(u32 size, sead::Heap* heap = 0, s32 align = 4) throw();    // 0x0010BAB4
void* operator new[](u32 size, sead::Heap* heap = 0, s32 align = 4) throw();  // 0x0010CEE0

// Plain, non-throwing allocations. Matched sources declare these size-only forms themselves; the
// declarations here let new headers be self-contained.
void* operator new(u32 size) throw();
void* operator new[](u32 size) throw();
void* operator new(u32 size, NoThrow) throw();

#endif
