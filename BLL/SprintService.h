#pragma once
#include "DTO.h"
#include "DAL.h"
#include "Tree.h"
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

			repTask->setFilterStatusNotAssigned((int)TaskStatusEnum::Open);

			vector<shared_ptr<DTO::Task>> result;
			auto list = repTask->findAll();
			for (auto item : list) {
				result.push_back(make_shared<DTO::Task>(*item));
			}
			return result;
		}
		vector<shared_ptr<DTO::Task>> getTodoTaskList() override {
			auto repTask = repositoryList->task;

			repTask->setFilterAssignedTo(currUser->id);

			vector<shared_ptr<DTO::Task>> result;
			auto list = repTask->findAll();
			for (auto item : list) {
				if (item->status != TaskStatusEnum::Resolved) {
					result.push_back(make_shared<DTO::Task>(*item));
				}
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
		void getTaskListHistoryBetween(time_t start, time_t end,
			vector<DTO::Task>& taskList,
			vector<DTO::TaskStatus>& taskStatusList,
			vector<DTO::TaskComment>& taskCommentList,
			vector<DTO::TaskAssigned>& taskAssignedList) override
		{
			auto repTask = repositoryList->task;
			auto repTaskStatus = repositoryList->taskStatus;
			auto repTaskComment = repositoryList->taskComment;
			auto repTaskAssigned = repositoryList->taskAssigned;

			repTask->setFilterCreatedByBetween(currUser->id, start, end);
			auto list1 = repTask->findAll();
			for (auto item : list1) {
				taskList.push_back(DTO::Task(*item));
			}

			repTaskStatus->setFilterModifiedByBetween(currUser->id, start, end);
			auto list2 = repTaskStatus->findAll();
			for (auto item : list2) {
				taskStatusList.push_back(DTO::TaskStatus(*item));
			}

			repTaskComment->setFilterModifiedByBetween(currUser->id, start, end);
			auto list3 = repTaskComment->findAll();
			for (auto item : list3) {
				taskCommentList.push_back(DTO::TaskComment(*item));
			}

			repTaskAssigned->setFilterAssignedToBetween(currUser->id, start, end);
			auto list4 = repTaskAssigned->findAll();
			for (auto item : list4) {
				taskAssignedList.push_back(DTO::TaskAssigned(*item));
			}
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
		shared_ptr<DTO::TaskStatus> setStatus(TaskStatusEnum status) override {
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

		// Employee and session logic
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
		virtual void addTime(float hours) {
			auto repSession = repositoryList->session;

			currSession->shiftHours += hours;
			repSession->update(*currSession);
		}
		time_t getTime() {
			return time(0) + (int)(currSession->shiftHours * 3600);
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
		void buildEmployeeTree(map<string, bool>& haveSeen, Tree<DTO::Employee>& tree, shared_ptr<DTO::Employee> root) {
			auto repEmployee = repositoryList->employee;
			tree.item = root;

			repEmployee->setFilterManagerId(root->id);
			auto list = repEmployee->findAll();

			for (auto item : list) {
				if (!haveSeen[item->id]) {
					haveSeen[item->id] = true;
					tree.children[item->id] = make_shared<Tree<DTO::Employee>>();
					buildEmployeeTree(haveSeen, *tree.children[item->id], make_shared<DTO::Employee>(*item));
				}
			}
		}
		shared_ptr<Entities::Employee> getTeamLead() {
			auto repEmployee = repositoryList->employee;
			auto root = currUser;

			map<string, bool> haveSeen;
			haveSeen[root->id] = true;

			while (root->managerId != "" && !haveSeen[root->managerId]) {
				haveSeen[root->managerId] = true;
				repEmployee->setFilterId(root->managerId);
				auto item = repEmployee->findOne();
				if (root->managerId == item->id) {
					root = item;
				}
				else break;
			}

			return root;
		}
		void getEmployeeListTree(Tree<DTO::Employee>& tree) override {
			auto repEmployee = repositoryList->employee;

			auto root = getTeamLead();

			map<string, bool> haveSeen;
			haveSeen[root->id] = true;

			buildEmployeeTree(haveSeen, tree, make_shared<DTO::Employee>(*root));
		}
		bool setManager(string employeeId) override {
			auto repEmployee = repositoryList->employee;
			
			auto root = currUser;

			map<string, bool> haveSeen;
			haveSeen[root->id] = true;

			// Check that tree of employees will stay a tree
			while (root->managerId != "" && !haveSeen[root->managerId]) {
				haveSeen[root->managerId] = true;
				repEmployee->setFilterId(root->managerId);
				auto item = repEmployee->findOne();
				if (root->managerId == item->id) {
					root = item;
				}
				else break;
			}

			for (auto i : haveSeen) {
				if (employeeId == i.first) {
					throw invalid_argument("Can not set myself as a manager for this employee");
				}
			}

			repEmployee->setFilterId(employeeId);
			auto employee = repEmployee->findOne();

			if (employee->id == employeeId) {
				employee->managerId = currUser->id;
				repEmployee->update(*employee);

				return true;
			}

			return false;
		}

		// Report logic
		shared_ptr<DTO::Report> getSprintReport() override {
			auto repReport = repositoryList->report;

			repReport->setFilterTypeStatusCreatedBy(ReportTypeEnum::Sprint, ReportStatusEnum::Draft, currUser->id);
			try {
				auto report = repReport->findOne();
				return make_shared<DTO::Report>(*report);
			}
			catch (...) {
				/* Realize validation
				* team lead should start sprint (get createdAt of his report)
				* check that we have not report after createdAt time yet
				*/
				auto root = getTeamLead();
				time_t sprintCreated = 0;

				if (root->id != currUser->id) {
					repReport->setFilterTypeStatusCreatedBy(ReportTypeEnum::Sprint, ReportStatusEnum::Draft, root->id);
					try {
						auto rootReport = repReport->findOne();
						sprintCreated = rootReport->createdAt;
					}
					catch (...) {
						throw invalid_argument("At first team lead should create draft of sprint report");
					}
				}

				bool ok = true;
				if (root->id != currUser->id) {
					try {
						repReport->setFilterTypeCreatedByBetween(ReportTypeEnum::Sprint, currUser->id, sprintCreated, getTime());
						auto report = repReport->findOne();
						ok = false;
					}
					catch (...) {}
				}

				if (ok) {
					Entities::Report report(currUser->id, getTime(), ReportTypeEnum::Sprint);
					report.id = repReport->create(report);
					return make_shared<DTO::Report>(report);
				}
				else {
					throw invalid_argument("Your current sprint report marked as ready");
				}				
			}
		}
		shared_ptr<DTO::Report> getDailyReport() override {
			time_t start;
			time_t end;
			auto repReport = repositoryList->report;

			getToday(start, end);
			repReport->setFilterTypeCreatedByBetween(ReportTypeEnum::Daily, currUser->id, start, end);
			
			try {
				auto report = repReport->findOne();
				return make_shared<DTO::Report>(*report);
			}
			catch (...) {
				Entities::Report report(currUser->id, getTime());
				report.id = repReport->create(report);
				
				return make_shared<DTO::Report>(report);
			}
		}
		shared_ptr<DTO::Report> putReport(string reportId, string text) override {
			auto repReport = repositoryList->report;
			repReport->setFilterId(reportId);
			auto report = repReport->findOne();
			if (report->createdBy != currUser->id) {
				throw invalid_argument("Access denied for this report");
			}
			if (report->status == ReportStatusEnum::Ready) {
				throw invalid_argument("Report is marked as ready");
			}
			report->lastModifiedAt = getTime();
			report->text = text;
			repReport->update(*report);

			return make_shared<DTO::Report>(*report);
		}
		shared_ptr<DTO::Report> markReportReady(string reportId) override {
			auto repReport = repositoryList->report;
			repReport->setFilterId(reportId);
			auto report = repReport->findOne();

			if (report->createdBy != currUser->id) {
				throw invalid_argument("Access denied for this report");
			}
			if (report->status == ReportStatusEnum::Ready) {
				throw invalid_argument("Report is marked as ready");
			}
			report->status = ReportStatusEnum::Ready;
			repReport->update(*report);

			return make_shared<DTO::Report>(*report);
		}
		vector<shared_ptr<DTO::Report>> getReportList(ReportTypeEnum type) {
			auto repReport = repositoryList->report;

			auto list = getAssistantList();
			vector<shared_ptr<DTO::Report>> result;

			if (type == ReportTypeEnum::Daily) {
				time_t start;
				time_t end;
				getToday(start, end);
				for (auto item : list) {
					repReport->setFilterTypeCreatedByBetween(type, item->id, start, end);
					try {
						auto report = repReport->findOne();
						result.push_back(make_shared<DTO::Report>(*report));
					}
					catch (...) {}
				}
			}
			else {
				for (auto item : list) {
					repReport->setFilterTypeStatusCreatedBy(ReportTypeEnum::Sprint, ReportStatusEnum::Draft, item->id);
					try {
						auto report = repReport->findOne();
						result.push_back(make_shared<DTO::Report>(*report));
					}
					catch (...) {}
				}
			}

			return result;
		}
		void getToday(time_t& start, time_t& end) {
			time_t currTime = getTime();
			struct tm t;
			localtime_s(&t, &currTime);
			t.tm_hour = 0;
			t.tm_min = 0;
			t.tm_sec = 0;
			start = mktime(&t);
			end = start + 24 * 3600;
		} 

	private:
		// time_t time = 0;
		Mongo::RepositoryList* repositoryList;
	};
}