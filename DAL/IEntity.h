#pragma once
#include "common.h"

namespace DAL {
	class IEntity {
	public:
		IEntity() {}

		IEntity(string id) {
			this->id = id;
		}

		string id = "";
	};
}
