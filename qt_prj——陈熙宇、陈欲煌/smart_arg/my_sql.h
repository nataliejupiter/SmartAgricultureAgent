#ifndef MY_SQL_H
#define MY_SQL_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QByteArray>
#include <QSqlQuery>
class my_sql
{
public:
    my_sql();
    bool connectToDatabase();
    QByteArray readImageData(const QString &filePath);
    bool insertImage(const QByteArray &imageData);
    int sqlInit();
};

#endif // MY_SQL_H
