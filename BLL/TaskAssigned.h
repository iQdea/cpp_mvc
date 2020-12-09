#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class TaskAssigned : public ITaskPart {
		public:
			TaskAssigned(shared_ptr<Entities::TaskAssigned> item) : ITaskPart(item->id, item->taskId, item->modifiedBy, item->modifiedAt) {
				assignedTo = item->assignedTo;
			}

			string assignedTo;
		};
	}
}
