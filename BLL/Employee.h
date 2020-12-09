#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class Employee : public IEntity {
		public:
			Employee(shared_ptr<Entities::Employee> item) : IEntity(item->id) {
				name = item->name;
				managerId = item->managerId;
			}

			string name;
			string managerId;
		};
	}
}
