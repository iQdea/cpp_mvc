#pragma once
#include "EntityList.h"

namespace DAL {
	namespace Entities {
		class TaskList : public EntityList {
		public:
			TaskList(database db) : EntityList(db) {
				coll = db["task"];
			}

			shared_ptr<Entity> getEntity(shared_ptr<view> doc) override {
				string title = (*doc)["title"].get_utf8().value.to_string();
				return shared_ptr<Entity>(new Task(db, "", title));
			}
		};
	}
}
