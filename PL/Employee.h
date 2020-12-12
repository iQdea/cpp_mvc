#pragma once
namespace ViewModel {
	class Employee {
	public:
		Employee(shared_ptr<DTO::Employee> item) {
			id = item->id;
			name = item->name;
		}

		string str() {
			stringstream ss;
			ss << "employee:" << id << "<-" << name;
			return ss.str();
		}

		string id;
		string name;
	};
}