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
    msgBox.setText("Projektverwaltung v1.0.0<br><br>by <a href=\"https://github.com/enthalpie/TUII\">TUII_enthalpie_github</a><br><br><br>Licensed under "
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

// we create the menu entries dynamically, dependent on the existing translations.
void MainWindow::createLanguageMenu(void)
{
 QActionGroup* langGroup = new QActionGroup(ui->menuLanguage);
 langGroup->setExclusive(true);

 connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

 // format systems language
 QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
 defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"

 m_langPath = QApplication::applicationDirPath();
 m_langPath.append("/languages");
 QDir dir(m_langPath);
 QStringList fileNames = dir.entryList(QStringList("TranslationExample_*.qm"));

 for (int i = 0; i < fileNames.size(); ++i) {
  // get locale extracted by filename
  QString locale;
  locale = fileNames[i]; // "TranslationExample_de.qm"
  locale.truncate(locale.lastIndexOf('.')); // "TranslationExample_de"
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
QString path = QApplication::applicationDirPath();
    path.append("/languages/");
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
  switchTranslator(m_translator, QString("TranslationExample_%1.qm").arg(rLanguage));
  switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
  //ui->statusBar.showMessage(tr("Current Language changed to %1").arg(languageName));
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
  }
 }
 QMainWindow::changeEvent(event);
}


void MainWindow::on_actionDeutsch_triggered()
{
    //slotLanguageChanged("de");
}

void MainWindow::on_actionEnglisch_triggered()
{

}
