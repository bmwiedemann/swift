/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/optional.hpp>

#include "Swiften/Base/String.h"
#include "Swiften/JID/JID.h"

namespace Swift {
	class MUCBookmark {
		public:
			MUCBookmark(const JID& room, const String& bookmarkName) : room_(room), name_(bookmarkName){};
			void setAutojoin(bool enabled) {autojoin_ = enabled;};
			void setNick(const boost::optional<String>& nick) {nick_ = nick;};
			void setPassword(const boost::optional<String>& password) {password_ = password;};
			bool getAutojoin() const {return autojoin_;};
			const boost::optional<String>& getNick() const {return nick_;};
			const boost::optional<String>& getPassword() const {return password_;};
			const String& getName() const {return name_;};
			const JID& getRoom() const {return room_;};

			bool operator==(const MUCBookmark& rhs) const {return rhs.room_ == room_ && rhs.name_ == name_ && rhs.nick_ == nick_ && rhs.password_ == password_ && rhs.autojoin_ == autojoin_;};
		private:
			JID room_;
			String name_;
			boost::optional<String> nick_;
			boost::optional<String> password_;
			bool autojoin_;
	};
}

