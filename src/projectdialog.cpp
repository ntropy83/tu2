#include "../inc/projectdialog.h"
#include "ui_projectdialog.h"
#include "src/project_poster.cpp"

#include <QTimer>
#include <QMessageBox>

projectDialog::projectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::projectDialog)
{
    ui->setupUi(this);
    ui->label_saved->setVisible(false);
    ui->label_error->setVisible(false);
    ui->label_new_mile->setVisible(false);
    ui->label_new_project->setVisible(false);

    enable_milestone_buttons(false);
    ui->tabWidget->setTabEnabled(3, false);

    this->setTabOrder(ui->lineEdit_title, ui->lineEdit_MA);
    this->setTabOrder(ui->lineEdit_MA, ui->dateEdit_start);

    this->setTabOrder(ui->radioButton_4, ui->dateEdit_milestones);
    this->setTabOrder(ui->dateEdit_milestones, ui->textEdit_milestones);
    this->setTabOrder(ui->textEdit_milestones, ui->pushButton_new_milestones);
    this->setTabOrder(ui->pushButton_new_milestones, ui->pushButton_edit_milestones);
    this->setTabOrder(ui->pushButton_edit_milestones, ui->dateEdit_project);
    this->setTabOrder(ui->dateEdit_project, ui->textEdit_project);
    this->setTabOrder(ui->textEdit_project, ui->pushButton_project_new);
    this->setTabOrder(ui->pushButton_project_new, ui->pushButton_project_edit);
    this->setTabOrder(ui->pushButton_project_edit, ui->pushButton_saveall);

    this->setTabOrder(ui->textEdit_Bewertung, ui->horizontalSlider_AEffekt);
    this->setTabOrder(ui->horizontalSlider_AEffekt, ui->horizontalSlider_Wertschoepfung);
    this->setTabOrder(ui->horizontalSlider_Wertschoepfung, ui->horizontalSlider_oeffi);
    this->setTabOrder(ui->horizontalSlider_oeffi, ui->horizontalSlider_Bindung);
    this->setTabOrder(ui->horizontalSlider_Bindung, ui->lineEdit_res_personell);
    this->setTabOrder(ui->lineEdit_res_personell, ui->lineEdit_res_finanziell);
    this->setTabOrder(ui->lineEdit_res_finanziell, ui->textEdit_risiken);
    this->setTabOrder(ui->textEdit_risiken, ui->pushButton_saveall);

    this->setTabOrder(ui->horizontalSlider_NEffekte_ab, ui->lineEdit_res_personell_ab);
    this->setTabOrder(ui->lineEdit_res_personell_ab, ui->lineEdit_res_finanziell_ab);
    this->setTabOrder(ui->lineEdit_res_finanziell_ab, ui->textEdit_llearned);
    this->setTabOrder(ui->textEdit_llearned, ui->pushButton_saveall);
}

projectDialog::~projectDialog()
{
    delete ui;
    global_edit = "nein";
}

void projectDialog::enable_milestone_buttons(bool setting){
    ui->label_milestones->setEnabled(setting);
    ui->tableView_milestones->setEnabled(setting);
    ui->dateEdit_milestones->setEnabled(setting);
    //ui->pushButton_new_milestones->setEnabled(setting);
    ui->pushButton_edit_milestones->setEnabled(setting);
    ui->textEdit_milestones->setEnabled(setting);

    ui->tableView_milestones->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_milestones->verticalHeader()->setVisible(false);
    ui->tableView_milestones->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_milestones->setWordWrap(true);
    ui->tableView_milestones->setTextElideMode(Qt::ElideMiddle);

    ui->label_project->setEnabled(setting);
    ui->tableView_project->setEnabled(setting);
    ui->dateEdit_project->setEnabled(setting);
    //ui->pushButton_project_new->setEnabled(setting);
    ui->pushButton_project_edit->setEnabled(setting);
    ui->textEdit_project->setEnabled(setting);

    ui->tableView_project->horizontalHeader()->setStretchLastSection(true);
    ui->tableView_project->verticalHeader()->setVisible(false);
    ui->tableView_project->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView_project->setWordWrap(true);
    ui->tableView_project->setTextElideMode(Qt::ElideMiddle);
}

