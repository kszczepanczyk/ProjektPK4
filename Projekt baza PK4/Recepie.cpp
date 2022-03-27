#pragma once
#include "Recepie.h"


Recepie::Recepie(std::string name, int prepTime, std::string mealType, std::string description, std::vector<std::pair<Product, int>> products) :
	name(name), prepTime(prepTime), mealType(mealType), description(description), products(products) {
}

Recepie::Recepie(std::string name, int prepTime, std::string mealType, std::string description, std::vector<std::vector<std::pair<Product, int>>> products) :
	name(name), prepTime(prepTime), mealType(mealType), description(description) {
	this->tmpProducts = products;
}

std::string Recepie::getName()
{
	return name;
}

std::string Recepie::getMealType()
{
	return mealType;
}

std::string Recepie::getDescription()
{
	return description;
}

int Recepie::getPrepTime()
{
	return prepTime;
}

void Recepie::setName(std::string name) {
	this->name = name;
}

void Recepie::setTime(int time) {
	this->prepTime = time;
}

void Recepie::setDescription(std::string desc) {
	this->description = desc;
}

void Recepie::setType(std::string type) {
	this->mealType = type;
}