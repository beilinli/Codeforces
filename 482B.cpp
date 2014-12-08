#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

const int MAXN = 1e5 + 5;
const int MAXB = 30;

int ls[MAXN], rs[MAXN], qs[MAXN], out[MAXN];
int res[MAXN];

int main(void) {
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);

	vector <pair <int, int> > intv[MAXN];

	for (int i = 0; i < m; i++) {
		scanf("%d", &ls[i]);
		scanf("%d", &rs[i]);
		scanf("%d", &qs[i]);

		for (int j = 0; j < MAXB; j++) {
			if (qs[i] & (1 << j))
				intv[j].push_back(make_pair(ls[i], rs[i]));
		}
	}

	for (int j = 0; j < MAXB; j++) {
		int sz = intv[j].size();
		if (sz == 0) continue;

		sort(intv[j].begin(), intv[j].end());

		vector <pair <int, int> > v;
		pair <int, int> prev = intv[j][0];
		for (int i = 1; i < sz; i++) {
			if (prev.second >= intv[j][i].first)
				prev = make_pair(prev.first, max(prev.second, intv[j][i].second));
			else {
				v.push_back(prev);
				prev.first = intv[j][i].first;
				prev.second = intv[j][i].second;
			}
		} v.push_back(prev);

		memset(res, 0, sizeof(res));
		for (int i = 0; i < v.size(); i++) {
			for (int k = v[i].first; k <= v[i].second; k++)
				res[k] = 1;
		}

		for (int i = 1; i <= n; i++)
			res[i] += res[i - 1];

		for (int i = 0; i < m; i++) {
			if (qs[i] & (1 << j)) continue;

			int diff = rs[i] - ls[i] + 1;
			if (res[rs[i]] - res[ls[i] - 1] == diff) {
				cout << "NO\n";
				return 0;
			}
		}

		for (int i = 1; i <= n; i++) {
			int r = res[i] - res[i - 1];
			out[i] |= (r << j);
		}
	}

	cout << "YES\n";
	for (int i = 1; i <= n; i++) printf("%d ", out[i]);
	printf("\n");
	
	return 0;
}
