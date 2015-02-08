#include<iostream>
using namespace std;
int palindrome(char A[],int i,int j){
	if(j < i)
		return 1;
	if(i==j && A[i]==A[j])
		return 1;
	if(A[i]!=A[j])
		return 0;
	else
		return palindrome(A,i+1,j-1);
		
}
int main (int argc, char *argv[]){
	char A[20];
	int j;
	cout<<"Enter a String\n";
	cin.getline(A,20);
	for(j=0;A[j]!='\0';j++);
	if(palindrome(A,0,j-1) == 0)
		cout<<"It's not a palindrome.";
	else
		cout<<"It's a palindrome.";
	cout<<endl;
	return 0;
}

