#pragma once
namespace ViewModel {
	class Task {
	public:
		Task(DTO::Task& item) {
			id = item.id;
			title = item.title;
		}

		string str() {
			stringstream ss;
			ss << "task:" << id << ":" << title;
			return ss.str();
		}

		string id;
		string title;
	};
}
