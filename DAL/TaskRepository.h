#pragma once
#include "common.h"
#include "Task.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TaskRepository : public Repository<Task> {
		public:
			TaskRepository(database db) : Repository() {
				coll = db["task"];
			}

			shared_ptr<Task> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string title = parseString(doc, "title");
				string createdBy = parseOid(doc, "createdBy");

				return shared_ptr<Task>(new Task(id, title, createdBy));
			}

			void setData(basicDoc& doc, shared_ptr<Task> item) override {
				addField<string>(doc, "title", item->title);
				addField<oid>(doc, "createdBy", getOid(item->createdBy));
			}

			void setFilterCreatedBy(string createdBy) {
				filter = shared_ptr<value>(new value(document{}
					<< "createdBy" << createdBy
				<< finalize));
			}
		};
	}
}