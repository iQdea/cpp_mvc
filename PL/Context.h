#pragma once
#include "DAL.h"
#include "BLL.h"

using namespace DAL;
using namespace BLL;

class Context {
public:
	Context(shared_ptr<SprintService> sprintService) {
		this->sprintService = sprintService;
	}

	shared_ptr<DTO::Employer> teamLead;
	shared_ptr<DTO::Employer> user;
	shared_ptr<DTO::Employer> employer;
	shared_ptr<DTO::Task> task;
	shared_ptr<SprintService> sprintService;
};
