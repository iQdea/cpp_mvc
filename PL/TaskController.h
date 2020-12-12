#pragma once
#include "IController.h"
#include "ViewModels.h"

namespace Controllers {
	class TaskController : public IController {
	public:
		TaskController(SprintService* sprintService) : IController(sprintService) {}

		string add(string title, string descr) {
			ViewModel::Task response(sprintService->addTask(title, descr));
			return response.str();
		}
		string select(string id) {
			ViewModel::Task response(sprintService->selectTask(id));
			return response.str();
		}
		string assignTo(string id) {
			ViewModel::TaskAssigned response(sprintService->assignTo(id));
			return response.str();
		}
		string assignToMe() {
			ViewModel::TaskAssigned response(sprintService->assignTo(sprintService->currUser->id));
			return response.str();
		}
		string setStatus(int status) {
			ViewModel::TaskStatus response(sprintService->setStatus((StatusType) status));
			return response.str();
		}
		string addComment(string comment) {
			ViewModel::TaskComment response(sprintService->addComment(comment));
			return response.str();
		}
		string getCommentList() {
			string responce = "";
			auto list = sprintService->getCommentList();
			for (auto item : list) {
				ViewModel::TaskComment comment(item);
				if (responce != "") {
					responce += "|";
				}
				responce += comment.str();
			}
			return responce;
		}
		string opened() {
			string responce = "";
			auto list = sprintService->getOpenedTaskList();
			for (auto item : list) {
				ViewModel::Task task(item);
				if (responce != "") {
					responce += "|";
				}
				responce += task.str();
			}
			return responce;
		}
		string assigned() {
			string responce = "";
			auto list = sprintService->getAssignedTaskList();
			for (auto item : list) {
				ViewModel::Task task(item);
				if (responce != "") {
					responce += "|";
				}
				responce += task.str();
			}
			return responce;
		}
	};
}