#include<stdio.h>
#include<stdlib.h>
#include "fixed.h"


#define Ki 1 
#define Kf 1
#define af 0.75



fixed float2fixed( float ftvalue,int ipart,int fpart ){
    fixed new;
    new.ipart = ipart;
    new.fpart = fpart;
    new.bit_length = ipart + fpart ;
    new.value =(int64_t)(ftvalue*((float)(1<<fpart)));
    return new;
}

float fixed2float( fixed f){
    float out, out_i=0, out_f=0;
    out_i = (f.value >>f.fpart ) ;
    out_f = (float)(f.value&((1<<f.fpart)-1 )) / (float)(1<<((f.fpart)));
    //  float = (unsigned int) + unsigned int /2^16
    
    //out=(out_i==-1) ? (out_f*-1) : out_i+out_f ;
    //out=(out_i==-1 ) ? (out_f*-1) : ( (out_i> 0)? out_i+out_f: out_i-out_f  );
    out = out_i+out_f;
    //printf("--> %f\n",out);

    return out ;

}

void fixed_ini(fixed *inf,int ipart,int fpart ){
    inf->ipart = ipart ;
    inf->fpart = fpart ;
    inf->bit_length = ipart+fpart;
    inf->value = 0;
}

float fix_mul_add(float a,float b,float c,int ipart,int fpart){
    fixed fixed_out ,fixed1,fixed2,fixed3 ;
    float fp_out=0;
    if( a> (2<<ipart )-1 ) a=(2<<ipart )-1 ; 

    fixed1 = float2fixed(a,ipart,fpart);
    fixed2 = float2fixed(b,ipart,fpart);
    fixed3 = float2fixed(c,ipart*2,fpart*2);
    fixed_ini(&fixed_out  ,ipart*2,fpart*2);

    fixed_out.value  = fixed1.value * fixed2.value;
    fixed_out.value += fixed3.value ;

    fp_out = fixed2float( fixed_out) ;
    //printf("-->%f\n",fp_out);
    return fp_out;
    //return a*b+c;
}

void init_fixed_arg(struct Fixed_arg_s *fixed_arg  ){

    //C99
    //used when FIND_POINT
    /*
    //D -> dot -> gemm
    .Dfk_i =3,       //stddev range
    .Dwk_f =1,       //stddev range, used on weight
    .Dwa_f =0.5,    //error rate, used on weight
    //A -> add -> bias
    .Afk_i =3,       //feature    renge for int
    .Abk_i =3,       //bias       range for int
    .Abk_f =1,       //bias       range for frac.
    .Aba_f =0.5      //bias       error rate for frac.
     */

    //D -> dot -> gemm
    fixed_arg->Dfk_i =Ki;       //stddev range
    fixed_arg->Dwk_f =Kf;       //stddev range, used on weight
    fixed_arg->Dwa_f =af;    //error rate, used on weight
    //A -> add ->->bias
    fixed_arg->Afk_i =Ki;       //feature    renge for int
    fixed_arg->Abk_i =Ki;       //bias       range for int
    fixed_arg->Abk_f =Kf;       //bias       range for frac.
    fixed_arg->Aba_f =af;     //bias       error rate for frac.

}

float float_to_fixed(float input,int integer,int fractional ){
    int tmp_fixed;
    int max_int =((1<<(integer-1))-1 ) ;
    int sign=1;

    if(input<0) input*=-1,sign=-1;

    tmp_fixed = (double)(round(input * (1 <<( fractional))));
    if( (tmp_fixed>>fractional) > max_int )
        tmp_fixed = (max_int <<fractional) +  (tmp_fixed&(  (1<<(fractional+1))-1  ) ) ;

    double out=((double)tmp_fixed / (double)(1 << fractional));

    out*=sign;
    return  out;
}



void array2fixed(float *X,int length,int i_part, int f_part){

    //double *output = malloc(length*sizeof(double));// new double [length];

    int i;
    for(i=0 ; i<length ; i++)   
        X[i] = float_to_fixed(X[i],i_part,f_part);
    //output[i] = float_to_fixed(X[i],i_part,f_part);

    //    return X;//output;
}


int find_int_part(struct distributed data_dis ,int range ){
    float t_max, t_min;
    int i_part=1;

    t_max = abs(data_dis.ave+ data_dis.stddev*range);
    t_min = abs(data_dis.ave- data_dis.stddev*range);
    t_max = max(t_max,t_min);
    i_part=1+(int)ceil(  log(t_max+0.001)/log(2.0)  );
    if(i_part < 1 ) i_part=1;
    //printf("i_part>>>>>>>>\t %d,%f ",i_part,t_max );

    return i_part;
}

int find_frac_part(struct distributed data_dis, float range ,float error ){
    int f_part=1,i;
    double tmp_f=0.0;
    double error_range = (double)data_dis.stddev *(double)range * ((double)error) ;
    //printf("EEEEEEEE %f\n",error_range);

    //printf("\ttmp_f:%f\n",tmp_f);
    for(i=1;i<20;i++){
        tmp_f = 1.0/(1<<i);
        if(tmp_f < error_range )break;
    }

    //printf("\terror:%f\n",error_range);
    f_part=i;
    //printf(">>>>>>> %d\n",f_part);
    return f_part;
}

int fixed_policy_adjust(int i_part, int p_part ,int method ){
    int data= i_part + p_part ;
    switch(method){
        case 0:
            return p_part;

        case 1:
            if (data< 4) data=4;
            else if(data< 8) data=8;
            else if(data<16) data=16;
            else  data=16 ,printf("[fixed.h] convert loss\n");
            p_part= data-i_part;
            return p_part;


        default:
            return p_part;

    }
}





