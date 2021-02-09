#include "../inc/save_handler.hpp"
#include "../inc/mainwindow.hpp"
#include "../inc/projectdialog.hpp"
#include "../inc/project_poster.hpp"
#include "ui_mainwindow.h"

#include <QFile>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(app_dir != "") ui->label_linux->setEnabled(true);

    // Initiale Erstellung der Projekte.lib sowie Auslesen der DB
    // Initialisierung der tableView's

    ui->tableView->setModel(readout("active"));
    ui->tableView->setColumnWidth(0,2);
    ui->tableView->setColumnWidth(1,250);
    ui->tableView->setColumnWidth(7,200);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_2->setModel(readout("ended"));
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setColumnWidth(0,2);
    ui->tableView_2->setColumnWidth(1,250);
    ui->tableView_2->setColumnWidth(7,200);
    ui->tableView_2->verticalHeader()->setVisible(false);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// tableView refresh nach der Projektspeicherung
void MainWindow::refresh_mainWindow()
{
    ui->tableView->setModel(readout("active"));
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnWidth(0,2);
    ui->tableView->verticalHeader()->setVisible(false);

    ui->tableView_2->setModel(readout("ended"));
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_2->setColumnWidth(0,2);
    ui->tableView_2->verticalHeader()->setVisible(false);
}

// Signalverbindung mit dem projectdialog Fenster
void MainWindow::on_actionProjekt_erstellen_triggered()
{
    projectDialog pDialog;
    pDialog.setModal(true);
    connect(&pDialog, SIGNAL(refresh_mainWindow()), this, SLOT(refresh_mainWindow()));
    pDialog.exec();
}

// Projekt editieren
void MainWindow::on_actionProjekt_editieren_triggered()
{
    if(ui->tableView->currentIndex().isValid() && ui->tabWidget->currentIndex() == 0)
    {
        projectDialog pDialog;
        pDialog.setEditText(ui->tableView->model()->data(ui->tableView->model()->index(
                                                             ui->tableView->selectionModel()->currentIndex().row(),0)).toString());
        pDialog.setModal(true);
        connect(&pDialog, SIGNAL(refresh_mainWindow()), this, SLOT(refresh_mainWindow()));
        pDialog.exec();
    }else if(ui->tableView_2->currentIndex().isValid() && ui->tabWidget->currentIndex() == 1)
    {
        projectDialog pDialog;
        pDialog.setEditText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(
                                                               ui->tableView_2->selectionModel()->currentIndex().row(),0)).toString());
        pDialog.setModal(true);
        connect(&pDialog, SIGNAL(refresh_mainWindow()), this, SLOT(refresh_mainWindow()));
        pDialog.exec();
    }else{
        QMessageBox msgBox;
        msgBox.setText("Bitte wählen Sie eine Zeile aus...");
        msgBox.exec();
    }
}

void MainWindow::on_tableView_doubleClicked()
{
    if(ui->tableView->currentIndex().isValid() && ui->tabWidget->currentIndex() == 0)
    {
        project_poster ppDialog;
        ppDialog.setprojectText(ui->tableView->model()->data(ui->tableView->model()->index(
                                                             ui->tableView->selectionModel()->currentIndex().row(),0)).toString());
        ppDialog.setModal(true);
        ppDialog.exec();
    }else if(ui->tableView_2->currentIndex().isValid() && ui->tabWidget->currentIndex() == 1)
    {
        project_poster ppDialog;
        ppDialog.setprojectText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(
                                                               ui->tableView_2->selectionModel()->currentIndex().row(),0)).toString());
        ppDialog.setModal(true);
        ppDialog.exec();
    }
}

void MainWindow::on_tableView_2_doubleClicked()
{
    if(ui->tableView->currentIndex().isValid() && ui->tabWidget->currentIndex() == 0)
    {
        project_poster ppDialog;
        ppDialog.setprojectText(ui->tableView->model()->data(ui->tableView->model()->index(
                                                             ui->tableView->selectionModel()->currentIndex().row(),0)).toString());
        ppDialog.setModal(true);
        ppDialog.exec();
    }else if(ui->tableView_2->currentIndex().isValid() && ui->tabWidget->currentIndex() == 1)
    {
        project_poster ppDialog;
        ppDialog.setprojectText(ui->tableView_2->model()->data(ui->tableView_2->model()->index(
                                                               ui->tableView_2->selectionModel()->currentIndex().row(),0)).toString());
        ppDialog.setModal(true);
        ppDialog.exec();
    }
}

// Show Version
void MainWindow::on_actionVersion_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Projektverwaltung v1.1.1<br><br>by <a href=\"https://github.com/enthalpie/TUII\">tu2_ntropy</a><br><br><br>Licensed under "
                   "<a href=\"https://github.com/enthalpie/TUII/blob/master/LICENSE\">GPL-3.0</a>");
    msgBox.exec();
}

void MainWindow::on_actionHilfe_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Klicken Sie auf Projektverwaltung im Menu und erstellen Sie ein Projekt.<br>Danach erscheint es in der Hauptliste und Details können per Doppelklick auf "
                   "die Zeile des Projektes aufgerufen werden.<br><br>Um Ein Projekt zu editieren, wählen sie mit einfachem Klick die Zeile des Projektes in der Hauptliste aus (Spalte ist egal) und "
                   "klicken Sie im Menu Projektverwaltung auf editieren. Jetzt können Sie auch Meilensteine hinzufügen und Projektfortschrittsberichte schreiben.");
    msgBox.exec();
}

// Close Program
void MainWindow::on_actionBeenden_triggered()
{
    this->close();
}
