#pragma once
#include "common.h"
#include "EntityList.h"
#include "Team.h"

namespace DAL {
	namespace Entities {
		class TeamList : public EntityList {
		public:
			TeamList(database db) : EntityList(db) {
				coll = db["team"];
			}

			shared_ptr<Entity> getEntity(shared_ptr<view> doc) override {

				string id;
				int number;
				string leadId;
				
				try { id = (*doc)["_id"].get_oid().value.to_string(); }
				catch (...) { id = ""; }

				try { number = (*doc)["number"].get_int32().value; }
				catch (...) { number = 0; }

				try { leadId = (*doc)["lead"].get_utf8().value.to_string(); }
				catch (...) { leadId = ""; }

				return shared_ptr<Entity>(new Team(db, id, number, leadId));
			}

			void setFilterByNumber(int number) {
				filter = shared_ptr<value>(new value(document{} << "number" << number << finalize));
			}
		};
	}
}
