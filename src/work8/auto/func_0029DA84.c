extern unsigned data_007143B8;
extern unsigned data_0070D7D0;
extern unsigned data_00711DE8;
extern void func_0029E40C(unsigned);
extern unsigned func_004C403C(unsigned, unsigned);
extern void func_001E6CE8(unsigned);

void func_0029DA84(void)
{
    func_0029E40C(data_007143B8);
    func_001E6CE8(data_0070D7D0);
    while (func_004C403C(data_00711DE8, 1) == 0) {}
}
