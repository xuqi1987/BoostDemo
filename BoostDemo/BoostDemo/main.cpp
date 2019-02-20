//
//  main.cpp
//  BoostDemo
//
//  Created by xuqi on 2019/2/19.
//  Copyright © 2019 xuqi. All rights reserved.
//
#include <boost/timer.hpp>
#include <boost/progress.hpp>

#define BOOST_DATE_TIME_SOURCE
#include <boost/date_time/gregorian/gregorian.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace boost;
using namespace boost::gregorian;

#define LOG(log) cout<<log<<endl;

#define PrintWeek(l0,l1,l2,l3,l4,l5,l6) \
cout<<setiosflags(ios::left)<<setw(5) <<l0; \
cout<<setiosflags(ios::left)<<setw(5) <<l1; \
cout<<setiosflags(ios::left)<<setw(5) <<l2; \
cout<<setiosflags(ios::left)<<setw(5) <<l3; \
cout<<setiosflags(ios::left)<<setw(5) <<l4; \
cout<<setiosflags(ios::left)<<setw(5) <<l5; \
    cout<<setiosflags(ios::left)<<setw(5) <<l6 << endl

#define PrintDay(l0) cout<<setiosflags(ios::left)<<setw(4) <<l0

void dateDemo()
{
    // insert code here...
    // 使用timer显示时间

    timer t;
    LOG("max (h):" << t.elapsed_max()/3600 );
    LOG("min (s):" << t.elapsed_min());
    LOG("elapsed (ms):" << t.elapsed() *1000 );

    // 显示进度条
    vector<string> v(5, "aa");
    ofstream fs("./test.txt");
    progress_display pd(v.size());
    for (auto& x : v)
    {
        fs <<x<<endl;
        //sleep(1);
        ++pd;
    }

    // 处理日期
    date d1(2019,1,23);
    //date d2 = from_string("2002/1/25");
    //date d2(from_string("2019/01/23"));
    date d3 = from_undelimited_string("20190123");
    LOG(d3.day() << d3.month() << d3.year());
    LOG(d3);

    date d4 = day_clock::local_day();
    LOG("local_day:" << day_clock::local_day());
    LOG("universal_day:" << day_clock::universal_day());

    // 时间运算
    LOG(d3 - d4 + weeks(3));

    // 时间区间
    date_period dp1(d3,d4);
    date_period dp2(d3,days(15));

    LOG(dp1);
    LOG(dp2.last().day());

    LOG(dp2.contains(date(2019,1,26)));

    // 日期迭代
    day_iterator d_iter(d4);
    ++d_iter;
    LOG(d_iter->day());

     // 显示本月
    cout.setf(ios::left); //设置对齐方式为left
    cout.width(4); //设置宽度为7，不足用空格填充

    cout << "---------------------------------"<<endl;
    PrintWeek("日","一", "二","三","四","五","六");

    date s_d(d4.year(),d4.month(),1);
    date e_d = d4.end_of_month();

    for(day_iterator s_iter(s_d); s_iter != e_d; ++s_iter)
    {
        int i = s_iter->day_of_week();
        while(i-- && s_iter->day() == 1)
        {
            PrintDay(" ");
        }
        if (s_iter->day_of_week() == 0)
        {
            cout << endl;
        }

        PrintDay(s_iter->day());
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    

    dateDemo();
    return 0;
}
