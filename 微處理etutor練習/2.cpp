#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

void printBinary(unsigned int num)
{
	int ans[32];
	int mark=0;
	for(int i=0;i<32;i++)
		ans[i]=0;
	while(num>=2)
	{
		ans[mark] = num & ~((num>>1)<<1);
		num=(num>>1);
		mark++;
	}
	ans[mark] = num;
	reverse(ans,ans+32);
	for(int i=0;i<32;i++)
		cout<<ans[i];	
	cout<<endl;
}

void printOctal(unsigned int num)
{
	int ans[12];
	int mark=0;
	for(int i=0;i<12;i++)
		ans[i]=0;	
	while(num>=8)
	{
		ans[mark] = num & ~((num>>3)<<3);
		num=(num>>3);
		mark++;
	}
	ans[mark] = num;
	reverse(ans,ans+12);
	for(int i=0;i<12;i++)
		cout<<ans[i];	
	cout<<endl;
}

void printHexidecimal(unsigned int num)
{
	char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char ans[8]={'0','0','0','0','0','0','0','0'};
	int mark=0;
	
	while(num>=16)
	{
		ans[mark] = arr[ ( num & ~((num>>4)<<4) ) ];
		num=(num>>4);
		mark++;
	}
	
	ans[mark] = arr[num];
	reverse(ans,ans+8);
	
	cout<<"0x";
	for(int i=0;i<8;i++)
		cout<<ans[i];	
	cout<<endl;
}

int main()
{
	unsigned int num,count=0;
	while(cin>>num)
	{
		count++;
		cout<<"Case "<<count<<": "<<num<<endl;
		printBinary(num);
		printOctal(num);
		printHexidecimal(num);
	}

}


