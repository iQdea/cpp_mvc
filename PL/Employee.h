#pragma once
namespace ViewModel {
	class Employee {
	public:
		Employee(DTO::Employee& item) {
			id = item.id;
			name = item.name;
		}

		string str() {
			stringstream ss;
			ss << "{" 
				<< "\"type\":\"employee\","
				<< "\"id\":\"" << id << "\","
				<< "\"name\":\"" << name << "\""
				<< "}";
			return ss.str();
		}

		string json() {
			stringstream ss;
			ss << "{"
				<< "\"type\":\"employee\","
				<< "\"id\":\"" << id << "\","
				<< "\"name\":\"" << name << "\""
				<< "}";
			return ss.str();
		}

		string id;
		string name;
	};
}
