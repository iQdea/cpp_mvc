#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class TaskComment : public ITaskPart {
		public:
			TaskComment(shared_ptr<Entities::TaskComment> item) : ITaskPart(item->id, item->taskId, item->modifiedBy, item->modifiedAt) {
				comment = item->comment;
			}

			string comment;
		};
	}
}
