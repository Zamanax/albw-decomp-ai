typedef unsigned char u8; typedef unsigned int u32;
struct Node { u32 unk0; struct Node* next; struct Base* link; u8 type; u8 unk_d; u8 shift; };
struct Base { u32 unk0; u32 unk4; struct Node head; };
void func_003D57CC(struct Base** pp, u32 mask) {
again:
    {
        struct Base* b = *pp;
        struct Node* s = &b->head;
        struct Node* n = s->next;
        while (n != s) {
            if (n->type != 4 || !(mask & (1u << n->shift))) {
                n = n->next;
                continue;
            }
            *pp = n->link;
            goto again;
        }
    }
}
