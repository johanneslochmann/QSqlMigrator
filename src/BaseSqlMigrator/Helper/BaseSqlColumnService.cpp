/****************************************************************************
**
** Copyright (C) 2013, HicknHack Software
** All rights reserved.
** Contact: http://www.hicknhack-software.com/contact
**
** This file is part of the QSqlMigrator
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "BaseSqlMigrator/Helper/BaseSqlColumnService.h"

#include <QStringList>

using namespace Structure;

namespace Helper {

BaseSqlColumnService::BaseSqlColumnService(const TypeMapperService &typeMapperService)
    : m_typeMapperService(typeMapperService)
{
}

QString BaseSqlColumnService::buildColumnTypeSql(const Column &column) const
{
    return m_typeMapperService.map(column.type());
}

QStringList BaseSqlColumnService::buildColumnOptionsSql(const Column &column) const
{
    QStringList sqlColumnOptions;
    if (column.isPrimary()) {
        sqlColumnOptions << "PRIMARY KEY";
    }
    else if (!column.isNullable()) {
        sqlColumnOptions << "NOT NULL";
    }
    if (column.isUnique()) {
        sqlColumnOptions << "UNIQUE";
    }
    if (column.hasDefaultValue()) {
        sqlColumnOptions << QString("DEFAULT (%1)").arg(column.defaultValue());
    }
    return sqlColumnOptions;
}

QString BaseSqlColumnService::generateColumnDefinitionSql(const Column &column) const
{
    QStringList columnParts = buildColumnOptionsSql(column);
    columnParts.push_front(buildColumnTypeSql(column));
    columnParts.push_front(column.name());
    return columnParts.join(" ");
}

QString BaseSqlColumnService::generateColumnsDefinitionSql(const QList<Column> &columnList) const
{
    QStringList sqlColumnDefinitions;
    foreach (Column column, columnList) {
        sqlColumnDefinitions << generateColumnDefinitionSql(column);
    }
    return sqlColumnDefinitions.join(", ");
}

QString BaseSqlColumnService::generateIndexColumnDefinitionSql(const Index::Column& column) const
{
    QString sqlSortOrder;
    switch (column.sortOrder()) {
    //case Index::Ascending: // fall through
    case Index::Default:
        sqlSortOrder = "ASC";
        break;
    case Index::Descending:
        sqlSortOrder = "DESC";
        break;
    default:
        sqlSortOrder = "";
        break;
    }

    return QString("%1 %2").arg(column.name(), sqlSortOrder);
}

QString BaseSqlColumnService::generateIndexColumnsDefinitionSql(const Index::ColumnList &columns) const
{
    QStringList sqlIndexColumnDefinitions;
    QListIterator<Index::Column> i(columns);
    while (i.hasNext()) {
        sqlIndexColumnDefinitions << this->generateIndexColumnDefinitionSql(i.next());
    }
    return sqlIndexColumnDefinitions.join(", ");
}

} // namespace Helper
