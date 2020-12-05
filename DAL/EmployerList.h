#pragma once
#include "common.h"
#include "EntityList.h"
#include "Employer.h"

namespace DAL {
	namespace Entities {
		class EmployerList : public EntityList {
		public:
			EmployerList(database db) : EntityList(db) {
				coll = db["employer"];
			}

			shared_ptr<Entity> getEntity(shared_ptr<view> doc) {
				string id;
				string name;

				try { id = (*doc)["_id"].get_oid().value.to_string(); }
				catch (...) { id = ""; }

				try { name = (*doc)["name"].get_utf8().value.to_string(); }
				catch (...) { name = ""; }

				return shared_ptr<Entity>(new Employer(db, id, name));
			}

			void setFilterById(string id) {
				filter = shared_ptr<value>(new value(document{} 
					<< "_id" << oid{ string_view{id} }
					<< finalize));
			}

			void setFilterByManagerId(string id) {
				filter = shared_ptr<value>(new value(document{}
					<< "manager" << oid{ string_view{id} }
				<< finalize));
			}
			void setFilterByName(string name) {
				filter = shared_ptr<value>(new value(document{}
					<< "name" << name
				<< finalize));
			}
		};
	}
}
