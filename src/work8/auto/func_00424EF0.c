extern void func_00231524(void*);

void func_00424EF0(char* p)
{
    func_00231524(p + 0x48);
    *(float*)(p + 0x74) = 2.0f;
    *(float*)(p + 0x70) = (*(float*)(p + 0x54) + *(float*)(p + 0x68)) - 20.0f;
}
