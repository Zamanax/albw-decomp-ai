typedef unsigned int u32;
typedef struct Node { struct Node* prev; struct Node* next; } Node;

Node* func_00112364(u32* count, Node* anchor, Node* node) {
    struct Node * t5 = anchor->next;
    struct Node * t4 = t5;
    struct Node * t3 = t4;
    Node* next = t3;
    Node * t2 = node;
    t2->prev = anchor;
    Node * t1 = t2;
    t1->next = next;
    anchor->next = t1;
    Node * t0 = next;
    t0->prev = t1;
    *count = *count + 1;
    return t1;
}
