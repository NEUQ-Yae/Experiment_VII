#include <iostream>
#include <fstream>
#include <iomanip>
#define FORMAT setw(2)<<setfill('0')
using namespace std;

class Date; //对Date类的提前引用声明
class Time {
public:
    Time(int,int,int);
    void add_a_second(Date &);  //增加1秒，1秒后可能会到了下一天，乃到下一月、下一年
    friend ostream& operator<<(ostream&, Time&); //输出格式：hour:minute:second
    friend void writeToFile(Time&, Date&);
private:
    int hour;
    int minute;
    int sec;
};

class Date {
public:
    Date(int,int,int);
    friend void Time::add_a_second(Date &);
    friend ostream& operator<<(ostream&, Date&); //输出格式：year年month月day日
    friend void writeToFile(Time&, Date&);
private:
    int month;
    int day;
    int year;
};

/********************补充代码实现题目要求*****************/
void Time::add_a_second(Date &dt)
{
    int days(int m, int y);
    sec += 1;
    if (sec >= 60) {
        sec = 0;
        minute += 1;
        if (minute >= 60) {
            minute = 0;
            hour += 1;
            if (hour >= 24) {
                hour = 0;
                dt.day += 1;
                if (dt.day >= days(dt.month, dt.year)) {
                    dt.day = 1;
                    dt.month += 1;
                    if (dt.month >= 12) {
                        dt.month = 1;
                        dt.year += 1;
                    }
                }
            }
        }
    }

}
Time::Time(int h, int m, int s){
    hour = h;
    minute = m;
    sec = s;
}
Date::Date(int m, int d, int y){
    month = m;
    day = d;
    year = y;
}
ostream& operator << (ostream& output, Date& dt)
{
    output << dt.year << "年" << dt.month << "月" << dt.day << "日";
    return output;
}
ostream& operator << (ostream& output, Time& tm)
{
    output << endl << tm.hour << ":" << tm.minute << ":" << tm.sec;
    return output;
}



/*************************************************************/

int days(int m, int y) { //days函数返回第y年第m月的天数
    int d[]={0,31,28,31,30,31,30,31,31,30,31,30,31}; //数组下标从0开始，而月份从1开始，所以给定d[0]=0
    if((y%100==0&&y%4!=0)||(y%400==0)) d[2]=29; //如果是闰年，则二月份是29天
    return d[m];
}

void writeToFile(Time& t, Date& d) {
    ofstream outFile("res.txt");
    outFile<<d.year<<"年"<<d.month<<"月"<<d.day<<"日"<<" "<<FORMAT<<t.hour<<":"<<FORMAT<<t.minute<<":"<<FORMAT<<t.sec<<endl;
    outFile.close();
}

int main() {
    Time tm(23,59,59);
    Date dt(12,31,2020);

    tm.add_a_second(dt);
    cout<<dt<<tm;   //屏幕上的输出是：2021年1月1日(换行)0:0:0
    writeToFile(tm, dt);    //文件中的输出是：2021年1月1日(空格)00:00:00
    int pause;
    cin >> pause;
    return 0;
}
