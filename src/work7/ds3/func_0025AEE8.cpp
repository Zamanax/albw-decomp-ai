#include "ds3.h"

#include "sead_string.h"

struct S25AEE8 { char pad[0x78]; u32 m78; };
extern "C" void* data_00711F50;
extern "C" void func_004E97BC(void*, const SafeString&, void*);
void func_0025AEE8(S25AEE8* self) {
    func_004E97BC(data_00711F50, SafeString("SE_ENV_FOREST_SWORD_EPILOGUE"), (char*)self + 0x78);
}
