typedef unsigned int u32;
typedef int s32;

typedef struct Node Node;
struct Node {
    Node* m0;
    Node* m4;
    s32 m8;
};

typedef s32 (*CmpFn)(u32, u32);

void func_0049F434(Node* self, u32 base, CmpFn cmp) {
    Node* r7;
    Node* r4;
    Node* t;
    Node* sb;
    Node * t1 = self;

    s32 n = self->m8;
    if (n <= 1) {
        return;
    }
    r7 = ((u32)n > 1u) ? t1->m4->m4 : 0;
    if (r7 == t1) {
        return;
    }
    do {
        Node * t0 = r7;
        sb = t0->m4;
        r4 = t0->m0;
        if (cmp((u32)r4 - base, (u32)t0 - base) > 0) {
            for (r4 = r4->m0; r4 != self; r4 = r4->m0) {
                if (cmp((u32)r4 - base, (int)t0 - base) <= 0) {
                    break;
                }
            }
            t = r7->m0;
            if (0 != t) {
                t->m4 = r7->m4;
            }
            t = r7->m4;
            if (t != 0) {
                t->m0 = r7->m0;
            }
            r7->m4 = 0;
            r7->m0 = 0;
            t = r4->m4;
            r4->m4 = r7;
            r7->m4 = t;
            r7->m0 = r4;
            if (0 != t) {
                t->m0 = r7;
            }
        }
        r7 = sb;
    } while (r7 != self);
}
