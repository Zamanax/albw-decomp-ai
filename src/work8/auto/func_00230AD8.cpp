extern "C" void func_00230ADC();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_00230AD8() { func_00230ADC(); }
