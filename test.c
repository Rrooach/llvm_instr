#include <bits/stdc++.h>

using namespace std;

int prime[100050];
bool isprime[100050];
void check(int n)
{
    int cnt = 0;
    prime[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (isprime[i])
        {
            prime[cnt++] = i;
            for (int j = i + i; j < n; j += i)
                isprime[j] = false;
        }
    }
}

int main()
{
    // caculate all the prime within 1 to n;
    int n;
    cin >> n;
    memset(isprime, true, sizeof(isprime));
    check(n);
    for (int i = 0; i < n; ++i)
        if (isprime[i])
            cout << i << ends;
        system("pause");
    return 0;
}
