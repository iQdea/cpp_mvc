#pragma once
#include "common.h"
#include "TaskStatus.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TaskStatusRepository : public Repository<TaskStatus> {
		public:
			TaskStatusRepository(database db) : Repository() {
				coll = db["task-status"];
			}

			shared_ptr<TaskStatus> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string taskId = parseOid(doc, "taskId");
				string modifiedBy = parseOid(doc, "modifiedBy");
				time_t modifiedAt = 0;
				int status = parseInt(doc, "status");

				return shared_ptr<TaskStatus>(new TaskStatus(id, taskId, modifiedBy, modifiedAt, status));
			}

			void setData(basicDoc& doc, shared_ptr<TaskStatus> item) override {
				addField<oid>(doc, "_id", getOid(item->id));
				addField<oid>(doc, "taskId", getOid(item->taskId));
				addField<oid>(doc, "modifiedBy", getOid(item->modifiedBy));
				addField<int>(doc, "status", (int)item->status);
			}
		};
	}
}