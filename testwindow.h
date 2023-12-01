#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QTimer>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui { class TestWindow; }

class TestWindow : public QDialog
{
    Q_OBJECT

public:
    TestWindow(QWidget*, const QString&);
    ~TestWindow(void);

private slots:
    void onTimerTestTimeout(void);
    void onButtonNextClicked(void);
    void onTimerMinuteTimeout(void);
    void onButtonPreviousClicked(void);

private:
    Ui::TestWindow* ui;
    QLabel* labelTimer;
    QVBoxLayout* layout;
    QLabel* labelQuestion;
    QPushButton* buttonNext;
    QPushButton* buttonPrevious;

    QTimer* timerTest;
    QTimer* timerMinute;

    int testIndex;

    void stopTest(void);
    void displayTest(const int);
    void deleteTestUI(void) const;
    void updateResults(const int testIndex);
};

#endif // TESTWINDOW_H
