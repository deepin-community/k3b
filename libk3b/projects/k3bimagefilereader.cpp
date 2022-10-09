/*
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "k3bimagefilereader.h"

#include <QDebug>
#include <QFile>



class K3b::ImageFileReader::Private
{
public:
    Private()
        : isValid(false) {
    }

    QString filename;
    QString imageFilename;
    bool isValid;
};


K3b::ImageFileReader::ImageFileReader()
{
    d = new Private();
}


K3b::ImageFileReader::~ImageFileReader()
{
    delete d;
}


void K3b::ImageFileReader::openFile( const QString& filename )
{
    d->filename = filename;
    d->imageFilename = QString();
    setValid(false);

    if( !filename.isEmpty() )
        readFile();
}


void K3b::ImageFileReader::setValid( bool b )
{
    d->isValid = b;
}


void K3b::ImageFileReader::setImageFilename( const QString& filename )
{
    d->imageFilename = filename;
}


bool K3b::ImageFileReader::isValid() const
{
    return d->isValid;
}


QString K3b::ImageFileReader::filename() const
{
    return d->filename;
}


QString K3b::ImageFileReader::imageFilename() const
{
    return d->imageFilename;
}
