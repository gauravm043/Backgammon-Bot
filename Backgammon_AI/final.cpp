#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <utility>
#include<time.h>
#define pii pair<int, int>
#define VI vector < int >
#define PB push_back
#define FOR(i,a,b) for(i=a;i<b;i++)
#define FORD(i,a,b) for(i=a;i>b;i--)
using namespace std;
int weight[25];
int board[100]; // goes from b-12(bob home which alice 0 ) to a-12 (alice home)
int bar,bar1;
int a[15],b[15];
string ans[2];
int debug=0;
int w=0;
int dice1,dice2;
long long int bestresult=-100;
int bestboard[25];
const int sign =1;
int race=0;
int ismycheck(int i)
{
	if(sign>0 && board[i]>0 || board[i]==-1)
		return 1;
	if(sign<0 && board[i]<0 || board[i]==1)
		return 1;
	if(board[i]==0)
		return 0;
	return -1;
}
pair <int,int> move[2];
//move[0].second=-10;
//move[1].first=-10;
//move[1].second=-10;
pair <int,int> bestmove[2];
//bestmove[0].first=-10;
//bestmove[0].second=-10;
//bestmove[1].first=-10;
//bestmove[1].second=-10;
typedef long long LL;
int d[2]={0};
int hit=0;
void calculateheuritic()
{
	if(debug==1)
		cout<<24-move[0].first<<" "<<24-move[0].second<<endl;;
	if(debug==1)
		cout<<24-move[1].first<<" "<<24-move[1].second<<endl;;
	long long sum=hit*300;
	if(debug==1)
		for(int i=0;i<24;i++)
			cout<<board[i]<<" ";
	if(debug==1)
		cout<<endl;
	if(bar1==0)
	sum+=board[24]*200;
	if(debug==1)
		cout<<" 50= "<<board[24]<<endl;
//	if(move[0].first <12 && rand()%2!=1)
	{
//		sum+=50;
	}
//	if(move[1].first < 12 && rand()%2!=0)
//		sum+=50;
	//	if(hit>0)
	if(debug==1)
		cout<<"hit :"<<hit<<"\n\n";
	int i;
	if(race==1)
	{
		if(move[0].first<18 && move[0].first>=12)
			sum+=30;
		if(move[0].first<12 && move[0].first>=0)
			sum+=60;
		if(move[1].first<18 && move[1].first>=12)
			sum+=30;
		if(move[1].first<12 && move[1].first>=0)
			sum+=60;
	}
//	cout<<"inter:"<<sum<<endl;
	for(i=0;i<24;i++)
	{
		if((board[i]>0 && sign>0) || (board[i]<0 && sign<0))
			sum+=abs(board[i])*weight[i];
//		if(board[i]>=sign*2)
//				sum+=board[i]*10;
		if(board[i]>2 && i<18)
		{
			int j;
			for(j=i+1;j<i+10;j++)
			{
				if(board[j]==-1)
					sum+=30;
			}
		}
		if(board[i]==1)
		{
			int j;
			int arr[10]={10,20,25,30,35,40,30,25,20};
			for(j=i+1;j<i+8;j++)
			{
				if(board[j]<0)
					sum=sum-arr[j-i-1];
			}
		}
		if(board[i] >=2)
			sum+=20;
		if(board[i] >=2 && i>=18)
			sum+=20;
		if(board[i]==sign)
			sum-=40;
	}
	if(debug==1)
		cout<<"sum="<<sum<<endl;
	if(sum>bestresult)
	{
		bestresult=sum;
		for(i=0;i<24;i++)
		{
			bestboard[i]=board[i];
		}
		bestmove[0]=move[0];
		bestmove[1]=move[1];
	}
	return ;
}
void allcon(int depth)
{
	if(depth==2)
	{
		if(bestmove[0].first==-10)
		{
			bestmove[0]=move[0];
		}
	}
	if(debug==1)
	{
		cout<<"depth-"<<depth<<" d[0]="<<d[0] <<" d[1]="<<d[1] <<"bar="<<bar<<"   board ->\n";
		for(int i=0;i<24;i++)
			cout<<board[i]<<" ";
		cout<<endl;
	}
	if(depth>3)
		return;
	if(depth==3)
	{
		calculateheuritic();
		return;
	}
	int i;
	if(bar>0)
	{
		dice1--;
		dice2--;
		for(i=0;i<=bar;i++)
		{
			if(bar==0)
				break;
			//if(d[0]==0)
			int c=1;
			if((  ismycheck(sign*dice1 )==1 || ismycheck(sign*dice1)==0)&& d[0]==0 && board[dice2]!=-1)
			{
				if(board[i]==sign*-1)
				{
					c=1;
					hit++;
					board[i]=0;
					hit++;
					bar-=sign;
				}
				//				else
				{	board[sign*dice1]+=sign;
					move[depth-1].first=-1;
					move[depth-1].second=sign*dice1;
					bar--;
					d[0]=1;
					depth++;
					c=0;
				}
			}
			if((  ismycheck(sign*dice2 )==1 || ismycheck(sign*dice2)==0)&& d[1]==0 &&c==1)
			{
				//		cout<<"in\n"<<endl;
				if(board[i]==sign*-1)
				{
					//continue;
					board[i]=0;
					hit++;
					hit++;
					bar-=sign;
				}
				board[sign*dice2]+=sign;
				move[depth-1].first=-1;
				move[depth-1].second=sign*dice2;
				bar--;
				d[1]=1;
				depth++;
			}
		}
		dice1++;
		dice2++;
	}
//	cout<<"BAR      +++++++++++++++++ "<<bar<<endl;
	if(bar>0 && depth==1)
	{
		if(debug==1)
			cout<<"NO MOVE\n";
		return;
	}
	/*	if(bar>0 && sign>0 )
		{
		if(depth==1)
		{
		if(debug==1)
		cout<<"NO MOVE\n";
		return;
		}
		}*/
	if(depth==3)
	{	
		allcon(depth);
		return;
	}

	if(bar>0)
	{
		allcon(depth+1);
		return;
	}
	int c=0;
	for(i=0;i<24;i++)
	{
		//		cout<<"i="<<i<<" "<<sign*board[i]<<endl;
		if(board[i]*sign>0)
		{
			if(d[0]==0)
			{	
				if(i+sign*(dice1)<24)
					if(i+sign*(dice1)>=0)
					{
						if(ismycheck(i+sign*dice1)==1 || ismycheck(i+sign*dice1)==0 )
						{
							int c=0;	
							//							cout<<"move "<<i<<endl;
							if(board[i+sign*dice1]==sign*-1)
							{
								c=1;
								board[i+sign*dice1]=0;
								hit++;
								if(i+sign*dice1 < 6)
									hit+=5;
								else if(i+sign*dice1 < 12)
									hit+=2;
								bar-=sign;
								if(i+sign*dice1 >20)
									hit--;
							}
							//			board[sign*dice1]+=sign;
							board[i]-=sign;
							board[i+sign*dice1]+=sign;
							d[0]=1;
							move[depth-1].first=i;
							move[depth-1].second=i+sign*dice1;
							allcon(depth+1);
							c++;
							board[i]+=sign;
							board[i+sign*dice1]-=sign;
							if(c==1)
							{
								board[i+sign*dice1]=sign*-1;
								hit--;bar+=sign;
								if(i+sign*dice1 >20)
									hit++;
								if(i+sign*dice1 < 6)
									hit-=5;
								else if(i+sign*dice1 < 12)
									hit-=2;
							}
							d[0]=0;
						}
					}
			}
			if(d[1]==0)
			{		if(i+sign*(dice2)<24)
				if(i+sign*(dice2)>=0)
				{
					if(ismycheck(i+sign*dice2)==1 || ismycheck(i+sign*dice2)==0 )
					{	
						int c=0;
						if(board[i+sign*dice2]==sign*-1)
						{
							c=1;
							board[i+sign*dice2]=0;
							hit++;bar-=sign;
							if(i+sign*dice2 >20)
								hit--;
								if(i+sign*dice2 < 6)
									hit+=5;
								else if(i+sign*dice2 < 12)
									hit+=2;
						}
						board[i]-=sign;
						board[i+sign*dice2]+=sign;
						d[1]=1;
						move[depth-1].first=i;
						move[depth-1].second=i+sign*dice2;
						allcon(depth+1);
						c++;
						board[i]+=sign;
						board[i+sign*dice2]-=sign;
						d[1]=0;
						if(c==1)
						{
							board[i+sign*dice2]=sign*-1;
							hit--;bar+=sign;
							if(i+sign*dice2 >20)
								hit++;
								if(i+sign*dice2 < 6)
									hit-=5;
								else if(i+sign*dice2 < 12)
									hit-=2;
						}
					}
				}
			}
		}
	}
	if(c==0)
		allcon(3);
}
void homestate()
{
//	cout<<"here\n\n";
	int i,j,k,c=0;
	for(i=18;i<24;i++)
	{
		//		for(k=0;k<24;k++)
		//			cout<<board[k]<<"-";
		//		cout<<endl;
		if(board[i]>0)
		{	
			if(debug==1)
				cout<<"i="<<i<<endl;
			if(i+dice1<=24)
			{	
				if(board[i+dice1]<-1)
					continue;
				board[i+dice1]++;
				//	if(i+dice1!=24)
				move[0].second=i+dice1;

			}
			else
			{
				if(debug==1)
					cout<<"i="<<i <<"heare\n";
				for(k=i-1;k>=18;k--)
					if(board[k]>0)
						break;
				if(k!=17)
				{	
					board[i]++;
					break;
				}
				else
				{
					move[0].second=24;
					board[24]++;
				}
			}
			board[i]--;
			move[0].first=i;
			for(j=18;j<24;j++)
			{
				if(debug==1)
					cout<<j<<"=j"<<endl;
				if(board[j]>0)
				{
					if(j+dice2<=24)
					{
						if(board[j+dice2]<-1)
							continue;
						board[j+dice2]++;
						move[1].second=j+dice2;
					}
					else
					{
						for(k=j-1;k>=18;k--)
							if(board[k]>0)
								break;
						if(debug==1)
							cout<<"in"<<k<<endl;
						if(k!=17)
						{
							board[j]++;
							break;
						}
						else
						{
							if(debug==1)
								cout<<"24\n";
							board[24]++;
						}	move[1].second=24;
					}
					board[j]--;
					move[1].first=j;
					calculateheuritic();
					c++;
					board[j]++;
					if(j+dice2<=24)
						board[j+dice2]--;
					else
						board[24]--;
				}
			}

			board[i]++;
			if(i+dice1<=24)
				board[i+dice1]--;
			else
			{
				board[24]--;
			}
		}
	}
	if(c==0)
	{		
		for(i=18;i<24;i++)
		{
			//              for(k=0;k<24;k++)
			//                      cout<<board[k]<<"-";
			//              cout<<endl;
			if(board[i]>0)
			{
				if(debug==1)
					cout<<"i="<<i<<endl;
				if(i+dice1<=24)
				{
					if(board[i+dice1]<-1)
						continue;
					board[i+dice1]++;
					//      if(i+dice1!=24)
					move[0].second=i+dice1;

				}
				else
				{
					if(debug==1)
						cout<<"i="<<i <<"heare\n";
					for(k=i-1;k>=18;k--)
						if(board[k]>0)
							break;
					if(k!=17)
					{
						board[i]++;
						break;
					}
					else
					{
						move[0].second=24;
						board[24]++;
					}
				}
				board[i]--;
				move[0].first=i;
				calculateheuritic();
				board[i]++;
				if(i+dice1<=24)
					board[i+dice1]--;
				else
				{
					board[24]--;
				}

			}
		}
		for(i=18;i<24;i++)
		{
			//              for(k=0;k<24;k++)
			//                      cout<<board[k]<<"-";
			//              cout<<endl;
			if(board[i]>0)
			{
				if(debug==1)
					cout<<"i="<<i<<endl;
				if(i+dice2<=24)
				{
					if(board[i+dice2]<-1)
						continue;
					board[i+dice2]++;
					//      if(i+dice1!=24)
					move[0].second=i+dice2;

				}
				else
				{
					if(debug==1)
						cout<<"i="<<i <<"heare\n";
					for(k=i-1;k>=18;k--)
						if(board[k]>0)
							break;
					if(k!=17)
					{
						board[i]++;
						break;
					}
					else
					{
						move[0].second=24;
						board[24]++;
					}
				}
				board[i]--;
				move[0].first=i;
				calculateheuritic();
				board[i]++;
				if(i+dice2<=24)
					board[i+dice2]--;
				else
				{
					board[24]--;
				}

			}
		}
	}
}
int main()
{
	srand(time(NULL));
//	int t1=4;
//	while(t1--)
//		cout<<rand()<<endl;
	int i,j,k,n,t;
	move[0]=make_pair(-10,-10);
	move[1]=make_pair(-10,-10);
	bestmove[0]=make_pair(-10,-10);
	bestmove[1]=make_pair(-10,-10);
	//	string name;
	//	cin>>name;
	/*	for(i=0;i<12;i++)
		cin>>a[i];
		for(i=0;i<12;i++)
		cin>>b[i];
		j=0;
		for(i=11;i>=0;i--)
		board[j++]=b[i];	
		for(i=0;i<12;i++)
		board[j++]=a[i];
		if(name[0]=='B')
		{
		w=1;
		sign=-1;
	//		dice1*=-1
	//		dice2*=-1
	}*/
	int yy=0;
	for(i=0;i<24;i++)
	{
		cin>>board[i];
		if(i<18 && board[i]>0)
			yy++;
	}
	int g=0;
	for(i=18;i<24;i++)
	{
		if(board[i]>0)
			g+=board[i];
	}
	if(g>9)
		race=1;
//	cin>>bar>>bar1;
	char c;
	c=getchar();
	c=getchar();
	bar=0;
	bar1=0;
	if(c=='\n')
	{
		bar1=0;
		bar=0;
	}
	else
	{
		while(c!='\n')
		{
			if(c=='a')
				bar++;
			else if(c=='b')
				bar1++;
			c=getchar();
		}
	}
	if(debug==1)
		cout<<bar<<" -  "<<bar1<<endl;
/*	char oo[100];
	cin>>oo;
	for(i=0;oo[i]!='\0';i++)
	{
		if(oo[i]=='a')
			bar++;
	}
//	cin>>bar;*/
	cin>>dice1>>dice2;
	for(i=0;i<6;i++)
		weight[i]=3*(i+1);
	for(i=6;i<18;i++)
		weight[i]=1*(i-6);
	for(i=18;i<24;i++)
		weight[i]=2*(i-12);
	if(yy==0 && bar==0)
		homestate();
	else
		allcon(1);
	if(debug==1)
	cout<<"race="<<race<<endl;
	if(debug==1)
		cout<<"BEST "<<bestresult <<endl;
	{
		//	for(i=0;i<24;i++)
		//		cout<<bestboard[i]<<" ";
		//		cout<<endl;

		if(bestmove[0].first ==-10)
			cout<<"pass\n";
		else if(bestmove[0].first ==-1)
			cout<<"Z "<<(bestmove[0].second+1)%25<<endl;
		else
			cout<<(bestmove[0].first+1)%25<<" "<<(bestmove[0].second+1)%25<<endl;

		if(bestmove[1].first ==-10)
			cout<<"pass\n";
		else if(bestmove[1].first ==-1)
			cout<<"Z "<<(bestmove[1].second+1)%25<<endl;
		else
			cout<<(bestmove[1].first+1)%25<<" "<<(bestmove[1].second+1)%25<<endl;
	}
	/*	if(bestmove[0].first ==-10)
		cout<<"pass\n";

		else
		{ 
		if(bestmove[0].first==-1)
		cout<<"Z ";
		else if(bestmove[0].first <12)
		cout<<"B"<<12-bestmove[0].first<<" ";
		else if(bestmove[0].first <24)
		cout<<"A"<<bestmove[0].first-11<<" ";

		if(bestmove[0].second <12)
		cout<<"B"<<12-bestmove[0].second;
		else if(bestmove[0].second <24)
		cout<<"A"<<bestmove[0].second-11;
		cout<<endl;
		}
		if(bestmove[1].first ==-10)
		cout<<"pass\n";
		else
		{
		if(bestmove[1].first==-1)
		cout<<"Z ";
		else	if(bestmove[1].first <12)
		cout<<"B"<<12-bestmove[1].first<<" ";
		else if(bestmove[1].first <24)
		cout<<"A"<<bestmove[1].first-11<<" ";

		if(bestmove[1].second <12)
		cout<<"B"<<12-bestmove[1].second;
		else if(bestmove[1].second <24)
		cout<<"A"<<bestmove[1].second-11;
		}*/
	return 0;
}
