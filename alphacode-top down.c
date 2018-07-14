#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long int *vetor=NULL;

void alloc (int n){

  vetor=realloc(vetor,sizeof(long long int)*n);
}

void init (int n){
 int i;

 for(i=0;i<n;i++)
    vetor[i]=-1;
}


long long int countWays (char *digits_code, int index){

  long long int count=0;

  if(index==-1)
    return 1;

  if(index<-1)
    return 0;

  if(vetor[index+1]!=-1)
    return vetor[index+1];



  else{
        if(digits_code[index]>'0'){
            vetor[index]=countWays(digits_code,index-1);
            count=vetor[index];

        }

        if(index-1>=0)
            if(digits_code[index-1]=='1' ||( digits_code[index-1]=='2' && digits_code[index]<'7')){
                vetor[index-1]=countWays(digits_code,index-2);
                count=count+vetor[index-1];


            }

  return count;}

}

int main (void){

char digits[5002];
int tam;

while(scanf(" %s",digits),strcmp(digits,"0")){

    tam=strlen(digits);

    alloc(tam+1);
    init(tam+1);
    printf("%lld\n",countWays(digits,tam-1));
    free(vetor);
    vetor=NULL;

}

return 0;}
