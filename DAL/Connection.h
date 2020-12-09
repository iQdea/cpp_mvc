#pragma once
#include "common.h"

namespace DAL {
	namespace Mongo {
		class Connection  {
		public:
			Connection(string url);
			mongocxx::database db;
		private:
			mongocxx::instance instance{};
			mongocxx::uri uri;
			mongocxx::client client;
		};
	}
}