#pragma once
#include "IEntity.h"

namespace DAL {
	namespace Entities {
		class Employee : public IEntity {
		public:
			Employee(string name, string managerId) : IEntity() {
				this->name = name;
				this->managerId = managerId;
			};
			Employee(string id, string name, string managerId) : IEntity(id) {
				this->name = name;
				this->managerId = managerId;
			};

			string name;
			string managerId;
		};
	}
}
