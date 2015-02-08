#include<iostream>
using namespace std;
int palindrome(char A[],int i,int j){
	int boolean;
	if(j<i)
		return 1;
	else
	if(i==j && A[i]==A[j])
		return 1;
	else
	if(A[i]!=A[j])
		return 0;
	else
		return boolean=palindrome(A,i+1,j-1);
		
}
int main (int argc, char *argv[]){
	char A[20];
	int j,boolean,i=0;
	cout<<"enter string\n";
	cin.getline(A,20);
	for(j=0;A[j]!='\0';j++);
	j=j-1;
	boolean=palindrome(A,i,j);
	cout<<boolean;
	return 0;
}

