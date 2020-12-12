#pragma once
#include "common.h"
#include "TaskComment.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TaskCommentRepository : public Repository<TaskComment> {
		public:
			TaskCommentRepository(database db) : Repository() {
				coll = db["task-comment"];
			}

			shared_ptr<TaskComment> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string taskId = parseOid(doc, "taskId");
				string modifiedBy = parseOid(doc, "modifiedBy");
				time_t modifiedAt = 0;
				string comment = parseString(doc, "comment");

				return make_shared<TaskComment>(taskId, modifiedBy, modifiedAt, comment);
			}

			void setData(basicDoc& doc, TaskComment& item) override {
				addField<oid>(doc, "_id", getOid(item.id));
				addField<oid>(doc, "taskId", getOid(item.taskId));
				addField<oid>(doc, "modifiedBy", getOid(item.modifiedBy));
				addField<string>(doc, "comment", item.comment);
			}
			
			void setFilterTaskId(string taskId) {
				filter = shared_ptr<value>(new value(document{}
					<< "taskId" << oid{ string_view{taskId} }
				<< finalize));
			}
		};
	}
}