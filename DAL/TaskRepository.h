#pragma once
#include "common.h"
#include "Task.h"
#include "Connection.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TaskRepository : public Repository<Task> {
		public:
			TaskRepository(database db) : Repository() {
				coll = db["task"];
			}

			shared_ptr<Task> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				string title = parseString(doc, "title");
				string descr = parseString(doc, "descr");
				string createdBy = parseOid(doc, "createdBy");
				time_t createdAt = parseInt(doc, "createdAt");
				StatusType status = (StatusType) parseInt(doc, "status");
				string assignedTo = parseOid(doc, "assignedTo");
				string lastModifiedBy = parseOid(doc, "lastModifiedBy");
				time_t lastModifiedAt = parseInt(doc, "lastModifiedAt");

				return make_shared<Task>(id, title, descr, createdBy, createdAt, status, assignedTo,
					lastModifiedBy, lastModifiedAt);
			}

			void setData(basicDoc& doc, Task& item) override {
				addField<string>(doc, "title", item.title);
				addField<oid>(doc, "createdBy", getOid(item.createdBy));
				addField<int>(doc, "createdAt", item.createdAt);
				addField<int>(doc, "status", (int)item.status);
				if (item.assignedTo != "") {
					addField<oid>(doc, "assignedTo", getOid(item.assignedTo));
				}
				addField<oid>(doc, "lastModifiedBy", getOid(item.lastModifiedBy));
				addField<int>(doc, "lastModifiedAt", item.lastModifiedAt);
			}

			void setFilterCreatedBy(string createdBy) {
				filter = shared_ptr<value>(new value(document{}
					<< "createdBy" << getOid(createdBy)
				<< finalize));
			}

			void setFilterStatusNotAssigned(int status) {
				filter = shared_ptr<value>(new value(document{}
					<< "status" << status
					<< "assignedTo" << open_document
					<< "$exists" << false
					<< close_document
					<< finalize));
			}

			void setFilterAssignedTo(string assignedTo) {
				filter = shared_ptr<value>(new value(document{}
					<< "assignedTo" << getOid(assignedTo)
					<< finalize));
			}
		};
	}
}