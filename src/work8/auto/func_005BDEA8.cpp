// static initializer for data_0070D8F0 / data_0070D8F8 / strs_0076FF10 /
// strs_0076FF30 / list_0076FCA8 / factory_0076FCC8
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

s64 data_0070D8F0 = Id64().v;
Pair data_0070D8F8;

SafeString strs_0076FF10[4] = {
    "N_ArrowT_00",
    "N_ArrowB_00",
    "N_ArrowL_00",
    "N_ArrowR_00"
};

SafeString strs_0076FF30[2] = {
    "on",
    "off"
};

extern void* func_00604D20();
extern const u32 ro_00693108;

PtrList<5> list_0076FCA8;

Factory factory_0076FCC8(func_00604D20, ro_00693108, "MiniGameRSPot", &list_0076FCA8,
                          "\203X\203^\203W\203A\203\200\227p\232\342", 0, 0);
