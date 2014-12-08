#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <utility>
#include <sstream>
using namespace std;

#define A first
#define B second
#define MP make_pair
#define PB push_back
#define TOED bad

#define FOR(i, a, b) for (int i = a; i < b; i++)
#define MEM(p, v) memset(p, v, sizeof(p))
#define SCD(i) scanf("%d", &(i))

typedef long long LL;
typedef pair <int, int> PII;

const int MOD = 1e9 + 7;
const int MAXN = 5e3 + 5;

LL ways[MAXN][MAXN];

int main(void) {
	int n, a, b, k;
	cin >> n >> a >> b >> k;
	ways[a][0] = 1;

	for (int i = 1; i <= k; i++) {
		LL sum[MAXN];
		sum[0] = 0;
		for (int j = 1; j <= n; j++) sum[j] = (sum[j - 1] + ways[j][i - 1]) % MOD;
	
		for (int j = 1; j <= n; j++) {
			if (j == b) continue;
			
			int x, y;
			if (j > b) {
				x = (j + b)/2 + 1;
				y = n;
			} else {
				x = 1;
				y = (j + b - 1)/2;
			}
			ways[j][i] = sum[y] - sum[x - 1];
			if (x <= j && j <= y) ways[j][i] -= ways[j][i - 1];
			ways[j][i] %= MOD;
			if (ways[j][i] < 0) ways[j][i] += MOD;
		}
	}

	LL totes = 0;
	for (int i = 1; i <= n; i++) {
		//cout << ways[i][k] << ' ';
		totes = (totes + ways[i][k]) % MOD;
	}
	cout << totes << '\n';
	return 0;
}
