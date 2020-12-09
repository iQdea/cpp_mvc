#pragma once
#include "common.h"

namespace DAL {
	template <class T> class IRepository {
	public:
		virtual string create(shared_ptr<T> item) = 0;
		virtual void update(shared_ptr<T> item) = 0;
		virtual void remove(string id) = 0;
		virtual shared_ptr<T> findOne() = 0;
		virtual vector<shared_ptr<T>> findAll() = 0;
	};
}