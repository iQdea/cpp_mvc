#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Team : public IEntity {
		public:
			Team(string id, int number, string leadId = "") : IEntity(id) {
				this->number = number;
				this->leadId = leadId;
			}

			int number;
			string leadId;
		};
	}
}

