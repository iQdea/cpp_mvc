#pragma once
#include "common.h"
#include "Report.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class ReportRepository : public Repository<Report> {
		public:
			ReportRepository(database db) : Repository() {
				coll = db["report"];
			}

			shared_ptr<Report> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string text = parseString(doc, "text");
				string createdBy = parseOid(doc, "createdBy");
				time_t createdAt = parseInt(doc, "createdAt");
				ReportStatusEnum status = (ReportStatusEnum) parseInt(doc, "status");
				ReportTypeEnum type = (ReportTypeEnum) parseInt(doc, "type");
				time_t lastModifiedAt = parseInt(doc, "lastModifiedAt");

				return make_shared<Report>(id, text, createdBy, createdAt, status, type, lastModifiedAt);
			}

			void setData(basicDoc& doc, Report& item) override {
				addField<string>(doc, "text", item.text);
				addField<oid>(doc, "createdBy", getOid(item.createdBy));
				addField<int>(doc, "createdAt", item.createdAt);
				addField<int>(doc, "status", (int)item.status);
				addField<int>(doc, "type", (int)item.type);
				addField<int>(doc, "lastModifiedAt", item.lastModifiedAt);
			}

			void setFilterTypeStatusCreatedBy(ReportTypeEnum type, ReportStatusEnum status, string createdBy) {
				filter = shared_ptr<value>(new value(document{}
					<< "type" << (int)type
					<< "status" << (int)status
					<< "createdBy" << getOid(createdBy)
					<< finalize));
			}

			void setFilterTypeCreatedByBetween(ReportTypeEnum type, string createdBy, time_t start, time_t end) {
				filter = shared_ptr<value>(new value(document{}
					<< "type" << (int) type
					<< "createdBy" << getOid(createdBy)
					<< "createdAt" << open_document
					<< "$gte" << (int)start
					<< "$lt" << (int)end
					<< close_document
					<< finalize));
			}
		};
	}
}