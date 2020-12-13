#pragma once
#include "IController.h"
#include "ViewModels.h"
#include <string>
using namespace std;

namespace Controllers {
	class UserController : public IController {
	public:
		UserController(SprintService* sprintService) : IController(sprintService) {}

		void auth(string sessionId) {
			sprintService->auth(sessionId);
		}

		string info() {
			DTO::Employee currUser = *sprintService->currUser;
			ViewModel::Employee item(currUser);
			return item.json();
		}

		string login(string name) {
			ViewModel::Session response(*sprintService->login(name));
			return response.str();
		}

		string buildTree(Tree<DTO::Employee>& tree) {
			ViewModel::Employee item(*tree.item);
			string children;
			children = "[";
			for (auto i : tree.children) {
				if (children != "[") {
					children += ",";
				}
				children += buildTree(*i.second);
			}
			children += "]";
			return "{\"item\":" + item.str() + ",\"children\":" + children + "}";
		}

		string tree() {
			Tree<DTO::Employee> tree;
			sprintService->getEmployeeListTree(tree);

			return buildTree(tree);
		}

		string add(string name) {
			ViewModel::Employee response(*sprintService->addAssistant(name));
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
			string response = "";
			auto list = sprintService->getAssistantList();
			for (auto item : list) {
				ViewModel::Employee employee(*item);
				if (response != "") {
					response += "|";
				}
				response += employee.str();
			}
			return response;
		}

		void logout() {
			sprintService->logout();
		}

		void addTime(double hours) {
			sprintService->addTime(hours);
		}
	};
}