void projectDialog::setEditText(QString index){

    QStringList line_data = edit_readout(index);
    global_edit = index;
    enable_milestone_buttons(true);
    ui->tabWidget->setTabEnabled(3, true);
    ui->tableView_milestones->setModel(readout_mp("_m"));
    ui->tableView_project->setModel(readout_mp("_p"));

    ui->lineEdit_title->setText(line_data.at(1));
    ui->lineEdit_MA->setText(line_data.at(2));

    QDate Date = QDate::fromString(line_data.at(4),"dd.MM.yyyy");
    ui->dateEdit_start->setDate(Date);
    ui->dateEdit_start->setEnabled(false);

    if(line_data.at(3) == "aktiv"){
        ui->radioButton->setChecked(true);
    }else if(line_data.at(3) == "pausiert"){
        ui->radioButton_2->setChecked(true);
    }else if(line_data.at(3) == "beendet"){
        ui->radioButton_3->setChecked(true);
    }

    QDate Date_Bericht = QDate::fromString(line_data.at(6),"dd.MM.yyyy");
    ui->dateEdit_Bericht->setDate(Date_Bericht);

    if(line_data.at(7) == "nein"){
        ui->radioButton_5->setChecked(true);
    }else if(line_data.at(7) == "ja"){
        ui->radioButton_4->setChecked(true);
    }

    ui->textEdit_bemerkung->setText(line_data.at(8));
    ui->lineEdit_participants->setText(line_data.at(9));
    ui->textEdit_pgoals->setText(line_data.at(10));
    ui->textEdit_role->setText(line_data.at(11));
    ui->textEdit_ptext->setText(line_data.at(12));

    if(line_data.at(13) == "unbewertet"){
        QDate Date_Bewertung = QDate::fromString(global_start_time,"dd.MM.yyyy");
        ui->dateEdit_Bewertung->setDate(Date_Bewertung);
    }else{
        QDate Date_Bewertung = QDate::fromString(line_data.at(13),"dd.MM.yyyy");
        ui->dateEdit_Bewertung->setDate(Date_Bewertung);
    }
    ui->textEdit_Bewertung->setText(line_data.at(14));
    ui->horizontalSlider_AEffekt->setValue(line_data.at(15).toInt());
    ui->label_AEffekte->setText(line_data.at(15));
    ui->horizontalSlider_Wertschoepfung->setValue(line_data.at(16).toInt());
    ui->label_WEffekte->setText(line_data.at(16));
    ui->horizontalSlider_oeffi->setValue(line_data.at(17).toInt());
    ui->label_OEffekte->setText(line_data.at(17));
    ui->horizontalSlider_Bindung->setValue(line_data.at(18).toInt());
    ui->label_NEffekte->setText(line_data.at(18));

    ui->lineEdit_res_personell->setText(line_data.at(19));
    ui->lineEdit_res_finanziell->setText(line_data.at(20));
    ui->textEdit_risiken->setText(line_data.at(21));

    QDate Date_abschluss = QDate::fromString(line_data.at(22),"dd.MM.yyyy");
    ui->dateEdit_abschluss->setDate(Date_abschluss);

    ui->textEdit_fazit_ab->setText(line_data.at(23));
    ui->horizontalSlider_AEffekte_ab->setValue(line_data.at(24).toInt());
    ui->label_AEffekte_ab->setText(line_data.at(24));
    ui->horizontalSlider_WEffekte_ab->setValue(line_data.at(25).toInt());
    ui->label_WEffekte_ab->setText(line_data.at(25));
    ui->horizontalSlider_OEffekte_ab->setValue(line_data.at(26).toInt());
    ui->label_OEffekte_ab->setText(line_data.at(26));
    ui->horizontalSlider_NEffekte_ab->setValue(line_data.at(27).toInt());
    ui->label_NEffekte_ab->setText(line_data.at(27));

    ui->lineEdit_res_personell_ab->setText(line_data.at(28));
    ui->lineEdit_res_finanziell_ab->setText(line_data.at(29));
    ui->textEdit_llearned->setText(line_data.at(30));
}

