#pragma once
#include "Connection.h"
#include "UserController.h"
#include <sstream>

using namespace std;
using namespace Controllers;

class ControllerList {
public:
	ControllerList(shared_ptr<Context> context) {
		user = shared_ptr<UserController>(new UserController(context));
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
};
