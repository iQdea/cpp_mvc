#pragma once
#include "Connection.h"
#include "TaskRepository.h"
#include "TaskAssignedRepository.h"
#include "TaskCommentRepository.h"
#include "TaskStatusRepository.h"
#include "EmployeeRepository.h"
#include "SessionRepository.h"
#include "ReportRepository.h"

namespace DAL {
	namespace Mongo {
		class RepositoryList {
		public:
			RepositoryList(string url) {
				connection = make_shared<Connection>(url);
				auto db = connection->db;

				task = make_shared<TaskRepository>(db);
				taskAssigned = make_shared<TaskAssignedRepository>(db);
				taskStatus = make_shared<TaskStatusRepository>(db);
				taskComment = make_shared<TaskCommentRepository>(db);
				employee = make_shared<EmployeeRepository>(db);
				session = make_shared<SessionRepository>(db);
				report = make_shared<ReportRepository>(db);
			}
			
			shared_ptr<TaskCommentRepository> taskComment;
			shared_ptr<TaskAssignedRepository> taskAssigned;
			shared_ptr<TaskStatusRepository> taskStatus;
			shared_ptr<Connection> connection;
			shared_ptr<TaskRepository> task;
			shared_ptr<EmployeeRepository> employee;
			shared_ptr<SessionRepository> session;
			shared_ptr<ReportRepository> report;
		};
	}
}