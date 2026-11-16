extern float func_0068C7E0(float a, float b, float c, float d, float e, float f, float g);

void func_0051D3EC(unsigned char* dst, const unsigned char* p1, const unsigned char* p2, float t) {
    dst[0] = (unsigned char)(unsigned int)func_0068C7E0(t, 0.0f, (float)p1[0], 0.0f, 1.0f, (float)p2[0], 1.0f);
    dst[1] = (unsigned char)(unsigned int)func_0068C7E0(t, 0.0f, (float)p1[1], 0.0f, 1.0f, (float)p2[1], 1.0f);
    dst[2] = (unsigned char)(unsigned int)func_0068C7E0(t, 0.0f, (float)p1[2], 0.0f, 1.0f, (float)p2[2], 1.0f);
    dst[3] = (unsigned char)(unsigned int)func_0068C7E0(t, 0.0f, (float)p1[3], 0.0f, 1.0f, (float)p2[3], 1.0f);
}
