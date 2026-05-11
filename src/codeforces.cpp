#include<bits/stdc++.h>
using namespace std;
#define int long long
#define float long double
#define Aniket  ios_base::sync_with_stdio(false); cin.tie(0);
#define G 1000000000000000000
#define g 1000000000
#define ff first
#define ss second
#define endl "\n"
#define mod 1000000007
#define MOD 998244353
#define mk make_pair
#define ppair(_) if(DEBUG) cout<<"("<<_.ff<<","<<_.ss<<") ";
#define inp(_) for(auto &__ : _) cin>>__;
#define pv(_) if(DEBUG) {for(auto &__ : _) cout<<__<<" ";cout<<endl;}
#define ppv(_) if(DEBUG) {for(auto &__ : _) ppair(__);cout<<endl;}

// =============================================================================

const int N = 2e5 + 10;
const bool DEBUG = false;

void boom() 
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n),pres(n);
    inp(a);
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++)
    {
        if(i>=1)
        pres[i] += pres[i-1] + a[i];
        else
            pres[i]=a[i];
    }
    vector<int>pre(n);
    for(int i=0;i<n;i++)
    {
        if(i-k-1 >=0)
            pre[i] += pre[i-k-1] + a[i];
        else
            pre[i] = a[i];
    }
    // pv(pre);
    for(int i=0;i<n;i++)
    {
        if(i-k >=0)
        {
            cout<<pres[i] - pre[i-k]<<" ";
        }
        else
        {
            cout<<pres[i]<<" ";
        }
    }
    cout<<endl;
}  

// =============================================================================

int32_t main()
{
    Aniket
    int tnt = 1;
    cin >> tnt;
    for (int i = 1; i <= tnt; i++)
    {
        if (DEBUG)
            cout << "TEST CASE #" << i << endl;
        boom();
    }
}