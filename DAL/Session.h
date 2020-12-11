#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Session : public IEntity {
		public:
			Session(int number, string employeeId, string taskId) : IEntity() {
				this->number = number;
				this->employeeId = employeeId;
				this->taskId = taskId;
			};
			Session(string id, int number, string employeeId, string taskId) : IEntity(id) {
				this->number = number;
				this->employeeId = employeeId;
				this->taskId = taskId;
			};

			int number;
			string employeeId;
			string taskId;
		};
	}
}
