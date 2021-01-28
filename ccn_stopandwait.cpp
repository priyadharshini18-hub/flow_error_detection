#include<iostream>
#include<ctime>
using namespace std;
int word[10];
int sender(int *w, int j)
{
    int send=rand()%2;
    if(send==0)
    {
        cout<<"Data lost while sending"<<endl;
    }
    else{
        int e=rand()%2;
        if(e==1)
        {
            cout<<"Sending Frame"<<j<<" with errors"<<endl;
            int t=*w%10;
            *w=*w/10;
            if(t==1)
            {
                *w=((*w)*10);
            }
            else
            {
                *w=((*w)*10)+1;
            }
        }
        else
        {
            cout<<"Sending Frame"<<j<<" without errors"<<endl;
        }
    }
    return send;
}
int checkParity(int data)
{
    int count1=0;
    while(data!=0)
    {
        int t=data%10;
        if(t==1)
        {
            count1++;
        }
        data=data/10;
    }
    if(count1%2==0)
    {
        return 0;
    }
    else{return 1;}

}

int receiver(int w, int j)
{
    int r=rand()%2;
    cout<<"Data Recieved: "<<w<<" "<<endl;
    int ch=checkParity(w);
    if(ch==0)
    {
        if(r==0)
        {
            cout<<"Acknowledgement Frame"<<j<<" : Parity verified"<<endl;
        }
        else{
            cout<<"Acknowledge lost"<<endl;
            cout<<"TIME OUT!!!"<<endl;
        }
    }
    else
    {
        if(r==0)
        {
            cout<<"Frame"<<j<<" : Parity failed"<<endl;
        }
        else
        {
            cout<<"Acknowledgement lost"<<endl;
            cout<<"TIME OUT!!!"<<endl;
        }
    }
    if(r==0 && ch==0)
    {
        return 1;
    }
    else{return 0;}
}
int makeEvenParity(int w)
{
    int t,t1=w,c=0;
    while(w)
    {
        t=w%10;
        if(t==1)
        {
            c++;
        }
        w=w/10;
    }
    if(c%2==0)
    {
        return(t1*10);
    }
    else{
        return((t1*10)+1);
    }
}
int main()
{

    int n;
    cout<<"Enter the number of frames ";
    cin>>n;
    //int word[n];
    cout<<"Enter the words ";
    for(int i=0;i<n;i++)
    {
        cin>>word[i];
    }
    for(int i=0;i<n;i++)
    {
        word[i]=makeEvenParity(word[i]);
        cout<<word[i]<<endl;
    }
    cout<<endl<<endl;
    int j=0;
    while(j!=n)
    {
        int w=word[j];
        int c1=sender(&w,j);
        if(c1==1)
        {
            int c2=receiver(w,j);
            if(c2==1)
            {
                j++;
                cout<<endl<<endl;
            }
        }
    }
}
