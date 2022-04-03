#ifndef GAME_MATH_H
#define GAME_MATH_H
#ifndef M_PI    
    #define M_PI 3.141592653f
#endif

#define RADIANS(theta) ((theta) * M_PI / 180.0f)
#define DEGREES(theta) ((theta) * 180.0f / M_PI)

float int_power(float x, int y);
// Taylor series approximation for sin and cos
float taylor_sin(float theta);
float taylor_cos(float theta);
int round_to_int(float val);
float bin_search_sqrt(float val);

void wrap_val(float *val, float lower_bound, float upper_bound);
#endif