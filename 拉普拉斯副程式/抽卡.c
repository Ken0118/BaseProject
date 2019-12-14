#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    int num,store,hour,minute,storeH,storeM,count,waitH,waitM,i,open,list[3];
    char ask[5];
    srand(time(NULL));
    printf("目前時間(24小時制): ");
    scanf("%d:%d",&hour,&minute);
    count=0;
    while(1){
        printf("----------------------------------------\n");
        printf("\n優惠抽卡按 1\n一般抽卡按 2\n輸入數字: ");
        scanf("%d",&num);
        if(num==1 && count==3){
            printf("~~~今日優惠次數已用完!\t前往下列店家消費可打折噢!!\n");
            for(i=0;i<3;i++) printf("%d ",list[i]); //將抽到的優惠店家顯示
            printf("\n");
            continue;
        }
        store=rand()%100+1; //一百家店
        printf("\n抽到店家: %d\n",store);
        storeH=rand()%19+5;
        storeM=rand()%60;
        //printf("店家營業時間: %d:%d\n",storeH,storeM);
        if(storeH<hour) open=1; //已經開門
        else if(storeH==hour){ //如果小時是一樣的
            if(storeM<=minute) open=1; //再來比較分鐘，如果營業時間小於現在時間，已開門
            else open=0;
        }
        else open=0; //未營業

        if(open==1){ //已營業
            if(num==1){
                list[count]=store; //將店名存到list
                count=count+1; //此時優惠抽卡少一次
            }
            printf("是否前往店家?(yes or no): ");
            scanf("%s",ask);
            if(stricmp(ask,"yes")==0) break; //前往店家，結束程式
            else continue; //不前往，重抽
        }
        else{ //未營業
            printf("店家「%d」尚未營業!\n",store);
            if(storeM<minute){ //計算剩餘時間
                waitH=storeH-1-hour;
                waitM=storeM+60-minute;
            }
            else{
                waitH=storeH-hour;
                waitM=storeM-minute;
            }
            if(waitH>0) printf("還剩 %d 小時 %d 分鐘開門\n",waitH,waitM);
            else printf("還剩 %d 分鐘開門\n",waitM);
            if(num==1) printf("目前為優惠抽卡，如要重抽，此次將不計次數。\n");
            printf("\n~不重抽將直接前往該店~\n");
            printf("是否重抽?(yes or no): ");
            scanf("%s",ask);
            if(stricmp(ask,"yes")==0) continue; //重抽
            else{ //不重抽，表示想要等
                if(num==1){ //看是否為優惠抽卡
                    list[count]=store;
                    count=count+1; //次數加一
                }
                break; //程式結束
            }
        }
    }
    printf("\n~前往店家「%d」~\n",store); //選擇前往時，才印出前往店家字樣
    return 0;
}
