#pragma once
#include "common.h"
#include <vector>

namespace BLL {
	using namespace std;
	using namespace DAL;
	class ISprintService {
	public:
		// Task logic
		virtual shared_ptr<DTO::Task> addTask(string title) = 0;
		virtual shared_ptr<DTO::Task> selectTask(string id) = 0;
		virtual vector<shared_ptr<DTO::Task>> getUserTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListCreatedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListModifiedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListAssignedToAssistants() = 0;

		// Task assigned logic
		virtual shared_ptr<DTO::TaskAssigned> assignTo(string employeeId) = 0;

		// Task status logic
		virtual shared_ptr<DTO::TaskStatus> setStatus(StatusType status) = 0;

		// Task comment logic
		virtual shared_ptr<DTO::TaskComment> addComment(string comment) = 0;

		// Employer logic
		virtual shared_ptr<DTO::Session> login(string name) = 0;
		virtual shared_ptr<DTO::Employee> addAssistant(int sessionNumber, string name) = 0;
		virtual vector<shared_ptr<DTO::Employee>> getAssistantList() = 0;

		// Employer manager logic
		virtual bool setManager(int sessionNumber, string employeeId) = 0;

		shared_ptr<DTO::Task> task = 0;
		shared_ptr<DTO::Employee> user = 0;
	};
}
