#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Session : public IEntity {
		public:
			Session(shared_ptr<Entities::Session> item) : IEntity(item->id) {
				number = item->number;
				employeeId = item->employeeId;
				taskId = item->taskId;
			}

			int number;
			string employeeId;
			string taskId;
		};
	}
}
