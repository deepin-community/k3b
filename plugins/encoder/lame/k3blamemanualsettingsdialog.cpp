/*
    SPDX-FileCopyrightText: 1998-2007 Sebastian Trueg <trueg@k3b.org>
    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "k3blamemanualsettingsdialog.h"
#include "k3bplugin_i18n.h"

K3bLameManualSettingsDialog::K3bLameManualSettingsDialog( QWidget* parent )
    : QDialog( parent )
{
    setWindowTitle( i18n("(Lame) Manual Quality Settings") );
    setupUi( this );
}


K3bLameManualSettingsDialog::~K3bLameManualSettingsDialog()
{
}
