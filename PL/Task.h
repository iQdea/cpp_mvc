#pragma once
namespace ViewModel {
	class Task {
	public:
		Task(DTO::Task& item) {
			id = item.id;

			title = item.title;
			descr = item.descr;

			createdBy = item.createdBy;
			createdAt = item.createdAt;

			lastModifiedAt = item.lastModifiedAt;
			lastModifiedBy = item.lastModifiedBy;

			assignedTo = item.assignedTo;
			status = (int) item.status;
		}

		string str() {
			stringstream ss;
			ss << "task:" << id << ":" << title;
			return ss.str();
		}

		string json() {
			stringstream ss;
			ss << "{"
				<< "\"entityType\":\"task\","
				<< "\"id\":\"" << id << "\","
				<< "\"title\":\"" << title << "\","
				<< "\"descr\":\"" << descr << "\","
				<< "\"status\":" << status << ","
				<< "\"assignedTo\":\"" << assignedTo << "\","
				<< "\"createdBy\":\"" << createdBy << "\","
				<< "\"createdAt\":" << createdAt << ","
				<< "\"lastModifiedBy\":\"" << lastModifiedBy << "\","
				<< "\"lastModifiedAt\":" << lastModifiedAt
				<< "}";
			return ss.str();
		}

		string id;
		
		string title;
		string descr;

		string createdBy;
		time_t createdAt;

		string lastModifiedBy;
		time_t lastModifiedAt;

		string assignedTo;
		int status;
	};
}
