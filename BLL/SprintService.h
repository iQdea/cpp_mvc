#pragma once
#include "DTO.h"
#include "DAL.h"
#include "ISprintService.h"

namespace BLL {
	using namespace DAL;
	using namespace std;

	class SprintService : public ISprintService {
	public:
		SprintService(Mongo::RepositoryList* repositoryList) {
			this->repositoryList = repositoryList;
		}

		// Task logic
		shared_ptr<DTO::Task> addTask(string title, string descr) override {
			auto repTask = repositoryList->task;

			Entities::Task task(title, descr, currUser->id, getTime());
			task.id = repTask->create(task);

			return make_shared<DTO::Task>(task);
		}

		shared_ptr<DTO::Task> selectTask(string id) override {
			auto repTask = repositoryList->task;
			auto repSession = repositoryList->session;

			repTask->setFilterId(id);
			auto task = repTask->findOne();

			currSession->taskId = id;
			repSession->update(*currSession);
			
			return make_shared<DTO::Task>(*task);
		}
		vector<shared_ptr<DTO::Task>> getUserTaskList() override {
			auto repTask = repositoryList->task;
			repTask->setFilterCreatedBy(currUser->id);

			vector<shared_ptr<DTO::Task>> result;
			auto list = repTask->findAll();
			for (auto item : list) {
				result.push_back(make_shared<DTO::Task>(*item));
			}
			return result;
		}
		vector<shared_ptr<DTO::Task>> getTaskList() override {
			vector<shared_ptr<DTO::Task>> result;
			return result;
		}
		vector<shared_ptr<DTO::Task>> getOpenedTaskList() override {
			auto repTask = repositoryList->task;

			repTask->setFilterStatusNotAssigned((int) StatusType::Open);

			vector<shared_ptr<DTO::Task>> result;
			auto list = repTask->findAll();
			for (auto item : list) {
				result.push_back(make_shared<DTO::Task>(*item));
			}
			return result;
		}
		vector<shared_ptr<DTO::Task>> getAssignedTaskList() override {
			auto repTask = repositoryList->task;

			repTask->setFilterAssignedTo(currUser->id);

			vector<shared_ptr<DTO::Task>> result;
			auto list = repTask->findAll();
			for (auto item : list) {
				result.push_back(make_shared<DTO::Task>(*item));
			}
			return result;
		}

		vector<shared_ptr<DTO::Task>> getTaskListCreatedBetween(time_t start, time_t end) override {
			vector<shared_ptr<DTO::Task>> result;
			return result;
		}
		vector<shared_ptr<DTO::Task>> getTaskListModifiedBetween(time_t start, time_t end) override {
			vector<shared_ptr<DTO::Task>> result;
			return result;
		}
		vector<shared_ptr<DTO::Task>> getTaskListAssignedToAssistants() override {
			vector<shared_ptr<DTO::Task>> result;
			return result;
		}

		// Task assigned logic
		shared_ptr<DTO::TaskAssigned> assignTo(string employeeId) override {
			auto repTask = repositoryList->task;
			auto repTaskAssigned = repositoryList->taskAssigned;

			if (currTask->id != currSession->taskId) {
				throw invalid_argument("Task is not selected");
			}

			string modifiedBy = currUser->id;
			time_t modifiedAt = getTime();
			string assignedTo = employeeId;

			Entities::TaskAssigned taskAssigned(currTask->id, modifiedBy, modifiedAt, assignedTo);
			taskAssigned.id = repTaskAssigned->create(taskAssigned);

			currTask->assignedTo = assignedTo;
			currTask->lastModifiedAt = modifiedAt;
			currTask->lastModifiedBy = modifiedBy;
			repTask->update(*currTask);

			return make_shared<DTO::TaskAssigned>(taskAssigned);
		}

