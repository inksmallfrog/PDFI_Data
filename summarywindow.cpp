#include "summarywindow.h"
#include "ui_summarywindow.h"

SummaryWindow::SummaryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SummaryWindow)
{
    ui->setupUi(this);
}

SummaryWindow::~SummaryWindow()
{
    delete ui;
}
