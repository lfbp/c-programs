#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
 char *sub;
 long long int *vetor;
 long long int tam_vetor;
 int init;
 uint32_t key;

}cell;
typedef struct{
  long long int tam_table;
  long long int qt_elt;
  long long int seq;
}info;
uint32_t key_generator(char *sub){

 uint32_t c=0;
 long long int i=0;

 while(sub[i]){

    c=128*c+sub[i];
    i++;
 }

return c;
}
char *read_text(char *txt,long long int n){

  long long int tam_txt=0,indice=0;
  char aux[10000];

  while(n){

    long long int i,j;

    scanf(" %[^\n]",aux);
    tam_txt=tam_txt+strlen(aux)+2;
    txt=realloc(txt,sizeof(char)*tam_txt);
    i=0;
    j=strlen(aux)-1;

    while(i<=j){

        txt[indice]=aux[i];
        indice++;
        i++;
    }

    txt[indice]='\n';
    indice++;


    n--;
  }
 txt[indice]='\0';
return txt;}
void init_table (cell *table,long long int i,long long int f){

  while(i<=f){
    table[i].init=0;
    table[i].vetor=NULL;
    table[i].tam_vetor=0;
    table[i].sub=NULL;
    i++;
  }

}
cell *rehash(cell *table,long long int q){

   cell *new_table=NULL;
   long long int new_tam=2*q+1,i;

   new_table=realloc(new_table,sizeof(cell)*(new_tam));
   init_table(new_table,0,new_tam-1);

   for(i=0;i<q;i++){

      if(table[i].init==1){

         long long int pos=table[i].key%new_tam,find=0;

         while(find==0){

            if(new_table[pos].init==0){
                find=1;
                new_table[pos].key=table[i].key;
                new_table[pos].init=1;
                new_table[pos].sub=table[i].sub;
                new_table[pos].tam_vetor=table[i].tam_vetor;
                new_table[pos].vetor=table[i].vetor;


            }else
             pos=(pos+1)%new_tam;
         }


      }
   }

return new_table;}
long long int *insert_elt (long long int *vetor,long long int tam,long long int n){

   long long int i=tam-1;

   vetor=realloc(vetor,sizeof(long long int)*(tam+1));

   while(i>=0 && vetor[i]>n){
        vetor[i+1]=vetor[i];
        i--;
    }
    vetor[i+1]=n;


return vetor;}
cell *make_hash(cell *table,char *txt, long long int k, info *x){

  long long int i=0,f=k-1,end=strlen(txt);
  double alfa;
  char aux[1000];

  alfa=((double)x->qt_elt)/x->tam_table;

  table=realloc(table,sizeof(cell)*x->tam_table);
  init_table(table,0,x->tam_table-1);
  alfa=0;

  while(f<end){

       uint32_t aux_key;
       long long int j,k,pos;
       int find=0;
       char sub_aux[1000];

      if(alfa>=0.5){
         table=rehash(table,x->tam_table);
         x->tam_table=2*x->tam_table+1;
      }

      for(j=i,k=0;j<=f;j++,k++)
        sub_aux[k]=txt[j];
      sub_aux[k]='\0';
      //printf("%s %d %d\n",sub_aux,i,f);
       aux_key=key_generator(sub_aux);
       pos=aux_key%x->tam_table;

       while(find==0){


        if(table[pos].init==0){
            find=1;
            table[pos].init=1;
            table[pos].sub=malloc(sizeof(char)*(k+1));
            strcpy(table[pos].sub,sub_aux);
            table[pos].vetor=insert_elt(table[pos].vetor,table[pos].tam_vetor,i);
            table[pos].tam_vetor++;
            table[pos].key=aux_key;
            x->qt_elt++;
        }else if(!strcmp(sub_aux,table[pos].sub)){
            find=1;
            table[pos].vetor=insert_elt(table[pos].vetor,table[pos].tam_vetor,i);
            table[pos].tam_vetor++;
        }else
          pos=(pos+1)%x->tam_table;
    }

      i++;
      f++;
      alfa=((double)x->qt_elt)/x->tam_table;


  }

//printf("!!! elementos %d, alfa %lf, Q %d!!!\n",x->qt_elt,alfa,x->tam_table);
return table;}
void show_table (cell *table, info *x){

 long long int i;

 for(i=0;i<x->tam_table;i++){

    if(table[i].init==1){
        long long int j;
        printf("%s ",table[i].sub);
        for(j=0;j<table[i].tam_vetor;j++)
            printf("%d%c",table[i].vetor[j],j+1==table[i].tam_vetor?'\n':' ');
    }
    else
        printf("vazio\n");
 }

}
cell *search_kmer(char *kmer, cell *table,long long int q){

  uint32_t key=key_generator(kmer);
  long long int pos=key%q;

  while(1){

     if(table[pos].init==0){
        return &table[pos];
     }else if(!strcmp(table[pos].sub,kmer)){
        return &table[pos];
     }else
       pos=(pos+1)%q;

  }

}
void search_word(char *word,long long int *vetor,long long int tam,char *txt,long long int k,long long int n){

  long long int i,dif,j,pos;
  int first=1;

  printf("%lld: ",n);
  for(i=0;i<tam;i++){

     pos=vetor[i];

     dif=0;
     j=0;
     while(word[k+j] && dif==0 && txt[pos+j+k]){

          if(txt[pos+j+k]==word[k+j])
            j++;
          else
            dif=1;

     }


     if(!word[k+j] && dif==0 && txt[pos+k+j]){

        if(first==1){
            printf("%lld",pos);
            first=0;
        }
        else
            printf(" %lld",pos);
     }


  }
  printf("\n");

}
long long int count_seq(cell *table,long long int q){

 long long int i,maior=0,contador=0;
 int begin=0;

 for(i=0;i<q;i++){

    if(table[i].init==1 && begin==0){
        contador++;
        begin=1;
    }else if(table[i].init==1 && begin==1){
        contador++;
    }else if((table[i].init==0 && begin==1) || (i+1)==q){
         begin=0;

         if(contador>maior)
            maior=contador;
         contador=0;
    }
 }
return maior;}
int main (){

long long int n,k,m,i=0,j=0,*vetor=NULL;
char *txt=NULL,temp[10000],kmer[10000];
cell *table=NULL;
info x;
scanf("%lld %lld",&k,&x.tam_table);
//printf("%d %d\n",k,x.tam_table);
scanf(" $TXT %lld",&n);
txt=read_text(txt,n);
x.qt_elt=0;
x.seq=0;
table=make_hash(table,txt,k,&x);
//printf("%d %d %d\n",x.qt_elt,x.tam_table,x.seq);
//show_table(table,&x);
scanf(" $CONSULTAS %lld",&m);

while(i<m){

    cell *find;
    scanf(" %[^\n]",temp);

    for(j=0;j<k;j++)
        kmer[j]=temp[j];
    kmer[j]='\0';

    //printf("%s: ",kmer);
    find=search_kmer(kmer,table,x.tam_table);
    //printf("!!!!!%s!!!!\n",temp);
    search_word(temp,find->vetor,find->tam_vetor,txt,k,i);

    /*for(j=0;j<find->tam_vetor;j++)
     printf("%d%c",find->vetor[j],j+1==find->tam_vetor?'.':' ');
    printf("\n");*/




i++;}
x.seq=count_seq(table,x.tam_table);
printf("%lld %lld %lld\n",x.qt_elt,x.tam_table,x.seq);

return 0;}
