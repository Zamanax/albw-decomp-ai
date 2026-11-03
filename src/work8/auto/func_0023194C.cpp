typedef unsigned char u8; typedef unsigned short u16; typedef short s16; typedef unsigned int u32; typedef float f32;
struct Inner{u8 pad[0x10];f32 value;};
struct E{u8 pad[0x10];Inner*inner;f32 value;u8 gap[0x20];};
struct Array{u8 pad[8];u32 count;E*data;E&at(u32 i){return i<count?data[i]:data[0];}};
struct O{u16 kind;s16 index;u32 m4;Array*array;};
void f23194C(O*p,int v){if(p->array&&p->index>=0){f32 f=(f32)v;E&e=p->array->at(p->index);e.value=f;e.inner->value=f;}}
