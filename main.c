#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct list{
	int x;
	char a[20];
	struct list *next;
	struct list *prev;
};
typedef struct list n;
void printList(n *node){
	n *iter;
	iter=node;
	printf("\n");
	while(iter != NULL){
		printf("%s,%d",iter->a,iter->x);
		if(iter->next!=NULL){
			printf(" -> ");
		}
		iter=iter->next;
	}
}
n* createNode(char *input){
	n* iter=(n*)malloc(sizeof(n));
	strcpy(iter->a,input);
	iter->x=1;
	iter->next=NULL;
	iter->prev=NULL;
	return iter;
}
n* insertAtHead(n* node,n* iter){
	iter->next=node;
	node->prev=iter;
	node=iter;
	node->prev=NULL;
	return node;
}
n* searchList(n* node,char *input,int T,int L,int *found){
	n *iter;
	iter=node;
	int a=1;
	while(iter != NULL){
		if(strcmp(input,iter->a)==0){
			*found=1;
			(iter->x)++;
			if(iter->x > T && iter!=node){
				if(iter->next != NULL){
					iter->prev->next=iter->next;	
					iter->next->prev=iter->prev;
				}
				else{
					iter->prev->next=NULL;
				}
				iter->prev=NULL;
				iter->next=node;
				node->prev=iter;
				node=iter;
			}	
			return node;
		}
		iter=iter->next;
		a++;
	}
	*found=0;
	return node;
}
void checkList(n* node,n* iter,int L,int *found){
	int a=1;
	iter=node;
	while(iter->next !=NULL){
		a++;
		iter=iter->next;
	}
	if(a==L+1){
		iter->prev->next=NULL;
		iter->prev=NULL;
		free(iter);
	}
}
int main() {
	char input[20]="";
	int workType=0,choose=1,T,L,found;
	FILE *fp;
	printf("BLM2512_Homework1\nBir tusa basin...");
	getch();
	system("cls");
	printf("Esik degeri giriniz.\n");
	scanf("%d",&T);
	printf("Cache Buffer kapasitesi giriniz.\n");
	scanf("%d",&L);
	n *root,*iter;
	while(!(workType==1 || workType==2)){
		printf("Calisma tipi secin.\n1.Console dan elle.\n2.Dosya adresi girin.(Orn:text.txt)\n");
		scanf("%d",&workType);
	}
	switch(workType){
		case 1:
			printf("Veri giriniz.\n");
			scanf("%s",input);
			break;
		case 2:
			scanf("%s",input);
			fp=fopen(input,"r+");
			fscanf(fp,"%s",input);
			break;
	}
	root=createNode(input);
	system("cls");
	printList(root);
	if(workType==1){
		printf("\n0. Cikis\n1. Girdi Ekle\n");
		scanf("%d",&choose);
	}
	while(choose==1){
		switch(workType){
			case 1:
				printf("Veri giriniz.\n");
				scanf("%s",input);
				break;
			case 2:
				fscanf(fp,"%s ",input);
				break;
		}
		root=searchList(root,input,T,L,&found);
		if(found==0){
			root=insertAtHead(root,createNode(input));
			checkList(root,iter,L,&found);
		}
		printList(root);
		switch(workType){
			case 1:
				printf("\n0. Cikis\n1. Girdi Ekle\n");
				scanf("%d",&choose);
				break;
			case 2:
				if(feof(fp)){
					choose=0;
				}
				break;
		}
	}
	while(root!=NULL){
		iter=root->next;
		free(root);
		root=iter;
	}
}
