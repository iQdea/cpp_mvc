#pragma once
#include "common.h"
#include "Session.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class SessionRepository : public Repository<Session> {
		public:
			SessionRepository(database db) : Repository() {
				coll = db["session"];
			}

			shared_ptr<Session> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				int number = parseInt(doc, "number");
				string employeeId = parseOid(doc, "employeeId");
				string taskId = parseOid(doc, "taskId");

				return shared_ptr<Session>(new Session(id, number, employeeId, taskId));
			}

			void setData(basicDoc& doc, shared_ptr<Session> item) override {
				addField<int>(doc, "number", item->number);
				addField<oid>(doc, "employeeId", getOid(item->employeeId));
				addField<oid>(doc, "taskId", getOid(item->taskId));
			}

			void setSortNumberDesc() {
				options.sort(document{} << "number" << -1 << finalize);
			}

			void setFilterNumber(int number) {
				filter = shared_ptr<value>(new value(document{} << "number" << number << finalize));
			}
		};
	}
}