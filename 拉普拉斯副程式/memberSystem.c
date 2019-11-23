//member system 2019/11/18
#include <stdio.h>
#include <stdlib.h>
//全域變數
int g_userStatus=0;//代表使用者的狀態: 0是未登入, 1是已登入
char g_userName[50]="0";//代表使用者的名字 會員系統用來判斷當前登入的會員身分

//副程式宣告
void signUp(); //註冊
void store_userData(FILE* fpa, char user_name[], char password[], char email[]); //儲存使用者資訊
int email_check(FILE* fpr, char email[]); //判斷信箱是否重複註冊 1:沒重複 0:有重複
int password_check(char password[]); //判斷密碼是否符合規定 1:符合 0:不符合
int name_check(FILE* fpr, char userName[]); //判斷名字是否註冊過了 1:沒重複 0:有重複
void login(); //登入
int login_check(FILE* fpr, char user_name[], char user_password[]); //檢查帳號密碼是否符合 1:符合 0:不符合
void logout(); //登出
void member_system(); //會員系統
void showMyFavorite(); //顯示使用者的收藏店家 //加入個人收藏
void user_comment(); //顯示使用者的評論文章紀錄
void UI_setting(); //介面設置

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

void member_system() //會員系統
{
    int choice;
    while(1){
        printf("\n-----------------Member System----------------\n");
        if(g_userStatus==0){//未登入
            printf("(1)註冊 (2)登入: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    signUp();
                    break;
                case 2:
                    login();
                    break;
                default:
                    printf("沒有這個選項請重新選擇!\n");
                    continue;
            }
        }else if(g_userStatus==1){//已登入
            printf("%s 你好!\n",g_userName);
            printf("(1)個人收藏 (2)評論文章 (3)介面設置 (4)登出: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    showMyFavorite();
                    break;
                case 2:
                    user_comment();
                    break;
                case 3:
                    UI_setting();
                    break;
                case 4:
                    logout();
                    break;
                default:
                    printf("沒有這個選項請重新選擇!\n");
                    continue;
            }
        }
    }
}

void showMyFavorite()//顯示使用者的收藏店家 //加入個人收藏
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
                printf("%s",data);
        }
    }
    fclose(fpr);
}

void user_comment()//顯示使用者的評論文章紀錄
{
    printf("there is no comment\n");
}

void UI_setting()//介面設置
{
    int choice;
    printf("--------------------\n");
    printf("介面設置\n");
    printf("--------------------\n");
    while(1){
        printf("(1)白底黑字 (2)黑底綠字 (3)藍底黃字: ");
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
            default:
                printf("沒有這個選項請重新選擇!\n");
                continue;
        }
        break;
    }
}

int main()
{
    member_system();
    return 0;
}
