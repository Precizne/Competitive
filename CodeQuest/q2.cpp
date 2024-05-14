#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include<map>
using namespace std;
int mex(vector<int> &arr, int N)
{
    sort(arr.begin(), arr.end());
    int mex = 0;
    for (int idx = 0; idx < N; idx++)
    {
        if (arr[idx] == mex)
        {
            mex += 1;
        }
    }
    return mex;
}
 
void solve()
{
    len:
    cout<<"\n>> Enter the length of array (1 <= N <= 1e5) : ";
    string n_s;
    int n;
    cin>>n_s;
    try
    {
        n = stoi(n_s);
    }
    catch(exception e)
    {
        cout<<"\n[Error] : N should be an integer.\n\n";
        goto len;
    }
    if(n<=0 || n>100000)
    {
        cout<<"\n[Error] : Enter length of array within bounds.\n\n";
        goto len;
    }
    cout<<endl;
    arr:
    cout<<">> Enter N integers of an array (0 <= A[i] < N) : ";
    vector<int>a(n);
    for(int i=0;i<n;i++)
    {
        string a_s;
        cin>>a_s;
        try
        {
            a[i] = stoi(a_s);
        }
        catch(exception e)
        {
            cout<<"\n[Error] : A["<<i<<"] should be an integer.\n\n";
            goto arr;
        }
        if(a[i]<0 || a[i]>=n)
        {
            cout<<"\n[Error] : Enter A["<<i<<"] within bounds.\n\n";
            goto arr;
        }
    }
    cout<<endl;
    cout<<">> Jury answer : "<<mex(a,n)<<endl<<endl;
    cout<<"===============================================================================================\n\n";

}

void init()
{
    cout<<"________          __                 __       _____  .__         .__                          \n";
    cout<<"\\_____  \\  __ ___/  |_______  __ ___/  |_    /  _  \\ |  |   ____ |  |__   ____   _____ ___.__.\n";
    cout<<" /   |   \\|  |  \\   __\\____ \\|  |  \\   __\\  /  /_\\  \\|  | _/ ___\\|  |  \\_/ __ \\ /     <   |  |\n";
    cout<<"/    |    \\  |  /|  | |  |_> >  |  /|  |   /    |    \\  |_\\  \\___|   Y  \\  ___/|  Y Y  \\___  |\n";
    cout<<"\\_______  /____/ |__| |   __/|____/ |__|   \\____|__  /____/\\___  >___|  /\\___  >__|_|  / ____|\n";
    cout<<"        \\/            |__|                         \\/          \\/     \\/     \\/      \\/\\/     \n";
    cout<<"===============================================================================================\n\n";
    cout<<"================Instructions================\n\n";
    cout<<">> You have to enter the input based on given constraints,mentioned on the prompt.\n\n";
    cout<<">> Based on output provided,you have to guess the source code and sumbit it on codeforces\n\n";
    cout<<">> To exit,press (CTRL+C)\n\n\n";
    cout<<"===============================================================================================\n\n";

}
void clrsrc()
{
    cout<<"\nPress [Enter] to continue...";
    cin.ignore();
    getchar();
}

int main()
{
    // find mex of the array 
    while(true)
    {
        
        printf( "\033[2J"       // clear the screen
            "\033[1;1H" );  // move cursor home
        init();
        solve();
        clrsrc();
    }
}