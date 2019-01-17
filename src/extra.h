#ifndef EXTRA_H
#define EXTRA_H


#include <stdio.h>
#include <stdio.h>
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


struct distributed{
    float count;
    float min;
    float max;
    float ave;
    float varaince;
    float stddev;
    int mode;
};

void initial_dist(struct distributed *d );

struct distributed cal_distribution(float *data, int length);

void gen_weight(float *bias,int len_b ,float *weight,int len_w,float *outmap ,int len_f ,int layer);


#endif
