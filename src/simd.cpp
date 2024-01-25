#include "bits/stdc++.h" 
#include <nmmintrin.h>
         
#pragma GCC target("avx2")

#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define reprate(i, a, b, c) for (int i = (a); i < (b); i += (c))

using namespace std;

const int SZ = 2e5 + 5, ROOTSZ = 635;
 
int a[SZ], b[SZ], d[4], c[SZ];

int freq[ROOTSZ][SZ];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	auto register_sum = [&](__m128i &a) -> int {
		a = _mm_add_epi32(a, _mm_slli_si128(a, 4));
		a = _mm_add_epi32(a, _mm_slli_si128(a, 8));
		return _mm_extract_epi32(a, 3);
	};

	int tc; cin >> tc;
	while(tc--) {
		int n; cin >> n;

		long long s = sqrt(2*n);

		rep(i, 0, n) {
			cin >> a[i];
		}

		__m128i s_cmp = _mm_set1_epi32(s + 1);
		__m128i zeros_cmp = _mm_setzero_si128();
		__m128i n_cmp = _mm_set1_epi32(n + 1);

		long long ans = 0;
		reprate(i, 0, n, 4) {
			rep(j, 0, 4) {
				if (i + j < n) cin >> b[i+j];
				else b[i+j] = 0;
				c[i+j] = a[i+j] * a[i+j] - b[i+j];
			}
			__m128i a_cur = _mm_setr_epi32(a[i], a[i+1], a[i+2], a[i+3]);
			__m128i msk = _mm_cmplt_epi32(a_cur, s_cmp);
			_mm_storeu_si128((__m128i*) d, msk);
			rep(j, 0, 4) {
				if (d[j] == -1) freq[a[i+j]][b[i+j]]++;
			}

		}

		reprate(i, 0, n, 4) {
			__m128i a_cur = _mm_setr_epi32(a[i], a[i+1], a[i+2], a[i+3]);
			__m128i c_cur = _mm_setr_epi32(c[i], c[i+1], c[i+2], c[i+3]);

			__m128i msk1 = _mm_cmplt_epi32(a_cur, s_cmp);
			__m128i msk2 = _mm_cmpgt_epi32(c_cur, zeros_cmp);
			__m128i msk3 = _mm_cmplt_epi32(c_cur, n_cmp);
			
			__m128i sum = _mm_add_epi32(msk1, msk2);
			sum = _mm_add_epi32(sum, msk3);

			_mm_storeu_si128((__m128i*) d, sum);
			rep(j, 0, 4) {
				if (i + j >= n) continue;
				// negative for some reason, cause some wrapping i think
				if (d[j] == -3) { // all three conditions are valid
					ans += freq[a[i+j]][c[i+j]];
				}
			}
		}
		reprate(i, 2, s + 1, 8) {
			__m128i freq_cur = _mm_setr_epi32(freq[i][i*i/2], freq[i+2][(i+2)*(i+2)/2], freq[i+4][(i+4)*(i+4)/2], freq[i+6][(i+6)*(i+6)/2]);
			ans -= register_sum(freq_cur);
		}

		ans /= 2;

		// orkar inte tänka på hur vvvvvvvv kan paralleliseras

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
