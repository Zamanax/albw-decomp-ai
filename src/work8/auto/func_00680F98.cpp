#include "../../work7/gpt30/factory132.h"
struct SafeString30{const char*text;virtual~SafeString30(){}virtual void assure()const{}SafeString30(const char*s):text(s){}};
extern "C" void func_004880F0(WindowBase30*,const SafeString30&);
struct Window00680F98:WindowBase30 {
    Window00680F98():WindowBase30(2){func_004880F0(this,SafeString30("npc_name_darkzelda"));}
};
Window00680F98* target(Heap30* heap){
    ScopedHeapSwitch30 scoped(heap);
    Window00680F98* p=new(heap,4)Window00680F98;
    return p;
}
