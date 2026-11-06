#include "albw_types.h"

struct Obj003DA464 {
	u8* buf;
	u32 base;
};

void func_003DA464(Obj003DA464* p, u32 pos, u32 n) {
	u32 d = pos - p->base;
	u8 * t1 = p->buf;
	u8 * t0 = t1;
	u8* b = t0;
	u32 idx = d >> 4;
	u32 end = n + idx;
	if (end > idx) {
		for (u32 i = idx; i < end; i++) {
			b[i] = 0;
		}
	}
}
