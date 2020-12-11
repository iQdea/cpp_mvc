#pragma once
#include "common.h"
#include <vector>

namespace BLL {
	using namespace std;
	using namespace DAL;
	class ISprintService {
	public:
		// Task logic
		virtual shared_ptr<DTO::Task> addTask(int sessionNumber, string title) = 0;
		virtual shared_ptr<DTO::Task> selectTask(int sessionNumber, string id) = 0;
		virtual vector<shared_ptr<DTO::Task>> getUserTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskList() = 0;
		virtual vector<shared_ptr<DTO::TaskComment>> getCommentList(int sessionNumber) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListCreatedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListModifiedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListAssignedToAssistants() = 0;

		// Task assigned logic
		virtual shared_ptr<DTO::TaskAssigned> assignTo(int sesionNumber, string employeeId) = 0;

		// Task status logic
		virtual shared_ptr<DTO::TaskStatus> setStatus(int sessionNumber, StatusType status) = 0;

		// Task comment logic
		virtual shared_ptr<DTO::TaskComment> addComment(int sessionNumber, string comment) = 0;

		// Employer logic
		virtual shared_ptr<DTO::Session> login(string name) = 0;
		virtual shared_ptr<DTO::Employee> addAssistant(int sessionNumber, string name) = 0;
		virtual vector<shared_ptr<DTO::Employee>> getAssistantList(int sessionNumber) = 0;

		// Employer manager logic
		virtual bool setManager(int sessionNumber, string employeeId) = 0;

		shared_ptr<DTO::Task> task = 0;
		shared_ptr<DTO::Employee> user = 0;
	};
}
