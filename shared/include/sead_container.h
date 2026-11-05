// sead's intrusive containers and pointer arrays (ALBW stand-in reconstruction).
//
// One definition for every matched source (tools/headermigrate.py measures how many independently
// matched functions accept it unchanged). The game's originals live in namespace sead; the types
// are defined there and re-exported into the global namespace, because most matched sources spell
// them unqualified and the rest spell them `sead::...` — a using-declaration serves both from one
// definition.
//
// Layouts are verified by every matched source that defined the type locally:
//   ListNode   8 bytes  {mPrev, mNext}            erase_ 0x10F1F8 (unlink both ways, then null both)
//   ListImpl  12 bytes  {mStartEnd, mCount}       front 0x49F688, indexOf 0x58080C, erase inline
//   OffsetList +4       {..., mOffset}            node at (object + mOffset)
//   Buffer<T>  8 bytes  {mSize, mBuffer}          at/operator() are the bounds-checked accessor forms
//   PtrArrayImpl 12     {mPtrNum, mPtrNumMax, mPtrs}  erase(position, num) 0x48C320
//   PtrArray<T>        = PtrArrayImpl (base at offset 0) + typed helpers
//
// Uncalled inline members generate no code, so members are a superset; where two source forms of the
// same helper are distinguishable in the bytes, both are kept under distinct names (see the notes).

#ifndef ALBW_SEAD_CONTAINER_H
#define ALBW_SEAD_CONTAINER_H

#include "albw_types.h"

namespace sead {

// Intrusive doubly linked list node, 8 bytes, {mPrev, mNext}. Two source forms: without a
// constructor (8 of the 13 matched sources; the node is linked explicitly by the enclosing list
// constructor, so a constructor would emit no extra code) and with the nulling constructor
// (`ListNodeZero`). `next()` is a real inline helper of the game's node (0x003222C4 calls it).
class ListNode {
public:
    ListNode* next() const { return mNext; }
    ListNode* prev() const { return mPrev; }
    void erase_();
    ListNode* mPrev;
    ListNode* mNext;
};

// Same node with the nulling constructor: `ListNode n;` stores {0, 0} (0x0010CE7C's IDisposer
// constructor, and the ListImpl constructors that begin with `mStartEnd()`).
class ListNodeZero {
public:
    ListNodeZero* next() const { return mNext; }
    void erase_();
    ListNodeZero* mPrev;
    ListNodeZero* mNext;
    ListNodeZero() : mPrev(0), mNext(0) {}
};

// The sentinel node plus the element count. The constructor links the sentinel to itself, which is
// what the matched list/offset-list constructors inline (0x00107AE0, 0x0010B368, 0x0010BDD8,
// 0x006874D4, 0x006874EC); the zeroing of the node that some sources spell as `mStartEnd()` is
// dead once the two links are stored, so it is not repeated here.
class ListImpl {
public:
    ListImpl() : mCount(0) {
        mStartEnd.mNext = &mStartEnd;
        mStartEnd.mPrev = &mStartEnd;
    }
    ListNode* front() const { return mCount > 0 ? mStartEnd.mNext : 0; }
    s32 indexOf(const ListNode* n) const;
    void erase(ListNode* n) { n->erase_(); --mCount; }
    ListNode mStartEnd;
    s32 mCount;
};

// Same two members, constructor out of line: 0x00689C64 matches the in-TU definition
// `ListImplOut::ListImplOut() : mStartEnd(), mCount(0) { ... }`, so this type only declares it.
class ListImplOut {
public:
    ListImplOut();
    ListNodeZero* front() const { return mCount > 0 ? mStartEnd.mNext : 0; }
    ListNodeZero mStartEnd;
    s32 mCount;
};

// A list whose elements embed their node at a fixed offset. front/toObj/next come from the matched
// inline users 0x0030D120 and 0x003222C4; objToListNode/listNodeToObj from 0x0049F5A8.
template <class T>
class OffsetList : public ListImpl {
public:
    ListNode* objToListNode(T* o) const { return (ListNode*)((char*)o + mOffset); }
    T* listNodeToObj(ListNode* n) const { return (T*)((char*)n - mOffset); }
    T* front() const {
        ListNode* n = ListImpl::front();
        return n ? listNodeToObj(n) : 0;
    }
    T* toObj(ListNode* n) const {
        if (!n) return 0;
        return listNodeToObj(n);
    }
    T* next(T* o) const {
        ListNode* node = objToListNode(o);
        ListNode* n = node->mNext;
        if (n == &mStartEnd) return 0;
        return listNodeToObj(n);
    }
    s32 indexOf(T* o) const { return ListImpl::indexOf(objToListNode(o)); }
    void erase(T* o) {
        s32 off = mOffset;
        ListImpl::erase((ListNode*)((char*)o + off));
    }

