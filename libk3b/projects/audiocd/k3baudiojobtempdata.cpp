/*
    SPDX-FileCopyrightText: 1998-2007 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "k3baudiojobtempdata.h"
#include "k3baudiodoc.h"
#include "k3baudiotrack.h"
#include "k3bglobals.h"
#include "k3bversion.h"
#include "k3bmsf.h"
#include "k3bcore.h"

#include <QDebug>
#include <QFile>


class K3b::AudioJobTempData::Private
{
public:
    Private( K3b::AudioDoc* _doc )
        : doc(_doc) {
    }

    QVector<QString> bufferFiles;
    QVector<QString> infFiles;
    QString tocFile;

    K3b::AudioDoc* doc;
};


K3b::AudioJobTempData::AudioJobTempData( K3b::AudioDoc* doc, QObject* parent )
    : QObject( parent )
{
    d = new Private( doc );
}


K3b::AudioJobTempData::~AudioJobTempData()
{
    delete d;
}


QString K3b::AudioJobTempData::bufferFileName( int track )
{
    if( (int)d->bufferFiles.count() < track )
        prepareTempFileNames();
    return d->bufferFiles.at(track-1);
}

QString K3b::AudioJobTempData::bufferFileName( K3b::AudioTrack* track )
{
    return bufferFileName( track->trackNumber() );
}


QString K3b::AudioJobTempData::tocFileName()
{
    if( d->tocFile.isEmpty() )
        prepareTempFileNames();
    return d->tocFile;
}


QString K3b::AudioJobTempData::infFileName( int track )
{
    if( (int)d->infFiles.count() < track )
        prepareTempFileNames();
    return d->infFiles.at( track - 1 );
}

QString K3b::AudioJobTempData::infFileName( K3b::AudioTrack* track )
{
    return infFileName( track->trackNumber() );
}


K3b::AudioDoc* K3b::AudioJobTempData::doc() const
{
    return d->doc;
}


void K3b::AudioJobTempData::prepareTempFileNames( const QString& path )
{
    d->bufferFiles.clear();
    d->infFiles.clear();

    QString prefix = K3b::findUniqueFilePrefix( "k3b_audio_", path ) + '_';

    for( int i = 0; i < d->doc->numOfTracks(); i++ ) {
        d->bufferFiles.append( prefix + QString::number( i+1 ).rightJustified( 2, '0' ) + ".wav" );
        d->infFiles.append( prefix + QString::number( i+1 ).rightJustified( 2, '0' ) + ".inf" );
    }

    d->tocFile = prefix + ".toc";
}


void K3b::AudioJobTempData::cleanup()
{
    for( int i = 0; i < d->infFiles.count(); ++i ) {
        if( QFile::exists( d->infFiles[i] ) )
            QFile::remove(  d->infFiles[i] );
    }

    for( int i = 0; i < d->bufferFiles.count(); ++i ) {
        if( QFile::exists( d->bufferFiles[i] ) )
            QFile::remove(  d->bufferFiles[i] );
    }

    if( QFile::exists( d->tocFile ) )
        QFile::remove(  d->tocFile );
}



