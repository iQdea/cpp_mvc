#pragma once
#include "common.h"

namespace DAL {
	class IEntity {
	public:
		IEntity() {}

		IEntity(string id) {
			setId(id);
		}
		string getId() {
			return id;
		}
		void setId(string id) {
			this->id = id;
		}

		string id = "";
	};
}
