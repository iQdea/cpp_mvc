#pragma once
namespace ViewModel {
	class TaskAssigned {
	public:
		TaskAssigned(DTO::TaskAssigned& item) {
			id = item.id;
		}

		string str() {
			stringstream ss;
			ss << "task-assigned:" << id;
			return ss.str();
		}

		string id;
	};
}