#include "iostream"
using namespace std;
#define MAX 10

template <class T>
class Stack {
private:
	T a[MAX];
	int top;
public:
	Stack(){
		top = -1;
	}
	void Push(T item) {
		if(top == MAX-1) {
			cout<< "Stack Overflow"<<endl;
			return;
		}
		a[++top] = item;
	}
 
	int Pop() {
		if(top == -1) {
			cout<< "Stack Underflow"<<endl;
			return 0;
		}
		T data = a[top--];
		return data;
	}
	void Display() {
		if(top == -1) {
			cout<<"Stack is empty"<<endl;
			return;
		}
		for(int i=top; i>=0; i--)
			cout<<a[i]<<" ";
		cout<<endl;
	}
};
int main()
{
	Stack<int> s;
	int ch, item;
	cout<<"STACK"<<endl;
	cout<<"\t1. Push"<<endl;
	cout<<"\t2. Pop"<<endl;
	cout<<"\t3. Display"<<endl;
	cout<<"\t4. Exit"<<endl;
	do {
		cout<<"Enter your choice: ";
		cin>>ch;
		switch(ch) {
			case 1 :
				cout<<"Enter the element to be pushed: ";
				cin>>item;
				s.Push(item);
				s.Display();
				break;
			case 2:
				if((item = s.Pop())!=0) cout<<"The element popped is "<<item<<endl;
				s.Display();
				break;
			case 3:
				s.Display();
				break;
			case 4:
				cout<<"Exiting..."<<endl;
				break;
			default:
				cout<<"Wrong Choice!!!"<<endl;
				break;
		}
	} while(ch!=4);
	return 0;
}