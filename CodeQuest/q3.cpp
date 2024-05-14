#include<iostream>
#include<vector>
#include<string>
#include <algorithm>
#include<map>
using namespace std;
int linear_search(vector<string>&a,string &s)
{
    for(int i=0;i<a.size();i++)
    {
        if(a[i]==s)
        {
            return  i;
        }
    }
    return -1;
}
void solve()
{
    cout<<">> Alice,Bob playing cards\n\n";
    vector<string>num ={"king","queen","jack","ace","2","3","4","5","6","7","8","9","10"};
    vector<string>col ={"club","diamond","heart","spade"};

    alice:
    cout<<">> Enter Alice\'s card : ";
    string a_n,a_c;
    cin>>a_n>>a_c;
    transform(a_n.begin(), a_n.end(), a_n.begin(), ::tolower); 
    transform(a_c.begin(), a_c.end(), a_c.begin(), ::tolower); 

    int x_a = linear_search(num,a_n);
    int y_a = linear_search(col,a_c);

    if(x_a==-1 || y_a==-1)
    {
        cout<<"[Error] : Enter Valid Card.\n\n";
        goto alice;
    }
    cout<<endl;

    bob:
    cout<<">> Enter Bob\'s card : ";
    string b_n,b_c;
    cin>>b_n>>b_c;
    cout<<endl;
    transform(b_n.begin(), b_n.end(), b_n.begin(), ::tolower); 
    transform(b_c.begin(), b_c.end(), b_c.begin(), ::tolower); 
    
    int x_b = linear_search(num,b_n);
    int y_b = linear_search(col,b_c);

    if(x_b==-1 || y_b==-1)
    {
        cout<<"[Error] : Enter Valid Card.\n\n";
        goto bob;
    }

    cout<<">> Jury answer : ";
    if(x_a < x_b)
    {
        cout<<"Alice\n\n";
    }
    else if(x_a > x_b)
    {
        cout<<"Bob\n\n";
    }
    else
    {
        if(y_a < y_b)
        {
            cout<<"Alice\n\n";
        }
        else if(y_a > y_b)
        {
            cout<<"Bob\n\n";
        }
        else
        {
            cout<<"Draw\n\n";
        }
    }
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
    // playing cards ...lexographical order. 
    while(true)
    {
        printf( "\033[2J"       // clear the screen
        "\033[1;1H" );  // move cursor home
        init();
        solve();
        clrsrc();
    }
}
