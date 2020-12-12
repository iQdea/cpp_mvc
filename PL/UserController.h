#pragma once
#include "IController.h"
#include <string>
#include "ViewModels.h"

using namespace std;

namespace Controllers {
	class UserController : public IController {
	public:
		UserController(SprintService* sprintService) : IController(sprintService) {}

		void auth(string sessionId) {
			sprintService->auth(sessionId);
		}

		string login(string name) {
			ViewModel::Session response(sprintService->login(name));
			return response.str();
		}

		string add(string name) {
			ViewModel::Employee response(sprintService->addAssistant(name));
			return response.str();
		}

		string manager(string employeeId) {
			if (sprintService->setManager(employeeId)) {
				return "success:true";
			}
			else {
				return "success:false";
			}
		}
		string getAssistantList() {
			string responce = "";
			auto list = sprintService->getAssistantList();
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
			sprintService->logout();
		}
	};
}