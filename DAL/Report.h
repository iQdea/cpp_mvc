#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Report : public IEntity {
		public:
			Report(string createdBy, time_t createdAt) : IEntity() {
				this->createdBy = createdBy;
				this->createdAt = createdAt;
			};

			Report(string createdBy, time_t createdAt, ReportTypeEnum type) : IEntity() {
				this->createdBy = createdBy;
				this->createdAt = createdAt;
				this->type = type;
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

			string text = "";
			string createdBy;
			time_t createdAt;

			ReportStatusEnum status = ReportStatusEnum::Draft;
			ReportTypeEnum type = ReportTypeEnum::Daily;

			time_t lastModifiedAt = 0;
		};
	}
}
