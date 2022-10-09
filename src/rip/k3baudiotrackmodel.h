/*
    SPDX-FileCopyrightText: 2011 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2008 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_AUDIO_TRACK_MODEL_H_
#define _K3B_AUDIO_TRACK_MODEL_H_

#include <QAbstractItemModel>

namespace KCDDB {
    class CDInfo;
}

namespace K3b {
    class Medium;
    
    class AudioTrackModel : public QAbstractItemModel
    {
        Q_OBJECT

    public:
        explicit AudioTrackModel( QObject* parent = 0 );
        ~AudioTrackModel() override;

        enum Columns {
            TrackNumberColumn = 0,
            TitleColumn,
            ArtistColumn,
            LengthColumn,
            NumColumns
        };

        enum Roles {
            MediumRole = 6000,
            TrackNumberRole,
            ArtistRole,
            TitleRole,
            CommentRole,
            LengthRole
        };

        void setMedium( const Medium& medium );
        Medium medium() const;

        void setCddbInfo( const KCDDB::CDInfo& data );
        KCDDB::CDInfo cddbInfo() const;

        void setTrackChecked( int track, bool checked );
        bool trackChecked( int trackIndex ) const;
        QList<int> checkedTrackIndices() const;

        int columnCount( const QModelIndex& parent = QModelIndex() ) const override;
        QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
        QVariant headerData ( int section, Qt::Orientation orientation, int role ) const override;
        Qt::ItemFlags flags( const QModelIndex& index ) const override;
        QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
        QModelIndex parent( const QModelIndex& index ) const override;
        int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
        bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
        QMimeData* mimeData( const QModelIndexList& indexes ) const override;
        QStringList mimeTypes() const override;

    public Q_SLOTS:
        void checkAll();
        void uncheckAll();

    private:
        class Private;
        Private* const d;
    };
}

#endif
