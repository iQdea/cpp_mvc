#pragma once
#include "IRepositoryList.h"
#include "Connection.h"
#include "TaskRepository.h"
#include "TaskAssignedRepository.h"
#include "TaskCommentRepository.h"
#include "TaskStatusRepository.h"
#include "EmployeeRepository.h"
#include "SessionRepository.h"

namespace DAL {
	namespace Mongo {
		class RepositoryList { // : IRepositoryList<TaskRepository, EmployeeRepository> {
		public:
			RepositoryList(string url) {
				connection = shared_ptr<Connection>(new Connection(url));
				task = shared_ptr<TaskRepository>(new TaskRepository(connection->db));
				taskAssigned = shared_ptr<TaskAssignedRepository>(new TaskAssignedRepository(connection->db));
				taskStatus = shared_ptr<TaskStatusRepository>(new TaskStatusRepository(connection->db));
				taskComment = shared_ptr<TaskCommentRepository>(new TaskCommentRepository(connection->db));
				employee = shared_ptr<EmployeeRepository>(new EmployeeRepository(connection->db));
				session = shared_ptr<SessionRepository>(new SessionRepository(connection->db));
			}
			
			shared_ptr<TaskRepository> getTask() {
				return task;
			}
			shared_ptr<EmployeeRepository> getEmployee() {
				return employee;
			}
			shared_ptr<TaskCommentRepository> taskComment;
			shared_ptr<TaskAssignedRepository> taskAssigned;
			shared_ptr<TaskStatusRepository> taskStatus;
			shared_ptr<Connection> connection;
			shared_ptr<TaskRepository> task;
			shared_ptr<EmployeeRepository> employee;
			shared_ptr<SessionRepository> session;
		};
	}
}