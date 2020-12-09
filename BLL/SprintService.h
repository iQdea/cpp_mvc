#pragma once
#include "DTO.h"
#include "DAL.h"
#include "ISprintService.h"

namespace BLL {
	using namespace DAL;
	//using namespace DAL::Entities;
	using namespace std;

	class SprintService : ISprintService {
	public:
		SprintService(shared_ptr<Mongo::RepositoryList> repositoryList) {
			this->repositoryList = repositoryList;
			//employerList = shared_ptr<EmployerList>(new EmployerList(db));
		}
		// Task logic
		shared_ptr<DTO::Task> addTask(string title) override {
			checkUser();
			auto repTask = repositoryList->getTask();
			shared_ptr<Entities::Task> task(new Entities::Task(title, user->id, getTime()));
			task->setId(repTask->create(task));
			return shared_ptr<DTO::Task>(new DTO::Task(task));
		}
		shared_ptr<DTO::Task> selectTask(string id) override {
			auto repTask = repositoryList->getTask();
			repTask->setFilterId(id);
			auto task = repTask->findOne();
			this->task = shared_ptr<DTO::Task>(new DTO::Task(task));
			return this->task;
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
		virtual vector<shared_ptr<DTO::Task>> getTaskList() = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListCreatedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListModifiedBetween(time_t start, time_t end) = 0;
		virtual vector<shared_ptr<DTO::Task>> getTaskListAssignedToAssistants() = 0;

		// Task assigned logic
		virtual DTO::TaskAssigned assignTo(string employeeId) = 0;

		// Task status logic
		virtual DTO::TaskStatus setStatus(StatusType status) = 0;

		// Task comment logic
		virtual DTO::TaskComment addComment(string comment) = 0;

		// Employer logic
		virtual shared_ptr<DTO::Employee> login(string name) = 0;
		virtual shared_ptr<DTO::Employee> addAssistant(string name) = 0;
		virtual vector<shared_ptr<DTO::Employee>> getAssistantList() = 0;

		// Employer manager logic
		virtual void setManager(string managerId) = 0;

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
	};
}