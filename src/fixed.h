#include<stdio.h>
#include<stdlib.h>
#include"extra.h"


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

