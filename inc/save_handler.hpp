#ifndef SAVE_HANDLER_H
#define SAVE_HANDLER_H

#include <iostream>

#include "globals.hpp"

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QStandardItem>
#include <QDateTime>

// Tage die vergangen sein müssen, bis zur Update Warnung
static int yellow_warn = 14;
static int red_warn = 31;

// Datumssortierer - Struct's
struct date_sort {
    int datum;
    QString text;
};

// Speicherpfade definieren

#ifdef _WIN32
    static QString app_dir = "";
    static QString maindir = "Projekte/";
    static QString prjdir = "data/";
    static QString lib_index = "index.lib";
#else
    static QString home = QDir::homePath();
    static QString app_dir = home + "/.local/share/tu2";
    static QString maindir = home + "/.local/share/tu2/Projekte/";
    static QString prjdir = home + "/.local/share/tu2/data/";
    static QString lib_index = home + "/.local/share/tu2/index.lib";
#endif

// Zählt die Anzahl der Projekte und inkrementiert sie bei Neuanlage
inline QString counter(QString action){

    QFile file(lib_index);
    QString process_line;

    if(action=="read"){

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return "Kann auf das Dateisystem nicht zugreifen";

        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            process_line.append(line);
        }

        file.close();

    }else if(action=="write"){

        if (!file.open(QIODevice::ReadWrite))
            qDebug() << "Kann auf das Dateisystem nicht zugreifen";

        QTextStream in(&file);
        qint64 inkrement;
        in >> inkrement;
        inkrement++;

        file.resize(0);

        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << inkrement;
        file.flush();
        file.close();

        qDebug() << "index.lib wurde inkrementiert...";
    }

    return process_line;
}

// Lese Datein ins Edit-Fenster

inline QStringList edit_readout(QString index){
    QFile file(maindir + index);

    if (!file.open(QIODevice::ReadOnly))
      qDebug() << "Keine Projekte gefunden...";

    QString line = file.readLine();
    QStringList line_data=line.split(" /// ", Qt::SkipEmptyParts, Qt::CaseInsensitive);

    file.close();
    return line_data;
}

// Initialisiert die Projekte und index.lib und liest die Projekte aus
// Das Auslesen umfasst auch alle Text- und Spalteneffekte

inline QStandardItemModel* readout(QString tab){
// First Initialize

    QFile file(lib_index);
    QStandardItemModel *model = new QStandardItemModel;

    if(!file.exists()){
        QDir _dir;
        if(app_dir != "") _dir.mkdir(app_dir);
        _dir.mkdir(maindir);
        _dir.mkdir(prjdir);

        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);

            stream << "0";

            file.close();
            qDebug() << "index.lib wurde erstmalig erstellt...";
        }
    }

// Nach dem zweiten Programmstart ab hier ausführen

    QDir dir = maindir;
    int line_count = 0;
    bool prj_end = false;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); i++) {

        QFileInfo fileInfo = list.at(i);

        QString temp_filename = qPrintable(QString("%1").arg(fileInfo.fileName()));
        QFile file(maindir + temp_filename);

           if (!file.open(QIODevice::ReadOnly))
              qDebug() << "Keine Projekte gefunden...";

           while (!file.atEnd()) {

              QString line =  file.readLine();
              QStringList line_data=line.split(" /// ", Qt::SkipEmptyParts, Qt::CaseInsensitive);

              if(line_data.at(6) == "01.01.2020"){ line_data[6] = "-"; }

              if(line_data.at(3) == "beendet")
                 prj_end=true;

              if(tab == "active" && !prj_end){

                 for(int j=0;j<9;j++){
                    QString m_prop=line_data.at(j);
                    QStandardItem *item=new QStandardItem(m_prop);
                    model->setItem(line_count,j,item);
                    }

                 line_count++;
               }

               if(tab == "ended" && prj_end){

                  for(int j=0;j<9;j++){
                     QString m_prop=line_data.at(j);
                     QStandardItem *item=new QStandardItem(m_prop);
                     model->setItem(line_count,j,item);
                  }
                  line_count++;
               }
               prj_end=false;
           }
        file.close();
     }