    // Iterator that survives erasing the current object (0x003222C4).
    class robustIterator {
    public:
        robustIterator(T* ptr, s32 offset) : mPtr(ptr), mNextNode(0), mOffset(offset) {
            mNextNode = static_cast<ListNode*>((void*)((u32)mPtr + mOffset))->next();
        }
        robustIterator& operator++() {
            mPtr = static_cast<T*>((void*)((u32)mNextNode - mOffset));
            mNextNode = mNextNode->next();
            return *this;
        }
        bool operator!=(const robustIterator& o) const { return mPtr != o.mPtr; }
        T& operator*() const { return *mPtr; }
        T* mPtr;
        ListNode* mNextNode;
        s32 mOffset;
    };
    robustIterator robustBegin() const {
        return robustIterator(static_cast<T*>((void*)((u32)mStartEnd.next() - mOffset)), mOffset);
    }
    robustIterator robustEnd() const {
        const ListNode* n = &mStartEnd;
        return robustIterator(static_cast<T*>((void*)((u32)n - mOffset)), mOffset);
    }

    s32 mOffset;
};

// Length-prefixed array over external storage (StateMgr's state names are a Buffer<StateName>; see
// statemgr.h, which flattens the same {s32, T*} pair). `at` and `operator()` are two spellings of
// the same bounds-checked accessor found in matched code (0x00449A00, and the flattened forms in
// 0x0058AC5C / 0x0028BC74): index < size returns the element, otherwise element 0.
template <class T>
class Buffer {
public:
    T& operator[](s32 i) { return mBuffer[i]; }
    const T& operator[](s32 i) const { return mBuffer[i]; }
    s32 size() const { return mSize; }
    T* begin() { return mBuffer; }
    T* end() { return mBuffer + mSize; }
    T& at(s32 i) const {
        if ((u32)i < (u32)mSize) return mBuffer[i];
        return mBuffer[0];
    }
    T& operator()(s32 i) const {
        if ((u32)i < (u32)mSize) return mBuffer[i];
        return mBuffer[0];
    }
    s32 mSize;
    T* mBuffer;
};

// Pointer array base: count, capacity, untyped storage. erase(position, num) is 0x48C320 and is
// declared only; PtrArray<T> below is layout-compatible with the sources that carry the three
// members directly (the base subobject starts at offset 0).
class PtrArrayImpl {
public:
    s32 size() const { return mPtrNum; }
    bool isEmpty() const { return mPtrNum == 0; }
    void erase(s32 position, s32 num);
    s32 mPtrNum;
    s32 mPtrNumMax;
    void** mPtrs;
};

// Typed view of the same three members (0x001E337C, 0x001E36CC, 0x001DE378, 0x001DBE4C, 0x00448244,
// 0x00449A00, 0x004B92E4). The casts to T** are no-ops in the emitted code.
template <class T>
class PtrArray : public PtrArrayImpl {
public:
    T** begin() const { return (T**)mPtrs; }
    T** end() const { return (T**)mPtrs + mPtrNum; }
    T* at(s32 i) const {
        if ((u32)i < (u32)mPtrNum) return (T*)mPtrs[i];
        return 0;
    }
    T* operator[](s32 i) const { return (T*)mPtrs[i]; }
    s32 indexOf(const T* p) const {
        for (s32 i = 0; i < mPtrNum; ++i) {
            if (mPtrs[i] == p) return i;
        }
        return -1;
    }
    void pushBack(T* p) {
        if (mPtrNum < mPtrNumMax) {
            mPtrs[mPtrNum] = p;
            ++mPtrNum;
        }
    }
    void erase(s32 position) { PtrArrayImpl::erase(position, 1); }
};

}

// Unqualified spellings used by the matched sources.
using sead::ListNode;
using sead::ListNodeZero;
using sead::ListImpl;
using sead::ListImplOut;
using sead::OffsetList;
using sead::Buffer;
using sead::PtrArrayImpl;
using sead::PtrArray;

#endif