void projectDialog::on_pushButton_saveall_clicked()
{
    QString Zustand, report;
    if(!(ui->lineEdit_title->text()=="") && !(ui->lineEdit_MA->text()=="") && !(ui->lineEdit_participants->text()=="")
            && !(ui->textEdit_pgoals->toPlainText()=="") && !(ui->textEdit_role->toPlainText()=="") && !(ui->textEdit_ptext->toPlainText()=="")){

    if(ui->radioButton->isChecked())
        Zustand = ui->radioButton->text();
    if(ui->radioButton_2->isChecked())
        Zustand = ui->radioButton_2->text();
    if(ui->radioButton_3->isChecked())
        Zustand = ui->radioButton_3->text();
    if(ui->radioButton_4->isChecked())
        report = ui->radioButton_4->text();
    if(ui->radioButton_5->isChecked())
        report = ui->radioButton_5->text();

    QString report_date = ui->dateEdit_Bericht->text();
    QString update_report = "-";
    if(global_edit != "" && global_edit != "nein"){
        if (ui->tableView_project->model()->index(0,0).data().toString() != ""){
            update_report = ui->tableView_project->model()->index(0,0).data().toString();
        }
    }

    if(ui->textEdit_Bewertung->toPlainText() == ""){ ui->textEdit_Bewertung->setPlainText("-"); }
    if(ui->lineEdit_res_personell->text() == ""){ ui->lineEdit_res_personell->setText("-"); }
    if(ui->lineEdit_res_finanziell->text() == ""){ ui->lineEdit_res_finanziell->setText("-"); }
    if(ui->textEdit_risiken->toPlainText() == ""){ ui->textEdit_risiken->setText("-"); }

    if(ui->textEdit_fazit_ab->toPlainText() == ""){ ui->textEdit_fazit_ab->setPlainText("-"); }
    if(ui->lineEdit_res_personell_ab->text() == ""){ ui->lineEdit_res_personell_ab->setText("-"); }
    if(ui->lineEdit_res_finanziell_ab->text() == ""){ ui->lineEdit_res_finanziell_ab->setText("-"); }
    if(ui->textEdit_llearned->toPlainText() == ""){ ui->textEdit_llearned->setText("-"); }

            create_entry_lib(ui->lineEdit_title->text(),ui->lineEdit_MA->text(),Zustand,ui->dateEdit_start->text(),
                            update_report, report_date , report,
                            ui->textEdit_bemerkung->toPlainText(),ui->lineEdit_participants->text(),ui->textEdit_pgoals->toPlainText(),
                            ui->textEdit_role->toPlainText(),ui->textEdit_ptext->toPlainText(), ui->dateEdit_Bewertung->text(), ui->textEdit_Bewertung->toPlainText(), ui->label_AEffekt->text(),
                            ui->label_Wertschoepfung->text(), ui->label_oeffi->text(), ui->label_Bindung->text(),
                            ui->lineEdit_res_personell->text(), ui->lineEdit_res_finanziell->text(), ui->textEdit_risiken->toPlainText(),ui->dateEdit_abschluss->text(),
                            ui->textEdit_fazit_ab->toPlainText(), ui->label_AEffekte_ab->text(), ui->label_WEffekte_ab->text(), ui->label_OEffekte_ab->text(), ui->label_NEffekte_ab->text(),
                            ui->lineEdit_res_personell_ab->text(), ui->lineEdit_res_finanziell_ab->text(), ui->textEdit_llearned->toPlainText());
            ui->label_saved->setVisible(true);
            QTimer::singleShot(3000, ui->label_saved, &QLabel::hide);
            ui->pushButton_saveall->setVisible(false);
            QTimer::singleShot(500, this, &QDialog::close);
            emit refresh_mainWindow();
    }else{
            ui->label_error->setVisible(true);
            QTimer::singleShot(5000, ui->label_error, &QLabel::hide);
    }
}

void projectDialog::on_pushButton_new_milestones_clicked()
{
    QDate Date = QDate::fromString(global_start_time,"dd.MM.yyyy");
    if(ui->dateEdit_milestones->text() != global_start_time && ui->textEdit_milestones->toPlainText() != ""){

        create_mp(ui->dateEdit_milestones->text(), ui->textEdit_milestones->toPlainText(), "_m");
        ui->dateEdit_milestones->setDate(Date);
        ui->textEdit_milestones->setText("");
        ui->label_new_mile->setVisible(true);
        QTimer::singleShot(4000, ui->label_new_mile, &QLabel::hide);

        ui->tableView_milestones->setModel(readout_mp("_m"));

    }else{
        QMessageBox msgBox;
        msgBox.setText("Sie müssen ein Datum wählen und einen Text eingeben...");
        msgBox.exec();
    }
}

void projectDialog::on_pushButton_project_new_clicked()
{
    QDate Date = QDate::fromString(global_start_time,"dd.MM.yyyy");
    if(ui->dateEdit_project->text() != global_start_time && ui->textEdit_project->toPlainText() != ""){

        create_mp(ui->dateEdit_project->text(), ui->textEdit_project->toPlainText(), "_p");
        ui->dateEdit_project->setDate(Date);
        ui->textEdit_project->setText("");
        ui->label_new_project->setVisible(true);
        QTimer::singleShot(4000, ui->label_new_project, &QLabel::hide);

        ui->tableView_project->setModel(readout_mp("_p"));

    }else{
        QMessageBox msgBox;
        msgBox.setText("Sie müssen ein Datum wählen und einen Text eingeben...");
        msgBox.exec();
    }
}

