struct Obj {
    void* vptr;
    unsigned char pad0[0x1d0];
    int mCnt;
    int mN;
    int mBegin;
    int mEnd;
    float mRatio;
    unsigned char mPad1;
    unsigned char mState;
};

void func_0048DBB0(struct Obj* o)
{
    unsigned char st = o->mState;
    if (st == 0) {
        return;
    }
    if (st == 1) {
        float ratio;
        if (o->mN > 0) {
            ratio = (float)o->mCnt / (float)(o->mN + 1);
        } else {
            ratio = 0.0f;
        }
        o->mRatio = ratio;
        if (o->mCnt == 0) {
            int two = 2;
            void (*f5c)(struct Obj*, int*) = *(void (**)(struct Obj*, int*))((char*)o->vptr + 0x5c);
            f5c(o, &two);
        }
        void (*f58)(struct Obj*) = *(void (**)(struct Obj*))((char*)o->vptr + 0x58);
        f58(o);
    } else if (st == 2) {
        void (*f58)(struct Obj*) = *(void (**)(struct Obj*))((char*)o->vptr + 0x58);
        f58(o);
        o->mRatio = 1.0f;
    } else if (st == 3) {
        void (*f58)(struct Obj*) = *(void (**)(struct Obj*))((char*)o->vptr + 0x58);
        f58(o);
        if (o->mEnd != o->mBegin) {
            o->mRatio = 1.0f - ((float)(o->mCnt - o->mBegin) / (float)(o->mEnd - o->mBegin));
        }
    } else {
        return;
    }
    o->mCnt = o->mCnt + 1;
}
