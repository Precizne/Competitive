#include <bits/stdc++.h>

using namespace std;

// Smallest Prime Factor

const int MAXN = 1e6 + 1;
vector<int> spf(MAXN + 1);
// vector<int> pri;
void sieve() {
   for(int i = 0; i <= MAXN; i++) {
      spf[i] = i;
   }
   for(int i = 2; i <= MAXN; i++) {
   if(spf[i] == i) {
         // pri.push_back(i);
         for(int j = 2 * i; j <= MAXN; j += i) {
            spf[j] = min(spf[j], i);
         }
      }
   }
}

// Prime Factorization

vector<int> fvec(int x) {
   vector<int> f;
   while(x != 1) {
      f.push_back(spf[x]);
      x /= spf[x];
   }
   return f;
}

map<int, int> fmap(int x) {
   map<int, int> f;
   while(x != 1) {
      f[spf[x]]++;
      x /= spf[x];
   }
   return f;
}

// String Tokenizer

vector<string> tokenize(string s, string del = " ") {
   int start, end = -1 * del.size();
   vector<string> strv;
   do {
      start = end + del.size();
      end = s.find(del, start);
      strv.push_back(s.substr(start, end - start));
   } 
   while (end != -1);
   return strv;
}

// Modulus Functions

// Extended Euclidean GCD

int gcdext(int a, int b, int* p, int* q) {
   if(a == 0) {
      *p = 0;
      *q = 1;
      return b;
   }
   int c, d;
   int g = gcdext(b % a, a, &c, &d);
   *p = d - (b / a) * c;
   *q = c;
   return g;
}

// Modulus Addition

int modsum(int a, int b, int m) {
   int c = ((a % m) + (b % m)) % m;
   c = (c < 0) ? (m + c) : c;
   return c;
}

// Modulus Multiplication

int modpro(int a, int b, int m) {
   int c = ((a % m) * (b % m)) % m;
   c = (c < 0) ? (m + c) : c;
   return c;
}

// Modulus Exponentiation

int modexp(int a, int b, int m) {
   int c;
   if(a == 0) {
      return 0;
   }
   if(b == 0) {
      return 1;
   }
   if(b % 2 == 0) {
      c = modexp(a, b / 2, m);
      c = modpro(c, c, m);
   }
   else {
      c = modexp(a, b - 1, m);
      c = modpro(a, c, m);
   }
   c = (c < 0) ? (m + c) : c;
   return c;
}

// Modulus Inverse

int modinv(int a, int m) {
   int c, d;
   int g = gcdext(a, m, &c, &d);
   if(g != 1) {
      cerr << "ERROR: GCD DOESN'T EXIST!!! VERIFY CODE!!!" << endl;
      return 0;
   }
   c = (c < 0) ? (m + c) : c;
   return c;
}

// Manacher Algorithm

vector<int> manacher_odd(string s) {
   int n = s.size();
   s = "$" + s + "^";
   vector<int> p(n + 2);
   int l = 1, r = 1;
   for(int i = 1; i <= n; i++) {
      p[i] = max(0, min(r - i, p[l + (r - i)]));
      while(s[i - p[i]] == s[i + p[i]]) {
         p[i]++;
      }
      if(i + p[i] > r) {
         l = i - p[i];
         r = i + p[i];
      }
   }
   return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
   string t;
   for(auto c: s) {
      t += string("#") + c;
   }
   auto res = manacher_odd(t + "#");
   return vector<int>(begin(res) + 1, end(res) - 1);
}

// n - Dimension Vector

template<class... Args>
auto vec(size_t n, Args&&... args) {
   if constexpr(sizeof...(args) == 1)
	   return vector(n, args...);
   else
	   return vector(n, vec(args...));
}
