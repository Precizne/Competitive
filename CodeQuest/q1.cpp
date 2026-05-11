#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include<map>
using namespace std;
void solve()
{
    len:
    cout<<"\n>> Enter the length of string (1 <= N <= 1e5) : ";
    string n_s,k_s;
    cin>>n_s;
    int n,k;
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
        cout<<"\n[Error] : Enter length of string within bounds.\n\n";
        goto len;
    }
    cout<<endl;
    str:
    cout<<">> Enter the string : ";
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++)
    {
        if(!('a'<=s[i] && s[i]<='z'))
        {
            cout<<"\n[Error] : string should contain lower-case latin letters only.\n\n";
            goto str;
        }
    }
    if(s.size()!=n)
    {
        cout<<"\n[Error] : Your string size is not equal to the length of the string you entered :( \n\n";
        cout<<">> If you want to go back to enter N , Press 1 else press anything to re-enter the string : ";
        string q;
        cin>>q;
        cout<<endl<<endl;
        if(q=="1")
            goto len;
        else
            goto str; 
    }
    cout<<endl;
    integer:
    cout<<">> Enter the integer (1 <= K <= N) : ";
    cin>>k_s;
    try
    {
        k = stoi(k_s);
    }
    catch(exception e)
    {
        cout<<"\n[Error] : K should be an integer.\n\n";
        goto integer;
    }
    if(k<=0 || k>n)
    {
        cout<<"\n[Error] : The integer should be between 1 and N (inclusive).\n\n";
        goto integer;
    }
    cout<<endl;
    map<char,int>m;
    for(int i=0;i<n;i++)
    {
        m[s[i]]++;
    }
    cout<<">> Jury answer : ";
    for(auto i : m)
    {
        if(i.second>=k)
        {
            cout<<"YES\n\n";
            cout<<"===============================================================================================\n\n";
            return;
        }
    }

    cout<<"NO\n\n";
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
    // Given a string S, find if this string contains atleast K occurences of same character.  
    while(true)
    {
        printf( "\033[2J"       // clear the screen
            "\033[1;1H" );  // move cursor home
        init();
        solve();
        clrsrc();
    }
}