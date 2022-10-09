/*
    SPDX-FileCopyrightText: 1998-2007 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_EXCEPTIONS_H_
#define _K3B_EXCEPTIONS_H_

namespace K3b {
    namespace Device {
        class Device;
    }

    class Exceptions
    {
    public:
        /**
         * Returns true if the drive's firmware produces broken
         * Audio CDs with zero length pregaps.
         *
         * It simply uses a compiled in table.
         */
        static bool brokenDaoAudio( Device::Device* );
    };
}

#endif
