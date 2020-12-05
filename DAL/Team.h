#pragma once
#include "Entity.h"

namespace DAL {
	namespace Entities {
		class Team : public Entity {
		public:
			Team(database db, string id, int number, string leadId = "") : Entity(db, id) {
				coll = db["team"];
				this->number = number;
				setLeadId(leadId);
			}
			void create() override {
				auto result = coll.insert_one(document{}
					<< "number" << this->number
					<< "lead" << this->leadId
					<< finalize);
				id = result->inserted_id().get_oid().value.to_string();
			}
			void update() override {
				coll.update_one(current(), document{}
					<< "$set" << open_document
					<< "number" << this->number
					<< "lead" << this->leadId
					<< close_document << finalize);
			}
			void remove() override {}
			string getLeadId() {
				return this->leadId;
			}
			void setLeadId(string leadId) {
				this->leadId = leadId;
			}
		protected:
			int number;
			string leadId;
		};
	}
}

