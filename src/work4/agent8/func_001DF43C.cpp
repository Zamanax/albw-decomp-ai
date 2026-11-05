// Player::~Player (D1). Player vtable ro_006D1A88: 21 primary slots, secondary (ActorBaseB @0x320) at +0x5c.
typedef unsigned int u32;
typedef signed int s32;

struct SoundMgr;
extern SoundMgr* data_00711F50;
void func_0014A0E8(SoundMgr* mgr, s32 v);




#include "actor.h"


class Player : public ActorBaseExt {
public:
    virtual ~Player();
};

Player::~Player() {
    func_0014A0E8(data_00711F50, 0);
}
