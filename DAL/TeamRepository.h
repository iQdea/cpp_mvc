#pragma once
#include "common.h"
#include "Team.h"
#include "Repository.h"

namespace DAL {
	namespace Mongo {
		class TeamRepository : public Repository<Team> {
		public:
			TeamRepository(database db) : Repository() {
				coll = db["team"];
			}

			shared_ptr<Team> getEntity(view& doc) override {
				string id = parseOid(doc, "_id");
				int number = parseInt(doc, "number");
				string leadId = parseOid(doc, "leadId");

				return shared_ptr<Team>(new Team(id, number, leadId));
			}

			void setData(basicDoc& doc, shared_ptr<Team> item) override {
				addField<int>(doc, "number", item->number);
				addField<oid>(doc, "leadId", getOid(item->leadId));
			}

			void setFilterNumber(int number) {
				filter = shared_ptr<value>(new value(document{} << "number" << number << finalize));
			}
		};
	}
}