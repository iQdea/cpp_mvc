#include "Connection.h"

using namespace DAL;

Mongo::Connection::Connection(string url) {
	uri = mongocxx::uri(url);
	client = mongocxx::client(uri);
	db = client["sprint"];
}
