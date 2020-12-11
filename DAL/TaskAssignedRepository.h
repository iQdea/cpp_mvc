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
				addField<oid>(doc, "_id", getOid(item->id));
				addField<oid>(doc, "taskId", getOid(item->taskId));
				addField<oid>(doc, "modifiedBy", getOid(item->modifiedBy));
				addField<oid>(doc, "assignedTo", getOid(item->assignedTo));
			}
		};
	}
}