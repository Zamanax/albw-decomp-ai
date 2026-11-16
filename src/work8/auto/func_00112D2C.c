typedef unsigned int u32;
struct Node;
struct Links { struct Node* next; struct Node* prev; };
struct Node { char pad[0x278]; struct Links lk; };
struct Slot { char pad0[0x120]; struct Node* head; char pad1[0xFC]; struct Node* tail; };
void func_00112D2C(char* self, struct Node* n, u32 idx) {
    struct Slot* s = (struct Slot*)((u32*)self + idx);
    struct Node* z = 0;
    if (s->head == 0) {
        s->head = n;
        n->lk.prev = z;
        n->lk.next = z;
    } else {
        s->tail->lk.next = n;
        struct Links t = {z, s->tail};
        n->lk = t;
    }
    s->tail = n;
}
