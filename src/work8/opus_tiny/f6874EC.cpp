// 0x6874EC: sead-style OffsetList default ctor (vec_ctor element ctor): ListImpl() then mOffset(-1)
typedef int s32;

#include "sead_container.h"


struct OffsetList_6874EC : ListImpl { s32 mOffset; OffsetList_6874EC(); };
OffsetList_6874EC::OffsetList_6874EC() : mOffset(-1) {}
