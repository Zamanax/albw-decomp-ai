struct S;
struct Node{Node* next; S* prev;};
struct S{Node* head;};
void func_0010F1DC(S* p,Node* n){
 Node* h=p->head;
 p->head=n;
 n->prev=p;
 n->next=h;
 if(h) h->prev=(S*)n;
}
