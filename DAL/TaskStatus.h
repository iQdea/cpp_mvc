#pragma once
#include "TaskPart.h"

namespace DAL {
	namespace Entities {		
		class TaskStatus : public TaskPart {
		public:
			TaskStatus(database db, string id, string taskId, string modifiedBy, time_t modifiedAt, StatusType status) : TaskPart(db, id, taskId, modifiedBy, modifiedAt) {
				coll = db["task-status"];
				this->status = status;
			}
		private:
			StatusType status;
		};
	}
}

