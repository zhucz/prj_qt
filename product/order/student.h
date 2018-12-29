#ifndef STUDENT_H
#define STUDENT_H

class student {
    private:
        int age;
    public:
        void set_age(int);
        int get_age(void);
};


void student::set_age(int lage)
{
    this->age = lage;
}

int student::get_age(void)
{
    return this->age;
}



#endif // STUDENT_H
