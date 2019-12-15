#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Shop{
	char shopname[50];
	char shoptime[7][10];
	char category[20];
	int way;
	int open[8];
	int close[8];
	int shopEvaluation;
	int EvaluationNum;
	char item[101][101];
	int itemprice[101];
	//int itemcount;
}Shop;
Shop shoplist[20];

void Eattime(){
    int i,time,j,ZERO=0;
    printf("�п�J�P���s��(0~6����~��):");
    scanf("%d",&j);
    if(j<0||j>6){
        printf("�Э��s��J\n");
    }
    printf("�п�J���\�ɶ�(24�p��):");
    scanf("%d",&time);
    for(i=0;i<7;i++){
        if(time>=shoplist[i].open[j]&&time<=shoplist[i].close[j]){
            printf("�H�U���j�M���\�U:\n");
            printf("%s\n",shoplist[i].shopname);
            ZERO++;
        }
    }
    if(ZERO==0)printf("�S���ŦX���\�U\n");
}

void Category(){
    char nam[20];
    int i,j,ZERO=0;
    printf("�п�J�n�����O:(noodle,rice,subway,fastfood,dumpling):");
    scanf("%s",nam);
    for(i=0;i<7;i++){
        if(strcmp(nam,shoplist[i].category)==0){
            printf("%s\n",shoplist[i].shopname);
            for(j=0;j<5;j++){
                printf("%s %d\n",shoplist[i].item[j],shoplist[i].itemprice[j]);
            }
            printf("\n");
            ZERO++;
        }
    }
    if(ZERO==0){
        printf("�����ŦX����\n");
    }
}

void price(){
    int i,j,sum=0,a=5;
    printf("\n��������:\n");
    for(i=0;i<7;i++){
        printf("%s\n",shoplist[i].shopname);
        for(j=0;j<a;j++){
            printf("%s",shoplist[i].item[j]);
            printf("%d\n",shoplist[i].itemprice[j]);
            //if(shoplist[i].itemprice[j]==0) a--;
            sum=sum+shoplist[i].itemprice[j];

        }
        printf("��������=>%d��\n\n",sum/5);
        a=5;
        sum=0;
    }

}

int main(){
    FILE *Fptr=NULL;
    char name[101];
    int i=0,j=0,k=0,input;
    Fptr=fopen("shopinformation.txt","r");
    while(!feof(Fptr)){
        fscanf(Fptr,"%s",name);
        //printf("%s\n",name);
        if(strcmp(name,"way:")==0){
            fscanf(Fptr,"%d",&shoplist[i].way);
            //printf("WAY:%d\n",shoplist[i].way);
        }
        if(strcmp(name,"Shopname:")==0){
            fscanf(Fptr,"%s",shoplist[i].shopname);
            //printf("%s\n",shoplist[i].shopname);
        }
        if(strcmp(name,"category:")==0){
            fscanf(Fptr,"%s",shoplist[i].category);
            //printf("���O%s\n",shoplist[i].category);
        }
        if(strcmp(name,"Businesshours:")==0){
            for(j=0;j<7;j++){
                fscanf(Fptr,"%s %d %d",shoplist[i].shoptime[j],&shoplist[i].open[j],&shoplist[i].close[j]);
                //printf("%s %d %d\n",shoplist[i].shoptime[j],shoplist[i].open[j],shoplist[i].close[j]);
            }
        }
        if(strcmp(name,"Evaluation:")==0){
            fscanf(Fptr,"%d",&shoplist[i].shopEvaluation);
            //printf("Evaluation:%d\n",shoplist[i].shopEvaluation);
        }
        if(strcmp(name,"Number-of-reviews:")==0){
            fscanf(Fptr,"%d",&shoplist[i].EvaluationNum);
            //printf("EvaluationNum:%d\n",shoplist[i].EvaluationNum);
        }
        if(strcmp(name,"Productprice:")==0){
            j=0;
            while(j!=5){
                fscanf(Fptr,"%s %d",shoplist[i].item[j],&shoplist[i].itemprice[j]);
                //printf("%s",shoplist[i].item[j]);
                //printf("%d\n",shoplist[i].itemprice[j]);
                j++;
            }
            //shoplist[i].itemcount=j;
            i++;
            //printf("\n");
        }
    }
    while(1){
        printf("�����t�νп�J�Q�n�������覡:(1)���\�ɬq (2)�D�����O (3)���찪�C (4)Exit:");
        scanf("%d",&input);
        if(input==NULL){
            printf("�A�|����J:\n");
        }
        else if(input==1){
            Eattime();
        }
        else if(input==2){
            Category();
        }
        else if(input==3){
            price();
        }
        else if(input==4)break;
        else{
            printf("Error!!�Э��s��J\n");
        }
    }
	return 0;
}
