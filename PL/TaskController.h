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
		string add(int sessionNumber, string title) {
			ViewModel::Task response(context->sprintService->addTask(sessionNumber, title));
			return response.str();
		}
		string select(int sessionNumber, string id) {
			ViewModel::Task response(context->sprintService->selectTask(sessionNumber, id));
			return response.str();
		}
		string assignTo(int sessionNumber, string id) {
			ViewModel::TaskAssigned response(context->sprintService->assignTo(sessionNumber, id));
			return response.str();
		}
		string setStatus(int sessionNumber, int status) {
			ViewModel::TaskStatus response(context->sprintService->setStatus(sessionNumber, (StatusType) status));
			return response.str();
		}
		string addComment(int sessionNumber, string comment) {
			ViewModel::TaskComment response(context->sprintService->addComment(sessionNumber, comment));
			return response.str();
		}
		string getCommentList(int sessionNumber) {
			string responce = "";
			auto list = context->sprintService->getCommentList(sessionNumber);
			for (auto item : list) {
				ViewModel::TaskComment comment(item);
				if (responce != "") {
					responce += "|";
				}
				responce += comment.str();
			}
			return responce;
		}
	};
}