#include "bits/stdc++.h" 

#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define reprate(i, a, b, c) for (int i = (a); i < (b); i += (c))

using namespace std;

const int SZ = 2e5 + 5, ROOTSZ = 635;
 
int a[SZ], b[SZ], d[4], c[SZ];

int freq[ROOTSZ][SZ];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	int tc; cin >> tc;
	while(tc--) {
		int n; cin >> n;

		long long s = sqrt(2*n);

		rep(i, 0, n) {
			cin >> a[i];
		}

		rep(i, 0, n) {
			cin >> b[i];
			if (a[i] <= s) freq[a[i]][b[i]]++;
			c[i] = a[i] * a[i] - b[i];
		}

		long long ans = 0;
		rep(i, 0, n) {
			if (a[i] <= s) {
				if (1 <= c[i] && c[i] <= n) {
					ans += freq[a[i]][c[i]];
				}
			}
		}

		reprate(i, 2, s + 1, 2) {
			ans -= freq[i][i*i/2];
		}
		ans /= 2;

		rep(i, 0, n) {
			for(int j = 1; j <= s && j < a[i] && j*a[i] <= 2*n; j++) {
				if (j * a[i]-b[i] >= 1 && j * a[i] - b[i] <= n) {
					ans += freq[j][j*a[i]-b[i]];
				}
			}
		}
		
		rep(i, 0, n) {
			if (a[i] <= s) {
				freq[a[i]][b[i]] = 0;
			}
		}
		cout << ans << '\n';
	}
}
