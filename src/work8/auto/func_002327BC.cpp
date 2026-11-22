// 0x002327BC: Group::setMain(obj): cast obj to the member class and make it the main member.
#include "albw_types.h"
#include "sead_container.h"
#include "typenode.h"

extern const TypeNode data_0070B884;

struct Group;

// Member of a Group (node 0x0070B884; its base node is 0x00714C90, stored by func_005C3EA0).
struct Member : TypeNodeObject {
    TYPENODE(data_0070B884)

    // Become the group's main member (0x002327BC).
    void attach(Group* group, bool main) {
        mGroup = group;
        mIsMain = main;
        mInArray = !main;
    }
    // Become an array member of the group (0x002326C0).
    void join(Group* group, bool inArray) {
        mGroup = group;
        mInArray = inArray;
        mIsMain = !inArray;
    }

    u8 pad[0xac];
    Group* mGroup;     // +0xB0
    u8 pad2[0xc];
    u8 mInArray;       // +0xC0
    u8 mIsMain;        // +0xC1
};

// One main member plus an array of members (0x002326C0 add, 0x00232750 clear, 0x002327BC setMain;
// the callers pass a TypeNodeObject found elsewhere, e.g. func_0038A948).
struct Group {
    Member* mMain;                      // +0x00
    sead::PtrArray<Member> mMembers;    // +0x04

    void add(TypeNodeObject* obj);
    void setMain(TypeNodeObject* obj);
};

void Group::setMain(TypeNodeObject* obj) {
    Member* member = typeNodeCast<Member*>(obj);
    mMain = member;
    member->attach(this, true);
}
