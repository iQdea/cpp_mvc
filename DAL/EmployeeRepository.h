#pragma once
#include "common.h"
#include "Employee.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class EmployeeRepository : public Repository<Employee> {
		public:
			EmployeeRepository(database db) : Repository() {
				coll = db["employer"];
			}

			shared_ptr<Employee> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string name = parseString(doc, "name");
				string managerId = parseOid(doc, "managerId");

				return shared_ptr<Employee>(new Employee(id, name, managerId));
			}

			void setData(basicDoc& doc, shared_ptr<Employee> item) override {
				addField<string>(doc, "name", item->name);
				addField<oid>(doc, "managerId", getOid(item->managerId));
			}

			void setFilterManagerId(string id) {
				filter = shared_ptr<value>(new value(document{}
					<< "managerId" << oid{ string_view{id} }
				<< finalize));
			}

			void setFilterName(string name) {
				filter = shared_ptr<value>(new value(document{}
					<< "name" << name
					<< finalize));
			}
		};
	}
}