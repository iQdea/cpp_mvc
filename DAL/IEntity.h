#pragma once
#include "common.h"

namespace DAL {
	class IEntity abstract {
	public:
		IEntity() {}

		IEntity(string id) {
			this->id = id;
		}

		string id = "";
	};
}
