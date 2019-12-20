//2019/11/18 member system
//2019/12/18 +mainPage +drawCard_system
//2019/12/20 +category_system +sorting_system +review_system
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//全域變數
int g_userStatus=0;//代表使用者的狀態: 0是未登入, 1是已登入
char g_userName[50]="0";//代表使用者的名字 會員系統用來判斷當前登入的會員身分

//副程式宣告
void member_system(); //會員系統
void signUp(); //註冊
void store_userData(FILE* fpa, char user_name[], char password[], char email[]); //儲存使用者資訊
int email_check(FILE* fpr, char email[]); //判斷信箱是否重複註冊 1:沒重複 0:有重複
int password_check(char password[]); //判斷密碼是否符合規定 1:符合 0:不符合
int name_check(FILE* fpr, char userName[]); //判斷名字是否註冊過了 1:沒重複 0:有重複
void login(); //登入
int login_check(FILE* fpr, char user_name[], char user_password[]); //檢查帳號密碼是否符合 1:符合 0:不符合
void logout(); //登出
void addMyFavorite(); //加入個人收藏
void showMyFavorite(); //顯示使用者的收藏店家
int favoriteRepeat(char shop_name[]);//收藏店家重複
void reviewHistory(); //顯示使用者的評論文章紀錄
void UI_setting(); //介面設置
void mainPage();//登入後主頁面
void addMyFavorite();//加入收藏店家

void drawCard_system();//抽卡系統

void review_system();//評論系統

void category_system();//分類系統
void Eattime();
void Category();
void price();

void sorting_system();//排序系統
void PriceSorting();

//-------------------分類系統---------------------
typedef struct Shop{
	char shopname[50];
	char shoptime[7][10];
	char category[20];
	int way;                    //距離
	int open[8];
	int close[8];
	int shopEvaluation;         //評價
	int EvaluationNum;          //熱門
	char item[101][101];
	int itemprice[101];         //價位
}Shop;
Shop shoplist[20];
int PriceSum[7]={0};
char sortname[20];

void Eattime(){//分類系統
    int i,time,j,ZERO=0;
    printf("請輸入星期編號(0~6為日~六):");
    scanf("%d",&j);
    if(j<0||j>6){
        printf("請重新輸入\n");
    }
    printf("請輸入用餐時間(24小時):");
    scanf("%d",&time);
    for(i=0;i<7;i++){
        if(time>=shoplist[i].open[j]&&time<=shoplist[i].close[j]){
            printf("以下為搜尋到餐廳:\n");
            printf("%s\n",shoplist[i].shopname);
            ZERO++;
        }
    }
    if(ZERO==0)printf("沒有符合的餐廳\n");
}
void Category(){//分類系統
    char nam[20];
    int i,j,ZERO=0;
    printf("請輸入要的類別:(noodle,rice,subway,fastfood,dumpling):");
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
        printf("未有符合項目\n");
    }
}
void price(){//分類系統
    int i,j,sum=0,a=5;
    printf("\n平均價格:\n");
    for(i=0;i<7;i++){
        printf("%s\n",shoplist[i].shopname);
        for(j=0;j<a;j++){
            printf("%s",shoplist[i].item[j]);
            printf("%d\n",shoplist[i].itemprice[j]);
            //if(shoplist[i].itemprice[j]==0) a--;
            sum=sum+shoplist[i].itemprice[j];

        }
        printf("平均價位=>%d元\n\n",sum/5);
        a=5;
        sum=0;
    }

}

void category_system()//分類系統
{
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
            //printf("類別%s\n",shoplist[i].category);
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
        printf("分類系統請輸入想要的分類方式:(1)用餐時段 (2)主食類別 (3)價位高低 (4)Exit:");
        scanf("%d",&input);
        if(input==NULL){
            printf("你尚未輸入:\n");
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
            printf("Error\n");
        }
    }
    return;
}
//---------------評論系統----------------------
void review_system()//評論系統
{
    //扫描二维码还没有想出来怎么写，用输入代替？
    //先登录，再写评论
    char name[10],comment[200];
    //login();
    printf("請選擇你要評論的店家:");
    scanf("%s",name);
    printf("%s\n",name);
    printf("請輸入你的評論:");
    scanf("%*c");//讀換行符號
    gets(comment);
    printf("%s\n",comment);
    store_review(name,comment);
    printf("你的評論已發布!\n");
    return;
}

