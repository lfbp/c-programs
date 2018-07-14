#include <stdio.h>
#include <stdlib.h>

typedef struct edge {

int edge_origin;
int edge_end;

}edge;
typedef struct node{

int id;
int visited;
edge *vetor;
int tam_vetor;
int pre;

}node;
node* create_graf(node* graf,int n_node){

    int i;

    graf=(node*)realloc(graf,sizeof(node)*(n_node));

    for(i=0;i<n_node;i++){

        graf[i].id=i;
        graf[i].visited=0;
        graf[i].vetor=NULL;
        graf[i].tam_vetor=0;
        graf[i].pre=-1;

    }

return graf;}
void dfs(node* graf,int origin,int *cont,int *is_a_graf){

    int i;

    graf[origin].visited=1;
    (*cont)++;

    //printf("node %d\n",origin);

    for(i=0;i<graf[origin].tam_vetor;i++){

        int v;

        v=graf[origin].vetor[i].edge_end;


        if(graf[v].visited==1 && graf[origin].pre!=v){
                (*is_a_graf)=0;
                 //printf("pai de %d eh %d e nao %d\n",origin,graf[origin].pre,v);

        }
        else if(graf[v].visited==0){
            graf[v].pre=origin;
            dfs(graf,v,cont,is_a_graf);
        }

    }


}
int main (){

    int n_node,n_edge,i;
    node *graf=NULL;
    int cont=0,is_a_graf=1;

    scanf("%d %d",&n_node,&n_edge);

    graf=create_graf(graf,n_node);

    for(i=0;i<n_edge;i++){

        int u,v;

        scanf("%d %d",&u,&v);

        graf[u-1].vetor=(edge*)realloc(graf[u-1].vetor,sizeof(edge)*(graf[u-1].tam_vetor+1));
        graf[u-1].vetor[graf[u-1].tam_vetor].edge_origin=u-1;
        graf[u-1].vetor[graf[u-1].tam_vetor].edge_end=v-1;

        graf[v-1].vetor=(edge*)realloc(graf[v-1].vetor,sizeof(edge)*(graf[v-1].tam_vetor+1));
        graf[v-1].vetor[graf[v-1].tam_vetor].edge_origin=v-1;
        graf[v-1].vetor[graf[v-1].tam_vetor].edge_end=u-1;

        graf[u-1].tam_vetor++;
        graf[v-1].tam_vetor++;
    }


    dfs(graf,0,&cont,&is_a_graf);

    if(cont==n_node && is_a_graf==1)
        printf("YES\n");
    else
        printf("NO\n");


return 0;}
