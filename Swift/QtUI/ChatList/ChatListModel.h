/*
 * Copyright (c) 2010 Kevin Smith
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <QAbstractItemModel>
#include <QList>

#include "Swiften/MUC/MUCBookmark.h"

#include "Swift/QtUI/ChatList/ChatListGroupItem.h"

namespace Swift {
	class ChatListModel : public QAbstractItemModel {
		Q_OBJECT
		public:
			ChatListModel();
			void addMUCBookmark(const MUCBookmark& bookmark);
			void removeMUCBookmark(const MUCBookmark& bookmark);
			int columnCount(const QModelIndex& parent = QModelIndex()) const;
			QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
			QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
			QModelIndex parent(const QModelIndex& index) const;
			int rowCount(const QModelIndex& parent = QModelIndex()) const;
			ChatListItem* getItemForIndex(const QModelIndex& index) const;
		private:
			ChatListGroupItem* mucBookmarks_;
			ChatListGroupItem* root_;
	};

}
