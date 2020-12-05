#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Employer {
		public:
			Employer(shared_ptr<Entities::Employer> employer) {
				id = employer->getId();
				name = employer->getName();
			}
			string getId() {
				return id;
			}
			string getName() {
				return name;
			}
			void setAssistantList(vector<shared_ptr<Entities::Entity>> assistantList) {
				this->assistantList = assistantList;
			}
			int getAssistantCount() {
				return this->assistantList.size();
			}
		private:
			string id;
			string name;
			vector<shared_ptr<Entities::Entity>> assistantList;
		};
	}
}
