#pragma once
#include "DTO.h"
#include "DAL.h"
#include "ISprintService.h"

namespace BLL {
	using namespace DAL;
	//using namespace DAL::Entities;
	using namespace std;

	class SprintService : public ISprintService {
	public:
		SprintService(shared_ptr<Mongo::RepositoryList> repositoryList) {
			this->repositoryList = repositoryList;
			//employerList = shared_ptr<EmployerList>(new EmployerList(db));
		}
		// Task logic
		shared_ptr<DTO::Task> addTask(int sessionNumber, string title) override {
			auto repTask = repositoryList->task;
			auto repSession = repositoryList->session;

			repSession->setFilterNumber(sessionNumber);
			auto session = repSession->findOne();

			shared_ptr<Entities::Task> task(new Entities::Task(title, session->employeeId, getTime()));
			task->setId(repTask->create(task));

			return shared_ptr<DTO::Task>(new DTO::Task(task));
		}

		shared_ptr<DTO::Task> selectTask(int sessionNumber, string id) override {
			auto repTask = repositoryList->task;
			auto repSession = repositoryList->session;

			repSession->setFilterNumber(sessionNumber);
			auto session = repSession->findOne();

			repTask->setFilterId(id);
			auto task = repTask->findOne();

			session->taskId = id;
			repSession->update(session);
			
			return shared_ptr<DTO::Task>(new DTO::Task(task));
		}
		vector<shared_ptr<DTO::Task>> getUserTaskList() override {
			checkUser();
			auto repTask = repositoryList->getTask();
			repTask->setFilterCreatedBy(user->id);

			vector<shared_ptr<DTO::Task>> result;
			auto taskList = repTask->findAll();
			for (auto task : taskList) {
				result.push_back(shared_ptr<DTO::Task>(new DTO::Task(task)));
			}
			return result;
		}
		vector<shared_ptr<DTO::Task>> getTaskList() override {
			vector<shared_ptr<DTO::Task>> result;
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
		shared_ptr<DTO::TaskAssigned> assignTo(int sesionNumber, string employeeId) override {
			auto repTask = repositoryList->task;
			auto repSession = repositoryList->session;
			auto repTaskAssigned = repositoryList->taskAssigned;

			repSession->setFilterNumber(sessionNumber);
			auto session = repSession->findOne();

			repTask->setFilterId(session->taskId);
			auto task = repTask->findOne();

			string modifiedBy = session->employeeId;
			time_t modifiedAt = getTime();
			string assignedTo = employeeId;

			shared_ptr<Entities::TaskAssigned> taskAssigned(new Entities::TaskAssigned(task->id,modifiedBy,modifiedAt,assignedTo));
			taskAssigned->setId(repTaskAssigned->create(taskAssigned));

			return shared_ptr<DTO::TaskAssigned>();
		}

		// Task status logic
		shared_ptr<DTO::TaskStatus> setStatus(StatusType status) override {
			return shared_ptr<DTO::TaskStatus>();
		}

		// Task comment logic
		shared_ptr<DTO::TaskComment> addComment(string comment) override {
			return shared_ptr<DTO::TaskComment>();
		}

		// Employer logic
		shared_ptr<DTO::Session> login(string name) override {
			auto repEmployee = repositoryList->employee;
			auto repSession = repositoryList->session;

			repEmployee->setFilterName(name);
			auto employee = repEmployee->findOne();
			
			int sessionNumber = 1;
			repSession->setSortNumberDesc();
			try {
				auto lastSession = repSession->findOne();
				sessionNumber = lastSession->number + 1;
			} catch (...) {}

			shared_ptr<Entities::Session> session(new Entities::Session(sessionNumber, employee->id, ""));
			session->setId(repSession->create(session));

			return shared_ptr<DTO::Session>(new DTO::Session(session));
		}
		shared_ptr<DTO::Employee> addAssistant(int sessionNumber, string name) override {
			auto repEmployee = repositoryList->employee;
			auto repSession = repositoryList->session;

			repSession->setFilterNumber(sessionNumber);
			auto session = repSession->findOne();

			string managerId = session->employeeId;
			shared_ptr<Entities::Employee> employee(new Entities::Employee(name, managerId));
			employee->setId(repEmployee->create(employee));

			return shared_ptr<DTO::Employee>(new DTO::Employee(employee));
		}
		vector<shared_ptr<DTO::Employee>> getAssistantList() override {
			vector<shared_ptr<DTO::Employee>> result;
			return result;
		}

		// Employer manager logic
		bool setManager(int sessionNumber, string employeeId) override {
			auto repEmployee = repositoryList->employee;
			auto repSession = repositoryList->session;

			repSession->setFilterNumber(sessionNumber);
			auto session = repSession->findOne();

			repEmployee->setFilterId(employeeId);
			auto employee = repEmployee->findOne();

			// ищем себя
			repEmployee->setFilterId(session->employeeId);
			auto manager = repEmployee->findOne();

			if (employee->id != "" && manager->id != "") {
				employee->managerId = manager->id;
				repEmployee->update(employee);
				
				return true;
			}

			return false;
		}

		void test1() {
			// добавить задачу
			auto repTask = repositoryList->getTask();
			shared_ptr<Entities::Task> task1(new Entities::Task{"Title 21", "", time});
			task1->setId(repTask->create(task1));
			auto tasks = repTask->findAll();
			for (auto task : tasks) {
				repTask->remove(task->id);
			}
		}

		
		//shared_ptr<Team> getTeam() {
		//	shared_ptr<TeamList> teamList(new TeamList(db));
		//	teamList->setFilterByNumber(1);
		//	shared_ptr<Team> team;
		//	try {
		//		team = dynamic_pointer_cast<Team>(teamList->findOne());
		//	}
		//	catch (...) {
		//		team = shared_ptr<Team>(new Team(db, "", 1));
		//		team->create();
		//	}

		//	return team;
		//}
		//	
		//shared_ptr<DTO::Employer> getTeamLead() {
		//	shared_ptr<Team> team = getTeam();

		//	employerList->setFilterById(team->getLeadId());
		//	shared_ptr<Employer> teamLead = dynamic_pointer_cast<Employer>(employerList->findOne());

		//	return shared_ptr<DTO::Employer>(new DTO::Employer(teamLead));
		//}

		//void getAssistantList(shared_ptr<DTO::Employer> employer) {
		//	employerList->setFilterByManagerId(employer->getId());
		//	employer->setAssistantList(employerList->findAll());
		//}

		//shared_ptr<DTO::Employer> addTeamLead() {
		//	shared_ptr<Team> team = getTeam();

		//	shared_ptr<Employer> teamLead(new Employer(db, "", "Team Lead"));
		//	teamLead->create();

		//	team->setLeadId(teamLead->getId());
		//	team->update();

		//	return shared_ptr<DTO::Employer>(new DTO::Employer(teamLead));
		//}

		//shared_ptr<DTO::Task> addTask(string title) {
		//	shared_ptr<Task> task(new Task(db, "", title));
		//	task->create();
		//	return shared_ptr<DTO::Task>(new DTO::Task(task));
		//}

		//shared_ptr<DTO::Employer> addEmployer(string name) {
		//	shared_ptr<Employer> employer(new Employer(db, "", name));
		//	employer->create();
		//	return shared_ptr<DTO::Employer>(new DTO::Employer(employer));
		//}

		//void setManager(string employerId, string managerId) {
		//	employerList->setFilterById(employerId);
		//	shared_ptr<Employer> employer = dynamic_pointer_cast<Employer>(employerList->findOne());
		//	employer->setManager(managerId);
		//	employer->update();
		//}
		time_t getTime() {
			return time;
		}

		time_t time;
	private:
		void checkUser() {
			if (!user) {
				throw invalid_argument("user is not selected");
			}
		}

		shared_ptr<Mongo::RepositoryList> repositoryList;
		//shared_ptr<EmployerList> employerList;
		int sessionNumber = 0;
	};
}