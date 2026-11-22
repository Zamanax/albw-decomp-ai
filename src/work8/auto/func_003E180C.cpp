#include "albw_types.h"
struct Node { Node* prev; Node* next; };
struct Head { Node* first; };
extern "C" void func_003E180C(Head* p) {
    Node* n = p->first;
    if (n != 0) {
        do {
            Node* c = n;
            n = c->next;
            c->next = 0;
            c->prev = 0;
        } while (n != 0);
        p->first = 0;
    }
}
