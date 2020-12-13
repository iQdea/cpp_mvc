#pragma once
#include <map>
#include <string>
#include <memory>
using namespace std;

template <class T> class Tree {
public:
	shared_ptr<T> item;
	map<string, shared_ptr<Tree<T>>> children;
};