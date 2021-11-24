//
//  main.c
//  cainong
//  Copyright © 2020 Yizhe Chen. All rights reserved.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
FILE *fp;
char zhonglei[10][100][100], xinximing[100][100], xinxifenglei[20], xinxichengfen[100][100], zhongzhishuju[10], cmp[]="";
int zhongleishu[10], zhongleishumax,xinxishu,xinxifengleishu[100], zhongzhixinxi[100][10],
    zhongzhixinxishu,zairuflag,baocunflag,hash[100];
void shuchujiben(int bh)
{
    printf("蔬菜名称：%s %s 含营养成分：%s\n",xinximing[bh],zhonglei[xinxifengleishu[bh]][0],xinxichengfen[bh]);
}
void zairu()
{   int i,j,k;
    fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/蔬菜种类信息表.csv","r");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
    else {char str[N+1];
    fseek(fp, 0L, SEEK_SET); //指向文件开头
        zhongleishumax=0;
        fgets(str, N, fp); fgets(str, N, fp); //读两个空行
        for (i=1;i<=5;i++) zhongleishu[i]=0;
        strcpy(zhonglei[1][0],"根茎类");
        strcpy(zhonglei[2][0],"果菜类");strcpy(zhonglei[3][0],"瓜类");
        strcpy(zhonglei[4][0],"叶菜类"); strcpy(zhonglei[5][0],"菌类"); //1～100存放植物。
    while(fgets(str, N, fp) != NULL){
        j=0;
        for (i=0;i<=strlen(str); i++)
        {if ((str[i]==',')||(str[i]=='\r'))
        { j++;k=0;
            if ((str[i+1]!=',')&&(str[i+1]!='\r'))zhongleishu[j]++; if(zhongleishu[j]>zhongleishumax) zhongleishumax=zhongleishu[j];
                    else;}
            else{
                zhonglei[j][zhongleishu[j]][k]=str[i]; //从第1个开始有植物
                k++;
                }
        }
      }
    }
    fclose(fp);//读取处理种类文件结束
    
     fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/蔬菜基本信息表.csv","r");// fp指针指向文件头部
        if (fp==NULL) printf("不能加载文件!\n");
        else {char str[N+1];
             fseek(fp, 0L, SEEK_SET);
            fgets(str, N, fp);
            xinxishu=0;
               while(fgets(str, N, fp) != NULL){
                   i=2;
                   xinxishu++;
                   while (str[i]!=',')
                   {xinximing[xinxishu][i-2]=str[i];
                       i++;
                   }
                   i++;
                   j=i;
                   while (str[i]!=',')
                   {xinxifenglei[i-j]=str[i];
                       i++;
                   }
                   i++;
                   j=i;
                   xinxifengleishu[xinxishu]=atoi(xinxifenglei);//字符串数字转int数字
                   while (i<strlen(str)-1)
                   {xinxichengfen[xinxishu][i-j]=str[i];
                       i++;
                   }
                }
        }
    fclose(fp);//蔬菜基本信息处理读取结束
    
    fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/菜农种植信息表.csv","r");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
    else {char str[N+1];
        zhongzhixinxishu=0;
            fseek(fp, 0L, SEEK_SET);
            fgets(str, N, fp);
             while(fgets(str, N, fp) != NULL){
                 zhongzhixinxishu++;
                 i=0; k=0;
                 for (j=1;j<=5;j++)
                 {  memset(zhongzhishuju,0,sizeof(zhongzhishuju));//清空字符串
                     while (str[i]!=',')
                                       {zhongzhishuju[i-k]=str[i];
                                           i++;
                                       }
                     i++;
                     k=i;
                     zhongzhixinxi[zhongzhixinxishu][j]=atoi(zhongzhishuju);
                 }
             }
        }
    fclose(fp);//种植信息处理读取完毕
    
}
void baocun()
{    int i,j,k;
    fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/蔬菜种类信息表.csv","w");// fp指针指向文件头部
   if (fp==NULL) printf("不能加载文件!\n");
    fprintf(fp,"分类编号,1,2,3,4,5\n");
    fprintf(fp,"分类名称,根茎类,果菜类,瓜类,叶菜类,菌类\n");
    for (i=1;i<=zhongleishumax;i++)
    {
        for (j=0;j<=5;j++)
        {if (strcmp(zhonglei[j][i],cmp)==0)  fprintf(fp,"%c",',');
        else fprintf(fp,"%s,",zhonglei[j][i]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);//种类文件写入完成
    
    fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/蔬菜基本信息表.csv","w");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
    fprintf(fp,"蔬菜编号,蔬菜名称,分类码,营养成分\n");
    for (i=1;i<=xinxishu;i++)
    {
        fprintf(fp,"%d,%s,%d,%s\n",i,xinximing[i],xinxifengleishu[i],xinxichengfen[i]);
    }
     fclose(fp);//基本信息保存完成
    
    fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/菜农种植信息表.csv","w");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
    fprintf(fp,"编号,蔬菜编号,种植面积,收获重量,种植年份\n");
    for (i=1;i<=zhongzhixinxishu;i++)
       {
           fprintf(fp,"%d,%d,%d,%d,%d\n",zhongzhixinxi[i][1],zhongzhixinxi[i][2],
                   zhongzhixinxi[i][3],zhongzhixinxi[i][4],zhongzhixinxi[i][5]);
       }
     fclose(fp);//种植信息保存完成
}

void tongji1() //分别统计某年各类蔬菜（如叶菜类、根茎类等）种植总面积、收获总重量，按总重量降序排序后，输出分类名称、种植面积、收获总重量（按种类统计）
{   int tongji1[10][10],i,year,j,max,maxshu;
    printf("请输入年份\n");
    scanf("%d",&year);
    for (i=1;i<=5;i++) {tongji1[i][1]=0;tongji1[i][2]=0;}
    for (i=1; i<=zhongzhixinxishu;i++)
    {
        if (year==zhongzhixinxi[i][5]) {
                                        tongji1[xinxifengleishu[zhongzhixinxi[i][2]]][1]+=zhongzhixinxi[i][3];
                                        tongji1[xinxifengleishu[zhongzhixinxi[i][2]]][2]+=zhongzhixinxi[i][4];
                                        }
        }
    for(i=1;i<=5;i++) hash[i]=0;
    for(i=1;i<=5;i++)
    {   maxshu=-1;
        for (j=1;j<=5;j++)
            if ((!hash[j])&&(tongji1[j][2]>maxshu)) {max=j; maxshu=tongji1[j][2];}
        printf("%s %d年种植总面积%d 种植总重量%d\n",zhonglei[max][0],year,tongji1[max][1],tongji1[max][2]);
        hash[max]=1; //处理降序问题
    }
}

void tongji2() //以所输入的起止年份为条件（如2017-2019），按蔬菜名称（如菠菜、黄瓜等）统计该三年内所种各种蔬菜总面积、收获总重量，按总重量降序排序后，输出蔬菜名称、分类名称、种植面积、总重量。
{   int tongji2[100][10],i,year1,year2,j,max,maxshu;
    printf("请输入起始年份和结束年份\n");
     scanf("%d%d",&year1,&year2);
        for (i=1;i<=xinxishu;i++) {tongji2[i][1]=0;tongji2[i][2]=0;}
    for (i=1; i<=zhongzhixinxishu;i++)
       {
           if (year1<=zhongzhixinxi[i][5]<=year2) {
                                           tongji2[zhongzhixinxi[i][2]][1]+=zhongzhixinxi[i][3];
                                           tongji2[zhongzhixinxi[i][2]][2]+=zhongzhixinxi[i][4];
                                           }
           }
    for(i=1;i<=xinxishu;i++) hash[i]=0;
    for(i=1;i<=xinxishu;i++)
    {   maxshu=-1;
        for (j=1;j<=xinxishu;j++)
            if ((!hash[j])&&(tongji2[j][2]>maxshu)) {max=j; maxshu=tongji2[j][2];}
        printf("%s %s %d年到%d年种植总面积%d 种植总重量%d\n",xinximing[max],zhonglei[xinxifengleishu[max]][0],year1,year2,tongji2[max][1],tongji2[max][2]);
        hash[max]=1; //处理降序问题
    }
    
}

void tongji3() //分别统计某种类蔬菜的已有的数量
{ printf("请输入蔬菜分类码\n");
    int n;
    scanf("%d",&n);
    printf("%s的蔬菜有%d个\n",zhonglei[n][0],zhongleishu[n]);
}

void tongji4() //给定某个营养成分，程序自动判定含有该营养成分的蔬菜，并且显示输出所有含有该营养成分的蔬菜名称。
{ printf("请输入需要蔬菜含有的成分\n");
    char yuansu[50]; int i,pd;
    scanf("%s",yuansu);
    pd=0;
    for (i=1;i<=xinxishu;i++)
        if (strstr(xinxichengfen[i],yuansu)!=NULL) pd=1;
    if (pd) {   printf("含有成分%s的蔬菜有：",yuansu);
                for (i=1;i<=xinxishu;i++)
                       if (strstr(xinxichengfen[i],yuansu)!=NULL) printf("%s、",xinximing[i]);
            }
    else printf("无含有成分%s的蔬菜\n",yuansu);
    
}

void tongji5() //查找year年种植的所有蔬菜总面积和总重量
{   int zongz,zongmj,i,year;
    printf("请输入年份\n");
    scanf("%d",&year);
    zongz=0; zongmj=0;
    for (i=1; i<=zhongzhixinxishu;i++)
    {
        if (year==zhongzhixinxi[i][5]) {
                                        zongz+=zhongzhixinxi[i][3];
                                        zongmj+=zhongzhixinxi[i][4];
                                        }
        }
    printf("%d年蔬菜种植总面积：%d 总重量：%d\n",year,zongz,zongmj);
}

void daochu3()//1)统计并显示某年各类蔬菜种植信息（年份、分类名称、种植面积、收获总重量），并将统计结果写入文件（按年份各类蔬菜信息统计表.xls）中。
{ fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/按年份各类蔬菜信息统计表.csv","w");// fp指针指向文件头部
      if (fp==NULL) printf("不能加载文件!\n");
    int i,year,tongji1[10][10];
    fprintf(fp,"年份,分类名称,种植面积（分）,收获总重量（kg）\n");
    printf("请输入年份\n");
    scanf("%d",&year);
    for (i=1;i<=5;i++) {tongji1[i][1]=0;tongji1[i][2]=0;}
    for (i=1; i<=zhongzhixinxishu;i++)
    {
        if (year==zhongzhixinxi[i][5]) {
                                        tongji1[xinxifengleishu[zhongzhixinxi[i][2]]][1]+=zhongzhixinxi[i][3];
                                        tongji1[xinxifengleishu[zhongzhixinxi[i][2]]][2]+=zhongzhixinxi[i][4];
                                        }
        }
    for (i=1;i<=5;i++)
        fprintf(fp,"%d,%s,%d,%d\n",year,zhonglei[i][0],tongji1[i][1],tongji1[i][2]);
    fclose(fp);
}

void daochu4()//统计并显示某蔬菜（如菠菜、黄瓜等）三年内种植信息（年份、蔬菜名称、分类名称、面积、收获重量），并将统计结果写入文件（按蔬菜名称统计信息表.xls）中。
{fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/按蔬菜名称统计信息表.csv","w");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
    fprintf(fp,"年份,蔬菜名称,分类名称,种植面积（分）,收获重量（kg）\n");
    printf("请输入蔬菜名\n");
    int i,m[3000],z[3000],pd[3000];
    char mingzi[50],zl[50];
    scanf("%s",mingzi);
    pd[2018]=0;pd[2019]=0;pd[2020]=0;
    for (i=1; i<=zhongzhixinxishu;i++)
       if (strcmp(mingzi,xinximing[zhongzhixinxi[i][2]])==0)
                {
                    m[zhongzhixinxi[i][5]]=zhongzhixinxi[i][3];
                     z[zhongzhixinxi[i][5]]=zhongzhixinxi[i][4];
                    pd[zhongzhixinxi[i][5]]=1;
                    strcpy(zl,zhonglei[xinxifengleishu[zhongzhixinxi[i][2]]][0]);
                }
    for (i=2018;i<=2020;i++)
        if (pd[i]) fprintf(fp,"%d,%s,%s,%d,%d\n",i,mingzi,zl,m[i],z[i]);
        else fprintf(fp,"%d,%s,%s,%d,%d\n",i,mingzi,zl,0,0);
fclose(fp);
    
}
void daochu5()//统计并显示用户自由查询信息（如：年份=’2018’，收获重量>’30’,分类名称=’根茎类’），并将统计结果写入文件（该文件可由用户自主命名.xls）中。
{   fp=fopen("/Users/yizhechen/Desktop/study/xcode code/codec/cainong/cainong/test.csv","w");// fp指针指向文件头部
    if (fp==NULL) printf("不能加载文件!\n");
     fprintf(fp,"年份,蔬菜名称,分类名称,种植面积（分）,收获重量（kg）\n");
    printf("请输入种类名，种植年份，种植最小重量\n");
    int year,w,i;
    char zl[50];
    scanf("%s",zl);
    scanf("%d%d",&year,&w);
    for (i=1; i<=zhongzhixinxishu;i++)
        if ((year==zhongzhixinxi[i][5])&&(zhongzhixinxi[i][4]>=w)&&(strcmp(zl,zhonglei[xinxifengleishu[zhongzhixinxi[i][2]]][0])==0))
            {fprintf(fp,"%d,%s,%s,%d,%d\n",year,xinximing[zhongzhixinxi[i][2]],zl,zhongzhixinxi[i][3],zhongzhixinxi[i][4]);
                
            }
    fclose(fp);
}
int main()
{
    int  shuru1,shuru2,shuru3,shuru5,fenglei,weizhi,bianhao;   int i;
    char shuru4[100];
    if (zairuflag%2==0) zairu();
     do
     {printf("请从下方选择功能，Ctrl+d退出\n"); //win中为ctrl+z mac中为此
    printf("数据载入保存设置输入1\n");
    printf("数据维护输入2\n");
    printf("数据查询输入3\n");
     printf("数据统计输入4\n");
    printf("数据导入导出输入5\n");
        scanf("%d",&shuru1);
        if (shuru1==1) {  //设置部分
        printf("切换数据载入模式输入1\n");//默认都为自动
        printf("切换数据保存模式输入2\n");
        printf("手动载入数据输入3\n");
        printf("手动保存数据输入4\n");
              scanf("%d",&shuru2);
            if (shuru2==1) {zairuflag++; printf("切换成功!");};//奇数手动偶数i自动
            if (shuru2==2) {baocunflag++; printf("切换成功!");};
            if (shuru2==3) {zairu();     printf("载入成功!");  };
            if (shuru2==4) {baocun();    printf("保存成功!");  };
        };
        if (shuru1==2) {//处理数据功能
            printf("请问想对哪个文件处理？种类信息表按1 基本信息表按2 种植信息表按3\n");
            scanf("%d",&shuru2);
            if (shuru2==1) {
                            printf("请问需要什么操作？录入1 修改2 删除3\n");
                            scanf("%d",&shuru3);
                                    if (shuru3==1){
                                        printf("请输入录入的内容和分类码\n");
                                        scanf("%s\n%d",shuru4,&fenglei);//换行输入
                                        zhongleishu[fenglei]++;                              if(zhongleishu[fenglei]>zhongleishumax) zhongleishumax=zhongleishu[fenglei];     strcpy(zhonglei[fenglei][zhongleishu[fenglei]],shuru4);
                                         printf("录入成功！\n");
                                    }
                                    if (shuru3==2){
                                            printf("请输入修改的内容、分类码、位置\n");
                                            scanf("%s\n%d%d",shuru4,&fenglei,&weizhi);
                                            strcpy(zhonglei[fenglei][weizhi],shuru4);
                                            printf("修改成功！\n");
                                    }
                                    if (shuru3==3){
                                            printf("请输入删除的分类码、位置\n");
                                            scanf("%d%d",&fenglei,&weizhi);
                                            if (strcmp(zhonglei[fenglei][weizhi],cmp)==0)
                                                printf("无内容可删除！\n");
                                            else {
                                            strcpy(zhonglei[fenglei][weizhi],cmp);
                                            printf("删除成功！\n");
                                            }
                                    }
                            }//种类处理完毕
             if (shuru2==2) {   printf("请问需要什么操作？录入1 修改2 删除3\n");
                                scanf("%d",&shuru3);
                                if (shuru3==1){
                                     printf("请输入录入的内容逗号分隔\n");
                                      scanf("%s",shuru4);
                                        int i=2; int j;
                                        xinxishu++;
                                        while (shuru4[i]!=',')
                                        {xinximing[xinxishu][i-2]=shuru4[i];
                                            i++;
                                        }
                                        i++;
                                        j=i;
                                        while (shuru4[i]!=',')
                                        {xinxifenglei[i-j]=shuru4[i];
                                            i++;
                                        }
                                        i++;
                                        j=i;
                                        xinxifengleishu[xinxishu]=atoi(xinxifenglei);
                                        while (i<strlen(shuru4))
                                        {xinxichengfen[xinxishu][i-j]=shuru4[i];
                                            i++;
                                        }
                                        printf("录入成功！\n");
                                        }//基本信息录入完成
                             if (shuru3==2){
                                 printf("请输入想要修改的蔬菜编号、想要修改的信息位置编号2～4\n");
                                 scanf("%d%d",&bianhao,&weizhi);
                                 if (bianhao>xinxishu) printf("不存在蔬菜！\n");
                                 else{
                                 if (weizhi==3) {printf("请输入想要修改的数据\n");
                                                scanf("%d",&fenglei);
                                                xinxifengleishu[bianhao]=fenglei;
                                                }
                                 else   {printf("请输入想要修改的内容\n");
                                        scanf("%s",shuru4);
                                     if (weizhi==2) strcpy(xinximing[bianhao],shuru4);
                                            else strcpy(xinxichengfen[bianhao],shuru4);
                                        }
                                 printf("修改成功！\n");
                                 }
                                }//基本信息修改结束
                            if (shuru3==3){
                                        printf("请输入想要删除的蔬菜编号\n");
                                        scanf("%d",&bianhao);
                                int i;
                                for(i=bianhao;i<xinxishu;i++)
                                        {strcpy(xinximing[i],xinximing[i+1]);
                                            xinxifengleishu[i]=xinxifengleishu[i+1];
                                          strcpy(xinxichengfen[i],xinxichengfen[i+1]);
                                        };//后面的元素需要顺延填补空缺
                                        xinxifengleishu[xinxishu]=0;
                                        strcpy(xinximing[xinxishu],cmp);
                                        strcpy(xinxichengfen[xinxishu],cmp);
                                         xinxishu--;
                                         printf("删除成功！\n");
                                        }//x基本信息删除结束
                            }//基本信息处理结束
                if (shuru2==3) {   printf("请问需要什么操作？录入1 修改2 删除3\n");
                                               scanf("%d",&shuru3);
                                    if (shuru3==1){
                                                printf("请输入5个信息\n");
                                                zhongzhixinxishu++;
                                                 scanf("%d%d%d%d%d",&zhongzhixinxi[zhongzhixinxishu][1],&zhongzhixinxi[zhongzhixinxishu][2],&zhongzhixinxi[zhongzhixinxishu][3],&zhongzhixinxi[zhongzhixinxishu][4],&zhongzhixinxi[zhongzhixinxishu][5]);
                                                    printf("录入成功！\n");
                                                }
                    if (shuru3==2){printf("请输入想修改的数据编号、数据位置、数据\n");
                                    scanf("%d%d%d",&bianhao,&weizhi,&shuru5);
                                    zhongzhixinxi[bianhao][weizhi]=shuru5;
                                    printf("修改成功！\n");
                                                }
                    if (shuru3==3){ printf("请输入想要删除的信息编号\n");
                                    scanf("%d",&bianhao);
                                    int i,j;
                                
                                    for(i=bianhao;i<zhongzhixinxishu;i++)
                                        for (j=2;j<=5;j++)
                                            zhongzhixinxi[i][j]=zhongzhixinxi[i+1][j];
                                     for (j=1;j<=5;j++)
                                            zhongzhixinxi[zhongzhixinxishu][j]=0;
                                    zhongzhixinxishu--;
                                    printf("删除成功！\n");
                                }
                                }//种植信息处理完成
        };
        if (shuru1==3) {//查找数据功能
                        printf("请问想对哪个文件处理？种类信息表按1 基本信息表按2 种植信息表按3\n");
                        scanf("%d",&shuru2);
                        if (shuru2==1) {printf("请输入分类编码\n");
                                        scanf("%d",&shuru3);
                                        printf("%s的蔬菜有：\n",zhonglei[shuru3][0]);
                                        for (i=1;i<zhongleishu[shuru3];i++)
                                            printf("%s、",zhonglei[shuru3][i]);
                                        printf("%s\n",zhonglei[shuru3][i]);
                                        }//种类信息查询结束
                        if (shuru2==2) {printf("请输入查找模式1或2\n");
                                        scanf("%d",&shuru3);
                                                        if (shuru3==1){printf("请输入查询的名称内容\n");
                                                        scanf("%s",shuru4);
                                                        int pd=0;
                                                        for (i=1;i<=xinxishu;i++)
                                                            {
                                                            if (strstr(xinximing[i],shuru4)!=NULL)
                                                                {shuchujiben(i); pd=1;}
                                                            
                                                            }
                                                        if (!pd)printf("未找到蔬菜\n");
                                                        }
                                                        if (shuru3==2){printf("请输入查询的成分内容和分类码\n");
                                                            scanf("%s\n%d",shuru4,&fenglei);
                                                            int pd=0;
                                                            for (i=1;i<=xinxishu;i++)
                                                                {
                                                                if ((strstr(xinxichengfen[i],shuru4)!=NULL)&&(xinxifengleishu[i]==fenglei))
                                                                    {shuchujiben(i); pd=1;}
                                                                }
                                                            if (!pd)printf("未找到蔬菜\n");
                                                        }
                                                }//基本信息查询结束
                if (shuru2==3) {
                                            printf("请输入查找模式1或2\n");
                                            scanf("%d",&shuru3);
                                            if (shuru3==1){printf("请输入查询的名称内容和年份\n");
                                                            scanf("%s\n%d",shuru4,&shuru5);
                                                            int pd=0; //判断是否找到蔬菜
                                                            for (i=1;i<=zhongzhixinxishu;i++)
                                                                {
                                                                if ((strstr(xinximing[zhongzhixinxi[i][2]],shuru4)!=NULL)&&(zhongzhixinxi[i][5]==shuru5))
                                                                    {shuchujiben(zhongzhixinxi[i][2]); pd=1;}
                                                                }
                                                            if (!pd)printf("未找到蔬菜\n");
                                                            }
                                            if (shuru3==2){printf("请输入查询的名称内容\n");
                                                            scanf("%s",shuru4);
                                                            int pd=0;
                                                            for (i=1;i<=zhongzhixinxishu;i++)
                                                                {
                                                                if (strstr(xinximing[zhongzhixinxi[i][2]],shuru4)!=NULL)
                                                                {printf("%d年%s的种植重量为%d\n",zhongzhixinxi[i][5],xinximing[zhongzhixinxi[i][2]],zhongzhixinxi[i][4]);pd=1;}
                                                                
                                                                }
                                                            if (!pd)printf("未找到蔬菜\n");
                                                            }
                        }//种植信息查询结束
                                            
            };
         if (shuru1==4) {printf("请输入需要统计的模式1～5\n");
                        scanf("%d",&shuru2);
                        if (shuru2==1) tongji1();
                        if (shuru2==2) tongji2();
                        if (shuru2==3) tongji3();
                        if (shuru2==4) tongji4();
                        if (shuru2==5) tongji5();
        };
         if (shuru1==5) {printf("基础数据导入按1\n");
                        printf("基础数据导出按2\n");
                        printf("年份各类蔬菜信息统计表导出按3\n");
                        printf("蔬菜名称统计信息表导出按4\n");
                        printf("自由查询统计信息表导出按5\n");
                        scanf("%d",&shuru2);
                         if (shuru2==1){
                                    zairu();  printf("导入成功!");
                         }
                        if (shuru2==2){
                                    baocun();  printf("导出成功!");
                                                }
                        if (shuru2==3){
                                    daochu3();  printf("导出成功!");
                                    }
                        if (shuru2==4){
                                    daochu4();  printf("导出成功!");
                                                           }
                        if (shuru2==5){
                                    daochu5();  printf("导出成功!");
                                                           }
        };
        printf("\n");
         printf("按任意键继续，ctrl+d退出。\n");
        getchar();
          if (baocunflag%2==0) baocun();
    }
    while (getchar()!=EOF);
   
   
}
