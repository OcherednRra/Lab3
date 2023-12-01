#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <QList>
#include <QTimer>
#include <QString>

#include "testdata.h"

class TestManager
{
public:
    TestManager(const TestManager&) = delete;
    TestManager& operator=(const TestManager&) = delete;

    static TestManager& getInstance(void);

    int getTestsCount() const;
    int getTimeLimit(void) const;
    void loadTests(const QString& filePath);
    float calculateTestTotalResults(void) const;
    const TestData& getTest(const int index) const;
    void updateTestResults(const int index, const TestData& test);

private:
    explicit TestManager(void);
    ~TestManager(void);

    static TestManager* instance;

    int timeLimit;
    QList<TestData> tests;
};

#endif // TESTMANAGER_H
