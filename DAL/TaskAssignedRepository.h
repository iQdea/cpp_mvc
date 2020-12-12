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
				time_t modifiedAt = parseInt(doc, "modifiedAt");
				string assignedTo = parseOid(doc, "assignedTo");

				return make_shared<TaskAssigned>(id, taskId, modifiedBy, modifiedAt, assignedTo);
			}

			void setData(basicDoc& doc, TaskAssigned& item) override {
				addField<oid>(doc, "_id", getOid(item.id));
				addField<oid>(doc, "taskId", getOid(item.taskId));
				addField<oid>(doc, "modifiedBy", getOid(item.modifiedBy));
				addField<int>(doc, "modifiedAt", (int)item.modifiedAt);
				addField<oid>(doc, "assignedTo", getOid(item.assignedTo));
			}

			void setFilterAssignedToBetween(string assignedTo, time_t start, time_t end) {
				filter = shared_ptr<value>(new value(document{}
					<< "assignedTo" << getOid(assignedTo)
					<< "modifiedAt" << open_document
					<< "$gte" << (int)start
					<< "$lt" << (int)end
					<< close_document
					<< finalize));
			}
		};
	}
}