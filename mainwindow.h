#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ShowChart();
    void ShowCommentChart();
    void Clean();

private slots:
    void on_NameInput_textChanged(const QString &arg1);

    void on_PhoneInput_textChanged(const QString &arg1);

    void on_BoyRadio_clicked();

    void on_GirlRadio_clicked();

    void on_ProfilePwd_textChanged(const QString &arg1);

    void on_SkiilPwd_textChanged(const QString &arg1);

    void on_NaturePwd_textChanged(const QString &arg1);

    void on_PerformancePwd_textChanged(const QString &arg1);

    void on_CommentInput_textChanged();

    void on_Commit_clicked();

    void on_Cancel_clicked();

    void on_actionExit_triggered();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

    void on_ShowButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void sortByColumn(int column);

    void on_actionExport_triggered();

private:
    Ui::MainWindow *ui;

    int m_lastId;
    bool m_bIdInit;

    QString m_name;
    QString m_phone;
    QString m_gender;

    int m_profile;
    int m_skill;
    int m_nature;
    int m_performance;

    QString m_comment;
};

#endif // MAINWINDOW_H
