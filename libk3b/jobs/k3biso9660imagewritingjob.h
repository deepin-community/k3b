/*
    SPDX-FileCopyrightText: 2003-2009 Sebastian Trueg <trueg@k3b.org>
    SPDX-FileCopyrightText: 2011 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/


#ifndef K3BISO9660_IMAGE_WRITING_JOB_H
#define K3BISO9660_IMAGE_WRITING_JOB_H

#include "k3bjob.h"
#include "k3b_export.h"

namespace K3b {
    namespace Device {
        class Device;
    }

    class LIBK3B_EXPORT Iso9660ImageWritingJob : public BurnJob
    {
        Q_OBJECT

    public:
        explicit Iso9660ImageWritingJob( JobHandler* );
        ~Iso9660ImageWritingJob() override;

        Device::Device* writer() const override { return m_device; }

        QString jobDescription() const override;
        QString jobDetails() const override;
        QString jobSource() const override;
        QString jobTarget() const override;

    public Q_SLOTS:
        void cancel() override;
        void start() override;

        void setImagePath( const QString& path ) { m_imagePath = path; }
        void setSpeed( int s ) { m_speed = s; }
        void setBurnDevice( K3b::Device::Device* dev ) { m_device = dev; }
        void setWritingMode( K3b::WritingMode mode ) { m_writingMode = mode; }
        void setSimulate( bool b ) { m_simulate = b; }
        void setNoFix( bool b ) { m_noFix = b; }
        void setDataMode( int m ) { m_dataMode = m; }
        void setVerifyData( bool b ) { m_verifyData = b; }
        void setCopies( int c ) { m_copies = c; }

    protected Q_SLOTS:
        void slotWriterJobFinished( bool );
        void slotVerificationFinished( bool );
        void slotVerificationProgress( int );
        void slotWriterPercent( int );
        void slotNextTrack( int, int );
        void startWriting();

    private:
        bool prepareWriter();

        WritingMode m_writingMode;
        bool m_simulate;
        Device::Device* m_device;
        bool m_noFix;
        int m_speed;
        int m_dataMode;
        bool m_verifyData;
        QString m_imagePath;
        int m_copies;

        class Private;
        Private* d;
    };
}

#endif
