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
		string login(string name) {
			ViewModel::Session response(context->sprintService->login(name));
			return response.str();
		}

		string add(int sessionNumber, string name) {
			ViewModel::Employee response(context->sprintService->addAssistant(sessionNumber, name));
			return response.str();
		}

		string manager(int sessionNumber, string employeeId) {
			if (context->sprintService->setManager(sessionNumber, employeeId)) {
				return "success:true";
			}
			else {
				return "success:false";
			}
		}
		string getAssistantList(int sessionNumber) {
			string responce = "";
			auto list = context->sprintService->getAssistantList(sessionNumber);
			for (auto item : list) {
				ViewModel::Employee employee(item);
				if (responce != "") {
					responce += "|";
				}
				responce += employee.str();
			}
			return responce;
		}

		void logout() {}
	};
}