/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>
#include <Swiften/Base/boost_bsignals.h>

#include <Swiften/Elements/SearchPayload.h>
#include <Swiften/Base/String.h>
#include <Swiften/JID/JID.h>
#include <Swiften/Elements/DiscoInfo.h>
#include <Swiften/Elements/DiscoItems.h>
#include <Swiften/Elements/ErrorPayload.h>

namespace Swift {
	class UIEventStream;
	class UIEvent;
	class UserSearchWindow;
	class UserSearchWindowFactory;
	class IQRouter;
	class DiscoServiceWalker;

	class UserSearchResult {
		public:
			UserSearchResult(const JID& jid, const std::map<String, String>& fields) : jid_(jid), fields_(fields) {}
			const JID& getJID() const {return jid_;}
			const std::map<String, String>& getFields() const {return fields_;}
		private:
			JID jid_;
			std::map<String, String> fields_;
	};

	class UserSearchController {
		public:
			enum Type {AddContact, StartChat};
			UserSearchController(Type type, const JID& jid, UIEventStream* uiEventStream, UserSearchWindowFactory* userSearchWindowFactory, IQRouter* iqRouter);
			~UserSearchController();
		private:
			void handleUIEvent(boost::shared_ptr<UIEvent> event);
			void handleFormRequested(const JID& service);
			void handleDiscoServiceFound(const JID& jid, boost::shared_ptr<DiscoInfo> info, DiscoServiceWalker* walker);
			void handleDiscoWalkFinished(DiscoServiceWalker* walker);
			void handleFormResponse(boost::shared_ptr<SearchPayload> items, ErrorPayload::ref error, const JID& jid);
			void handleSearch(boost::shared_ptr<SearchPayload> fields, const JID& jid);
			void handleSearchResponse(boost::shared_ptr<SearchPayload> results, ErrorPayload::ref error, const JID& jid);
			Type type_;
			UIEventStream* uiEventStream_;
			UserSearchWindow* window_;
			UserSearchWindowFactory* factory_;
			boost::bsignals::scoped_connection uiEventConnection_;
			IQRouter* iqRouter_;
			JID jid_;
			DiscoServiceWalker* discoWalker_;
	};
}