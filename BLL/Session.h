#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Session : public IEntity {
		public:
			Session(Entities::Session& item) : IEntity(item.id) {
				employeeId = item.employeeId;
				taskId = item.taskId;
			}

			string employeeId;
			string taskId;
		};
	}
}
