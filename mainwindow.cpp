#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseconnect.h"
#include "odbcconnect.h"

#include <QtSql>
#include <QtGui>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_lastId = 0;
    m_bIdInit = true;
    m_gender = "Boy";
    ui->setupUi(this);
    DatabaseConnect();
    Clean();
    ShowChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_NameInput_textChanged(const QString &arg1)
{
    m_name = arg1;
}

void MainWindow::on_PhoneInput_textChanged(const QString &arg1)
{
    m_phone = arg1;
}

void MainWindow::on_BoyRadio_clicked()
{
    m_gender = "Boy";
}

void MainWindow::on_GirlRadio_clicked()
{
    m_gender = "Girl";
}

void MainWindow::on_ProfilePwd_textChanged(const QString &arg1)
{
    m_profile = arg1.toInt();
}

void MainWindow::on_SkiilPwd_textChanged(const QString &arg1)
{
    m_skill = arg1.toInt();
}

void MainWindow::on_NaturePwd_textChanged(const QString &arg1)
{
    m_nature = arg1.toInt();
}

void MainWindow::on_PerformancePwd_textChanged(const QString &arg1)
{
    m_performance = arg1.toInt();
}

void MainWindow::on_CommentInput_textChanged()
{
    m_comment = ui->CommentInput->toPlainText();
}

void MainWindow::on_Commit_clicked()
{
    if(m_name == ""){
        ui->NameInput->setText("No Name!");
        ui->NameInput->setFocus();
        return;
    }
    if(m_phone == ""){
        ui->PhoneInput->setText(QString("No Phone!"));
        ui->PhoneInput->setFocus();
        return;
    }

    QSqlQuery query;
    query.exec(QString("insert into brand values('%1', '%2', '%3', '%4', '%5', '%6',"
               "'%7', '%8', '%9')").arg(++m_lastId).arg(m_name).arg(m_phone).arg(m_gender)
               .arg(m_profile).arg(m_skill).arg(m_nature).arg(m_performance).arg(m_comment));
    Clean();
    ShowChart();
}

void MainWindow::on_Cancel_clicked()
{
    Clean();
}

void MainWindow::ShowChart()
{
    static QStandardItemModel *model = NULL;
    if(model != NULL){
        delete model;
    }
    model = new QStandardItemModel;

    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, QString("编号"));
    model->setHeaderData(1, Qt::Horizontal, QString("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QString("电话"));
    model->setHeaderData(3, Qt::Horizontal, QString("性别"));
    model->setSortRole(Qt::DisplayRole);

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->tableView->setColumnWidth(0,40);
    ui->tableView->setColumnWidth(1,100);
    ui->tableView->setColumnWidth(2,230);
    ui->tableView->setColumnWidth(3,40);

    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    QSqlQuery query;

    query.exec(QString("select id, name, phone, gender from brand"));
    for(int row = 0; query.next(); ++row){
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant(query.value(0).toInt()), Qt::EditRole);
        if(m_bIdInit){
            m_lastId = query.value(0).toInt();
        }
        model->setItem(row, 0, item);
        model->item(row,0)->setForeground(QBrush(QColor(255, 0, 0)));
        model->item(row,0)->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 1, new QStandardItem(QString(query.value(1).toString())));
        model->item(row,1)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,1)->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 2, new QStandardItem(query.value(2).toString()));
        model->item(row,2)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,2)->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 3, new QStandardItem(query.value(3).toString()));
        model->item(row,3)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,3)->setTextAlignment(Qt::AlignCenter);
    }

    model->sort(0, Qt::AscendingOrder);
    if(m_bIdInit){
        m_bIdInit = false;
    }
}

void MainWindow::Clean()
{
    m_name = "";
    m_phone = "";
    m_gender = "Boy";
    m_profile = 0;
    m_skill = 0;
    m_nature = 0;
    m_performance = 0;
    m_comment = "";

    ui->NameInput->clear();
    ui->PhoneInput->clear();
    ui->GirlRadio->setChecked(false);
    ui->BoyRadio->setChecked(true);
    ui->ProfilePwd->clear();
    ui->SkiilPwd->clear();
    ui->NaturePwd->clear();
    ui->PerformancePwd->clear();
    ui->CommentInput->clear();
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    int row = ui->tableView->indexAt(pos).row();
    int id = ui->tableView->model()->index(row, 0).data().toInt();
    QSqlQuery query;
    query.exec(QString("delete from brand where id='%1'").arg(id));
    ShowChart();
}

void MainWindow::on_ShowButton_clicked()
{
    if(ui->PasswordInput->text() != "ilovexcb" && ui->PasswordInput->text() != "ILOVEXCB"){
        ui->PasswordInput->setText(QString(""));
        ui->PasswordInput->setFocus();
        ui->CommentTable->hide();
    }
    else{
        ui->PasswordInput->setText(QString(""));
        ShowCommentChart();
    }
}

