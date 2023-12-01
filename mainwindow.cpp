#include <QFOnt>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "testwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->setWindowTitle("Lab3. Поляков, IO-15");
    this->setMinimumSize(300, 100);
    this->setMaximumSize(300, 100);

    this->buttonLoadTest = new QPushButton(this);

    this->buttonLoadTest->setGeometry(50, 25, 200, 50);

    this->buttonLoadTest->setText(">>> SELECT TEST <<<");
    this->buttonLoadTest->setFont(QFont(this->buttonLoadTest->font().family(), 12));

    connect(this->buttonLoadTest, &QPushButton::clicked, this, &MainWindow::onButtonLoadTestClicked);
}

void MainWindow::onButtonLoadTestClicked(void)
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr(">>> SELECT TEST <<<"), QDir::currentPath(), tr("All Files (*.txt)"));

    if (!fileName.isEmpty())
    {
        this->hide();
        this->testWindow = new TestWindow(this, fileName);
        this->testWindow->show();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("You have not selected any test"));
    }
}

MainWindow::~MainWindow(void)
{
    delete this->ui;
    this->ui = nullptr;

    delete this->buttonLoadTest;
    this->buttonLoadTest = nullptr;
}
