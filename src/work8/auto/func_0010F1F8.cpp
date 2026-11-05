#include "sead_container.h"

void ListNode::erase_() {
    ListNode* p = mPrev;
    if (p) p->mNext = mNext;
    ListNode* n = mNext;
    if (n) n->mPrev = mPrev;
    mNext = 0;
    mPrev = 0;
}