void store_review(char shop_name[],char comment[])
{
    FILE *fpa;
    char filename[50];
    char str2[50]="_review.txt";
    strcpy(filename,g_userName);
    strcat(filename,str2); //(檔案名稱:USERNAME_review.txt)

    fpa = fopen(filename,"a");
    fprintf(fpa,"%s\n",shop_name);
    fprintf(fpa,"%s\n",comment);
    fclose(fpa);
    return;
}
//----------------排序系統----------------------
void PriceSorting()//排序系統
{
    int i,j,sum=0,a=5;
    printf("\n平均價格:\n");
    for(i=0;i<7;i++)
    {
        for(j=0;j<a;j++)
        {
            sum=sum+shoplist[i].itemprice[j];
        }
        PriceSum[i]=sum/5;
        a=5;
        sum=0;
    }
}
void sorting_system()//排序系統
{
    int sortname;
    int n,stack[7]={0},top=-1,i,temp;
    char shopshopname[7][50];
    int j;

    printf("請輸入欲排序選項");
    printf("\n可輸入選項有:1.evaluation(評價) 2.evaluationNum(熱門程度) 3.itemprice(價格) 4.distance(距離)\n");
    printf("請問您的選擇為: ");
    scanf("%d",&sortname);

    /*排序-評價*/
    if (sortname==1)
    {
        n=0;
        while (n<7)
        {
            stack[n]=shoplist[n].shopEvaluation;
            n++;
        }
        for (i=0;i<7;i++)
        {
            for (j=0;j<i;j++)
            {
                if (stack[j]>stack[i])
                {
                    temp=stack[j];
                    stack[j]=stack[i];
                    stack[i]=temp;
                }
            }
        }

        for (j=6;j>-1;j--)
        {
            printf("%d\n",stack[j]);
        }
    }

    /*排序-熱門*/
    if (sortname==2)
    {
        n=0;
        while (n<7)
        {
            stack[n]=shoplist[n].EvaluationNum;
            n++;
        }
        for (i=0;i<7;i++)
        {
            for (j=0;j<i;j++)
            {
                if (stack[j]>stack[i])
                {
                    temp=stack[j];
                    stack[j]=stack[i];
                    stack[i]=temp;
                }
            }
        }

        for (j=6;j>-1;j--)
        {
            printf("%d\n",stack[j]);
        }
    }
    /*排序-價位*/
    if (sortname==3)
    {
        PriceSorting();
        n=0;
        while (n<7)
        {
            stack[n]=PriceSum[n];
            n++;
        }
        for (i=0;i<7;i++)
        {
            for (j=0;j<i;j++)
            {
                if (stack[j]>stack[i])
                {
                    temp=stack[j];
                    stack[j]=stack[i];
                    stack[i]=temp;
                }
            }
        }

        for (j=6;j>-1;j--)
        {
            printf("%d\n",stack[j]);
        }
    }

    /*排序-距離*/
    if (sortname==4)
    {
        n=0;
        while (n<7)
        {
            stack[n]=shoplist[n].way;
            n++;
        }
        for (i=0;i<7;i++)
        {
            for (j=0;j<i;j++)
            {
                if (stack[j]>stack[i])
                {
                    temp=stack[j];
                    stack[j]=stack[i];
                    stack[i]=temp;
                }
            }
        }

        for (j=6;j>-1;j--)
        {
            printf("%d\n",stack[j]);
        }
    }

}

//----------抽卡系統-------------------------
void drawCard_system()//抽卡系統
{
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
}
//--------------會員系統------------------
void signUp() //註冊
{
    char userName[50], password[30], email[30];
    FILE *fpr,*fpa;
    fpa = fopen("userData.txt","a");//用來增加資料的, 如果沒有userData.txt會新建一個
    fpr = fopen("userData.txt","r");//用來讀取資料的
    if(fpr==NULL){//沒有檔案
        printf("can't open file!\n");
        exit(EXIT_FAILURE);
    }
    printf("\n---------註冊--------\n");
    while(1){//輸入名字
        printf("名字: ");
        if(scanf("%s%*c",userName)==EOF)return;//如果輸入Ctrl-Z就跳出(取消註冊)
        if(name_check(fpr, userName))break; //判斷名字是否重複name_check()
    }
    while(1){//輸入密碼
        printf("密碼: ");
        if(scanf("%s%*c",password)==EOF)return;//如果輸入Ctrl-Z就跳出(取消註冊)
        if(password_check(password))break; //判斷密碼長度password_check()
    }
    while(1){
        printf("信箱: ");
        if(scanf("%s%*c", email)==EOF)return;//如果輸入Ctrl-Z就跳出(取消註冊)
        if(email_check(fpr, email))break; //判斷信箱是否以註冊過email_check()
    }
    store_userData(fpa,userName, password, email);
    printf("註冊成功!\n");
    fclose(fpr);
    fclose(fpa);
    return;
}

