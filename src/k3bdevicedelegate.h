/*
    SPDX-FileCopyrightText: 1998-2008 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef _K3B_DEVICE_DELEGATE_H_
#define _K3B_DEVICE_DELEGATE_H_

#include <KFileItemDelegate>

namespace K3b {
    class DeviceDelegate : public KFileItemDelegate
    {
        Q_OBJECT

    public:
        explicit DeviceDelegate( QObject* parent );
        ~DeviceDelegate() override;

        QSize sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
        void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
    };
}

#endif
