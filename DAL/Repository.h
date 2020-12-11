#pragma once
#include "common.h"
#include "Connection.h"
#include "IRepository.h"

namespace DAL {
	namespace Mongo {
		template <class T> class Repository : IRepository<T> {
		public:
			Repository() {
				filter = shared_ptr<value>(new value(document{}));
			}
			string create(shared_ptr<T> item) override {
				auto data = bsoncxx::builder::basic::document{};
				setData(data, item);
				auto result = coll.insert_one(data.view());
				return result->inserted_id().get_oid().value.to_string();
			}
			void update(shared_ptr<T> item) override {
				auto doc = bsoncxx::builder::basic::document{};
				auto data = bsoncxx::builder::basic::document{};
				setData(data, item);
				doc.append(kvp("$set", data.view()));

				coll.update_one(current(item), doc.view());
			}
			void remove(string id) override {
				coll.delete_one(current(id));
			}
			virtual shared_ptr<T> findOne() {
				auto result = coll.find_one(filter->view(), options);
				if (!result) {
					throw invalid_argument("Entity was not found");
				}

				// shared_ptr<view> v(new view(result->view()));
				view doc = result->view();
				return getEntity(doc);
			}
			vector<shared_ptr<T>> findAll() override {
				auto cursor = coll.find(filter->view(), options);
				vector<shared_ptr<T>> list;

				for (view doc : cursor) {
					list.push_back(getEntity(doc));
				}

				return list;
			}
			void setFilterId(string id) {
				filter = shared_ptr<value>(new value(document{}
					<< "_id" << oid{ string_view{id} }
				<< finalize));
			}
			virtual shared_ptr<T> getEntity(view& doc) = 0;
			virtual void setData(basicDoc& doc, shared_ptr<T> item) = 0;
		protected:
			collection coll;
			shared_ptr<value> filter;
			// shared_ptr<mongocxx::options::find> options;
			mongocxx::options::find options{};

			view_or_value current(shared_ptr<T> item) {
				return document{} << "_id" << getOid(item->getId()) << finalize;
			}
			view_or_value current(string id) {
				return document{} << "_id" << getOid(id) << finalize;
			}
			oid getOid(string id) {
				try {
					return oid(string_view(id));
				}
				catch (...) {
					return oid();
				}
			}

			int parseInt(view& doc, string key, int defaultValue = 0) {
				int result = defaultValue;

				try { result = doc[key].get_int32().value; }
				catch (...) {}
				
				return result;
			}

			string parseOid(view& doc, string key, string defaultValue = "") {
				string result = defaultValue;

				try { result = doc[key].get_oid().value.to_string(); }
				catch (...) {}

				return result;
			}

			string parseString(view& doc, string key, string defaultValue = "") {
				string result = defaultValue;

				try { result = doc[key].get_utf8().value.to_string(); }
				catch (...) {}

				return result;
			}

			template <class T2> void addField(basicDoc& doc, string key, T2 value) {
				try { doc.append(kvp(key, value)); }
				catch (...) {}
			}
		};
	}
}