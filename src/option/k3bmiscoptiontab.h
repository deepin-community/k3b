/*
    SPDX-FileCopyrightText: 1998-2008 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/


#ifndef K3BMISCOPTIONTAB_H
#define K3BMISCOPTIONTAB_H

#include "ui_base_k3bmiscoptiontab.h"


namespace K3b {
    class MiscOptionTab : public QWidget, public Ui::base_K3bMiscOptionTab
    {
        Q_OBJECT

    public:
        explicit MiscOptionTab(QWidget *parent=0);
        ~MiscOptionTab() override;

        void readSettings();
        bool saveSettings();

Q_SIGNALS:
        void changed();
    };
}

#endif
