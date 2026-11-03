#include "../../work7/gpt22/range.h"
extern "C" f32 ro_006BB870[];
static inline float clampf(float t,float lo,float hi){if(t>hi)t=hi;else if(t<lo)t=lo;return t;}
float func_00413ADC(float t){
  t = clampf(t, -90.4f, 6.0f);
  s32 i = (s32)(t * 10.0f);
  i += 904;
  return ro_006BB870[i];
}
