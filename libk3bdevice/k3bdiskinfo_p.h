/*
    SPDX-FileCopyrightText: 2008-2009 Sebastian Trueg <trueg@k3b.org>
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_DISKINFO_P_H_
#define _K3B_DISKINFO_P_H_

#include "k3bmsf.h"
#include "k3bdeviceglobals.h"

#include <QByteArray>
#include <QSharedData>

namespace K3b {
    namespace Device {
        class DiskInfoPrivate : public QSharedData
        {
        public:
            DiskInfoPrivate()
                : mediaType(MEDIA_UNKNOWN),
                  currentProfile(MEDIA_UNKNOWN),
                  diskState(STATE_UNKNOWN),
                  lastSessionState(STATE_UNKNOWN),
                  bgFormatState(BG_FORMAT_INVALID),
                  numSessions(0),
                  numTracks(0),
                  rewritable(false) {
            }

            MediaType mediaType;
            int currentProfile;

            MediaState diskState;
            MediaState lastSessionState;
            BackGroundFormattingState bgFormatState;
            int numSessions;
            int numTracks;
            int numLayers;  // only for DVD media
            int rewritable;

            K3b::Msf capacity;
            K3b::Msf usedCapacity;
            K3b::Msf firstLayerSize;

            QByteArray mediaId;
        };
    }
}

#endif
