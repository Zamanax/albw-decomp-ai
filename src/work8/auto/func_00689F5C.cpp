struct S{unsigned char pad[3];unsigned char count;};
float target(S*p,const float*values,float t){
  if(t<0.0f) return values[0];
  int n=p->count-1;
  float x=t*(float)n;
  int index=(int)(t*(float)n);
  if(index>=n) return values[index];
  values+=index;
  return values[0]+(values[1]-values[0])*(x-(float)index);
}
