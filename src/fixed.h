#ifndef FIXED_H
#define FIXED_H

#include"extra.h"



typedef struct fix_point{
    int ipart;
    int fpart;
    int bit_length;
    unsigned int value;
    //fromat: Qi.f
}fixed ;

struct Fixed_arg_s{
    int Dfk_i;
    int Dwk_f;
    float Dwa_f;

    int Afk_i;
    int Abk_i;

    //int Afk_f;
    int Abk_f;
    //int Afa_f;
    float Aba_f;
};

//extern static struct Fixed_arg_s fixed_arg;
//used when FIND_POINT
//static struct Fixed_arg_s fixed_arg;

float fix_mul_add(float a,float b,float c,int ipart,int fpart);
void init_fixed_arg(struct Fixed_arg_s *fixed_arg  );

float float_to_fixed(float input,int integer,int fractional); 


void array2fixed(float *X,int length,int i_part, int f_part);



int find_int_part(struct distributed data_dis ,int range );


int find_frac_part(struct distributed data_dis, float range ,float error );


int fixed_policy_adjust(int i_part, int p_part ,int method );
#endif
