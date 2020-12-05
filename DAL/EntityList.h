#pragma once
#include "Entity.h"

namespace DAL {
	namespace Entities {
		class EntityList {
		public:
			EntityList(database db) {
				this->db = db;
				filter = shared_ptr<value>(new value(document{}));
			}

			virtual shared_ptr<Entity> findOne() {
				auto result = coll.find_one(filter->view());
				if (!result) {
					throw invalid_argument("Entity was not found");
				}
				
				shared_ptr<view> v(new view(result->view()));
				return getEntity(v);
			}

			virtual vector<shared_ptr<Entity>> findAll() {
				auto cursor = coll.find(filter->view());
				vector<shared_ptr<Entity>> list;

				for (auto&& doc : cursor) {
					shared_ptr<view> v(new view(doc));
					list.push_back(getEntity(v));
				}

				return list;
			}

			virtual shared_ptr<Entity> getEntity(shared_ptr<view> doc) = 0;
		protected:
			database db;
			collection coll;
			shared_ptr<value> filter;
		};
	}
}