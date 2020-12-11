#pragma once
#include "IController.h"
#include <string>
#include "ViewModels.h"

using namespace std;

namespace Controllers {
	class UserController : public IController {
	public:
		UserController(shared_ptr<Context> context) : IController(context) {
		}
		void auth(string sessionId) {
			context->sprintService->auth(sessionId);
		}

		string login(string name) {
			ViewModel::Session response(context->sprintService->login(name));
			return response.str();
		}

		string add(string name) {
			ViewModel::Employee response(context->sprintService->addAssistant(name));
			return response.str();
		}

		string manager(string employeeId) {
			if (context->sprintService->setManager(employeeId)) {
				return "success:true";
			}
			else {
				return "success:false";
			}
		}
		string getAssistantList() {
			string responce = "";
			auto list = context->sprintService->getAssistantList();
			for (auto item : list) {
				ViewModel::Employee employee(item);
				if (responce != "") {
					responce += "|";
				}
				responce += employee.str();
			}
			return responce;
		}

		void logout() {
			context->sprintService->logout();
		}
	};
}