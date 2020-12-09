#pragma once
#include "common.h"

namespace DAL {
	template <
		class ITaskRepository, 
		class IEmployeeRepository
	> 
	class IRepositoryList {
	public:
		virtual shared_ptr<ITaskRepository> getTask() = 0;
		virtual shared_ptr<IEmployeeRepository> getEmployee() = 0;
	};
}