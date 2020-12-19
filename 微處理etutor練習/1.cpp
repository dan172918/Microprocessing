#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;

int main()
{
	char arr[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	unsigned int num,count=0;
	while(cin>>num)
	{
		count++;
		cout<<"Case "<<count<<": "<<num<<endl;
		char ans[8]={'0','0','0','0','0','0','0','0'};
		int mark=0;
		
		while(num>=16)
		{
			ans[mark] = arr[ ( num & ~( (num>>4) << 4 ) ) ];
			num=(num>>4);
			mark++;
		}
		
		ans[mark] = arr[num];
		reverse(ans,ans+8);
		
		for(int i=0;i<8;i++)
			cout<<ans[i]<<" ";	
		cout<<endl;
	}

}


