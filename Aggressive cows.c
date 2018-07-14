//Problem from spoj
#include <stdio.h>
#include <stdlib.h>

void show_vector(long long int *vetor,int tam){

int i;

for(i=0;i<tam;i++)
    printf("%lld%c",vetor[i],i+1==tam?'\n':' ');

}
void merge_sort(long long int *vetor,int init,int end,long long int *aux){

if(init<end){

    int med=(init+end)/2,i,j,k;

    merge_sort(vetor,init,med,aux);
    merge_sort(vetor,med+1,end,aux);

    i=init;
    j=med+1;
    k=init;

    while(i<=med && j<=end){

         if(vetor[i]<vetor[j]){

            aux[k]=vetor[i];
            i++;
         }
         else{

            aux[k]=vetor[j];
            j++;
         }

        k++;
    }

    while(i<=med)
        aux[k++]=vetor[i++];

    while(j<=end)
        aux[k++]=vetor[j++];

    for(k=init;k<=end;k++)
        vetor[k]=aux[k];
}


}
int fit(long long int *vetor,int tam,int dist,int k){

long long int pos=vetor[0];
int i,elts=1;

for(i=1;i<tam;i++){

    if(vetor[i]-pos>=dist){

        pos=vetor[i];
        elts++;
    }

    if(elts==k)
        return 1;
}

return 0;

}
long long int max_ans(long long int *vetor,int tam,int k){

long long int ans=0,dist;
long long int left,right;

left=vetor[0];
right=vetor[tam-1];

while(left < right){

    dist=(left+right)/2;

    if(fit(vetor,tam,dist,k)==1){

        left=dist+1;

        if(ans<dist)
            ans=dist;
    }else
      right=dist;

}

return ans;
}
int main (){

int cases,N,C,i;
long long int *vetor,*aux,ans;

scanf("%d",&cases);

while(cases){

    vetor=NULL;
    aux=NULL;

    scanf("%d %d",&N,&C);

    vetor=(long long int*)realloc(vetor,sizeof(long long int)*N);
    aux=(long long int*)realloc(aux,sizeof(long long int)*N);

    for(i=0;i<N;i++)
        scanf("%lld",&vetor[i]);

    //show_vector(vetor,N);
    merge_sort(vetor,0,N-1,aux);
    //show_vector(vetor,N);
    ans=max_ans(vetor,N,C);

    printf("%lld\n",ans);


cases--;}

free(vetor)
free(aux);
return 0;}
