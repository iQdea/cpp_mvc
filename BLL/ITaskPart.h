#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class ITaskPart : public IEntity {
		public:
			ITaskPart(string id, string taskId, string modifiedBy, time_t modifiedAt) : IEntity(id) {
				this->taskId = taskId;
				this->modifiedBy = modifiedBy;
				this->modifiedAt = modifiedAt;
			}

			string taskId;
			time_t modifiedAt;
			string modifiedBy;
		};
	}
}