void MainWindow::sortByColumn(int column){
    ui->CommentTable->sortByColumn(column, Qt::DescendingOrder);
}

void MainWindow::ShowCommentChart(){
    ui->CommentTable->show();

    static QStandardItemModel *model = NULL;
    if(model != NULL){
        delete model;
    }
    model = new QStandardItemModel;

    model->setColumnCount(9);
    model->setHeaderData(0, Qt::Horizontal, QString("编号"));
    model->setHeaderData(1, Qt::Horizontal, QString("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QString("电话"));
    model->setHeaderData(3, Qt::Horizontal, QString("性别"));
    model->setHeaderData(4, Qt::Horizontal, QString("P"));
    model->setHeaderData(5, Qt::Horizontal, QString("S"));
    model->setHeaderData(6, Qt::Horizontal, QString("N"));
    model->setHeaderData(7, Qt::Horizontal, QString("P"));
    model->setHeaderData(8, Qt::Horizontal, QString("评论"));

    //ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    //ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);

    ui->CommentTable->setModel(model);
    ui->CommentTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    connect(ui->CommentTable->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sortByColumn(int)));

    ui->CommentTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->CommentTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->CommentTable->setContextMenuPolicy(Qt::CustomContextMenu);

    ui->CommentTable->setColumnWidth(0,40);
    ui->CommentTable->setColumnWidth(1,100);
    ui->CommentTable->setColumnWidth(2,100);
    ui->CommentTable->setColumnWidth(3,40);
    ui->CommentTable->setColumnWidth(4,40);
    ui->CommentTable->setColumnWidth(5,40);
    ui->CommentTable->setColumnWidth(6,40);
    ui->CommentTable->setColumnWidth(7,40);
    ui->CommentTable->setColumnWidth(8,340);

    for(int i = 0; i < 9; ++i){
        //ui->CommentTable->setRowHeight(300);
        ui->CommentTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed);
    }

    QSqlQuery query;

    query.exec(QString("select id, name, phone, gender, profile, skill, nature, performance, comment from brand"));
    for(int row = 0; query.next(); ++row){
        QStandardItem **item = new QStandardItem* [5];
        for(int i = 0; i < 5; ++i){
            item[i] = new QStandardItem;
        }

        item[0]->setData(QVariant(query.value(0).toInt()), Qt::EditRole);
        model->setItem(row, 0, item[0]);
        model->item(row,0)->setForeground(QBrush(QColor(255, 0, 0)));
        model->item(row,0)->setTextAlignment(Qt::AlignCenter);

        model->setItem(row, 1, new QStandardItem(QString(query.value(1).toString())));
        model->item(row,1)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,1)->setTextAlignment(Qt::AlignCenter);

        model->setItem(row, 2, new QStandardItem(query.value(2).toString()));
        model->item(row,2)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,2)->setTextAlignment(Qt::AlignCenter);

        model->setItem(row, 3, new QStandardItem(query.value(3).toString()));
        model->item(row,3)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,3)->setTextAlignment(Qt::AlignCenter);

        item[1]->setData(QVariant(query.value(4).toInt()), Qt::EditRole);
        model->setItem(row, 4, item[1]);
        model->item(row,4)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,4)->setTextAlignment(Qt::AlignCenter);

        item[2]->setData(QVariant(query.value(5).toInt()), Qt::EditRole);
        model->setItem(row, 5, item[2]);
        model->item(row,5)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,5)->setTextAlignment(Qt::AlignCenter);

        item[3]->setData(QVariant(query.value(6).toInt()), Qt::EditRole);
        model->setItem(row, 6, item[3]);
        model->item(row,6)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,6)->setTextAlignment(Qt::AlignCenter);

        item[4]->setData(QVariant(query.value(7).toInt()), Qt::EditRole);
        model->setItem(row, 7, item[4]);
        model->item(row,7)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,7)->setTextAlignment(Qt::AlignCenter);

        model->setItem(row, 8, new QStandardItem(query.value(8).toString()));
        model->item(row,8)->setForeground(QBrush(QColor(0, 0, 0)));
        model->item(row,8)->setTextAlignment(Qt::AlignCenter);
    }

    model->sort(0, Qt::AscendingOrder);
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 1){
         ui->CommentTable->hide();
    }
}

void MainWindow::on_actionExport_triggered()
{
    if(!ui->CommentTable->isVisible()){
        ShowCommentChart();
        ui->CommentTable->hide();
    }


    QFileDialog dlg;
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    dlg.setNameFilter("*.xls");
    dlg.selectFile(QDate::currentDate().toString("yyyy-MM-dd.xls"));
    if(dlg.exec() != QDialog::Accepted){
        return;
    }
    QString filePath = dlg.selectedFiles()[0];
    if(!odbcConnect::saveFromTable(filePath, ui->CommentTable, QString("自动存储系统"))){
    }
}
