/*
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>
    SPDX-FileCopyrightText: 1998-2009 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "k3baction.h"

QAction* K3b::createAction( QObject* parent,
                            const QString& text, const QString& icon, const
                            QKeySequence& shortcut, QObject* receiver, const char* slot,
                            KActionCollection* actionCollection,
                            const QString& actionName )
{
    QAction* action = new QAction( parent );
    action->setText( text );
    if( !icon.isEmpty() ) {
        action->setIcon( QIcon::fromTheme( icon ) );
    }
    action->setShortcut( shortcut );
    if( receiver ) {
        QObject::connect( action, SIGNAL(triggered()),
                          receiver, slot );
    }
    if( actionCollection ) {
        actionCollection->addAction( actionName, action );
    }
    return action;
}


KToggleAction* K3b::createToggleAction( QObject* parent,
                                        const QString& text, const QString& icon, const
                                        QKeySequence& shortcut, QObject* receiver, const char* slot,
                                        KActionCollection* actionCollection,
                                        const QString& actionName )
{
    KToggleAction* action = new KToggleAction( parent );
    action->setText( text );
    if( !icon.isEmpty() ) {
        action->setIcon( QIcon::fromTheme( icon ) );
    }
    action->setShortcut( shortcut );
    if( receiver ) {
        QObject::connect( action, SIGNAL(triggered(bool)),
                          receiver, slot );
    }
    if( actionCollection ) {
        actionCollection->addAction( actionName, action );
    }
    return action;
}
