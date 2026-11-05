// 0x10B368: offset-list ctor: inline base list ctor {next=&head; count=0; prev=&head;} + node offset 0x10
typedef int s32;

#include "sead_container.h"


struct OffsetList_10B368 : ListImpl { s32 offset; OffsetList_10B368(); };
OffsetList_10B368::OffsetList_10B368() : offset(0x10) {}
