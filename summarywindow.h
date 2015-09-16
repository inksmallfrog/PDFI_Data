#ifndef SUMMARYWINDOW_H
#define SUMMARYWINDOW_H

#include <QWidget>

namespace Ui {
class SummaryWindow;
}

class SummaryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SummaryWindow(QWidget *parent = 0);
    ~SummaryWindow();

private:
    Ui::SummaryWindow *ui;
};

#endif // SUMMARYWINDOW_H
