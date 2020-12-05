#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Team {
		public:
			Team(shared_ptr<Entities::Team> team) {
				id = team->getId();
				// number = team->getNumber();
				leadId = team->getLeadId();
			}
			string getLeadId() {
				return leadId;
			}
		private:
			string id;
			string leadId;
		};
	}
}
