typedef unsigned int u32;
typedef int s32;
struct Node { u32 v; Node* next; };
struct List { u32 a; Node* head; u32 count; };

extern "C" Node* func_0058077C(List* l, u32 idx)
{
  if (idx >= l->count) return 0;
  Node* n = l->head;
  s32 s = (s32)idx;
  if (s > 0) {
    if (s & 1) n = n->next;
    for (s32 k = s >> 1; k != 0; --k) {
      n = n->next->next;
    }
  }
  return n;
}
