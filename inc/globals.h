#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>
#include <QDir>

QString global_edit;

// Speicherpfade definieren

#ifdef _WIN32
    static QString app_dir = "";
    static QString maindir = "Projekte/";
    static QString prjdir = "data/";
    static QString lib_index = "index.lib";
#else
    static QString home = QDir::homePath();
    static QString app_dir = home + "/.tu2_projects";
    static QString maindir = home + "/.tu2_projects/Projekte/";
    static QString prjdir = home + "/.tu2_projects/data/";
    static QString lib_index = home + "/.tu2_projects/index.lib";
#endif

// Tage die vergangen sein müssen, bis zur Update Warnung
int yellow_warn = 14;
int red_warn = 31;

#endif // GLOBALS_H
