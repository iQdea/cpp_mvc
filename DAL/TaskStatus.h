#pragma once

namespace DAL {
	namespace Entities {		
		class TaskStatus : public ITaskPart {
		public:
			TaskStatus(string id, string taskId, string modifiedBy, time_t modifiedAt, StatusType status) : ITaskPart(id, taskId, modifiedBy, modifiedAt) {
				this->status = status;
			}

			StatusType status;
		};
	}
}

