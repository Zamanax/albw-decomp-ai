struct Lnk {Lnk* prev; Lnk* next;};
void func_0049F6DC(Lnk* p, Lnk* v){Lnk* old=p->next;p->next=v;v->prev=p;v->next=old;if(old)old->prev=v;}
