#pragma once
#include "Entity.h"

namespace DAL {
	namespace Entities {		
		class Task : public Entity {
		public:
			Task(database db, string id, string title);
			void create() override;
			void update() override;
			void remove() override;
			void setTitle(string title);
			string getTitle();
		private:
			string title;
			time_t created;
			time_t modified;
			string assignedTo;
			StatusType status;
			vector<string> modifiedBy;
		};
	}
}
