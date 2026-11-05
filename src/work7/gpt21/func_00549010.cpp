#include "range.h"

#include "sead_math.h"
struct Joint{char pad[0x14];Mtx34*mat;};struct Model{char pad[0x24];Joint*joint;};struct S{char pad[0x40c];Model*model;char pad410[0x900-0x410];u32 index;};
Mtx34* f_549010(S*p){return &p->model->joint->mat[p->index];}
