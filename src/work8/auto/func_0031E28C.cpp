typedef unsigned char u8;
typedef unsigned int u32;
extern "C" u8* data_0070B960;
struct Base_004A1520{u8 pad[0x54];virtual ~Base_004A1520();};
struct B{u8 pad[0x58];~B();};
struct Member{u32 data;~Member();};
struct S:Base_004A1520,B{Member m;virtual ~S();};
S::~S(){ *(data_0070B960 + 0x2c1c) = 0; }
