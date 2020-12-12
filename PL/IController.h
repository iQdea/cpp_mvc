#pragma once
#include "BLL.h"

namespace Controllers {
	using namespace BLL::DTO;

	class IController {
	public:
		IController(BLL::SprintService* sprintService) {
			this->sprintService = sprintService;
		}
	protected:
		BLL::SprintService* sprintService;
	};
}