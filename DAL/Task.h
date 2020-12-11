#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {		
		class Task : public IEntity {
		public:
			Task(string title, string createdBy, time_t createdAt) : IEntity() {
				this->title = title;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};
			Task(string id, string title, string createdBy, time_t createdAt) : IEntity(id) {
				this->title = title;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};

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
