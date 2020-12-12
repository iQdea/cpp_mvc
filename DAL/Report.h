#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Report : public IEntity {
		public:
			Report(string text, string createdBy, time_t createdAt) : IEntity() {
				this->text = text;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};
			Report(string id, string text, string createdBy, time_t createdAt) : IEntity(id) {
				this->text = text;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};

			Report(string id, string text, string createdBy, time_t createdAt, ReportStatusEnum status,
				ReportTypeEnum type, time_t lastModifiedAt) : IEntity(id) {
				this->text = text;
				this->createdBy = createdBy;
				this->createdAt = createdAt;
				this->status = status;
				this->type = type;
				this->lastModifiedAt = lastModifiedAt;
			}

			string text;
			string createdBy;
			time_t createdAt;

			ReportStatusEnum status = ReportStatusEnum::Draft;
			ReportTypeEnum type = ReportTypeEnum::Daily;

			time_t lastModifiedAt = 0;
		};
	}
}
