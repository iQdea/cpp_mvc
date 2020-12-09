#pragma once

namespace DAL {
	namespace Entities {
		class TaskComment : public ITaskPart {
		public:
			TaskComment(string id, string taskId, string modifiedBy, time_t modifiedAt, string comment) : ITaskPart(id, taskId, modifiedBy, modifiedAt) {
				this->comment = comment;
			}

			string comment;
		};
	}
}

