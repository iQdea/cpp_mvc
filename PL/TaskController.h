#pragma once
#include "IController.h"
#include <string>
#include "ViewModels.h"
using namespace std;

namespace Controllers {
	class TaskController : public IController {
	public:
		TaskController(shared_ptr<Context> context) : IController(context) {
		}
		string addTask(int sessionNumber, string title) {
			ViewModel::Task response(context->sprintService->addTask(sessionNumber, title));
			return response.str();
		}
		string selectTask(int sessionNumber, string id) {
			ViewModel::Task response(context->sprintService->selectTask(sessionNumber, id));
			return response.str();
		}
	};
}