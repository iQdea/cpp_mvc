#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class TaskStatus : public ITaskPart {
		public:
			TaskStatus(Entities::TaskStatus& item) : ITaskPart(item.id, item.taskId, item.modifiedBy, item.modifiedAt) {
				status = item.status;
			}

			TaskStatusEnum status;
		};
	}
}
