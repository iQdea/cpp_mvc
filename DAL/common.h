#pragma once
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <ctime>
#include <stdexcept>
namespace DAL {
	using namespace std;
	
	enum class StatusType { Open = 0, Active, Resolved };

	namespace Entities {
		using basicDoc = bsoncxx::builder::basic::document;
		using bsoncxx::builder::stream::close_array;
		using bsoncxx::builder::stream::document;
		using bsoncxx::builder::stream::finalize;
		using bsoncxx::builder::stream::open_array;
		using bsoncxx::builder::stream::open_document;
		using bsoncxx::builder::stream::close_document;
		using bsoncxx::builder::basic::kvp;
		using bsoncxx::builder::basic::make_array;
		using bsoncxx::builder::basic::make_document;
		using bsoncxx::document::value;
		using bsoncxx::stdx::string_view;
		using bsoncxx::document::view_or_value;
		using bsoncxx::document::view;
		using bsoncxx::oid;
		using mongocxx::database;
		using mongocxx::collection;
	}
	namespace Mongo {
		using namespace Entities;
	}
}