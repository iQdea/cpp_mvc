#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Task : public IEntity {
		public:
			Task(Entities::Task& item) : IEntity(item.id) {
				title = item.title;
				descr = item.descr;

				createdBy = item.createdBy;
				createdAt = item.createdAt;

				lastModifiedAt = item.lastModifiedAt;
				lastModifiedBy = item.lastModifiedBy;

				assignedTo = item.assignedTo;
				status = item.status;
			}

			string title;
			string descr;

			string createdBy;
			time_t createdAt;

			time_t lastModifiedAt = 0;
			string lastModifiedBy = "";

			string assignedTo = "";
			TaskStatusEnum status = TaskStatusEnum::Open;
		};
	}
}
