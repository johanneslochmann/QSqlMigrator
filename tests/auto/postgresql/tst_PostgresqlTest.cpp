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
#include "../BasicTest/BasicTest.h"
#include "PostgresqlMigrator/PostgresqlMigrator.h"

#include "PostgresqlConfig.h"

#include <QString>
#include <QtTest>

using namespace Structure;
using namespace Migrations;
using namespace MigrationExecution;

#define POSTGRESQL_STRUCTURE_DATABASE "postgres"
#define POSTGRESQLTEST_DATABASE_NAME "qdb_migrator_test_db"

class PostgresqlTest : public BasicTest
{
    Q_OBJECT

public:
    PostgresqlTest();
};

PostgresqlTest::PostgresqlTest()
    : BasicTest(POSTGRESQL_DRIVERNAME, POSTGRESQLTEST_DATABASE_NAME, &PostgresqlMigrator::buildContext,
                POSTGRESQL_STRUCTURE_DATABASE,
                POSTGRESQL_HOSTNAME, POSTGRESQL_HOSTPORT, POSTGRESQL_USERNAME, POSTGRESQL_PASSWORD)
{
}

QTEST_MAIN(PostgresqlTest)

#include "tst_PostgresqlTest.moc"
