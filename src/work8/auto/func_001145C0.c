typedef unsigned int u32;
typedef unsigned long long u64;
u32 func_001145C0(u64 x){
    u32* w=(u32*)&x;
    u32 value=w[1]<<1;
    u32 kind=w[0]|(value<<11);
    if(kind)kind=4;
    if(value>>21)kind|=1;
    if((value>>21)==0x7ffu)kind|=2;
    if(kind==1)kind=5;
    return kind;
}
