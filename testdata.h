#ifndef TESTDATA_H
#define TESTDATA_H

#include <QList>
#include <QPair>
#include <QString>

struct TestData
{
    QString question;
    QList<QPair<QPair<QString, bool>, bool>> answers;
};

#endif // TESTDATA_H
