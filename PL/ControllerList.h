#pragma once
#include "Connection.h"
#include "UserController.h"
#include "TaskController.h"
#include <sstream>

using namespace std;
using namespace Controllers;

class ControllerList {
public:
	ControllerList(shared_ptr<Context> context) {
		user = shared_ptr<UserController>(new UserController(context));
		task = shared_ptr<TaskController>(new TaskController(context));
	}

	string route(string request) {
		vector<string> parts;
		stringstream ss(request);
		string part;
		string response = "success:true|";

		while (getline(ss, part, '|')) {
			parts.push_back(part);
		}

		try {
			if (parts.size() >= 3) {
				if (parts[0] == "user") {
					if (parts[1] == "login") {
						string name = parts[2];
						response += user->login(name);
					}
					else if (parts[1] == "assistants") {
						int sessionNumber = stoi(parts[2]);
						response += user->getAssistantList(sessionNumber);
					}
					else if (parts.size() >= 4) {
						int sessionNumber = stoi(parts[2]);
						if (parts[1] == "add") {
							string name = parts[3];
							response += user->add(sessionNumber, name);
						}
						else if (parts[1] == "manager") {
							string employeeId = parts[3];
							response = user->manager(sessionNumber, employeeId);
						}
					}
				}
			}
			if (parts.size() >= 4) {
				int sessionNumber = stoi(parts[2]);
				if (parts[0] == "task") {
					if (parts[1] == "select") {
						string id = parts[3];
						response += task->select(sessionNumber, id);
					}
					else if (parts[1] == "add") {
						string title = parts[3];
						response += task->add(sessionNumber, title);
					}
					else if (parts[1] == "assign") {
						string employeeId = parts[3];
						response = task->assignTo(sessionNumber, employeeId);
					}
					else if (parts[1] == "status") {
						int status = stoi(parts[3]);
						response = task->setStatus(sessionNumber, status);
					}
					else if (parts[1] == "comment") {
						if (parts[3] == "show") {
							response += task->getCommentList(sessionNumber);
						}
						else if (parts[3] == "add") {
							string comment = parts[4];
							response = task->addComment(sessionNumber, comment);
						}
					}
				}
			}
		}
		catch (exception e) {
			response = "success:false";
			cout << e.what() << endl;
		}
		catch (...) {
			response = "success:false";
			cout << "Some error occured" << endl;
		}
		
		return response;
	}

	shared_ptr<UserController> user;
	shared_ptr<TaskController> task;
};
