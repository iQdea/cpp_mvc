#pragma once
#include "common.h"
namespace BLL {
	namespace DTO {
		class IEntity {
		public:
			IEntity(string id)  {
				this->id = id;
			}

			string id;
		};
	}
}
