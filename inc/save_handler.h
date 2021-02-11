#ifndef SAVE_HANDLER_H
#define SAVE_HANDLER_H


#include <QFile>
#include <QStandardItem>
#include <QTextStream>
#include <QDateTime>

#include <QDebug>

class saveHandler
{

public:
    saveHandler();

    QString counter(QString action);
    QStringList edit_readout(QString index);
    QStandardItemModel* readout(QString tab);
    QStandardItemModel* readout_mp(QString type);
    QStringList edit_readout_mp(QString type);
    void edit_create_mp(int index, QString type, QString edit_date, QString edit_text);
    void create_mp(QString date, QString text, QString type);
    inline void create_entry_lib(QString title, QString MA, QString status, QString start, QString update, QString last_report, QString report_next,
                                 QString Bemerkung, QString participants, QString pgoals, QString role, QString ptext, QString date_bewertung, QString bewertung, QString AEffekt, QString WEffekt,
                                 QString OEffekt, QString NEffekt, QString res_personell, QString res_finanziell, QString risiken, QString date_ab, QString fazit_ab, QString AEffekt_ab,
                                 QString WEffekt_ab, QString OEffekt_ab, QString NEffekt_ab, QString res_personell_ab, QString res_finanziell_ab, QString llearned);

};

#endif // SAVE_HANDLER_H
