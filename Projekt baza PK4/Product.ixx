export module Product;
export import <string>;

export class Product {
	std::string name;
	int calories;
	int spiciness;
public:
	Product(std::string name, int calories, int spiciness);
	Product(std::string name);
	std::string getName();
	int getCalories();
	int getSpiciness();
	void setName(std::string);
	void setCalories(int);
	void setSpiciness(int);

	friend bool operator== (Product&, std::string&);
};

export Product::Product(std::string name, int calories, int spiciness) : name(name), calories(calories), spiciness(spiciness) {
}

export Product::Product(std::string name) : name(name) {
}

export std::string Product::getName()
{
	return name;
}

export int Product::getCalories()
{
	return calories;
}

export int Product::getSpiciness()
{
	return spiciness;
}

export void Product::setCalories(int calories) {
	this->calories = calories;
}

export void Product::setName(std::string name) {
	this->name = name;
}

export void Product::setSpiciness(int spiciness) {
	this->spiciness = spiciness;
}

export bool operator== (Product& lhs, std::string& rhs)
{
	if (lhs.name == rhs) {
		return true;
	}
	return false;
}