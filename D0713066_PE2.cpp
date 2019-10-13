#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main (){
	FILE *cfPtr;//���ɫ��� 
	int randwalk;//�s�H��0~7��줧�ܼ�	
	int n,m,**Array,i,j,count=1,starti,startj,newPlase=1;//�G�����ж}�ʺA�}�C��֪Ŷ����O,newPlase�p��s���m��1�� 
	int Wi[8]={1,1,1,0,-1,-1,-1,0},Wj[8]={1,0,-1,-1,-1,0,1,1};//�E�c���V��0~7�s��Ӥ@���}�C 
	cfPtr= fopen("D0713066_PE2.csv","w");//��CSV�� 
	scanf("%d %d %d %d",&n,&m,&starti,&startj);//��J n m �}�C�j�p sti stj �_�l�}�C��m 
	if(n>2&&n<=40&&m>=2&&m<=20&&starti>=0&&starti<n&&startj>=0&&startj<m){//�P�_��J�O�_�ŦX�W�h�_�h�Q�� 
		Array=(int**)calloc(n,sizeof(int*));//��calloc ���b int �ʺA�}�C 
		for(i=0;i<n;i++){
			Array[i]=(int*)calloc(m,sizeof(int));
		}
		Array[starti][startj]=1;//�N�_�l��m�]��1 
		srand(time(NULL));//�ήɶ��F��üƼз� 
		while(1){
			if(count>50000)break;//�p��count �W�L50000 ���X 
			randwalk=rand()%8;//�üƨ�0~7 
			if((starti+Wi[randwalk])>=0&&(starti+Wi[randwalk])<n&&(startj+Wj[randwalk])>=0&&(startj+Wj[randwalk])<m){
				//��sti �� stj �P�@�}�l�s���G���}�C �h�� �B�� �çP�_ �O�_�b��ɤ� 
				starti=starti+Wi[randwalk];//�ŦX�h�s�Jsti 
				startj=startj+Wj[randwalk];//�ŦX�h�s�Jstj
				Array[starti][startj]++;//�s��m���ܼ�+1 
				if(Array[starti][startj]==1){//���p�O�s�ܼƬ�1�hnewplase�p�� �h1 
					newPlase++;
					count++;//�`�B�ƪ�count�]�n+1 
				}
				else{//���p�s��m���O1�h�u�n�p���`�B�� 
					count++;//�`�B�ƪ�count�]�n+1
				}
			}
			else{//���p�e�� �P�_sti stj ���쪺�B�� ���� �h���L�����s�ü� 
				continue;
			}
			if(newPlase==n*m)break;//���pnewplace�p�⧹�C�Ӧ�m�����L1���h���X�j�� 
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){	
				printf("%d ",Array[i][j]);	//��X�}�C 
			}	
			printf("\n");
		}
		printf("Sum : %d\n",count);//��X�`�� 
	}
	else{
		printf("Error!\n");//scanf���~ �Q�� 
	}
	fprintf(cfPtr,"Total number of legal moves: %d",count);//�g�Jcsv�ɤ� 
	fprintf(cfPtr,"\n");//�O�o���� 
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){		
			fprintf(cfPtr,"%d,",Array[i][j]);//�� ','	�~��N��Ƥ����@��@�� 
		}	
		fprintf(cfPtr,"\n");//��ƴ��� 
	}
	fclose(cfPtr);//�ϥΧ��O�o�����ɮ� 
	return 0;
} 
