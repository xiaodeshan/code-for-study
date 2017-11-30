#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#define MAX_N 2001
#define inf 0x7c7c7c7c
using namespace std;

int n,k;
int wantK;
int* data;
int dp[MAX_N][MAX_N];

int getVal(int x, int y){
   return (x - y) * (x - y);
}

int main()
{


    while(cin >> n >> k){
        wantK = 2 * k;
        data = new int[n];
        for(int i = 0; i < n; i++)
            cin >> data[i];
        sort(data, data + n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j <= wantK; j++){
                dp[i][j] = inf;
            }
        // dp[0][x] =
        for(int i = 0; i < n; i++)
            dp[i][0] = 0;
        dp[1][2] = getVal(data[0], data[1]);

        for(int i = 2; i < n; i++){
            for(int j = 0; j <= wantK && j <= i + 1; j++){
                if(j >= 2)
                    dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + getVal(data[i], data[i - 1]));
                dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                dp[i][j] = min(dp[i][j], dp[i - 2][j]);

                //for(int k = i - 2; k >= 0 && k >= j - 2 && j >= 2; k--){
                //    if(k >= 1)
                //        dp[i][j] = min(dp[i][j], dp[k - 1][j - 2] + getVal(data[k], data[i]));
                //    else if(j == 2)
                //        dp[i][j] = min(dp[i][j], getVal(data[k], data[i]));
                //}
            }
        }

        //for(int i = 0; i < n; i++)
        //    for(int j = 0; j <= wantK; j++)
        //        cout << "i " << i << " j:" << j << " dp " << dp[i][j] << endl;

        cout << dp[n - 1][wantK] << endl;
    }
    return 0;
}


