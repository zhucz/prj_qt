#include <iostream>
#include "student.h"
using namespace std;

int main(int argc, char *argv[])
{
    int a = 3;
    int b = 1;

    student xiaohua;

    xiaohua.set_age(10);

    int c = a+b;
    cout << "Hello World!" << endl;
    cout << "c = " << c << endl;

    cout << "xiaohua = " << xiaohua.get_age()<<endl;
    cout << "xiaohua = " << xiaohua.get_age()<<endl;
    cout << "xiaohua = " << xiaohua.get_age()<<endl;
    return 0;
}
