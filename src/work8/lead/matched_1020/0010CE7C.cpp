struct Heap;
extern "C" Heap *data_00715210;
extern "C" Heap *func_0010E2A4(Heap *cur, const void *addr);
extern "C" void func_0010DEF0(Heap *heap, void *disposer);

#include "sead_container.h"

class IDisposer_006F7DE8 {
public:
    IDisposer_006F7DE8();
    virtual ~IDisposer_006F7DE8();
    Heap *mDisposerHeap;
    ListNodeZero mListNode;
};
IDisposer_006F7DE8::IDisposer_006F7DE8() : mDisposerHeap(0)
{
    if (data_00715210 != 0) {
        mDisposerHeap = func_0010E2A4(data_00715210, this);
        if (mDisposerHeap != 0) func_0010DEF0(mDisposerHeap, this);
    }
}
