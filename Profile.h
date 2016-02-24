#ifndef _PROFILE_H_
#define _PROFILE_H_
#include <iostream>
using namespace std;

class Profile
{
public:
	Profile(string name );
	~Profile();
	string GetName(){ return this->name; };
	void SetName(string name){ this->name = name; };
	unsigned int GetAge(){ return this->age; };
	void SetAge(unsigned int age){ this->age = age; };
	string GetOccupation(){ return this->occupation; };
	void SetOccupation(string occupation){ this->occupation = occupation; };

private:
	string name;
	unsigned int age;
	string occupation;
};

#endif
