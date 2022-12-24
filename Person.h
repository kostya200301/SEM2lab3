//
// Created by user on 25.05.2022.
//

#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H


#include <ctime>
#include <string>
#include <iostream>


using namespace std;






class Person_ID {
public:
    int series;
    int number;
    Person_ID() {
        series = 0;
        number = 0;
    }
    Person_ID(int series1, int number1) {
        series = series1;
        number = number1;
    }


};


class Person {
private:
    Person_ID id;
    string firstName;
    string middleName;
    string lastName;
    int age;
public:
    Person(Person_ID id1, string firstName1, string middleName1, string lastName1, int age1) {
        id = id1;
        firstName = firstName1;
        middleName = middleName1;
        lastName = lastName1;
        age = age1;

    }
    Person(){
        id = Person_ID(0, 0);
        firstName = "0";
        middleName = "0";
        lastName = "0";
        age = 0;
    }

    void SetAge(int k) {
        this->age = k;
    }

    Person_ID GetID() {return this->id;};
    string GetFirstName() {return this->firstName;};
    string GetMiddleName() {return this->middleName;};
    string GetLastName() {return this->lastName;};
    time_t GetAge() {return this->age;};
};


string GenString(int size) {
    string str = "";
    for (int i = 0; i < size; i++) {
        str += (char)(97 + rand() % 26);
    }
    return str;
}

Person GenPerson() {
    Person person(Person_ID(rand() % 1000, rand() % 1000), GenString(6), GenString(6), GenString(6), rand() % 100);
    return person;
}

Person* GenPersonLink() {
    Person* person = new Person(Person_ID(rand() % 1000, rand() % 1000), GenString(6), GenString(6), GenString(6), rand() % 100);
    return person;
}


int operator > (Person n1, Person n2){
    if (n1.GetAge() > n2.GetAge()) {
        return 1;
    }
    return 0;
}

int operator < (Person n1, Person n2){
    if (n1.GetAge() < n2.GetAge()){
        return 1;
    }
    return 0;
}


int operator == (Person_ID n1, Person_ID n2){
    if (n1.number == n2.number && n1.series == n2.series){
        return 1;
    }
    return 0;
}

int operator == (Person n1, Person n2){
    if (n1.GetAge() == n2.GetAge() && n1.GetID() == n2.GetID()){
        return 1;
    }
    return 0;
}

float GetAge(Person* p) {
    return (float)p->GetAge();
}


std::ostream& operator << (std::ostream &out, Person &person)
{
    out << "(" << person.GetFirstName() << " " << person.GetMiddleName() << " " << person.GetLastName() << " " << person.GetAge() << " " << person.GetID().series << " " << person.GetID().number << ")";
    return out;
}

std::ostream& operator << (std::ostream &out, Person* person)
{
    out << "(" << person->GetFirstName() << " " << person->GetMiddleName() << " " << person->GetLastName() << " " << person->GetAge() << " " << person->GetID().series << " " << person->GetID().number << ")";
    return out;
}

istream& operator>>(istream &in, Person& person)
{
    cout << "MANDATORY FORMAT WITH BRACKETS!!: (Name MiddleName LastName Age series number)\n";
    char bracket;
    in >> bracket;
    string FN;
    string MN;
    string LN;
    int old;
    int series;
    int number;
    in >> FN >> MN >> LN >> old >> series >> number;
    in >> bracket;
    person = Person(Person_ID(series, number), FN, MN, LN, old);
    return in;
}

Person operator * (Person pers, int k){
    pers.SetAge(pers.GetAge() * k);
    return pers;
}

#endif //LAB3_PERSON_H
