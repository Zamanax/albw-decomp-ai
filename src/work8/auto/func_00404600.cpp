struct Node5039 { Node5039* next; Node5039* previous; };
struct Item5039 { virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void update(); Node5039 node; };
struct Target5039 { virtual void v0();virtual void v1();virtual void v2();virtual void v3();virtual void v4();virtual void v5();virtual void v6();virtual void v7();virtual void v8();virtual void v9(); };
struct Elem5039 { Node5039 node; Target5039* obj; };
struct Object5039 { char pad[8]; Node5039 sentinel; char pad2[0x1c]; Node5039 sentinel2; void update(); };
void Object5039::update() {
    Node5039* end=&sentinel;
    for(Node5039* p=sentinel.next;p!=end;p=p->next) {
        Item5039* item=(Item5039*)((char*)p-4);
        item->update();
    }
    Node5039* end2=&sentinel2;
    for(Node5039* q=sentinel2.next;q!=end2;q=q->next) {
        Target5039* t=((Elem5039*)q)->obj;
        t->v9();
    }
}
