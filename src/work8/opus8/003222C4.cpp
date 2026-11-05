typedef unsigned char u8; typedef signed char s8; typedef unsigned short u16; typedef short s16;
typedef unsigned int u32; typedef int s32;


#include "sead_container.h"
namespace sead {
namespace PtrUtil { inline void* addOffset(const void* p, s32 off) { return (void*)((u32)p + off); } }







}
struct Item {
    char pad[0xfc];
    s32 mfc;
    char pad100[8];
    u8 b108;
};
bool func_0052EF6C(Item* it);

class Mgr {
public:
    void update();
    s32 updateList();
    void func_00321900();
    void func_00321A24();
    void func_00321D9C();
    char pad0[8];
    sead::OffsetList<Item> mList;
    u32 mFlags;
    s32 m1c;
    s32 m20;
};

inline s32 Mgr::updateList()
{
        s32 n = 0;
        for (sead::OffsetList<Item>::robustIterator it = mList.robustBegin(), end = mList.robustEnd(); it != end; ++it) {
            if (!func_0052EF6C(&*it)) {
                mList.erase(&*it);
            } else if (!(*it).b108 || (*it).mfc != 0) {
                n++;
            }
        }
        return n;
}
void Mgr::update()
{
    if (mList.mCount != 0) {
        s32 n = updateList();
        m20 = m1c;
        m1c = n;
        if (mList.mCount != 0) {
            if (mFlags & 0x10) {
                func_00321A24();
                return;
            }
            if (mFlags & 0xb) func_00321D9C();
            if (mFlags & 4) func_00321900();
        }
    }
}
