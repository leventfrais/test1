#include<bits/stdc++.h>
using namespace std;
const int N=1e3+7;//自反 对称 传递 r s t
int n,t,vis[N];;
int a[N],r1[N][N],r2[N][N],r3[N][N],r[N];
int rR[N][N],sR[N][N],tR[N][N],R[N][N],IA[N][N];
string s;
int getit(int from)//数字字符转化为整型数
{
	int ans=0;
	for(int i=from;vis[i];i++)
		ans=ans*10+s[i]-'0';
	return ans;
}
int getitlen(int from)//数字位数
{
	int ans=0;
	for(int i=from;vis[i];i++)
		ans++;
	return ans;
}
void getnum()//字符串里面成对的提取出数字
{
	cin>>s;
	int pos=0;
	for(int i=0;i<s.length();i++)
		vis[i]=0;
	for(int i=1;i<=t;i++)
		r[i]=0;
	t=0;//初始化
	
	for(int i=0;i<s.length();i++)
		if(s[i]=='=') pos=i;//记录等号=的坐标，防止把R1的1也算进去
	
	for(int i=0;i<s.length();i++)
		if(i>pos)
			if(s[i]>='0'&&s[i]<='9') vis[i]=1;//数字坐标
	for(int i=0;i<s.length();i++)
	{
		if(vis[i])//如果是数字
		{	
			r[++t]=getit(i);//字符串转数字
			int len=getitlen(i);
			i+=len;
		}
	}
}
void input()//输出
{
	getnum();
	n=t;
	for(int i=1;i<=n;i++)
		a[i]=r[i];

	//---- -----
	getnum();
	for(int i=1;i<=t;i+=2)
		r1[r[i]][r[i+1]]=1;
		
	getnum();
	for(int i=1;i<=t;i+=2)
		r2[r[i]][r[i+1]]=1;
}
void check()//检查输出
{
	cout<<"R1:"<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<r1[i][j]<<" ";
		cout<<endl;
	}
	cout<<"R2:"<<endl;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<r2[i][j]<<" ";
		cout<<endl;
	}
}
int mcalc(int p,int q)//矩阵乘法
{
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=r1[p][i]*r2[i][q];
	return ans>=1?1:0;//析取
}
void compound()//关系的合成
{
	int tot=0,cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			r3[i][j]=mcalc(i,j);
			if(r3[i][j])tot++;
		}
	cout<<"R3={";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(r3[i][j])
			{
				cnt++;
				if(cnt<tot)
					cout<<"<"<<i<<","<<j<<">,";
				else 
					cout<<"<"<<i<<","<<j<<">}"<<endl;
			}
		}
	}
}
void find_rR()//自反闭包
{
	int cnt=0,tot=0;
	for(int i=1;i<=n;i++)
		IA[i][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(IA[i][j] || r1[i][j])
			{
				rR[i][j]=1;
				tot++;
			}

	cout<<"rR={";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(rR[i][j])
			{
				cnt++;
				if(cnt<tot)
					cout<<"<"<<i<<","<<j<<">,";
				else 
					cout<<"<"<<i<<","<<j<<">}"<<endl;
			}
		}
	}
}
void find_sR()//对称闭包
{
	int cnt=0,tot=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			R[i][j]=r1[j][i];//转置矩阵

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(R[i][j] || r1[i][j])
			{
				sR[i][j]=1;
				tot++;
			}
				
	cout<<"sR={";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(sR[i][j])
			{
				cnt++;
				if(cnt<tot)
					cout<<"<"<<i<<","<<j<<">,";
				else 
					cout<<"<"<<i<<","<<j<<">}"<<endl;
			}
		}
	}
}
void find_tR()//warshall 传递闭包
{
	int tot=0,cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		tR[i][j]=r1[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(tR[j][i])
				for(int k=1;k<=n;k++)
					tR[j][k]=tR[j][k]+tR[i][k]>=1?1:0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(tR[i][j])tot++;	
	cout<<"tR={";
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(tR[i][j])
			{
				cnt++;
				if(cnt<tot)
					cout<<"<"<<i<<","<<j<<">,";
				else 
					cout<<"<"<<i<<","<<j<<">}"<<endl;
			}
		}
	}
}
void find()//求闭包
{
	find_rR();
	find_sR();
	find_tR();
}
int main()
{
	input();
	cout<<"解得"<<endl;
	compound();
	find();
	//check();
	return 0;
}
/*
A={1,2,3,4}
R1={<1,1>,<1,2>,<1,3>,<1,4>,<2,3>}
R2={<1,1>,<1,2>,<2,1>,<2,2>,<3,3>,<4,4>}

1 1 1 1
0 0 1 0
0 0 0 0
0 0 0 0
--------------------------------
A={1,2,3,4}
R1={<2,4>,<4,2>,<3,3>}
R2={<2,1>,<3,2>,<4,3>}

0 0 0 0
0 0 1 0
0 1 0 0
1 0 0 0
--------------------------------
A={1,2}
R1={<1,2>}
R2={<2,1>}
--------------------------------
A={1,2,3,4}
R1={<1,2>,<2,4>,<4,1>,<4,3>}

1 1 1 1
1 1 1 1
0 0 0 0
1 1 1 1
*/