// Erstellt das Tabellenmodell

     model->setHeaderData(0, Qt::Horizontal, "#");
     model->setHeaderData(1, Qt::Horizontal, "Projekttitel");
     model->setHeaderData(2, Qt::Horizontal, "Mitarbeiter");
     model->setHeaderData(3, Qt::Horizontal, "Zustand");
     model->setHeaderData(4, Qt::Horizontal, "Start");
     model->setHeaderData(5, Qt::Horizontal, "Letztes Update");
     model->setHeaderData(6, Qt::Horizontal, "Letzter Bericht");
     model->setHeaderData(7, Qt::Horizontal, "Bericht nä. Sitzung");
     model->setHeaderData(8, Qt::Horizontal, "Bemerkungen");

     for(int i=0; i<model->rowCount();i++){

        if(model->index(i, 5).data().toString() != "-" && model->index(i, 3).data().toString() == "aktiv"){

            QDate datecheck = QDate::fromString(model->index(i, 5).data().toString(),"dd.MM.yyyy");
            QDate datecheck_red = datecheck.addDays(red_warn);
            QDate datecheck_yellow = datecheck.addDays(yellow_warn);

            if(datecheck_yellow <= QDate::currentDate()){
                 model->setData(model->index(i,5), QBrush(Qt::yellow), Qt::BackgroundRole);

                 if(datecheck_red <= QDate::currentDate()){
                     model->setData(model->index(i,5), QBrush(Qt::red), Qt::BackgroundRole);
                 }
            }
        }

        if(model->index(i, 7).data().toString() == "ja" || model->index(i, 7).data().toString() == "yes"){
           model->setData(model->index(i,7), QBrush(Qt::yellow), Qt::BackgroundRole);
        }
        if(model->index(i, 3).data().toString() == "aktiv" || model->index(i, 3).data().toString() == "active"){
           model->setData(model->index(i,3), QBrush(Qt::green), Qt::BackgroundRole);
        }
        if(model->index(i, 3).data().toString() == "pausiert" || model->index(i, 3).data().toString() == "paused"){
           model->setData(model->index(i,3), QBrush(Qt::cyan), Qt::BackgroundRole);
        }
        if(model->index(i, 3).data().toString() == "beendet" || model->index(i, 3).data().toString() == "finished"){
           model->setData(model->index(i,3), QBrush(Qt::red), Qt::BackgroundRole);
        }
     }
     model->sort(2,Qt::AscendingOrder);
     return model;
}

// Milestones und Projektfortschritt auslesen
inline QStandardItemModel* readout_mp(QString type){

    QStandardItemModel *model = new QStandardItemModel;   
    QString datei;
    datei = global_edit;
    int row = 0;

    QFile file(prjdir + datei + type);

    if(file.exists()){

      if (!file.open(QIODevice::ReadOnly))
         qDebug() << "Keine Projekte gefunden...";

      QString line = file.readLine();
      QStringList line_data=line.split(" /// ", Qt::SkipEmptyParts, Qt::CaseInsensitive);
      std::vector<date_sort> data_helpy(line_data.size());

      for (int j=0; j < line_data.size(); j=j+2){
        QDateTime helper = QDateTime::fromString(line_data.at(j),"dd.MM.yyyy");
        helper.setTimeSpec(Qt::UTC);
        int UTC_Time = helper.toTime_t();
        data_helpy[row].datum = UTC_Time;
        data_helpy[row].text = line_data.at(j+1);
        row++;
      }

      std::sort(data_helpy.begin(), data_helpy.end(), []
                (const date_sort &a, const date_sort &b){
                    return a.datum > b.datum;
                });

      for(int row=0; row < line_data.size()/2; row++){
         QDateTime timestamp;
         timestamp.setTime_t(data_helpy[row].datum);
         QString m_prop=timestamp.toString("dd.MM.yyyy");
         QString t_prop=data_helpy[row].text;

         QStandardItem *item=new QStandardItem(m_prop);
         QStandardItem *item_t = new QStandardItem(t_prop);

         model->setItem(row,0,item);
         model->setItem(row,1,item_t);
      }

    file.close();
    }

// Erstellt das Tabellenmodell

     model->setHeaderData(0, Qt::Horizontal, "Datum");
     model->setHeaderData(1, Qt::Horizontal, "Meilenstein");

    return model;

}

// Lese Datein ins Edit-Fenster

inline QStringList edit_readout_mp(QString type){

    QStringList line_data, line_formatted;
    QString line_reordered;
    int row = 0;

    QFile file(prjdir + global_edit + type);

    if(file.exists()){

      if (!file.open(QIODevice::ReadOnly))
         qDebug() << "Keine Projekte gefunden...";

      QString line = file.readLine();
      QStringList line_data=line.split(" /// ", Qt::SkipEmptyParts, Qt::CaseInsensitive);
      std::vector<date_sort> data_helpy(line_data.size());

      for (int j=0; j < line_data.size(); j=j+2){
        QDateTime helper = QDateTime::fromString(line_data.at(j),"dd.MM.yyyy");
        helper.setTimeSpec(Qt::UTC);
        int UTC_Time = helper.toTime_t();
        data_helpy[row].datum = UTC_Time;
        data_helpy[row].text = line_data.at(j+1);
        row++;
      }

      std::sort(data_helpy.begin(), data_helpy.end(), []
                (const date_sort &a, const date_sort &b){
                    return a.datum > b.datum;
                });

      for(int row=0; row < line_data.size()/2; row++){
         QDateTime timestamp;
         timestamp.setTime_t(data_helpy[row].datum);
         QString m_prop=timestamp.toString("dd.MM.yyyy");
         QString t_prop=data_helpy[row].text;

         line_reordered.append(" /// " + m_prop + " /// " + t_prop);
      }

      file.close();
    }
    line_formatted = line_reordered.split(" /// ", Qt::SkipEmptyParts, Qt::CaseInsensitive);
    return line_formatted;
}

