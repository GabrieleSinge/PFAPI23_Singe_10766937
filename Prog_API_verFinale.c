#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct staz_park{
  int var1;
  int var2;
  struct staz_park* testa_auto;
  struct staz_park* right;
  struct staz_park* left;
} nodo;


nodo* aggiungi_auto(nodo* p, int km, int n);

void black_hole_auto(nodo* p){
  if (p!=NULL) {
    black_hole_auto(p->left);
    black_hole_auto(p->right);
    free(p);
  }
  return;
}

void black_hole(nodo* p) {
  if (p!=NULL) {
    black_hole(p->left);
    black_hole(p->right);
    black_hole_auto(p->testa_auto);
    free(p);
  }
  return;
}

nodo* verifica_nodo(nodo* aux,int data){
    if (aux->var1!=data) {
      if (aux->var1 > data) {
        if (aux->left != NULL) {
          return verifica_nodo(aux->left,data);
        }
        else
          return NULL;
      }
      else{
        if (aux->right != NULL) {
          return verifica_nodo(aux->right,data);
        }
        else
          return NULL;
      }
    }
    else
      return aux;
    return NULL;
}

nodo* nodo_minimo(nodo* node) {
  nodo* current = node;
  while (current->left != NULL)
    current = current->left;

  return current;
}

nodo* newNodo(int input1,int input2){
  nodo* newNodo=malloc(sizeof(nodo));
  newNodo->var1=input1;
  newNodo->var2=input2;
  newNodo->testa_auto=NULL;
  newNodo->right=NULL;
  newNodo->left=NULL;
  return newNodo;
}

nodo* aggiungi_staz(nodo* p, int km, int n) {
  if (p == NULL){
    printf("aggiunta\n");
    nodo* aux=newNodo(km,n);
    int kappa=0,bin=0;
    for (int i = 0; i < n; i++) {
      bin=scanf("%d",&kappa);
      aux->testa_auto=aggiungi_auto(aux->testa_auto,kappa,0);
    }
    bin++;
    return aux;
  }
  if (km < p->var1)
    p->left = aggiungi_staz(p->left,km,n);
  else if (km==p->var1)
    printf("non aggiunta\n");
  else
    p->right = aggiungi_staz(p->right,km,n);
  return p;
}

nodo* aggiungi_auto(nodo* p, int km, int n) {
  if (p == NULL){
    if(n==1)
     printf("aggiunta\n");
    return newNodo(km,1);
  }

  if (km==(p->var1)){
    p->var2++;
    if(n==1)
      printf("aggiunta\n");
  }
  else if (km < p->var1){
    p->left = aggiungi_auto(p->left,km,n);
  }
  else{
    p->right = aggiungi_auto(p->right,km,n);
  }
  return p;
}

nodo *demolisci_staz(nodo* root, int key) {
  if (root == NULL){
    printf("non demolita\n");
    return root;
  }
  if (key < root->var1)
    root->left = demolisci_staz(root->left, key);
  else if (key > root->var1)
    root->right = demolisci_staz(root->right, key);

  else {
    if (root->left == NULL) {
      nodo* temp = root->right;
      printf("demolita\n");
      black_hole_auto(root->testa_auto);
      free(root);
      return temp;
    } else if (root->right == NULL) {
      nodo* temp = root->left;
      printf("demolita\n");
      black_hole_auto(root->testa_auto);
      free(root);
      return temp;
    }
    nodo* temp = nodo_minimo(root->right);
    root->var1 = temp->var1;
    root->var2 = temp->var2;
    nodo* swap=root->testa_auto;
    root->testa_auto=temp->testa_auto;
    temp->testa_auto=swap;
    root->right = demolisci_staz(root->right, temp->var1);
  }
  return root;
}