void store_userData(FILE* fpa, char user_name[], char password[], char email[]) //儲存使用者資訊
{
    fprintf(fpa,"\nname:%s password:%s email:%s\n",user_name,password,email);
}

int email_check(FILE* fpr, char email[])//判斷信箱是否重複註冊 1:沒重複 0:有重複
{
    char data[200];
    char name_data[50], password_data[50], email_data[50];
    rewind(fpr);//檔案指標移到開頭
    while(fgets(data, 128, fpr)!=NULL)
    {
        sscanf(data,"name:%s password:%s email:%s", name_data, password_data, email_data);
        if(strcmp(email_data,email)==0){
            printf("這個信箱已經註冊過了\n請重新輸入!\n\n");
            return 0;
        }
    }
    return 1;
}

int password_check(char password[])//判斷密碼是否符合規定 1:符合 0:不符合
{
    int len=strlen(password);
    if(len<8){
        printf("密碼長度至少要>=8\n\n");
        return 0;//長度小於8則不符合規定
    }
    return 1;
}

int name_check(FILE* fpr, char userName[]) //判斷名字是否註冊過了 1:沒重複 0:有重複
{
    char data[200];
    char name_data[50], password_data[50], email_data[50];
    rewind(fpr);//檔案指標移到開頭
    while(fgets(data, 128, fpr)!=NULL)
    {
        sscanf(data,"name:%s password:%s email:%s", name_data, password_data, email_data);
        if(strcmp(name_data,userName)==0){
            printf("這個名字已經被別人使用過了:(\n請重新輸入!\n\n");
            return 0;
        }
    }
    return 1;

}
void login() //登入
{
    FILE *fpr;
    fpr = fopen("userData.txt","r");
    char userName[50], password[30];
    printf("\n---------登入--------\n");
    while(1){
        printf("名字: ");
        if(scanf("%s%*c",userName)==EOF)return;//如果輸入Ctrl-Z就跳出(取消登入)
        printf("密碼: ");
        if(scanf("%s%*c",password)==EOF)return;//如果輸入Ctrl-Z就跳出(取消登入)
        if(login_check(fpr,userName,password))break;
        printf("帳號或密碼錯誤\n\n");

    }
    printf("\n登入成功! 你好 %s!\n",userName);
    g_userStatus=1;//使用者狀態: 已登入
    strcpy(g_userName,userName);//當前會員名稱
    fclose(fpr);
    return;
}

int login_check(FILE* fpr, char user_name[], char user_password[])//檢查帳號密碼是否符合 1:符合 0:不符合
{
    char name_data[50],password_data[50],email_data[50];
    char data[200];
    rewind(fpr);
    while(fgets(data, 128, fpr)!=NULL)//一次讀取一行
    {
        sscanf(data,"name:%s password:%s email:%s", name_data, password_data, email_data);//分析字串
        if(strcmp(name_data,user_name)==0){
            //printf("find same name!!\n");
            if(strcmp(password_data,user_password)==0){
                //printf("same password!!\n");
                return 1;
            }
        }
        data[0]='\0';//清空陣列
    }
    return 0;
}

void logout() //登出
{
    g_userStatus=0;
}

void LoginSignin() //選擇註冊或登入
{
    int choice;
    while(1){
        printf("(1)註冊 (2)登入 (3)離開: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                signUp();
                break;int choice;
            case 2:
                login();
                break;
            case 3:
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("沒有這個選項請重新選擇!\n");
                continue;
        }
        if(g_userStatus==1){ //使用者已登入
            return;
        }
    }
    return;
}

