#pragma once
#include "common.h"
#include "TaskAssigned.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TaskAssignedRepository : public Repository<TaskAssigned> {
		public:
			TaskAssignedRepository(database db) : Repository() {
				coll = db["task-assigned"];
			}

			shared_ptr<TaskAssigned> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string taskId = parseOid(doc, "taskId");
				string modifiedBy = parseOid(doc, "modifiedBy");
				time_t modifiedAt = 0;
				string assignedTo = parseOid(doc, "assignedTo");

				return shared_ptr<TaskAssigned>(new TaskAssigned(id, taskId, modifiedBy, modifiedAt, assignedTo));
			}

			void setData(basicDoc& doc, shared_ptr<TaskAssigned> item) override {
				TaskAssigned taskAssigned = *item;
				addField<string>(doc, "_id", taskAssigned.id);
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