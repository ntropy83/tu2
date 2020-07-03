#ifndef PROJECT_POSTER_H
#define PROJECT_POSTER_H

#include <QDialog>

namespace Ui {
class project_poster;
}

class project_poster : public QDialog
{
    Q_OBJECT

public:
    explicit project_poster(QWidget *parent = nullptr);
    ~project_poster();
    void setprojectText(QString index);

private:
    Ui::project_poster *ui;
};

#endif // PROJECT_POSTER_H
