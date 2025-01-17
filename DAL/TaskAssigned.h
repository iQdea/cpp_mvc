#pragma once

namespace DAL {
	namespace Entities {
		class TaskAssigned : public ITaskPart {
		public:
			TaskAssigned(string taskId, string modifiedBy, time_t modifiedAt, string assignedTo) : ITaskPart(taskId, modifiedBy, modifiedAt) {
				this->assignedTo = assignedTo;
			}
			TaskAssigned(string id, string taskId, string modifiedBy, time_t modifiedAt, string assignedTo) : ITaskPart(id, taskId, modifiedBy, modifiedAt) {
				this->assignedTo = assignedTo;
			}

			string assignedTo;
		};
	}
}

