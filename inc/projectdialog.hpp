#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class projectDialog;
}

class projectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit projectDialog(QWidget *parent = nullptr);
    ~projectDialog();
    void setEditText(QString index);
    void enable_milestone_buttons(bool setting);

signals:
    void refresh_mainWindow();

private slots:
    void on_pushButton_saveall_clicked();

    void on_pushButton_new_milestones_clicked();

    void on_pushButton_project_new_clicked();

    void on_pushButton_edit_milestones_clicked();

    void on_pushButton_project_edit_clicked();

    void on_horizontalSlider_AEffekt_valueChanged(int position);

    void on_horizontalSlider_Wertschoepfung_valueChanged(int position);

    void on_horizontalSlider_oeffi_valueChanged(int position);

    void on_horizontalSlider_Bindung_valueChanged(int position);

    void on_horizontalSlider_AEffekte_ab_valueChanged(int value);

    void on_horizontalSlider_WEffekte_ab_valueChanged(int value);

    void on_horizontalSlider_OEffekte_ab_valueChanged(int value);

    void on_horizontalSlider_NEffekte_ab_valueChanged(int value);

private:
    Ui::projectDialog *ui;
};

#endif // PROJECTDIALOG_H
