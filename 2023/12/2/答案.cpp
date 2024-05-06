#include <iostream>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <set>
 
using namespace std;
 
typedef long long LL;
int longtp[10002];
int arr[27] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,93,97,101};
 
multiset<int> divide(LL source)
{
    multiset<int> son;
    for(int j = 2; j < 10001;)
    {
        if(source < 10000)
        {
            son.insert(source);
            break;
        }
 
        if(source % j == 0)
        {
            source = source / j;
            son.insert(j);
            continue;
        }
        j++;
    }
    return son;
}
 
void cal(int num)
{
    for(int j = 0; j < 27;)
    {
        if(num == 1)
            break;
        if(num % (arr[j]) == 0)
        {
            num = num / arr[j];
            longtp[arr[j]]++;
            continue;
        }						//这里不需要判断指数是否大于阈值
        j++;
        if(j == 27)
            longtp[num]++;		//最后剩下的大于100的质数不能扔
    }
}
 
int main()
{
    int q, k;
    LL n, output;
    int temp[102];
    cin >> q;
 
    for(int i = 0; i < q; i++)
    {
        output = 1;
        cin >> n >> k;
 
        if(n > 10000)
        {
            multiset<int> division; 				//分离后的因式
            division = divide(n);
            memset(longtp, 0, sizeof(int)*10002);	//每次都要初始化所有指数为0
 
            for(auto it = division.begin(); it != division.end(); it++)
                cal(*it);							//计算所有因式
 
            for(int j = 2; j < 10001; j++)			//统一判断阈值
                if(longtp[j] >= k)
                    output *= pow(j, longtp[j]);
        }
        else
        {
            memset(temp, 0, sizeof(int)*102);
            for(int j = 0; j < 27; )
            {
                if(n % (arr[j]) == 0)
                {
                    n = n / arr[j];
                    temp[arr[j]]++;
                    continue;
                }
                if(temp[arr[j]] >= k)
                    output *= pow(arr[j], temp[arr[j]]);
                if(n == 1)
                    break;
                j++;
            }
        }
        cout << output << endl;
    }
    return 0;
}