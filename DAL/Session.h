#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Session : public IEntity {
		public:
			Session(string employeeId, string taskId) : IEntity() {
				this->employeeId = employeeId;
				this->taskId = taskId;
			};
			Session(string id, string employeeId, string taskId) : IEntity(id) {
				this->employeeId = employeeId;
				this->taskId = taskId;
			};

			string employeeId;
			string taskId;
		};
	}
}
