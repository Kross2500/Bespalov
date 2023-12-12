#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


class Animal {
protected:
	std::string Name;
	std::string Spec;
public:
	Animal(const std::string name, const std::string spec) : Name(name), Spec(spec) {};

	virtual void display() const {
		cout << Name << " " << Spec << endl;
	};

	void setName(const std::string& d) {
		Name = d;
	};
	void setSpec(const std::string& d) {
		Spec = d;
	};

	virtual ~Animal() {};
};


class Bird : public Animal {
protected:
	std::string wingspan;
public:
	Bird(const std::string& name, const std::string& spec, const std::string& d) : Animal(name, spec), wingspan(d) {};

	void display() const override {
		cout << Name << " " << Spec << " " << wingspan << endl;
	}

	~Bird() {};
};

class Mammal : public Animal {
protected:
	std::string wool_type;
public:
	Mammal(const std::string& name, const std::string& spec, const std::string& d) : Animal(name, spec), wool_type(d) {};

	void display() const override {
		cout << Name << " " << Spec << " " << wool_type << endl;
	}
	~Mammal() {};
};

void modifyObject(Animal* ptr) {
	ptr->setName("Lion");
	ptr->setSpec("Mammal");
}

int main() {
	vector<Animal*> vec;
	vec.resize(3);
	vec[0] = new Animal("Sparrow","Bird");
	vec[1] = new Bird("Sparrow", "Bird","54");
	vec[2] = new Mammal("Bear", "Mammal", "Rude");
	for (const auto i : vec) {
		i->display();
	}
	for (const auto i : vec) {
		modifyObject(i);
		i->display();
		delete i;
	}
	return 0;
}

