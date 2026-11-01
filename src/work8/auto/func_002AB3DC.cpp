extern "C" void func_002AB3E0();

// tail call to the next function; the linker turned the final `b` into a NOP
extern "C" void func_002AB3DC() { func_002AB3E0(); }
