#pragma once
#include "TaskPart.h"

namespace DAL {
	namespace Entities {
		class TaskAssigned : public TaskPart {
		public:
			TaskAssigned(database db, string id, string taskId, string modifiedBy, time_t modifiedAt, string assignedTo) : TaskPart(db, id, taskId, modifiedBy, modifiedAt) {
				coll = db["task-assigned"];
				this->assignedTo = assignedTo;
			}
		private:
			string assignedTo;
		};
	}
}

