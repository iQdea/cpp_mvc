#pragma once
#include "IRepositoryList.h"
#include "Connection.h"
#include "TaskRepository.h"
#include "EmployeeRepository.h"
#include "SessionRepository.h"

namespace DAL {
	namespace Mongo {
		class RepositoryList { // : IRepositoryList<TaskRepository, EmployeeRepository> {
		public:
			RepositoryList(string url) {
				connection = shared_ptr<Connection>(new Connection(url));
				task = shared_ptr<TaskRepository>(new TaskRepository(connection->db));
				employee = shared_ptr<EmployeeRepository>(new EmployeeRepository(connection->db));
				session = shared_ptr<SessionRepository>(new SessionRepository(connection->db));
			}
			
			shared_ptr<TaskRepository> getTask() {
				return task;
			}
			shared_ptr<EmployeeRepository> getEmployee() {
				return employee;
			}

			shared_ptr<Connection> connection;
			shared_ptr<TaskRepository> task;
			shared_ptr<EmployeeRepository> employee;
			shared_ptr<SessionRepository> session;
		};
	}
}