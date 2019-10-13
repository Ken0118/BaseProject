#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main (){
	FILE *cfPtr;//建檔指標 
	int randwalk;//存隨機0~7方位之變數	
	int n,m,**Array,i,j,count=1,starti,startj,newPlase=1;//二維指標開動態陣列減少空間浪費,newPlase計算新到位置為1的 
	int Wi[8]={1,1,1,0,-1,-1,-1,0},Wj[8]={1,0,-1,-1,-1,0,1,1};//九宮格方向照0~7存兩個一維陣列 
	cfPtr= fopen("D0713066_PE2.csv","w");//建CSV檔 
	scanf("%d %d %d %d",&n,&m,&starti,&startj);//輸入 n m 陣列大小 sti stj 起始陣列位置 
	if(n>2&&n<=40&&m>=2&&m<=20&&starti>=0&&starti<n&&startj>=0&&startj<m){//判斷輸入是否符合規則否則噴錯 
		Array=(int**)calloc(n,sizeof(int*));//用calloc 乾淨 int 動態陣列 
		for(i=0;i<n;i++){
			Array[i]=(int*)calloc(m,sizeof(int));
		}
		Array[starti][startj]=1;//將起始位置設為1 
		srand(time(NULL));//用時間達到亂數標準 
		while(1){
			if(count>50000)break;//計數count 超過50000 跳出 
			randwalk=rand()%8;//亂數取0~7 
			if((starti+Wi[randwalk])>=0&&(starti+Wi[randwalk])<n&&(startj+Wj[randwalk])>=0&&(startj+Wj[randwalk])<m){
				//用sti 跟 stj 與一開始存的二為陣列 去做 運算 並判斷 是否在邊界內 
				starti=starti+Wi[randwalk];//符合則存入sti 
				startj=startj+Wj[randwalk];//符合則存入stj
				Array[starti][startj]++;//新位置的變數+1 
				if(Array[starti][startj]==1){//假如是新變數為1則newplase計算 多1 
					newPlase++;
					count++;//總步數的count也要+1 
				}
				else{//假如新位置不是1則只要計算總步數 
					count++;//總步數的count也要+1
				}
			}
			else{//假如前面 判斷sti stj 跟方位的運算 不符 則略過重取新亂數 
				continue;
			}
			if(newPlase==n*m)break;//假如newplace計算完每個位置都走過1次則跳出迴圈 
		}
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){	
				printf("%d ",Array[i][j]);	//輸出陣列 
			}	
			printf("\n");
		}
		printf("Sum : %d\n",count);//輸出總數 
	}
	else{
		printf("Error!\n");//scanf錯誤 噴錯 
	}
	fprintf(cfPtr,"Total number of legal moves: %d",count);//寫入csv檔內 
	fprintf(cfPtr,"\n");//記得換行 
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){		
			fprintf(cfPtr,"%d,",Array[i][j]);//用 ','	才能將資料分成一格一格 
		}	
		fprintf(cfPtr,"\n");//資料換行 
	}
	fclose(cfPtr);//使用完記得關閉檔案 
	return 0;
} 
