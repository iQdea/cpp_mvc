#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Task {
		public:
			Task(shared_ptr<Entities::Task> task) {
				id = task->getId();
				title = task->getTitle();
			}
			string getTitle() {
				return title;
			}
		private:
			shared_ptr<Entities::Task> task;
			string id;
			string title;
		};
	}
}
