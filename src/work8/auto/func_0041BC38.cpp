typedef unsigned int u32; typedef int s32; typedef unsigned char u8; typedef float f32;
struct Counter22{s32 value;Counter22(s32 n):value(n){}operator s32()const{return value;}Counter22&operator++(){++value;return*this;}};
struct Owner22{};
typedef void(Owner22::*Method22)(u32,f32);
extern const Method22 ro_006BB358[];
struct Group22{u8 pad[0x90];Owner22*objects[16];Owner22*get(s32 i){if(i>15)return 0;return objects[i];}};
template<int K> static inline void impl(Group22*p,u32 mask,u32 a,f32 value){Method22 m=ro_006BB358[K];for(s32 i=0;i<16;++i,mask>>=1){if(!mask)break;if(mask&1){Owner22*o=p->get(i);if(o)(o->*m)(a,value);}}}
void func_0041BC38(Group22*p,u32 mask,u32 a,f32 value){impl<7>(p,mask,a,value);}
