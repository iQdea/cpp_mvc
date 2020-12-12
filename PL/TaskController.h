#pragma once
#include "IController.h"
#include "ViewModels.h"

namespace Controllers {
	class TaskController : public IController {
	public:
		TaskController(SprintService* sprintService) : IController(sprintService) {}

		string add(string title, string descr) {
			ViewModel::Task response(*sprintService->addTask(title, descr));
			return response.str();
		}
		string select(string id) {
			ViewModel::Task response(*sprintService->selectTask(id));
			return response.str();
		}
		string assignTo(string id) {
			ViewModel::TaskAssigned response(*sprintService->assignTo(id));
			return response.str();
		}
		string assignToMe() {
			ViewModel::TaskAssigned response(*sprintService->assignTo(sprintService->currUser->id));
			return response.str();
		}
		string setStatus(int status) {
			ViewModel::TaskStatus response(*sprintService->setStatus((StatusType) status));
			return response.str();
		}
		string addComment(string comment) {
			ViewModel::TaskComment response(*sprintService->addComment(comment));
			return response.str();
		}
		string getCommentList() {
			string response = "";
			auto list = sprintService->getCommentList();
			for (auto item : list) {
				ViewModel::TaskComment comment(*item);
				if (response != "") {
					response += "|";
				}
				response += comment.str();
			}
			return response;
		}
		string opened() {
			string response = "";
			auto list = sprintService->getOpenedTaskList();
			for (auto item : list) {
				ViewModel::Task task(*item);
				if (response != "") {
					response += "|";
				}
				response += task.str();
			}
			return response;
		}
		string assigned() {
			string response = "";
			auto list = sprintService->getAssignedTaskList();
			for (auto item : list) {
				ViewModel::Task task(*item);
				if (response != "") {
					response += "|";
				}
				response += task.str();
			}
			return response;
		}

		string changesToday() {
			time_t start;
			time_t end;
			vector<DTO::Task> taskList;
			vector<DTO::TaskStatus> taskListStatus;
			vector<DTO::TaskComment> taskListComment;
			vector<DTO::TaskAssigned> taskListAssigned;

			sprintService->getToday(start, end);
			sprintService->getTaskListHistoryBetween(start, end, 
				taskList, taskListStatus, taskListComment, taskListAssigned);

			string response = "";

			for (auto item : taskList) {
				ViewModel::Task task(item);
				if (response != "") {
					response += "|";
				}
				response += task.str();
			}

			for (auto item : taskListStatus) {
				ViewModel::TaskStatus taskStatus(item);
				if (response != "") {
					response += "|";
				}
				response += taskStatus.str();
			}

			for (auto item : taskListComment) {
				ViewModel::TaskComment taskComment(item);
				if (response != "") {
					response += "|";
				}
				response += taskComment.str();
			}

			for (auto item : taskListAssigned) {
				ViewModel::TaskAssigned taskAssigned(item);
				if (response != "") {
					response += "|";
				}
				response += taskAssigned.str();
			}

			return response;
		}
	};
}