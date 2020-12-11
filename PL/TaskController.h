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
		string add(string title) {
			ViewModel::Task response(context->sprintService->addTask(title));
			return response.str();
		}
		string select(string id) {
			ViewModel::Task response(context->sprintService->selectTask(id));
			return response.str();
		}
		string assignTo(string id) {
			ViewModel::TaskAssigned response(context->sprintService->assignTo(id));
			return response.str();
		}
		string setStatus(int status) {
			ViewModel::TaskStatus response(context->sprintService->setStatus((StatusType) status));
			return response.str();
		}
		string addComment(string comment) {
			ViewModel::TaskComment response(context->sprintService->addComment(comment));
			return response.str();
		}
		string getCommentList() {
			string responce = "";
			auto list = context->sprintService->getCommentList();
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