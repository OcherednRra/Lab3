#ifndef TESTBUILDER_H
#define TESTBUILDER_H

#include <QPair>
#include <QString>

#include "testdata.h"

class TestDataBuilder
{
public:
    TestDataBuilder();
    TestDataBuilder(const TestDataBuilder&);
    TestDataBuilder& operator=(const TestDataBuilder&);
    ~TestDataBuilder();

    void reset(void);
    TestData* getTest(void) const;
    TestDataBuilder& setQuestion(const QString&);
    TestDataBuilder& addAnswer(const QString&, const bool);

private:
    TestData* test;
};

#endif // TESTBUILDER_H