nodo* rottama_auto(nodo* root, int data,nodo* pippo) {
  if (root == NULL){
    printf("non rottamata\n");
    return root;
  }

  if (data < root->var1)
    root->left = rottama_auto(root->left, data,pippo);
  else if (data > root->var1)
    root->right = rottama_auto(root->right, data,pippo);

  else {
    if (root->var2 > 1) {
      root->var2--;
      pippo->var2--;
      printf("rottamata\n");
    }
    else{
      if (root->left == NULL) {
        nodo* temp = root->right;
        pippo->var2--;
        printf("rottamata\n");
        free(root);
        return temp;
      } else if (root->right == NULL) {
        nodo* temp = root->left;
        pippo->var2--;
        printf("rottamata\n");
        free(root);
        return temp;
      }
      nodo* temp = nodo_minimo(root->right);
      root->var1 = temp->var1;
      root->var2 = temp->var2;
      root->right = rottama_auto(root->right, temp->var1,pippo);
    }
  }
  return root;
}

int max_auto(nodo *p){
  if (p!=NULL) {
    while (p->right!=NULL) {
      p=p->right;
    }
    return p->var1;
  }
  else
    return 0;
}

void conta_stazioni(int start, int end, nodo* p,int* flag){
  if (p!=NULL) {
    if (p->left!=NULL){
      conta_stazioni(start,end,p->left,flag);
    }
    if (p->var1 >= start && p->var1<=end) {
      *flag+=1;
    }
    if (p->right!=NULL){
      conta_stazioni(start,end,p->right,flag);
    }
  }
  return;
}

void assegna_array(int start,int end,nodo* p,int* arr_staz,int* arr_auto,int* i) {
  if (p!=NULL) {
    if (p->left!=NULL){
      assegna_array(start,end,p->left,arr_staz,arr_auto,i);
    }
    if (p->var1 >= start && p->var1<=end) {
      arr_staz[*i]=p->var1;
      arr_auto[*i]=max_auto(p->testa_auto);
      *i=*i+1;
    }
    if (p->right!=NULL){
      assegna_array(start,end,p->right,arr_staz,arr_auto,i);
    }
  }

  return;
}

int max_staz_ragg(int part,int* arr_staz, int* arr_auto){
  int max_distance=arr_staz[part];
  for (int i = part-1; i >= 0; i--) {
    if (arr_staz[part]-arr_auto[part]<=arr_staz[i]) {
      max_distance=arr_staz[i];
    }
    else
      break;
  }
  return max_distance;
}

int stampa_percorso_indietro(int* arr_staz, int* arr_auto,int* min_array,int end_index_staz,int end_index_min,int* store,int* cnt){
  int kappa=end_index_min;
  if (arr_staz[0]==min_array[end_index_min]) {
    store[*cnt]=arr_staz[0];
    return 1;
  }
  while (arr_staz[end_index_staz] >= min_array[end_index_min]) {
    if (min_array[kappa] >= min_array[end_index_staz]) {
      kappa=end_index_staz;
    }
    end_index_staz--;
  }
  if(kappa==end_index_min)
    return 0;
  store[*cnt]=arr_staz[kappa];
  *cnt+=1;
  return stampa_percorso_indietro(arr_staz,arr_auto,min_array,end_index_staz,kappa,store,cnt);
}

int stampa_percorso_avanti(int end,int* arr_staz,int* arr_auto){
  if (arr_staz[0]+arr_auto[0]-arr_staz[end]>=0) {
    printf("%d ",arr_staz[0]);
    return 1;
  }
  else{
      for (int i = 1; i < end; i++) {
        if (arr_staz[i]+arr_auto[i]-arr_staz[end]>=0) {
          if (stampa_percorso_avanti(i,arr_staz,arr_auto)==1) {
            printf("%d ",arr_staz[i]);
            return 1;
          }
          else
            return 0;
        }
      }
    return 0;
  }
}

