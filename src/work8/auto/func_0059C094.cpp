// static initializer for data_0070BEF0 / data_0070BEF8 / strs_007535A0 /
// strs_007535C0 / list_00753338 / factory_00753358
typedef unsigned int u32;
typedef long long s64;
typedef unsigned char u8;

struct SafeString {
    const char* text;
    SafeString(const char* s) : text(s) {}
    virtual ~SafeString() {}
};

#pragma pack(4)
struct Id64 { s64 v; Id64() : v(-1) {} };
struct Pair { s64 v; Pair() : v(0) {} };
#pragma pack()

struct PtrCnt {
    int num, max;
    PtrCnt(int n) : num(0), max(n) {}
};

struct PtrListBase : PtrCnt {
    void** ptr;
    PtrListBase(int n, void* b) : PtrCnt(n), ptr(0) {
        if (b) {
            void** t = static_cast<void**>(b);
            ptr = t;
        }
    }
};

template <int N>
struct PtrList : PtrListBase {
    void* buffer[N];
    PtrList() : PtrListBase(N, buffer) {}
};

typedef void* (*CreateFn)();

struct Factory {
    char storage[0x248];
    Factory(CreateFn, u32, const SafeString&, PtrListBase*, const SafeString&, const char*, int);
    ~Factory();
};

s64 data_0070BEF0 = Id64().v;
Pair data_0070BEF8;

SafeString strs_007535A0[4] = {
    "N_ArrowT_00",
    "N_ArrowB_00",
    "N_ArrowL_00",
    "N_ArrowR_00"
};

SafeString strs_007535C0[2] = {
    "open",
    "close"
};

extern void* func_0060AB4C();
extern const u32 ro_0069353C;

PtrList<5> list_00753338;

Factory factory_00753358(func_0060AB4C, ro_0069353C, "MojDiary", &list_00753338,
                          "\203\211\203\224\203B\203I\202\314\223\372\213L", 0, 0);
