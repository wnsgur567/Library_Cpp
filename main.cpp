#include"Property.h"

#include <string>
#include <iostream>
class myClass {
private:
	Property<std::string> secretkey_;

	// ----------- user-defined implementation functions ------------------
	// in order to use these as parameters, the compiler needs to see them
	// before they are used as template arguments. It is possible to get rid
	// of this order dependency by writing the templates with slight
	// differences, but then the program must initialize them with the function
	// addresses at run time. ask me for details if you prefer this approach.

	// myKids is the real get function supporting NumberOfChildren property
	int myKids()
	{
		return 42;
	}

	// addWeight is the real set function supporting WeightedValue property
	float addWeight(float const& value)
	{
		std::cout << "WO function myClass::addWeight called with value "
			<< value
			<< std::endl;
		return value;
	}
	// setSecretkey and getSecretkey support the Secretkey property
	std::string setSecretkey(const std::string& key)
	{
		// extra processing steps here
		return secretkey_(key);
	}
	std::string getSecretkey()
	{
		// extra processing steps here
		return secretkey_();
	}

public:
	// Name and ID are read-write properties with automatic data store
	Property<std::string> Name;
	Property<long> ID;
	// Number_of_children is a read-only property
	ROProperty< int, myClass, &myClass::myKids > NumberOfChildren;
	// WeightedValue is a write-only property
	WOProperty< float, myClass, &myClass::addWeight > WeightedValue;
	// Secretkey is a read-write property calling user-defined functions
	RWProperty< std::string,
		myClass,
		&myClass::getSecretkey,
		&myClass::setSecretkey
	> Secretkey;

	IndexedProperty< std::string, std::string > Assignments;

	// constructor for this myClass object must notify member properties
	// what object they belong to
	myClass()
	{
		NumberOfChildren(this);
		WeightedValue(this);
		Secretkey(this);
	}
};
int main()
{
	myClass thing;

	// Property<> members:
	thing.Name("Pinkie Platypus");
	std::string s1 = thing.Name();
	std::cout << "Name = " << s1 << std::endl;
	thing.Name.set("Kuddly Koala");
	s1 = thing.Name.get();
	std::cout << "Name = " << s1 << std::endl;

	thing.Name = "Willie Wombat";
	s1 = thing.Name;
	std::cout << "Name = " << s1 << std::endl;
	std::cout << std::endl;

	thing.ID(12345678);
	long id = thing.ID();
	std::cout << "ID = " << id << std::endl;

	thing.ID.set(9999);
	id = thing.ID.get();
	std::cout << "ID = " << id << std::endl;

	thing.ID = 42;
	id = thing.ID;
	std::cout << "ID = " << id << std::endl;
	std::cout << std::endl;

	// ROProperty<> member
	int brats = thing.NumberOfChildren();
	std::cout << "Children = " << brats << std::endl;
	brats = thing.NumberOfChildren.get();
	std::cout << "Children = " << brats << std::endl;

	brats = thing.NumberOfChildren;
	std::cout << "Children = " << brats << std::endl;
	std::cout << std::endl;
	// WOProperty<> member
	thing.WeightedValue(2.71828);
	thing.WeightedValue.set(3.14159);
	thing.WeightedValue = 1.618034;
	std::cout << std::endl;
	// RWProperty<> member
	thing.Secretkey("*****");
	std::string key = thing.Secretkey();
	std::cout << "Secretkey = " << key << std::endl;
	thing.Secretkey.set("!!!!!");
	key = thing.Secretkey.get();
	std::cout << "Secretkey = " << key << std::endl;
	thing.Secretkey = "?????";
	key = thing.Secretkey;
	std::cout << "Secretkey = " << key << std::endl;
	std::cout << std::endl;

	// IndexedProperty<> member
	thing.Assignments("Convenor", "Herb");
	std::string job = thing.Assignments("Convenor");
	std::cout << "Convenor = " << job << std::endl;
	thing.Assignments.set_Item("Minutes", "Daveed");
	job = thing.Assignments.get_Item("Minutes");
	std::cout << "Minutes = " << job << std::endl;
	thing.Assignments["Coffee"] = "Francis";
	job = thing.Assignments["Coffee"];
	std::cout << "Coffee = " << job << std::endl;
	std::cout << std::endl;
	return 0;
}