void member_system() //會員系統
{
    int choice;
    while(1){
        printf("\n-----------------Member System----------------\n");
        printf("%s 你好!\n",g_userName);
        printf("(1)加入個人收藏 (2)評論文章紀錄 (3)介面設置 (4)個人收藏紀錄 (5)返回主介面 (6)登出 : ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                addMyFavorite();
                break;
            case 2:
                reviewHistory();
                break;
            case 3:
                UI_setting();
                break;
            case 4:
                showMyFavorite();
                break;
            case 5:
                return;
            case 6:
                logout();
                break;
            default:
                printf("沒有這個選項請重新選擇!\n");
                continue;
        }

    }
}
int favoriteRepeat(char shop_name[])//判斷有沒有重複收藏的店家
{
    FILE *fpr;
    char data[100];
    char file_name[30];
    strcpy(file_name,g_userName);
    strcat(file_name,"_Favorite.txt");//檔案名稱:USERNAME_Favorite.txt
    fpr = fopen(file_name,"r");//讀檔判斷是否有重複收藏店家
    while(!feof(fpr)){
        fscanf(fpr,"%s",data);
         if(strcmp(shop_name,data)==0){
            fclose(fpr);
            return 1;
         }
    }
    fclose(fpr);
    return 0;
}
void addMyFavorite() //加入個人收藏
{
    FILE *fpa,*fshop;
    fshop=fopen("shopinformation.txt","r");
    int add=0;//新增失敗0或成功1或重複2
    char file_name[30],data[300];
    char shop_name[50];//店名
    strcpy(file_name,g_userName);
    strcat(file_name,"_Favorite.txt");//檔案名稱:USERNAME_Favorite.txt
    fpa = fopen(file_name,"a");//寫入一個檔案(檔案名稱:USERNAME_Favorite.txt)

    while(1){
        printf("請輸入想加入收藏的店家名: ");
        if(scanf("%s",shop_name)==EOF)break;
        while(!feof(fshop)){
            fscanf(fshop,"%s",data);
            if(strcmp(shop_name,data)==0){//在shopinformation.txt中找到該店家
                if(favoriteRepeat(shop_name)){//重複收藏
                    add=2;
                    break;
                }else{//沒有重複收藏
                    fprintf(fpa,"%s\n",shop_name);
                    add=1;
                    break;
                }
            }
        }
        if(add==0){
            printf("\n查無此店家! 請重新輸入!\n");
            rewind(fshop);//檔案指標移回開頭
            continue;
        }else if(add==1){
            printf("加入成功!\n");
            break;
        }else{
            printf("您已收藏過此店家!\n");
            break;
        }
    }
    fclose(fshop);
    fclose(fpa);
}

void showMyFavorite() //顯示使用者的收藏店家
{
    printf("--------------------\n");
    printf("個人收藏\n");
    printf("--------------------\n");
    FILE *fpr,*fpw;
    char user_name[30], file_name[30], data[500];
    strcpy(file_name,g_userName);
    strcat(file_name,"_Favorite.txt");//檔案名稱:USERNAME_Favorite.txt
    fpr = fopen(file_name,"r");
    if(fpr==NULL){ //沒有此檔案
        fpw = fopen(file_name,"w");//建立一個檔案(檔案名稱:USERNAME_Favorite.txt)
        fclose(fpw);
        printf("你沒有收藏任何店家!\n");
    }else{ //有檔案
        fseek(fpr, 0, SEEK_END);//檔案指標移到結尾
        int len = ftell(fpr);
        if(len==0){//有檔案但是是空的
            printf("你沒有收藏任何店家!\n");
        }
        else{
            fseek(fpr, 0, SEEK_SET);//檔案指標移到開頭
            while(fscanf(fpr,"%s",data)!=EOF)//印出USERNAME_Favorite.txt的內容
                printf("%s\n",data);
        }
    }
    fclose(fpr);
}

void reviewHistory()//顯示使用者的評論文章紀錄
{
    FILE *fpr;
    char filename[50];
    char str2[50]="_review.txt";
    char review[128];
    strcpy(filename,g_userName);
    strcat(filename,str2); //(檔案名稱:USERNAME_review.txt)
    fpr = fopen(filename,"r");
    if(fpr==NULL){
        printf("沒有任何評論文章紀錄!\n");
    }else{
        while(!feof(fpr)){
            fgets(review, 128, fpr);//讀取一行
            printf("%s\n",review); //將評論印出
            review[0]=NULL;
        }
    }
}

void UI_setting()//介面設置
{
    int choice;
    printf("--------------------\n");
    printf("介面設置\n");
    printf("--------------------\n");
    while(1){
        printf("(1)白底黑字 (2)黑底綠字 (3)藍底黃字 (4)黑底白字: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                system("COLOR 70");
                break;
            case 2:
                system("COLOR 0A");
                break;
            case 3:
                system("COLOR 3E");
                break;
            case 4:
                system("COLOR 07");
                break;
            default:
                printf("沒有這個選項請重新選擇!\n");
                continue;
        }
        break;
    }
}

void mainPage()
{
    int choice;
    while(1){
        printf("\n-----Main Page-----\n");
        printf("請選擇功能\n");
        printf("(1)抽卡系統 (2)會員系統 (3)分類系統 (4)排序系統 (5)評論系統: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                drawCard_system();
                break;
            case 2:
                member_system();
                break;
            case 3:
                category_system();
                break;
            case 4:
                sorting_system();
                break;
            case 5:
                review_system();
                break;
            default:
                printf("沒有這個選項!\n");
        }
    }
}

int main()
{
    while(1){
        if(g_userStatus==0){//使用者未登入
            LoginSignin();
        }else{
            mainPage();//登入後主介面
        }
    }
    return 0;
}
