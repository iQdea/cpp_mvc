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

				return make_shared<Team>(id, number, leadId);
			}

			void setData(basicDoc& doc, Team& item) override {
				addField<int>(doc, "number", item.number);
				addField<oid>(doc, "leadId", getOid(item.leadId));
			}

			void setFilterNumber(int number) {
				filter = make_shared<value>(document{} << "number" << number << finalize);
			}
		};
	}
}