#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Session : public IEntity {
		public:
			Session(Entities::Session& item) : IEntity(item.id) {
				employeeId = item.employeeId;
				taskId = item.taskId;
				shiftHours = item.shiftHours;
			}

			string employeeId;
			string taskId;
			double shiftHours;
		};
	}
}
