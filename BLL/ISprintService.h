#pragma once
#include "common.h"
#include <vector>

namespace BLL {
	using namespace std;
	using namespace DAL;
	class ISprintService {
	public:
		// Task logic
		virtual shared_ptr<DTO::Task> addTask(string title, string descr) = 0;
		virtual shared_ptr<DTO::Task> selectTask(string id) = 0;
		virtual vector<shared_ptr<DTO::Task>> getUserTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getOpenedTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTodoTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getAssignedTaskList() = 0;
		virtual vector<shared_ptr<DTO::TaskComment>> getCommentList() = 0;
		virtual void getEmployeeListTree(Tree<DTO::Employee>& tree) = 0;
		virtual void getTaskListHistoryBetween(time_t start, time_t end,
			vector<DTO::Task>& taskList,
			vector<DTO::TaskStatus>& taskStatusList,
			vector<DTO::TaskComment>& taskCommentList,
			vector<DTO::TaskAssigned>& taskAssignedList) = 0;

		// Task assigned logic
		virtual shared_ptr<DTO::TaskAssigned> assignTo(string employeeId) = 0;

		// Task status logic
		virtual shared_ptr<DTO::TaskStatus> setStatus(TaskStatusEnum status) = 0;

		// Task comment logic
		virtual shared_ptr<DTO::TaskComment> addComment(string comment) = 0;

		virtual shared_ptr<DTO::Report> getDailyReport() = 0;
		virtual shared_ptr<DTO::Report> getSprintReport() = 0;
		virtual shared_ptr<DTO::Report> putReport(string reportId, string text) = 0;
		virtual shared_ptr<DTO::Report> markReportReady(string reportId) = 0;
		
		// Employer logic
		virtual void auth(string sessionId) = 0;
		virtual void logout() = 0;
		virtual shared_ptr<DTO::Session> login(string name) = 0;
		virtual shared_ptr<DTO::Employee> addAssistant(string name) = 0;
		virtual vector<shared_ptr<DTO::Employee>> getAssistantList() = 0;

		// Employer manager logic
		virtual bool setManager(string employeeId) = 0;

		shared_ptr<Entities::Session> currSession = 0;
		shared_ptr<Entities::Task> currTask = 0;
		shared_ptr<Entities::Employee> currUser = 0;
	};
}
