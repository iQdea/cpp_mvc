#pragma once
#include "Connection.h"
#include "TaskRepository.h"
#include "TaskAssignedRepository.h"
#include "TaskCommentRepository.h"
#include "TaskStatusRepository.h"
#include "EmployeeRepository.h"
#include "SessionRepository.h"

namespace DAL {
	namespace Mongo {
		class RepositoryList {
		public:
			RepositoryList(string url) {
				connection = shared_ptr<Connection>(new Connection(url));
				auto db = connection->db;
				task = shared_ptr<TaskRepository>(new TaskRepository(db));
				taskAssigned = shared_ptr<TaskAssignedRepository>(new TaskAssignedRepository(db));
				taskStatus = shared_ptr<TaskStatusRepository>(new TaskStatusRepository(db));
				taskComment = shared_ptr<TaskCommentRepository>(new TaskCommentRepository(db));
				employee = shared_ptr<EmployeeRepository>(new EmployeeRepository(db));
				session = shared_ptr<SessionRepository>(new SessionRepository(db));
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