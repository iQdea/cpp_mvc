#pragma once
#include "DTO.h"
#include "DAL.h"

namespace BLL {
	using namespace DAL::Entities;
	using mongocxx::database;

	class SprintService {
	public:
		SprintService(database db) {
			this->db = db;
			employerList = shared_ptr<EmployerList>(new EmployerList(db));
		}
		
		shared_ptr<Team> getTeam() {
			shared_ptr<TeamList> teamList(new TeamList(db));
			teamList->setFilterByNumber(1);
			shared_ptr<Team> team;
			try {
				team = dynamic_pointer_cast<Team>(teamList->findOne());
			}
			catch (...) {
				team = shared_ptr<Team>(new Team(db, "", 1));
				team->create();
			}

			return team;
		}
			
		shared_ptr<DTO::Employer> getTeamLead() {
			shared_ptr<Team> team = getTeam();

			employerList->setFilterById(team->getLeadId());
			shared_ptr<Employer> teamLead = dynamic_pointer_cast<Employer>(employerList->findOne());

			return shared_ptr<DTO::Employer>(new DTO::Employer(teamLead));
		}

		void getAssistantList(shared_ptr<DTO::Employer> employer) {
			employerList->setFilterByManagerId(employer->getId());
			employer->setAssistantList(employerList->findAll());
		}

		shared_ptr<DTO::Employer> addTeamLead() {
			shared_ptr<Team> team = getTeam();

			shared_ptr<Employer> teamLead(new Employer(db, "", "Team Lead"));
			teamLead->create();

			team->setLeadId(teamLead->getId());
			team->update();

			return shared_ptr<DTO::Employer>(new DTO::Employer(teamLead));
		}

		shared_ptr<DTO::Task> addTask(string title) {
			shared_ptr<Task> task(new Task(db, "", title));
			task->create();
			return shared_ptr<DTO::Task>(new DTO::Task(task));
		}

		shared_ptr<DTO::Employer> addEmployer(string name) {
			shared_ptr<Employer> employer(new Employer(db, "", name));
			employer->create();
			return shared_ptr<DTO::Employer>(new DTO::Employer(employer));
		}

		void setManager(string employerId, string managerId) {
			employerList->setFilterById(employerId);
			shared_ptr<Employer> employer = dynamic_pointer_cast<Employer>(employerList->findOne());
			employer->setManager(managerId);
			employer->update();
		}

	private:
		database db;
		shared_ptr<EmployerList> employerList;
	};
}