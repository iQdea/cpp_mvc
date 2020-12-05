#pragma once
#include "common.h"

namespace DAL {
	namespace Entities {
		class Entity {
		public:
			Entity(database db, string id) {
				this->db = db;
				this->id = id;
			}
			virtual void create() = 0;
			virtual void update() = 0;
			virtual void remove() = 0;
			string getId() {
				return id;
			}
			oid getOid() {
				return oid{ string_view{this->id} };
			}
			view_or_value current() {
				return document{} << "_id" << getOid() << finalize;
			}
		protected:
			database db;
			collection coll;
			string id;
		};
	}
}
