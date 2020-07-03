#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

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
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
