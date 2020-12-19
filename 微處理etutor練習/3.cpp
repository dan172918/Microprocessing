#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
using namespace std;

int main()
{
	int bit;
	vector<int> arr;
	
	while(cin>>bit && bit!=-1)
		arr.push_back(bit);
		
	sort(arr.begin(),arr.end());
	arr.erase(unique(arr.begin(),arr.end()),arr.end());
	
	for(int i=0;i<arr.size();i++)
		cout<<arr.at(i)<<" ";
	cout<<endl;	
	unsigned int num,count=0;
	int ans[32];
	while(cin>>num)
	{
		count++;
		cout<<"Case "<<count<<": "<<num<<endl;

		int mark=0,zeroCount=0;
		bool isAllBits=true;
		for(int i=0;i<32;i++)
			ans[i]=0;
		while(num>=2)
		{
			ans[mark] = num & ~((num>>1)<<1);
			num=(num>>1);
			mark++;
		}
		ans[mark] = num;
		for(int i=0;i<arr.size();i++)
			if(ans[arr[i]]!=1)
			{
				isAllBits=false;
				zeroCount++;
			}
		if(isAllBits==true)
			cout<<"true(all bits 1)"<<endl<<"true(exist bits 1)"<<endl;
		else if(zeroCount==arr.size())
			cout<<"false(all bits 1)"<<endl<<"false(exist bits 1)"<<endl;
		else
			cout<<"false(all bits 1)"<<endl<<"true(exist bits 1)"<<endl;
	}
}


