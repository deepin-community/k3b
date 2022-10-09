/*
    SPDX-FileCopyrightText: 2003-2008 Sebastian Trueg <trueg@k3b.org>
    SPDX-FileCopyrightText: 2009 Gustavo Pichorim Boiko <gustavo.boiko@kdemail.net>
    SPDX-FileCopyrightText: 2009-2010 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/


#include "k3bdataview.h"
#include "k3bdataburndialog.h"
#include "k3bdatadoc.h"
#include "k3bdataprojectmodel.h"
#include "k3bdataviewimpl.h"
#include "k3bdirproxymodel.h"

#include <KLocalizedString>
#include <KMessageBox>
#include <KActionCollection>
#include <KToolBar>

#include <QDebug>
#include <QUrl>
#include <QAction>
#include <QHeaderView>
#include <QTreeView>
#include <QSplitter>


K3b::DataView::DataView( K3b::DataDoc* doc, QWidget* parent )
:
    View( doc, parent ),
    m_doc( doc ),
    m_dataViewImpl( new DataViewImpl( this, m_doc, actionCollection() ) ),
    m_dirView( new QTreeView( this ) ),
    m_dirProxy( new DirProxyModel( this ) )
{
    m_dirProxy->setSourceModel( m_dataViewImpl->model() );

    // Dir panel
    m_dirView->setRootIsDecorated( false );
    m_dirView->setHeaderHidden( true );
    m_dirView->setAcceptDrops( true );
    m_dirView->setDragEnabled( true );
    m_dirView->setDragDropMode( QTreeView::DragDrop );
    m_dirView->setSelectionMode( QTreeView::SingleSelection );
    m_dirView->setVerticalScrollMode( QAbstractItemView::ScrollPerPixel );
    m_dirView->setModel( m_dirProxy );
    m_dirView->expandToDepth( 1 ); // Show first-level directories directories by default
    m_dirView->setColumnHidden( DataProjectModel::TypeColumn, true );
    m_dirView->setColumnHidden( DataProjectModel::SizeColumn, true );

    QSplitter* splitter = new QSplitter( this );
    splitter->addWidget( m_dirView );
    splitter->addWidget( m_dataViewImpl->view() );
    splitter->setStretchFactor( 0, 1 );
    splitter->setStretchFactor( 1, 3 );
    setMainWidget( splitter );

    // FIXME: always sort folders first in fileview
    // FIXME: allow sorting by clicking fileview headers

    connect( actionCollection()->action( "parent_dir" ), SIGNAL(triggered()),
             this, SLOT(slotParentDir()) );
    connect( m_dirView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
             this, SLOT(slotCurrentDirChanged()) );
    connect( m_dataViewImpl, SIGNAL(setCurrentRoot(QModelIndex)),
             this, SLOT(slotSetCurrentRoot(QModelIndex)) );

    if( m_dirProxy->rowCount() > 0 )
        m_dirView->setCurrentIndex( m_dirProxy->index( 0, 0 ) );

    // Setup toolbar
    toolBox()->addAction( actionCollection()->action( "project_data_import_session" ) );
    toolBox()->addAction( actionCollection()->action( "project_data_clear_imported_session" ) );
    toolBox()->addAction( actionCollection()->action( "project_data_edit_boot_images" ) );
    toolBox()->addSeparator();
    toolBox()->addAction( actionCollection()->action( "parent_dir" ) );
    toolBox()->addSeparator();
    toolBox()->addActions( createPluginsActions( m_doc->type() ) );
    toolBox()->addSeparator();
    toolBox()->addAction( actionCollection()->action( "project_volume_name" ) );

    // this is just for testing (or not?)
    // most likely every project type will have it's rc file in the future
    // we only add the additional actions since View already added the default actions
    setXML( "<!DOCTYPE gui SYSTEM \"kpartgui.dtd\">"
            "<gui name=\"k3bproject\" version=\"1\">"
            "<MenuBar>"
            " <Menu name=\"project\"><text>&amp;Project</text>"
            "  <Action name=\"project_data_import_session\"/>"
            "  <Action name=\"project_data_clear_imported_session\"/>"
            "  <Action name=\"project_data_edit_boot_images\"/>"
            " </Menu>"
            "</MenuBar>"
            "</gui>", true );
}


K3b::DataView::~DataView()
{
}


K3b::ProjectBurnDialog* K3b::DataView::newBurnDialog( QWidget* parent )
{
    return new DataBurnDialog( m_doc, parent );
}


void K3b::DataView::slotBurn()
{
    if( m_doc->burningSize() == 0 ) {
        KMessageBox::information( this, i18n("Please add files to your project first."),
                                  i18n("No Data to Burn") );
    }
    else {
        ProjectBurnDialog* dlg = newBurnDialog( this );
        dlg->execBurnDialog(true);
        delete dlg;
    }
}


void K3b::DataView::addUrls( const QList<QUrl>& urls )
{
    m_dataViewImpl->addUrls( m_dirProxy->mapToSource( m_dirView->currentIndex() ), urls );
}


void K3b::DataView::slotParentDir()
{
    m_dirView->setCurrentIndex( m_dirView->currentIndex().parent() );
}


void K3b::DataView::slotCurrentDirChanged()
{
    QModelIndexList indexes = m_dirView->selectionModel()->selectedRows();
    if( indexes.count() ) {
        m_dataViewImpl->slotCurrentRootChanged( m_dirProxy->mapToSource( indexes.first() ) );
    }
}


void K3b::DataView::slotSetCurrentRoot( const QModelIndex& index )
{
    m_dirView->setCurrentIndex( m_dirProxy->mapFromSource( index ) );
}


