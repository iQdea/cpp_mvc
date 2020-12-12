#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {		
		class Task : public IEntity {
		public:
			Task(string title, string descr, string createdBy, time_t createdAt) : IEntity() {
				this->title = title;
				this->descr = descr;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};
			Task(string id, string title, string descr, string createdBy, time_t createdAt) : IEntity(id) {
				this->title = title;
				this->descr = descr;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};

			Task(string id, string title, string descr, string createdBy, time_t createdAt, TaskStatusEnum status,
				string assignedTo, string lastModifiedBy, time_t lastModifiedAt) : IEntity(id) {
				this->title = title;
				this->descr = descr;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
				this->status = status;
				this->assignedTo = assignedTo;
				this->lastModifiedBy = lastModifiedBy;
				this->lastModifiedAt = lastModifiedAt;
			}

			string title;
			string descr;
			string createdBy;
			time_t createdAt;

			TaskStatusEnum status = TaskStatusEnum::Open;
			string assignedTo = "";

			string lastModifiedBy = "";
			time_t lastModifiedAt = 0;
		};
	}
}
