#pragma once
#include "Connection.h"
#include "UserController.h"
#include "TaskController.h"
#include "ReportController.h"
#include <sstream>

using namespace std;
using namespace Controllers;

class ControllerList {
public:
	ControllerList(SprintService* sprintService) {
		user = make_shared<UserController>(sprintService);
		task = make_shared<TaskController>(sprintService);
		report = make_shared<ReportController>(sprintService);
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
			if (parts.size() == 3 && parts[0] == "user" && parts[1] == "login") {
				string name = parts[2];
				response += user->login(name);
			}
			else if (parts.size() >= 3) {
				string sessionId = parts[0];
				user->auth(sessionId);

				if (parts[1] == "time") {
					if (parts.size() == 4 && parts[2] == "add") {
						double hours = stod(parts[3]);
						user->addTime(hours);
						response = "success:true";
					}
				}
				else if (parts[1] == "user") {
					if (parts.size() == 3 && parts[2] == "info") {
						response = user->info();
					}
					else if (parts.size() == 3 && parts[2] == "tree") {
						response += user->tree();						
					}
					else if (parts.size() == 3 && parts[2] == "logout") {
						user->logout();
						response = "success:true";
					}
					else if (parts.size() == 3 && parts[2] == "assistants") {
						response += user->getAssistantList();
					}
					else if (parts.size() == 4 && parts[2] == "add") {
						string name = parts[3];
						response += user->add(name);
					}
					else if (parts.size() == 4 && parts[2] == "manager") {
						string employeeId = parts[3];
						response = user->manager(employeeId);
					}
					else throw invalid_argument("Route not found");
				}
				else if (parts[1] == "report") {
					if (parts.size() == 3 && parts[2] == "daily") {
						response = report->daily();
					} 
					else if (parts.size() == 3 && parts[2] == "sprint") {
						response = report->sprint();
					}
					else if (parts.size() == 5 && parts[2] == "put") {
						string reportId = parts[3];
						string text = parts[4];
						response = report->put(reportId, text);
					}
					else if (parts.size() == 4 && parts[2] == "ready") {
						string reportId = parts[3];
						response = report->ready(reportId);
					}
					else throw invalid_argument("Route not found");
				}
				else if (parts[1] == "task") {
					if (parts.size() == 3 && parts[2] == "info") {
						response = task->info();
					}
					else if (parts.size() == 3 && parts[2] == "today") {
						response += task->changesToday();
					}
					else if (parts.size() == 3 && parts[2] == "opened") {
						response += task->opened();
					}
					else if (parts.size() == 3 && parts[2] == "todo") {
						response += task->todo();
					}
					else if (parts.size() == 3 && parts[2] == "assigned") {
						response += task->assigned();
					}
					else if (parts.size() == 4 && parts[2] == "select") {
						string taskId = parts[3];
						response += task->select(taskId);
					}
					else if (parts.size() == 5 && parts[2] == "add") {
						string title = parts[3];
						string descr = parts[4];
						response += task->add(title, descr);
					}
					else if (parts.size() == 4 && parts[2] == "assign") {
						string employeeId = parts[3];
						response = task->assignTo(employeeId);
					}
					else if (parts.size() == 3 && parts[2] == "assign") {
						response = task->assignToMe();
					}
					else if (parts.size() == 4 && parts[2] == "status") {
						int status = stoi(parts[3]);
						response = task->setStatus(status);
					}
					else if (parts[2] == "comment") {
						if (parts.size() == 4 && parts[3] == "show") {
							response += task->getCommentList();
						}
						else if (parts.size() == 5 && parts[3] == "add") {
							string comment = parts[4];
							response = task->addComment(comment);
						}
						else throw invalid_argument("Route not found");
					}
					else throw invalid_argument("Route not found");
				}
				else throw invalid_argument("Route not found");
			}
			else throw invalid_argument("Route not found");
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
	shared_ptr<ReportController> report;
};