void pianifica_percorso(int start,int end,nodo* root){
  if (start==end) {
    printf("%d\n",start);
    return;
  }
  int flag=0;
  int opp=1;
  if (start>end) {
    start=start-end;
    end=end+start;
    start=end-start;
    opp=-1;
  }
  nodo* p=root;
  while (p->var1 < start || p->var1 > end){
    if (p->var1 < start) {
      p=p->right;
    }
    else
      p=p->left;
  }

  conta_stazioni(start,end,p,&flag);
  int arr_staz[flag];
  int arr_auto[flag];
  int i=0;
  assegna_array(start,end,p,arr_staz,arr_auto,&i);


  if (opp==-1) {
    start=start-end;
    end=end+start;
    start=end-start;
    if (arr_staz[0]+arr_auto[flag-1]>=arr_staz[flag-1]) {
      printf("%d %d\n",start,end);
      return;
    }

    int cnt=1;
    int storage[flag];
    int aux[flag];
    for (int i = 0; i < flag; i++) {
      aux[i]=max_staz_ragg(i,arr_staz,arr_auto);
      storage[i]=0;
    }
    storage[0]=start;
    if(stampa_percorso_indietro(arr_staz,arr_auto,aux,flag-1,flag-1,storage,&cnt)==0)
      printf("nessun percorso\n");
    else{
      int index1=0,index2=0,index3=0;
      while (arr_staz[index1]!=storage[cnt]) {
        index1++;
      }
      index2=index1;
      while (arr_staz[index2]!=storage[cnt-1]) {
        index2++;
      }
      index3=index2;
      for (int i = cnt; i >=2; i--) {
          while (arr_staz[index3]!=storage[i-2]) {
            index3++;
          }
          int k=index1;
          while (k!=index2) {
            if (arr_staz[k]-arr_auto[k] <= arr_staz[index1]  &&  arr_staz[index3]-arr_auto[index3] <= arr_staz[k]) {
              storage[i-1]=arr_staz[k];
              break;
            }
            k++;
          }
          index1=k;
          index2=index3;
      }
      for (int i = 0; i < flag; i++) {
        if (storage[i+1]==0) {
          break;
        }
        printf("%d ",storage[i]);
      }
      if (end==0) {
        printf("%d 0\n",storage[cnt-1]);
      }
      else
        printf("%d\n",end);
    }
  }
  else{
    if(stampa_percorso_avanti(flag-1,arr_staz,arr_auto)==1)
      printf("%d\n",arr_staz[flag-1]);
    else
      printf("nessun percorso\n");
  }
  return;
}

int main() {
  char command[30];
  int bin=0;
  bin++;
  nodo* root=NULL;
  while (scanf("%s",command)!=EOF) {
    int input1=0,input2=0;
    if (strcmp(command,"aggiungi-stazione")==0) {
      bin=scanf(" %d %d",&input1,&input2);
      root=aggiungi_staz(root,input1,input2);
    }
    else if (strcmp(command,"demolisci-stazione")==0) {
      bin=scanf(" %d",&input1);
      root=demolisci_staz(root,input1);
    }
    else if (strcmp(command,"aggiungi-auto")==0){
      bin=scanf(" %d %d",&input1,&input2);
      nodo* aux=verifica_nodo(root,input1);
      if (aux!=NULL && (aux->var2)<512) {
        aux->testa_auto=aggiungi_auto(aux->testa_auto,input2,1);
        aux->var2++;
      }
      else
        printf("non aggiunta\n");
    }
    else if (strcmp(command,"rottama-auto")==0) {
      bin=scanf(" %d %d",&input1,&input2);
      nodo* pippo=verifica_nodo(root,input1);
      if (pippo!=NULL)
        pippo->testa_auto=rottama_auto(pippo->testa_auto,input2,pippo);
      else
        printf("non rottamata\n");
    }
    else if (strcmp(command,"pianifica-percorso")==0) {
      bin=scanf(" %d %d",&input1,&input2);
      pianifica_percorso(input1,input2,root);
    }
  }
  black_hole(root);
  return 0;
}
