#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Team : public IEntity {
		public:
			Team(shared_ptr<Entities::Team> item) : IEntity(item->id) {
				number = item->number;
				leadId = item->leadId;
			}

			string number;
			string leadId;
		};
	}
}
