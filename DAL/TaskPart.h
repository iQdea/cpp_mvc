#pragma once
#include "Entity.h"

namespace DAL {
	namespace Entities {
		class TaskPart : public Entity {
		public:
			TaskPart(database db, string id, string taskId, string modifiedBy, time_t modifiedAt) : Entity(db, id) {
				this->taskId = taskId;
				this->modifiedBy = modifiedBy;
				this->modifiedAt = modifiedAt;
			}
		protected:
			string taskId;
			time_t modifiedAt;
			string modifiedBy;
		};
	}
}

