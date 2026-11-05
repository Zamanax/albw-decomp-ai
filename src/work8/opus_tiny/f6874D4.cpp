// 0x6874D4: sead-style OffsetList default ctor (vec_ctor element ctor): ListImpl() then mOffset(-1)
typedef int s32;

#include "sead_container.h"


struct OffsetList_6874D4 : ListImpl { s32 mOffset; OffsetList_6874D4(); };
OffsetList_6874D4::OffsetList_6874D4() : mOffset(-1) {}
