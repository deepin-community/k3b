/*
    SPDX-FileCopyrightText: 2003-2007 Sebastian Trueg <trueg@k3b.org>
    SPDX-FileCopyrightText: 2009 Gustavo Pichorim Boiko <gustavo.boiko@kdemail.net>
    SPDX-FileCopyrightText: 2009-2010 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef K3B_MIXED_VIEW_H
#define K3B_MIXED_VIEW_H

#include "k3bview.h"

#include <QList>

class QAbstractItemModel;
class QAction;
class QModelIndex;
class QStackedWidget;
class QTreeView;

namespace K3b {
    class AudioTrack;
    class AudioDataSource;
    class AudioViewImpl;
    class DataViewImpl;
    class DirProxyModel;
    class MixedDoc;
    class MetaItemModel;

    class MixedView : public View
    {
        Q_OBJECT

    public:
        explicit MixedView( MixedDoc* doc, QWidget* parent = 0 );
        ~MixedView() override;

    public Q_SLOTS:
        void slotBurn() override;
        void addUrls( const QList<QUrl>& urls ) override;

    private Q_SLOTS:
        void slotParentDir();
        void slotCurrentDirChanged();
        void slotUpdateActions();
        void slotSetCurrentRoot( const QModelIndex& index );

    protected:
        /**
         * reimplemented from @ref View
         */
        ProjectBurnDialog* newBurnDialog( QWidget* parent = 0 ) override;

    private:
        MixedDoc* m_doc;
        AudioViewImpl* m_audioViewImpl;
        DataViewImpl* m_dataViewImpl;
        MetaItemModel* m_model;
        DirProxyModel* m_dirProxy;
        QTreeView* m_dirView;
        QStackedWidget* m_fileViewWidget;
        QList<QAction*> m_audioActions;
        QList<QAction*> m_dataActions;
    };
}

#endif
