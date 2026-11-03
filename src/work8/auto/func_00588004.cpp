typedef unsigned char u8;
typedef float f32;
struct Node { u8 pad0[0xc]; Node* link; u8 pad1[0xc]; f32 val; };
inline f32 clamp(f32 v,f32 lo,f32 hi){if(v<lo)v=lo;else if(v>hi)v=hi;return v;}
f32 func_00588004(void* unused, Node* p){
  f32 v = p->val;
  if (p->link) v = p->link->val + v;
  return clamp(v * 0.0025f, -0.6f, 0.6f);
}
