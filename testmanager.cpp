#include <QPair>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "testdata.h"
#include "testmanager.h"
#include "testdatabuilder.h"

TestManager* TestManager::instance = nullptr;

TestManager::TestManager() { }

TestManager::~TestManager(void) { }

int TestManager::getTestsCount() const
{
    return this->tests.count();;
}

int TestManager::getTimeLimit(void) const
{
    return this->timeLimit;
}

TestManager& TestManager::getInstance(void)
{
    if (instance == nullptr)
        instance = new TestManager();

    return *instance;
}

const TestData& TestManager::getTest(const int index) const
{
    if (index >= 0 && index < this->tests.size())
        return this->tests[index];

    throw std::runtime_error("Invalid test index.");
}

float TestManager::calculateTestTotalResults(void) const
{
    float totalScore = 0.0f;

    float testScore;
    int totalTrueAnswers;
    int trueAnswersMarked;
    int falseAnswersMarked;

    for (const TestData& test : this->tests)
    {
        testScore = 0.0f;
        totalTrueAnswers = 0;
        trueAnswersMarked = 0;
        falseAnswersMarked = 0;

        for (const QPair<QPair<QString, bool>, bool>& answer : test.answers)
        {
            if (answer.first.second)
            {
                totalTrueAnswers++;

                if (answer.second)
                    trueAnswersMarked++;
            }
            else if (answer.second)
                falseAnswersMarked++;
        }

        if (totalTrueAnswers > 0)
            testScore = static_cast<float>(trueAnswersMarked - falseAnswersMarked) / totalTrueAnswers;

        testScore = std::max(testScore, 0.0f);

        totalScore += testScore;
    }

    return totalScore;
}

void TestManager::updateTestResults(const int index, const TestData& test)
{
    if (index >= 0 && index < this->tests.size())
        this->tests[index] = test;
    else
        throw std::runtime_error("Invalid test index.");
}

void TestManager::loadTests(const QString& filePath)
{
    QFile file(filePath);
    QTextStream stream(&file);

    QString line;
    TestDataBuilder builder;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!stream.atEnd())
        {
            line = stream.readLine().trimmed();

            if (line.startsWith("Q."))
            {
                builder.setQuestion(line.mid(3).trimmed());
            }
            else if (line.startsWith("T."))
            {
                builder.addAnswer(line.mid(3).trimmed(), true);
            }
            else if (line.startsWith("F."))
            {
                builder.addAnswer(line.mid(3).trimmed(), false);
            }
            else if (line.startsWith("C."))
            {
                const int TIME = line.mid(3).trimmed().toInt();

                if (TIME > 0)
                    this->timeLimit = TIME * 60 * 1000;
                else
                    throw std::runtime_error("The contents of the file could not be read.");
            }
            else if (line.isEmpty())
            {
                if (!builder.getTest()->question.isEmpty())
                {
                    this->tests.append(*(builder.getTest()));
                    builder.reset();
                }
            }
            else
            {
                throw std::runtime_error("The contents of the file could not be read..");
            }
        }

        if (!builder.getTest()->question.isEmpty())
            this->tests.append(*(builder.getTest()));

        file.close();
    }
    else
        throw std::runtime_error("The contents of the file could not be read.");
}
