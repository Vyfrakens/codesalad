#include
#include
using namespace std;
class A
{
    int rel;
public:
    A()
    {
        rel=0;
    }
    //Basic to Class Conversion
    A(int trel)
    {
        rel=trel;
    }
    void set()
    {
        cout<>rel;
    }
    void display()
    {
        cout<<"\n The rel value is:"<<rel<<"\n";
    }
    //Class to Basic Conversion
    operator int()
    {
        int value=0;
        value=rel+100;
        return value;
    }
    friend class B;
};
class B
{
    int rel1;
    int rel2;
public:
    B()
    {
        rel1=0;
        rel2=0;
    }
    /*
     //Destination Constructor.
     B(A tobj)
     {
     rel1=tobj.rel/2;
     rel2=tobj.rel/2;
     }*/
    void set()
    {
        cout<>rel1;
        cout<>rel2;
    }
    void display()
    {
        cout<<"\n The Rel 1 is:"<<rel1<<"\n";
        cout<<"\n The Rel 2 is:"<<rel2<<"\n";
    }
    //Source Operator
    operator A()
    {
    A tobj;
    tobj.rel=rel1+rel2;
    return tobj;
}
};
int main()
{
    int result=100;
    A obj;
    obj.set(); //obj.rel=200
    obj.display();
    //Calling - Basic to Class Conversion
    obj=result;
    cout<<"\n Basic to Class conversion result is:";
    obj.display();
    cout<<"\n============================================";
    //Calling - Class to Basic Conversion
    result=obj;
    cout<<"\n Class to Basic conversion result is:"<<result<<"\n";
    cout<<"\n============================================";
    //Class to Class Conversion
    cout<<"\n\n Class A Details:";
    A aobj;
    aobj.set(); //100
    aobj.display(); //100
    cout<<"\n\n Class B Details:";
    B bobj;
    bobj.set(); //200,300
    bobj.display(); //200,300
    /*
     //Destination=Source
     bobj=aobj;
     bobj.display(); 
     */
    aobj=bobj; //200+300
    aobj.display(); //500
    return 0;
}
