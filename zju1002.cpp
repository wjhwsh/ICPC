/*
ZJU online just problem 1002: Fire Net
http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1002
*/
#include <iostream>
#include <math.h>

using namespace std;
int convert(char s[], int n)
{
  int result = 0;
  for (int i = 0; i < n; i++) {
    result = (result << 1);
    if(s[i]=='X') result = (result | 1);
  }
  return result;
}

bool isValid(int map[], int result[], int row, int len,  int candidate) {
  
  //check row
  unsigned int mask = 1;
  bool last = false;
  if (map[row] & candidate) {
    return false;
  }
  
  for(int i = 0; i < len ; i++) {
    if((mask & candidate) != 0 ){
      if(last) return false;
      last = true;
    }
    if(((mask & map[row]) !=0) && last) last = false;
    mask = (mask << 1);
  }
  
  return true;
}

bool isVerticalValid(int map[], int result[], int len) {
  unsigned int mask = 1;
  bool last = false;
  int candidate = 0;
  for(int i = 0; i < len ; i++) {
    last = false;
    for (int j = 0; j < len; j++) {
      candidate = result[j];
      if((mask & candidate) != 0 ){
        if(last) return false;
        last = true;
      }
      if(((mask & map[j]) !=0) && last) last = false;
    }
    mask = (mask << 1);
  }
  return true;
}



void process(int map[], int result[], int row, int len, int& maxCount) {
  if(row == len) {
    int ccount = 0;
    if (!isVerticalValid(map, result, len)) {
      return;
    }
    for( int i = 0; i < row; i++) {
      unsigned int mask = 1;
      for(int j = 0; j < row; j++)
      {
        if(mask & result[i]) ccount++;
        mask = (mask << 1);
      }
    }
    maxCount = (maxCount > ccount)? maxCount : ccount;
    return;
  }
  for( int i = 0; i < pow(2, len) ; i++) {
    if(isValid(map, result, row, len, i)) {
      result[row] = i;
      process(map, result, row + 1, len, maxCount);
    }
  }
}

int main()
{
  int n;
  int map[4], result[4], maxCount = 0;
  while(cin >> n, n) {
    if (n ==0 || n > 4) return 0;
    for (int i = 0; i < n; i++)
    {
      char s[10];
      cin >> s;
      map[i] = convert(s, n);
    }
    maxCount = 0;
    process(map, result, 0, n, maxCount);
    cout << maxCount << endl;
  }
}
