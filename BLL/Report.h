#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Report : public IEntity {
		public:
			Report(Entities::Report& item) : IEntity(item.id) {
				text = item.text;

				createdBy = item.createdBy;
				createdAt = item.createdAt;

				lastModifiedAt = item.lastModifiedAt;

				status = item.status;
				type = item.type;
			}

			string text;

			string createdBy;
			time_t createdAt;

			time_t lastModifiedAt = 0;

			ReportStatusEnum status = ReportStatusEnum::Draft;
			ReportTypeEnum type = ReportTypeEnum::Daily;
		};
	}
}
