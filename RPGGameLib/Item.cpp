#include "item.h"

Item::Item(string in_name, int init_size, int init_weight, int init_id, int money) {
	name_ = in_name;
	size_ = init_size;
	weight_ = init_weight;
	id_ = init_id;
	money_ = money;
}

Item::~Item()
{
}

void Item::SetSize(int in_size) {
	size_ = in_size >= 0 ? in_size : 0;
}

void Item::SetWeight(int in_weight) {
	weight_ = in_weight >= 0 ? in_weight : 0;
}

void Item::SetName(string in_name) {
	name_ = in_name;
}

int Item::GetSize() {
	return size_;
}

int Item::GetWeight() {
	return weight_;
}

string Item::GetName() {
	return name_;
}

int Item::GetID()
{
	return id_;
}

int Item::GetLevel()
{
	return 0;
}

int Item::GetMoney()
{
	return money_;
}