#include <stdio.h>
#include <stdlib.h>
struct matrix {
    int rows; 
    int cols; 
    float *digits;
};

struct matrix matrix_mul(struct matrix m1, struct matrix m2){
    struct matrix result;
    if(m1.cols == m2.rows){
        result.rows = m1.rows;
        result.cols = m2.cols;
        result.digits = malloc(result.rows*result.cols*sizeof(float));
        for(int i = 0; i<result.rows;i++){
            for(int j = 0;j<result.cols;j++){
                result.digits[i*result.cols + j] = 0.0;
                for(int k = 0; k<m1.cols;k++){
                    result.digits[i*result.cols + j] += m1.digits[i*m1.cols + k]*m2.digits[k*m2.cols + j];
                }
            }
        }
        return result;
    }
    else{
        result.cols = 0, result.rows = 0, result.digits = NULL;
        return result;
    }
}


int main(){
    struct matrix m1;
    struct matrix m2;
    m1.rows = 2, m1.cols = 2, m2.rows = 2, m2.cols = 2;
    m1.digits = (float[]){1,2,3,4};
    m2.digits = (float[]){2,0,1,2};
    struct matrix rrr = matrix_mul(m1,m2);
    for(int i = 0; i< rrr.rows; i++){
        for(int j = 0; j< rrr.cols; j++){
            printf("%f", rrr.digits[i*rrr.cols + j]);
        }
    }
    return 0;
}