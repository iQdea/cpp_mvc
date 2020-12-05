#pragma once
#include "Controller.h"
#include <string>
using namespace std;

namespace Controllers {
	class User : public Controller {
	public:
		User(shared_ptr<Context> context) : Controller(context) {
		}
		void login(shared_ptr<DTO::Employer> user) {
			context->user = user;
		}
		void logout() {}
		void setManager(shared_ptr<DTO::Employer> manager) {
			context->sprintService->setManager(context->user->getId(), manager->getId());
		}
	};
}