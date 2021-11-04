/**
  给定当前城市的时间，求另一个城市此时的时间
  例如：London 12:00AM，Moscow是3:00AM，已知Moscow是东三区
  把每一种情况都分开写，不要合并判断选项，这样更不容易出错
  特殊时刻一定要测试
*/

#include <stdio.h>
#include <string.h>

int Map[256][256];

char const A[3][100] = {
    "Yesterday",
    "Today",
    "Tomorrow"
};

int main(){
    //freopen("1.txt","r",stdin);

    Map['B']['W'] = - ( Map['W']['B'] = 13 );
    Map['B']['L'] = - ( Map['L']['B'] = 8 );
    Map['B']['M'] = - ( Map['M']['B'] = 5 );

    Map['W']['L'] = - ( Map['L']['W'] = -5 );
    Map['W']['M'] = - ( Map['M']['W'] = -8 );

    Map['L']['M'] = - ( Map['M']['L'] = -3 );

    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int hour,minunte,day = -100000000;
        char mm[11],c1[11],c2[11];

        scanf("%d:%d%s%s%s",&hour,&minunte,mm,c1,c2);

        if('P'==*mm&&12!=hour) hour += 12;
        else if('A'==*mm&&12==hour) hour = 0;

        int newHour = hour + Map[*c1][*c2];

        if(newHour>24){//明天
            day = 2;
            newHour -= 24;
            if(newHour>12){//明天下午
                *mm = 'P';
                newHour -= 12;
            }else if(12==newHour){//明天正午
                *mm = 'P';
            }else{//明天上午
                *mm = 'A';
            }
        }else if(24==newHour){//恰好是零点
            newHour = 12;
            *mm = 'A';
            day = 2;
        }else if(newHour>12){//今天下午
            newHour -= 12;
            *mm = 'P';
            day = 1;
        }else if(12==newHour){//恰好是正午
            *mm = 'P';
            day = 1;
        }else if(newHour>0){//今天上午
            *mm = 'A';
            day = 1;
        }else if(0==newHour){//零点
            newHour = 12;
            *mm = 'A';
            day = 1;
        }else if(newHour<0){//昨天
            day = 0;
            newHour += 24;

            if(newHour>12){//昨天下午
                *mm = 'P';
                newHour -= 12;
            }else if(12==newHour){//昨天正午
                *mm = 'P';
            }else{//昨天上午
                *mm = 'A';
            }
        }

        printf("Case %d: %s %d:%02d %s\n",kase,A[day],newHour,minunte,mm);
    }
    return 0;
}
