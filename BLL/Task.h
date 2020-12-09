#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Task : public IEntity {
		public:
			Task(shared_ptr<Entities::Task> item) : IEntity(item->id) {
				title = item->title;
				
				createdBy = item->createdBy;
				createdAt = item->createdAt;

				lastModifiedAt = item->lastModifiedAt;
				lastModifiedBy = item->lastModifiedBy;

				assignedTo = item->assignedTo;
				status = item->status;
			}

			string title;

			string createdBy;
			time_t createdAt;

			time_t lastModifiedAt = 0;
			string lastModifiedBy = "";

			string assignedTo = "";
			StatusType status = StatusType::Open;
		};
	}
}
