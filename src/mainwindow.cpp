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

    ui->label_linux->setVisible(false);
    if(app_dir != "") ui->label_linux->setVisible(true);

    // Initiale Erstellung der Projekte.lib sowie Auslesen der DB
    // Initialisierung der tableView's

    ui->tableView->setModel(readout("active"));
    ui->tableView->setColumnWidth(0,2);
    ui->tableView->setColumnWidth(1,350);
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

    createLanguageMenu();
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
        msgBox.setText("Bitte wählen Sie eine Zeile aus...\nPlease choose a row...");
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
    msgBox.setText("tu2 - PMS<br><br>repo: <a href=\"https://github.com/ntropy83/tu2\">github/ntropy83/tu2</a><br>Licensed under "
                   "<a href=\"https://github.com/ntropy83/tu2/blob/master/LICENSE\">GPL-3.0</a><br>v1.2.2");
    msgBox.exec();
}

void MainWindow::on_actionHilfe_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("[ger]<br>Klicken Sie auf Projektverwaltung im Menu und erstellen Sie ein Projekt.<br>Danach erscheint es in der Hauptliste und Details können per Doppelklick auf "
                   "die Zeile des Projektes aufgerufen werden.<br><br>Um Ein Projekt zu editieren, wählen sie mit einfachem Klick die Zeile des Projektes in der Hauptliste aus (Spalte ist egal) und "
                   "klicken Sie im Menu Projektverwaltung auf editieren. Jetzt können Sie auch Meilensteine hinzufügen und Projektfortschrittsberichte schreiben.<br><br>"
                   "[eng]<br>Click on Project Management in the menu and create a project by filling out its description.<br>After that it shows up in the main table and details can be viewed, if you "
                   "double click the entry.<br><br>To edit a project, chose it from the main table by clicking it once (column does not matter) and click Edit Project from the main menu. "
                   "Now you may add milestones and project progress reports aswell.");
    msgBox.exec();
}

// Close Program
void MainWindow::on_actionBeenden_triggered()
{
    this->close();
}

// we create the menu entries dynamically, dependent on the existing translations.
void MainWindow::createLanguageMenu(void)
{
    QActionGroup* langGroup = new QActionGroup(ui->menuLanguage);
    langGroup->setExclusive(true);

    connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

    // format systems language
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

    if (app_dir != ""){
        m_langPath = "";
    }else{
        m_langPath = QApplication::applicationDirPath();
    }

    if(app_dir != ""){
        m_langPath.append("/usr/lib/tu2/languages");
    }else{
        m_langPath.append("/languages");
    }

    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("tu2_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i) {
        // get locale extracted by filename
        QString locale;
        locale = fileNames[i]; // "tu2.qm"
        locale.truncate(locale.lastIndexOf('.')); // "tu2_de"
        locale.remove(0, locale.indexOf('_') + 1); // "de"

        QString lang = QLocale::languageToString(QLocale(locale).language());
        QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

        QAction *action = new QAction(ico, lang, this);
        action->setCheckable(true);
        action->setData(locale);

        ui->menuLanguage->addAction(action);
        langGroup->addAction(action);

        // set default translators and language checked
        if (defaultLocale == locale)
        {
            action->setChecked(true);
        }
    }
}

// Called every time, when a menu entry of the language menu is called
void MainWindow::slotLanguageChanged(QAction* action)
{
    if(0 != action) {
        // load the language dependant on the action content
        loadLanguage(action->data().toString());
        setWindowIcon(action->icon());
    }
}

void switchTranslator(QTranslator& translator, const QString& filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);

    // load the new translator
    QString path;

    if(app_dir != ""){
        path = "";
        path.append("/usr/lib/tu2/languages/");
    }else{
        path = QApplication::applicationDirPath();
        path.append("/languages/");
    }

     if(translator.load(path + filename)) //Here Path and Filename has to be entered because the system didn't find the QM Files else
          qApp->installTranslator(&translator);
}

void MainWindow::loadLanguage(const QString& rLanguage)
{
     if(m_currLang != rLanguage) {
          m_currLang = rLanguage;
          QLocale locale = QLocale(m_currLang);
          QLocale::setDefault(locale);
          QString languageName = QLocale::languageToString(locale.language());
          switchTranslator(m_translator, QString("tu2_%1.qm").arg(rLanguage));
          switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
     }
}

void MainWindow::changeEvent(QEvent* event)
{
     if(0 != event) {
          switch(event->type()) {
               // this event is send if a translator is loaded
               case QEvent::LanguageChange:
                    ui->retranslateUi(this);
               break;

               // this event is send, if the system, language changes
               case QEvent::LocaleChange:
               {
                    QString locale = QLocale::system().name();
                    locale.truncate(locale.lastIndexOf('_'));
                    loadLanguage(locale);
               }
               break;

               default:
               break;
         }
     }
     QMainWindow::changeEvent(event);
}
