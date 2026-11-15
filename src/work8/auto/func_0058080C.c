typedef unsigned int u32;
struct L { u32 prev; struct L* next; };

int func_0058080C(struct L* head, struct L* target) {
    struct L* cur = head->next;
    int idx = 0;
    if (cur == head) return -1;
    do {
        if (cur == target) return idx;
        cur = cur->next;
        idx++;
    } while (cur != head);
    return -1;
}
