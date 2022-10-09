/*
    SPDX-FileCopyrightText: 1998-2007 Sebastian Trueg <trueg@k3b.org>

    Based on the effects in popupMessage.cpp
    SPDX-FileCopyrightText: 2005 Max Howell <max.howell@methylblue.com>
    SPDX-FileCopyrightText: 2005 Seb Ruiz <me@sebruiz.net>

    Dissolve Mask (c) Kicker Authors kickertip.cpp, 2005/08/17

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "k3bwidgetshoweffect.h"

#include <QTimerEvent>
#include <QPainter>
#include <QWidget>


K3b::WidgetShowEffect::WidgetShowEffect( QWidget* widget, Effect e )
    : QObject( widget ),
      m_effect( e ),
      m_widget( widget ),
      m_dissolveSize( 0 ),
      m_dissolveDelta( -1 ),
      m_offset( 0 ),
      m_deleteSelf( false ),
      m_bEffectOnly( false )
{
}


K3b::WidgetShowEffect::~WidgetShowEffect()
{
}


void K3b::WidgetShowEffect::hide( bool effectOnly )
{
    m_bEffectOnly = effectOnly;
    m_bShow = false;
    m_offset = m_widget->height();
    killTimer( m_timerId );
    m_timerId = startTimer( 6 );
}


void K3b::WidgetShowEffect::show( bool effectOnly )
{
    m_bShow = true;
    m_offset = 0;
    m_dissolveSize = 24;
    m_dissolveDelta = -1;

    m_widget->ensurePolished();

    if( m_effect == Dissolve ) {
        // necessary to create the mask
        m_mask = QBitmap( m_widget->width(), m_widget->height() );
        // make the mask empty and hence will not show widget with show() called below
        dissolveMask();
        m_timerId = startTimer( 1000 / 30 );
    }
    else {
        m_widget->move( 0, m_widget->parentWidget()->height() );
        m_timerId = startTimer( 6 );
    }

    if( !effectOnly )
        m_widget->show();
}


void K3b::WidgetShowEffect::timerEvent( QTimerEvent* )
{
    switch( m_effect ) {
    case Slide:
        slideMask();
        break;

    case Dissolve:
        dissolveMask();
        break;
    }
}


void K3b::WidgetShowEffect::dissolveMask()
{
    if( m_bShow ) {
        m_widget->repaint();
        QPainter maskPainter(&m_mask);

        m_mask.fill(Qt::black);

        maskPainter.setBrush(Qt::white);
        maskPainter.setPen(Qt::white);
        maskPainter.drawRect( m_mask.rect() );

        m_dissolveSize += m_dissolveDelta;

        if( m_dissolveSize > 0 ) {
            //FIXME kde4
            //maskPainter.setRasterOp( Qt::EraseROP );

            int x, y, s;
            const int size = 16;

            for( y = 0; y < m_widget->height() + size; y += size ) {
                x = m_widget->width();
                s = m_dissolveSize * x / 128;

                for( ; x > size; x -= size, s -= 2 ) {
                    if( s < 0 )
                        break;

                    maskPainter.drawEllipse(x - s / 2, y - s / 2, s, s);
                }
            }
        }
        else if( m_dissolveSize < 0 ) {
            m_dissolveDelta = 1;
            killTimer( m_timerId );

            emit widgetShown( m_widget );

            if( m_deleteSelf )
                deleteLater();
        }

        m_widget->setMask( m_mask );
    }

    else {
        // just hide it for now
        emit widgetHidden( m_widget );
        if( !m_bEffectOnly )
            m_widget->hide();

        if( m_deleteSelf )
            deleteLater();
    }
}


void K3b::WidgetShowEffect::slideMask()
{
    if( m_bShow ) {
        m_widget->move( 0, m_widget->parentWidget()->height() - m_offset );

        m_offset++;
        if( m_offset > m_widget->height() ) {
            killTimer( m_timerId );

            emit widgetShown( m_widget );

            if( m_deleteSelf )
                deleteLater();
        }
    }
    else {
        m_offset--;
        m_widget->move( 0, m_widget->parentWidget()->height() - m_offset );

        if( m_offset < 0 ) {
            // finally hide the widget
            emit widgetHidden( m_widget );
            if( !m_bEffectOnly )
                m_widget->hide();

            if( m_deleteSelf )
                deleteLater();
        }
    }
}



K3b::WidgetShowEffect* K3b::WidgetShowEffect::showWidget( QWidget* w, Effect m )
{
    K3b::WidgetShowEffect* e = new K3b::WidgetShowEffect( w, m );
    e->m_deleteSelf = true;
    e->show();
    return e;
}


K3b::WidgetShowEffect* K3b::WidgetShowEffect::hideWidget( QWidget* w, Effect m )
{
    K3b::WidgetShowEffect* e = new K3b::WidgetShowEffect( w, m );
    e->m_deleteSelf = true;
    e->hide();
    return e;
}


