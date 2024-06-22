#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
 
#define Precizne cin.tie(nullptr) -> sync_with_stdio(false);
#define int long long
#define uint unsigned int
#define INF(t) numeric_limits<t>::max()
#define endl "\n"
 
using namespace std;

void zero() {
   int n = 10, k = 5, v = 0;
   vector<int> a(n);
   for(auto& i : a) {
      i = k - v;
      v++;
   }
   sort(a.begin(), a.end());
   int idx = lower_bound(a.begin(), a.end(), k) - a.begin();
   if(idx == n || a[idx] != k) {
      cout << "NO" << endl;
      return;
   }
   else {
      cout << "YES" << endl;
   }
}

signed main() {
   Precizne
   
   #ifndef ONLINE_JUDGE
      auto begin = chrono::high_resolution_clock::now();
      freopen("input.txt", "r", stdin); 
      freopen("output.txt", "w", stdout);
      freopen("error.txt", "w", stderr);
   #endif
   
   int progress = 1;
   cin >> progress;
   for(int p = 1; p <= progress; p++) {
      // cout << "Case #" << p << ": " << endl;
      #ifndef ONLINE_JUDGE
         cerr << "Case #" << p << ": " << endl;
      #endif
      zero();
   }
 
   #ifndef ONLINE_JUDGE
      auto end = chrono::high_resolution_clock::now();
      auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
      cerr << fixed << "Time: " << elapsed.count() * 1e-9 << " secs" << endl;
   #endif
 
   return 0;
}