void projectDialog::on_pushButton_edit_milestones_clicked()
{    
    if(ui->pushButton_edit_milestones->text() != "Speichern"){
        if(ui->tableView_milestones->currentIndex().isValid())
        {
             QStringList line_data = edit_readout_mp("_m");
             ui->pushButton_new_milestones->setEnabled(false);
             ui->pushButton_edit_milestones->setText("Speichern");

             QDate milestone_date = QDate::fromString(line_data[ui->tableView_milestones->currentIndex().row()*2],"dd.MM.yyyy");

             ui->dateEdit_milestones->setDate(milestone_date);
             ui->textEdit_milestones->setText(line_data[ui->tableView_milestones->currentIndex().row()*2+1]);
             ui->tableView_milestones->setEnabled(false);

        }else{
             QMessageBox msgBox;
             msgBox.setText("Bitte wählen Sie einen Meilenstein aus...");
             msgBox.exec();
        }
    }else{
        edit_create_mp(ui->tableView_milestones->currentIndex().row()*2, "_m", ui->dateEdit_milestones->text(), ui->textEdit_milestones->toPlainText());
        ui->tableView_milestones->setEnabled(true);
        ui->pushButton_new_milestones->setEnabled(true);
        ui->pushButton_edit_milestones->setText("Editieren");

        QDate milestone_date = QDate::fromString(global_start_time,"dd.MM.yyyy");
        ui->dateEdit_milestones->setDate(milestone_date);
        ui->textEdit_milestones->setText("");
        ui->tableView_milestones->setModel(readout_mp("_m"));
    }
}

void projectDialog::on_pushButton_project_edit_clicked()
{
    if(ui->pushButton_project_edit->text() != "Speichern"){
        if(ui->tableView_project->currentIndex().isValid())
        {
             QStringList line_data = edit_readout_mp("_p");
             ui->pushButton_project_new->setEnabled(false);
             ui->pushButton_project_edit->setText("Speichern");

             QDate project_date = QDate::fromString(line_data[ui->tableView_project->currentIndex().row()*2],"dd.MM.yyyy");

             ui->dateEdit_project->setDate(project_date);
             ui->textEdit_project->setText(line_data[ui->tableView_project->currentIndex().row()*2+1]);
             ui->tableView_project->setEnabled(false);

        }else{
             QMessageBox msgBox;
             msgBox.setText("Bitte wählen Sie einen Projektfortschrittseintrag aus...");
             msgBox.exec();
        }
    }else{
        edit_create_mp(ui->tableView_project->currentIndex().row()*2, "_p", ui->dateEdit_project->text(), ui->textEdit_project->toPlainText());
        ui->tableView_project->setEnabled(true);
        ui->pushButton_project_new->setEnabled(true);
        ui->pushButton_project_edit->setText("Editieren");

        QDate project_date = QDate::fromString(global_start_time,"dd.MM.yyyy");
        ui->dateEdit_project->setDate(project_date);
        ui->textEdit_project->setText("");
        ui->tableView_project->setModel(readout_mp("_p"));
    }
}

void projectDialog::on_horizontalSlider_AEffekt_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_AEffekt->setText(pos);
}

void projectDialog::on_horizontalSlider_Wertschoepfung_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_Wertschoepfung->setText(pos);
}

void projectDialog::on_horizontalSlider_oeffi_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_oeffi->setText(pos);
}

void projectDialog::on_horizontalSlider_Bindung_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_Bindung->setText(pos);
}

void projectDialog::on_horizontalSlider_AEffekte_ab_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_AEffekte_ab->setText(pos);
}

void projectDialog::on_horizontalSlider_WEffekte_ab_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_WEffekte_ab->setText(pos);
}

void projectDialog::on_horizontalSlider_OEffekte_ab_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_OEffekte_ab->setText(pos);
}

void projectDialog::on_horizontalSlider_NEffekte_ab_valueChanged(int value)
{
    QString pos = QVariant(value).toString();
    ui->label_NEffekte_ab->setText(pos);
}

void projectDialog::on_textEdit_milestones_textChanged()
{
    ui->pushButton_new_milestones->setEnabled(true);
}

void projectDialog::on_textEdit_project_textChanged()
{
    ui->pushButton_project_new->setEnabled(true);
}
