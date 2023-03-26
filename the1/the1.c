#include <stdio.h>
#define W_INDEX 0
#define H_INDEX 1
#define T_INDEX 2
#define P_INDEX 3
#define S_INDEX 4
#define A_INDEX 5
#define N_INDEX 6

int array[100000] = {0};
int main() {
    int i,j,z,x,y,r,k,w,h,initial_t,t,p,s,a,n;
    scanf("%d %d",&r,&k);
    for (j=0; j<r+1; j++){
        array[j]=1;
    }
    for (i=0; i<k; i++){
        scanf("%d %d %d %d %d %d %d",&w,&h,&initial_t,&p,&s,&a,&n);
        t = initial_t;
        for (x=0; x<n;){
            if ((t-initial_t) % a == 0){
                for (y=p; y<p+w; y++){
                    if ((y>=0) && (y<=r) && (array[y] < h)){
                        array[y] = h;
                    }
                }
                x++;
            }
            t++;
            p += s;
        }
    }
    for (z=0; z<r; z++){
        printf("%d ",array[z]);
    }
    printf("%d\n",array[r]);
    
    return 0;
}
