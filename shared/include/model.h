// The 0x48-byte model holder (bcl/kcl model): ctor 0x4EDC9C, load 0x4EDB28, ModelMgr::regist
// 0x4A7F00.  Allocation size 0x48 is the immediate of the three `mov r0,#0x48` calls in the npc
// constructor at 0x2CC8C0, 0x2CCF20 and 0x2CCFBC.
//
// Evidence for the members (all from the constructors that write them):
//   +0x10  cleared and reused by 0x4ED9C8 (0x4ED9D0)
//   +0x14  matrix node read at 0x2CD158 `ldr r0,[r0,#0x14]`
//   +0x18  set by 0x4ED9DC; 0x1E3EB0 stores an object whose +0x28 is the model id
//   +0x20  id, 0x4EDADC `str r0,[r4,#0x20]`
//   +0x28  callback object, 0x2CD138 `str r1,[r0,#0x28]`
//   +0x2C  actor id, 0x2CCFA4 `strh r1,[r0,#0x2c]`
//   +0x44  visibility byte, 0x2CD20C `strb sb,[r0,#0x44]`
//
// The bigger objects that matched sources also call `Model` (0x74..0x168 bytes with a Mtx34, an
// animation and a flag word) are a different class: they are not this one and are not migrated here.

#ifndef MODEL_H
#define MODEL_H

#include "albw_types.h"
#include "sead_string.h"

struct Model {
    Model();                                            // 0x4EDC9C
    void load(const sead::SafeString& path);            // 0x4EDB28

    u8 pad000[0x10];
    void* m10;                  // +0x10
    void* m14;                  // +0x14  matrix node
    void* m18;                  // +0x18
    u8 pad01c[4];
    u32 m20;                    // +0x20  id
    u8 pad024[4];
    void* m28;                  // +0x28  callback object
    u16 m2c;                    // +0x2C  actor id
    u8 pad02e[0x44 - 0x2e];
    u8 m44;                     // +0x44  visible flag
    u8 pad045[0x48 - 0x45];     // sizeof == 0x48
};

#endif
