#include "../inc/project_poster.h"
#include "ui_project_poster.h"
#include "src/save_handler.cpp"

project_poster::project_poster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::project_poster)
{
    ui->setupUi(this);
}

project_poster::~project_poster()
{
    delete ui;
    global_edit = "nein";
}

void project_poster::setprojectText(QString index){

   QStringList line_data = edit_readout(index);
   global_edit = index;
   this->setWindowTitle("Projektsteckbrief - " + line_data[1]);

   ui->label_titel->setText(line_data[1]);
   ui->label_MA->setText(line_data[2]);
   ui->label_Beteiligte->setText(line_data[9]);
   ui->label_status->setText(line_data[3]);

   if(line_data[3] == "aktiv"){
       ui->label_status_ampel->setStyleSheet("background-color: green;\ncolor: green;");
   }else if(line_data[3] == "pausiert"){
       ui->label_status_ampel->setStyleSheet("background-color: cyan;\ncolor: cyan;");
   }else if(line_data[3] == "beendet"){
       ui->label_status_ampel->setStyleSheet("background-color: red;\ncolor: red;");
   }

   ui->textEdit_rolle->setText(line_data[11]);
   ui->textEdit_ziele->setText(line_data[10]);
   ui->textEdit_beschreibung->setText(line_data[12]);

   ui->groupBox_2->setEnabled(false);
   ui->groupBox_7->setEnabled(false);
   ui->graphicsView->setEnabled(false);
   ui->graphicsView_3->setEnabled(false);

   if(line_data.at(13) == global_start_time){
       ui->label_bewertung->setText("<b>unbewertet</b>");
   }else{
       ui->label_bewertung->setText("Datum der Bewertung: " + line_data.at(13));
       ui->groupBox_2->setEnabled(true);
       ui->graphicsView->setEnabled(true);
   }
   ui->textEdit_beitrag_ziele->setText(line_data.at(14));
   ui->progressBar_AEffekte->setValue(line_data.at(15).toInt());
   ui->progressBar_WEffekte->setValue(line_data.at(16).toInt());
   ui->progressBar_OEffeke->setValue(line_data.at(17).toInt());
   ui->progressBar_NEffekte->setValue(line_data.at(18).toInt());
   ui->lineEdit_res_person->setText(line_data.at(19));
   ui->lineEdit_res_finanz->setText(line_data.at(20));
   ui->textEdit_kp->setText(line_data.at(21));

   if(line_data.at(22) == global_start_time){
       ui->label_bewertung_ab->setText("<b>unbewertet</b>");
   }else{
       ui->label_bewertung_ab->setText("Datum der Bewertung: " + line_data.at(22));
       ui->groupBox_7->setEnabled(true);
       ui->graphicsView_3->setEnabled(true);
   }
   ui->textEdit_fazit_ab->setText(line_data.at(23));
   ui->progressBar_AEffekte_ab->setValue(line_data.at(24).toInt());
   ui->progressBar_WEffekte_ab->setValue(line_data.at(25).toInt());
   ui->progressBar_OEffeke_ab->setValue(line_data.at(26).toInt());
   ui->progressBar_NEffekte_ab->setValue(line_data.at(27).toInt());
   ui->lineEdit_res_person_ab->setText(line_data.at(28));
   ui->lineEdit_res_finanz_ab->setText(line_data.at(29));
   ui->textEdit_ll->setText(line_data.at(30));

   ui->tableView_milestones->setModel(readout_mp("_m"));
   ui->tableView_fortschritt->setModel(readout_mp("_p"));

   ui->tableView_milestones->horizontalHeader()->setStretchLastSection(true);
   ui->tableView_milestones->verticalHeader()->setVisible(false);
   ui->tableView_milestones->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   ui->tableView_milestones->setEditTriggers(QAbstractItemView::NoEditTriggers);

   ui->tableView_fortschritt->horizontalHeader()->setStretchLastSection(true);
   ui->tableView_fortschritt->verticalHeader()->setVisible(false);
   ui->tableView_fortschritt->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
   ui->tableView_fortschritt->setEditTriggers(QAbstractItemView::NoEditTriggers);


}