		// Task status logic
		shared_ptr<DTO::TaskStatus> setStatus(StatusType status) override {
			auto repTask = repositoryList->task;
			auto repTaskStatus = repositoryList->taskStatus;

			if (currTask->id != currSession->taskId) {
				throw invalid_argument("Task is not selected");
			}

			string modifiedBy = currUser->id;
			time_t modifiedAt = getTime();

			Entities::TaskStatus taskStatus(currTask->id, modifiedBy, modifiedAt, status);
			taskStatus.id = repTaskStatus->create(taskStatus);

			currTask->status = status;
			currTask->lastModifiedAt = modifiedAt;
			currTask->lastModifiedBy = modifiedBy;
			repTask->update(*currTask);

			return make_shared<DTO::TaskStatus>(taskStatus);
		}

		// Task comment logic
		shared_ptr<DTO::TaskComment> addComment(string comment) override {
			auto repTaskComment = repositoryList->taskComment;

			if (currTask->id != currSession->taskId) {
				throw invalid_argument("Task is not selected");
			}

			string modifiedBy = currUser->id;
			time_t modifiedAt = getTime();

			Entities::TaskComment taskComment(currTask->id, modifiedBy, modifiedAt, comment);
			taskComment.id = repTaskComment->create(taskComment);

			return make_shared<DTO::TaskComment>(taskComment);
		}

		// Employer logic
		virtual void auth(string sessionId) {
			auto repTask = repositoryList->task;
			auto repEmployee = repositoryList->employee;
			auto repSession = repositoryList->session;

			repSession->setFilterId(sessionId);
			currSession = repSession->findOne();
			if (currSession->id != sessionId) {
				throw invalid_argument("Session not found");
			}

			repEmployee->setFilterId(currSession->employeeId);
			currUser = repEmployee->findOne();
			if (currUser->id != currSession->employeeId) {
				throw invalid_argument("User not found");
			}

			repTask->setFilterId(currSession->taskId);
			try {
				currTask = repTask->findOne();
			}
			catch (...) {
				currTask = make_shared<Entities::Task>("", "", "", getTime());
			}
		}
		
		virtual void logout() {
			auto repSession = repositoryList->session;

			repSession->remove(currSession->id);
		}

		shared_ptr<DTO::Session> login(string name) override {
			auto repEmployee = repositoryList->employee;
			auto repSession = repositoryList->session;

			repEmployee->setFilterName(name);
			auto employee = repEmployee->findOne();
			
			Entities::Session session(employee->id, "");
			session.id = repSession->create(session);

			return make_shared<DTO::Session>(session);
		}

		shared_ptr<DTO::Employee> addAssistant(string name) override {
			auto repEmployee = repositoryList->employee;

			string managerId = currUser->id;
			Entities::Employee employee(name, managerId);
			employee.id = repEmployee->create(employee);

			return make_shared<DTO::Employee>(employee);
		}
		
		virtual vector<shared_ptr<DTO::Employee>> getAssistantList() override {
			auto repEmployee = repositoryList->employee;

			repEmployee->setFilterManagerId(currUser->id);
			auto list = repEmployee->findAll();

			vector<shared_ptr<DTO::Employee>> result;
			for (auto item : list) {
				result.push_back(make_shared<DTO::Employee>(*item));
			}
			return result;
		}

		// Employer manager logic
		bool setManager(string employeeId) override {
			auto repEmployee = repositoryList->employee;

			repEmployee->setFilterId(employeeId);
			auto employee = repEmployee->findOne();

			if (employee->id == employeeId) {
				employee->managerId = currUser->id;
				repEmployee->update(*employee);
				
				return true;
			}

			return false;
		}

		virtual vector<shared_ptr<DTO::TaskComment>> getCommentList() override {
			auto repTask = repositoryList->task;
			auto repTaskComment = repositoryList->taskComment;

			if (currTask->id != currSession->taskId) {
				throw invalid_argument("Task is not selected");
			}

			repTaskComment->setFilterTaskId(currTask->id);
			auto list = repTaskComment->findAll();

			vector<shared_ptr<DTO::TaskComment>> result;
			for (auto item : list) {
				result.push_back(make_shared<DTO::TaskComment>(*item));
			}
			return result;
		}

		time_t getTime() {
			return time(0);
			// return time;
		}

	private:
		// time_t time = 0;
		Mongo::RepositoryList* repositoryList;
	};
}