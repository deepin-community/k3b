/*
    SPDX-FileCopyrightText: 2010 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2010 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_K3BVIDEODVDAUDIOMODEL_H_
#define _K3B_K3BVIDEODVDAUDIOMODEL_H_

#include <KIO/Global>

#include <QAbstractItemModel>
#include <QList>


namespace K3b {
    
    namespace VideoDVD {
        class AudioStream;
        class Title;
        class VideoDVD;
    }

    class VideoDVDAudioModel : public QAbstractItemModel
    {
        Q_OBJECT
        
    public:
        enum Columns {
            TitleColumn,
            VideoSizeColumn,
            FileSizeColumn,
            FileNameColumn,
            NumColumns
        };
        
    public:
        VideoDVDAudioModel( const VideoDVD::VideoDVD& dvd, const QList<int>& titles, QObject* parent = 0 );
        ~VideoDVDAudioModel() override;
        
        const VideoDVD::Title* titleForIndex( const QModelIndex& index ) const;
        QModelIndex indexForTitle( const VideoDVD::Title& title, int column = TitleColumn ) const;
        
        const VideoDVD::AudioStream* audioForIndex( const QModelIndex& index ) const;
        QModelIndex indexForAudio( const VideoDVD::AudioStream& audio, int column = TitleColumn ) const;
        
        void setVideoSize( const VideoDVD::Title& title, const QSize& videoSize );
        void setFileSize( const VideoDVD::Title& title, KIO::filesize_t fileSize );
        void setFileName( const VideoDVD::Title& title, const QString& fileName );
        
        int chosenAudio( const VideoDVD::Title& title ) const;
        
        QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
        int columnCount( const QModelIndex& parent = QModelIndex() ) const override;
        int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
        QModelIndex parent( const QModelIndex& child ) const override;
        QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const override;
        QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
        bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
        Qt::ItemFlags flags( const QModelIndex& index ) const override;
        
    private:
        class Private;
        Private* const d;
    };

}

#endif // _K3B_K3BVIDEODVDAUDIOMODEL_H_
