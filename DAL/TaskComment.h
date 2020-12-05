#pragma once
#include "TaskPart.h"

namespace DAL {
	namespace Entities {
		class TaskComment : public TaskPart {
		public:
			TaskComment(database db, string id, string taskId, string modifiedBy, time_t modifiedAt, string comment) : TaskPart(db, id, taskId, modifiedBy, modifiedAt) {
				coll = db["task-comment"];
				this->comment = comment;
			}
		private:
			string comment;
		};
	}
}

