/*
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_DEVICE_COMBO_BOX_H_
#define _K3B_DEVICE_COMBO_BOX_H_

#include "k3b_export.h"
#include <KComboBox>
#include <QList>

namespace K3b {
    namespace Device {
        class Device;
    }


    /**
     * A combobox to select a K3b device.
     *
     * It automatically removes devices that are removed from the system.
     */
    class LIBK3B_EXPORT DeviceComboBox : public KComboBox
    {
        Q_OBJECT

    public:
        explicit DeviceComboBox( QWidget* parent = 0 );
        ~DeviceComboBox() override;

        Device::Device* selectedDevice() const;

    Q_SIGNALS:
        void selectionChanged( K3b::Device::Device* );

    public Q_SLOTS:
        void addDevice( K3b::Device::Device* );
        void addDevices( const QList<K3b::Device::Device*>& );
        /**
         * Clears the device combo and tries to keep the current selection
         */
        void refreshDevices( const QList<K3b::Device::Device*>& );
        void removeDevice( K3b::Device::Device* );
        void setSelectedDevice( K3b::Device::Device* );

    private Q_SLOTS:
        void slotActivated( int );

    private:
        class Private;
        Private* d;
    };
}

#endif
