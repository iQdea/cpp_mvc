#pragma once
#include "Controller.h"
#include <string>
using namespace std;

/*
* добавление тимлида
* 
*/

namespace Controllers {
	class UserList : public Controller {
	public:
		UserList(shared_ptr<Context> context) : Controller(context) {
		}
		void getTeamLead() {
			context->teamLead = context->sprintService->getTeamLead();
		}
		void addTeamLead() {
			context->teamLead = context->sprintService->addTeamLead();
		}
		void getAssistantList() {
			context->sprintService->getAssistantList(context->teamLead);
		}
		void addEmployer(string name) {
			context->employer = context->sprintService->addEmployer(name);
		}
	};
}