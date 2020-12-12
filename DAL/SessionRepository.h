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
				string employeeId = parseOid(doc, "employeeId");
				string taskId = parseOid(doc, "taskId");

				return make_shared<Session>(id, employeeId, taskId);
			}

			void setData(basicDoc& doc, Session& item) override {
				addField<oid>(doc, "employeeId", getOid(item.employeeId));
				addField<oid>(doc, "taskId", getOid(item.taskId));
			}
		};
	}
}