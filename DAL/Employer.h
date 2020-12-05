#pragma once
#include "Entity.h"

namespace DAL {
	namespace Entities {
		class Employer : public Entity {
		public:
			Employer(database db, string id, string name) : Entity(db, id) {
				coll = db["employer"];
				this->name = name;
			}
			void setManager(string manager) {
				this->manager = manager;
			}
			void create() override {
				auto doc = bsoncxx::builder::basic::document{};
				doc.append(kvp("name", this->name));
				if (manager != "") {
					doc.append(kvp("manager", oid{string_view{manager}}));
				}
				auto result = coll.insert_one(doc.view());
				id = result->inserted_id().get_oid().value.to_string();
			}
			void update() override {
				auto setDoc = bsoncxx::builder::basic::document{};
				setDoc.append(kvp("name", this->name));
				if (manager != "") {
					setDoc.append(kvp("manager", oid{ string_view{manager} }));
				}
				
				auto doc = bsoncxx::builder::basic::document{};
				doc.append(kvp("$set", setDoc));

				coll.update_one(current(), doc.view());
			}
			void remove() override {}
			string getName() {
				return name;
			}
		private:
			string name;
			string manager;
			vector<string> assistantList;
		};
	}
}
