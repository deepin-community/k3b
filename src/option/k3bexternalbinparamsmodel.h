/*
    SPDX-FileCopyrightText: 2010 Michal Malek <michalm@jabster.pl>
    SPDX-FileCopyrightText: 1998-2010 Sebastian Trueg <trueg@k3b.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef K3B_EXTERNALBINPARAMSMODEL_H
#define K3B_EXTERNALBINPARAMSMODEL_H

#include <QAbstractItemModel>

namespace K3b {
    
    class DataDoc;
    class ExternalProgram;
    class ExternalBinManager;

    class ExternalBinParamsModel : public QAbstractTableModel
    {
        Q_OBJECT
        
    public:
        enum Columns {
            ProgramColumn,
            ParametersColumn,
            NumColumns
        };
        
    public:
        explicit ExternalBinParamsModel( ExternalBinManager* manager, QObject* parent = 0 );
        ~ExternalBinParamsModel() override;
        
        /**
         * Reloads programs from ExternalBinManager and updates the model
         */
        void reload();
        
        /**
         * Saves all changes made in model to ExternalBinManager
         */
        void save();
        
        ExternalProgram* programForIndex( const QModelIndex& index ) const;
        QModelIndex indexForProgram( ExternalProgram* program, int column = ProgramColumn ) const;
        
        Qt::ItemFlags flags( const QModelIndex& index ) const override;
        QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
        bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole ) override;
        int columnCount( const QModelIndex& parent = QModelIndex() ) const override;
        int rowCount( const QModelIndex& parent = QModelIndex() ) const override;
        QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
        QModelIndex buddy( const QModelIndex& index ) const override;
        
    private:
        class Private;
        Private* d;
    };

}

#endif // K3B_EXTERNALBINPARAMSMODEL_H
