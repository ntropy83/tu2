#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    // this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

protected slots:
    // this slot is called by the language menu actions
    void slotLanguageChanged(QAction* action);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionProjekt_erstellen_triggered();
    void on_actionProjekt_editieren_triggered();
    void on_actionBeenden_triggered();
    void refresh_mainWindow();
    void on_actionVersion_triggered();

    void on_tableView_doubleClicked();
    void on_tableView_2_doubleClicked();

    void on_actionHilfe_triggered();

private:
    // loads a language by the given language shortcur (e.g. de, en)
    void loadLanguage(const QString& rLanguage);

    // creates the language menu dynamically from the content of m_langPath
    void createLanguageMenu(void);

    Ui::MainWindow *ui; // ui definition from designer
    QTranslator m_translator; // contains the translations for this application
    QTranslator m_translatorQt; // contains the translations for qt
    QString m_currLang; // contains the currently loaded language
    QString m_langPath; // Path of language files. This is always fixed to /languages.
};

#endif // MAINWINDOW_H
