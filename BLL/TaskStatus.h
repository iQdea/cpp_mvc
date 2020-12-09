#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class TaskStatus : public ITaskPart {
		public:
			TaskStatus(shared_ptr<Entities::TaskStatus> item) : ITaskPart(item->id, item->taskId, item->modifiedBy, item->modifiedAt) {
				status = item->status;
			}

			StatusType status;
		};
	}
}
