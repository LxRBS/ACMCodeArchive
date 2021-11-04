/**
  ������ǰ���е�ʱ�䣬����һ�����д�ʱ��ʱ��
  ���磺London 12:00AM��Moscow��3:00AM����֪Moscow�Ƕ�����
  ��ÿһ��������ֿ�д����Ҫ�ϲ��ж�ѡ������������׳���
  ����ʱ��һ��Ҫ����
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

        if(newHour>24){//����
            day = 2;
            newHour -= 24;
            if(newHour>12){//��������
                *mm = 'P';
                newHour -= 12;
            }else if(12==newHour){//��������
                *mm = 'P';
            }else{//��������
                *mm = 'A';
            }
        }else if(24==newHour){//ǡ�������
            newHour = 12;
            *mm = 'A';
            day = 2;
        }else if(newHour>12){//��������
            newHour -= 12;
            *mm = 'P';
            day = 1;
        }else if(12==newHour){//ǡ��������
            *mm = 'P';
            day = 1;
        }else if(newHour>0){//��������
            *mm = 'A';
            day = 1;
        }else if(0==newHour){//���
            newHour = 12;
            *mm = 'A';
            day = 1;
        }else if(newHour<0){//����
            day = 0;
            newHour += 24;

            if(newHour>12){//��������
                *mm = 'P';
                newHour -= 12;
            }else if(12==newHour){//��������
                *mm = 'P';
            }else{//��������
                *mm = 'A';
            }
        }

        printf("Case %d: %s %d:%02d %s\n",kase,A[day],newHour,minunte,mm);
    }
    return 0;
}
