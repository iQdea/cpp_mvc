#include "DAL.h"
#include "BLL.h"
#include <iostream>
#include "UserList.h"
#include "User.h"
#include "Task.h"
#include "Context.h"

// https://github.com/Microsoft/vcpkg

using namespace std;
using namespace DAL;
using namespace BLL;

const string employerName[7] = { 
	"Steve Mathews", "Mark Smith", "Ann Philip", "Julie Ponds", "Michael Lans", "Susan Boyle", 
	"Sophie Cyrus" 
};

int main()
{
	string url = "mongodb+srv://qdea:qdea12345@cluster0.oeakp.mongodb.net/sprint?retryWrites=true&w=majority";
	shared_ptr<Mongo::RepositoryList> repositoryList(new Mongo::RepositoryList(url));

	shared_ptr<SprintService> sprintService(new SprintService(repositoryList));
	sprintService->test1();

	//shared_ptr<Context> context(new Context(sprintService));
	//shared_ptr<Controllers::UserList> userListCtrl(new Controllers::UserList(context));
	//shared_ptr<Controllers::User> userCtrl(new Controllers::User(context));
	//shared_ptr<Controllers::Task> taskCtrl(new Controllers::Task(context));

	//try {
	//	userListCtrl->getTeamLead();
	//}
	//catch (...) {
	//	userListCtrl->addTeamLead();
	//}
	//
	//userCtrl->login(context->teamLead);
	//userListCtrl->getAssistantList();
	//if (context->teamLead->getAssistantCount() == 0) {
	//	for (int i = 0; i < 7; i++) {
	//		userListCtrl->addEmployer(employerName[i]);
	//		userCtrl->login(context->employer);
	//		userCtrl->setManager(context->teamLead);
	//		userCtrl->login(context->teamLead);
	//	}
	//}

	//taskCtrl->add("Task 1");
	//userCtrl->logout();

	//shared_ptr<Entities::Task> taskEntity(new Entities::Task(db, "", "Task 3"));
	//taskEntity->create();
	//cout << taskEntity->getId();
	//taskEntity->setTitle("Task 2");
	//taskEntity->update();
	//shared_ptr<Entities::EmployerList> employerList(new Entities::EmployerList(db));
	//employerList->setFilterByName("Susan Boyle");
	//shared_ptr<Entities::Employer> employer = dynamic_pointer_cast<Entities::Employer>(employerList->findOne());
	//auto list = employerList->findAll();
	//for (auto i : list) {
	//	employer = dynamic_pointer_cast<Entities::Employer>(i);
	//	employer->remove();
	//}
	//taskEntity->remove();
	return 0;
}