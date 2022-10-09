/*
    SPDX-FileCopyrightText: 2010 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2010 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "k3baudiozerodatareader.h"
#include "k3baudiozerodata.h"

#include <cstring>

namespace K3b {


class AudioZeroDataReader::Private
{
public:
    Private( AudioZeroData& s )
        : source( s )
    {
    }

    AudioZeroData& source;
};


AudioZeroDataReader::AudioZeroDataReader( AudioZeroData& source, QObject* parent )
    : QIODevice( parent ),
      d( new Private( source ) )
{
}


AudioZeroDataReader::~AudioZeroDataReader()
{
    close();
}


bool AudioZeroDataReader::open( QIODevice::OpenMode mode )
{
    if( !mode.testFlag( QIODevice::WriteOnly ) ) {
        return QIODevice::open( mode );
    }
    else {
        return false;
    }
}


bool AudioZeroDataReader::isSequential() const
{
    return false;
}


qint64 AudioZeroDataReader::size() const
{
    return d->source.length().audioBytes();
}


qint64 AudioZeroDataReader::writeData( const char* /*data*/, qint64 /*len*/ )
{
    return -1;
}


qint64 AudioZeroDataReader::readData( char* data, qint64 maxlen )
{
    if( pos() + maxlen > size() )
        maxlen = size() - pos();

    ::memset( data, 0, maxlen );

    return maxlen;
}

} // namespace K3b
