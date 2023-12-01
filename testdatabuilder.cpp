#include "testdatabuilder.h"
#include "testdata.h"

#include <QPair>
#include <QString>

TestDataBuilder::TestDataBuilder() : test(new TestData()) { }

TestDataBuilder::~TestDataBuilder()
{
    delete this->test;
    this->test = nullptr;
}

TestData* TestDataBuilder::getTest(void) const
{
    return this->test;
}

TestDataBuilder& TestDataBuilder::setQuestion(const QString& question)
{
    this->test->question = question;
    return *this;
}

TestDataBuilder& TestDataBuilder::addAnswer(const QString& answer, const bool isCorrect)
{
    this->test->answers.append(qMakePair(qMakePair(answer, isCorrect), false));
    return *this;
}

void TestDataBuilder::reset(void)
{
    delete this->test;
    this->test = new TestData();
}