// Editierte Milestones / Projektfortschritte speichern
inline void edit_create_mp(int index, QString type, QString edit_date, QString edit_text){

    QStringList line_data = edit_readout_mp(type);
    QString output;

    edit_text = edit_text.simplified(); edit_text = edit_text.replace("///","\\\\\\");

    for (int i=0; i < line_data.size(); i=i+2){
        if(i == index){
            output.append(" /// ");
            output.append(edit_date);
            output.append(" /// ");
            output.append(edit_text);
        }else{
            output.append(" /// ");
            output.append(line_data[i]);
            output.append(" /// ");
            output.append(line_data[i+1]);
        }
    }

    QString datei;
    datei = global_edit;
    QFile file(prjdir + datei + type);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
       qDebug() << "Kann auf das Dateisystem nicht zugreifen";

    QTextStream stream(&file);

    stream.setCodec("UTF-8");

    stream << output;

    file.close();
    qDebug() << "Milestone/Projektfortschritt editiert...";
}

// Milestone oder Projektfortschritt speichern
inline void create_mp(QString date, QString text, QString type){
    QString datei;

    datei = global_edit;

    QFile file(prjdir + datei + type);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
       qDebug() << "Kann auf das Dateisystem nicht zugreifen";

    text = text.simplified(); text = text.replace("///","\\\\\\");

    QTextStream stream(&file);

    stream.setCodec("UTF-8");

    stream << " /// " << date << " /// " << text;

    file.close();
    qDebug() << "Milestone ergänzt...";
}


// Schreibt ein neues Projekt
inline void create_entry_lib(QString title, QString MA, QString status, QString start, QString update, QString last_report, QString report_next,
                             QString Bemerkung, QString participants, QString pgoals, QString role, QString ptext, QString date_bewertung, QString bewertung, QString AEffekt, QString WEffekt,
                             QString OEffekt, QString NEffekt, QString res_personell, QString res_finanziell, QString risiken, QString date_ab, QString fazit_ab, QString AEffekt_ab,
                             QString WEffekt_ab, QString OEffekt_ab, QString NEffekt_ab, QString res_personell_ab, QString res_finanziell_ab, QString llearned){

     QString datei;

     if(global_edit == "nein" || global_edit == ""){
        datei = counter("read");
     }else{
        datei = global_edit;
     }

     QFile file(maindir + datei);

     if(global_edit == "nein" || global_edit == ""){
         if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
             qDebug() << "Kann auf das Dateisystem nicht zugreifen";
     }else{
         if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
             qDebug() << "Kann auf das Dateisystem nicht zugreifen";
     }

     title = title.simplified(); title = title.replace("///", "\\\\\\"); MA = MA.simplified(); MA = MA.replace("///","\\\\\\"); Bemerkung = Bemerkung.simplified();
     Bemerkung = Bemerkung.replace("///","\\\\\\"); participants = participants.simplified(); participants = participants.replace("///","\\\\\\"); pgoals = pgoals.simplified();
     pgoals = pgoals.replace("///","\\\\\\"); role = role.simplified(); role = role.replace("///","\\\\\\"); ptext = ptext.simplified(); ptext = ptext.replace("///", "\\\\\\");
     bewertung = bewertung.simplified(); bewertung = bewertung.replace("///", "\\\\\\");  res_personell = res_personell.simplified(); res_personell = res_personell.replace("///", "\\\\\\");
     res_finanziell = res_finanziell.simplified(); res_finanziell = res_finanziell.replace("///", "\\\\\\");  risiken = risiken.simplified(); risiken = risiken.replace("///", "\\\\\\");
     fazit_ab = fazit_ab.simplified(); fazit_ab = fazit_ab.replace("///", "\\\\\\"); res_personell_ab = res_personell_ab.simplified(); res_personell_ab = res_personell_ab.replace("///", "\\\\\\");
     res_finanziell_ab = res_finanziell_ab.simplified(); res_finanziell_ab = res_finanziell_ab.replace("///", "\\\\\\"); llearned = llearned.simplified(); llearned = llearned.replace("///", "\\\\\\");

     QTextStream stream(&file);

     stream.setCodec("UTF-8");

     stream << datei.toInt() << " /// "<< title << " /// " << MA << " /// " << status << " /// " << start << " /// " << update << " /// " << last_report
                   << " /// " << report_next << " /// " << Bemerkung << " /// ";
     stream << participants << " /// " << pgoals << " /// " << role << " /// " << ptext << " /// " << date_bewertung << " /// " << bewertung << " /// " << AEffekt << " /// "
            << WEffekt << " /// " << OEffekt << " /// " << NEffekt << " /// " << res_personell << " /// " << res_finanziell << " /// " << risiken << " /// " << date_ab << " /// "
            << fazit_ab << " /// " << AEffekt_ab << " /// " << WEffekt_ab << " /// " << OEffekt_ab << " /// " << NEffekt_ab << " /// " << res_personell_ab << " /// "
            << res_finanziell_ab << " /// " << llearned;



     if (global_edit == "nein" || global_edit == ""){ counter("write"); }
     file.close();
     global_edit = "nein";
     qDebug() << "Projektliste ergänzt...";
}

#endif // SAVE_HANDLER_H
