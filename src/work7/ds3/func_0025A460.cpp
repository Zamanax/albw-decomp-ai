#include "ds3.h"

#include "sead_string.h"

struct SoundMgr;
extern "C" SoundMgr* data_00711F50;
extern "C" void func_004EC988(SoundMgr*, const SafeString&, int);
void func_0025A460() {
    func_004EC988(data_00711F50, SafeString("SE_ENV_UNDER_BRIDGE"), 0);
}
