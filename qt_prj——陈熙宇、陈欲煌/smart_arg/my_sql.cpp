#include "my_sql.h"

my_sql::my_sql()
{
    //sqlInit();
}
bool my_sql::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("123.60.15.215");    // 数据库服务器地址
    db.setPort(3306);               // 端口
    db.setDatabaseName("your_db");  // 数据库名
    db.setUserName("root");         // 用户名
    db.setPassword("password");     // 密码

    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return true;
}


QByteArray my_sql::readImageData(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return QByteArray();
    }
    return file.readAll(); // 读取二进制数据
}

bool my_sql::insertImage(const QByteArray &imageData) {
    QSqlQuery query;
    query.prepare("INSERT INTO images (image_data) VALUES (:imageData)");
    query.bindValue(":imageData", imageData, QSql::In | QSql::Binary);

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    }
    return true;
}

int my_sql::sqlInit()
{
    // 连接数据库
    if (!connectToDatabase()) return -1;

    // 读取图片
    QByteArray data = readImageData("path/to/image.jpg");
    if (data.isEmpty()) return -1;

    // 插入数据
    if (insertImage(data)) {
        qDebug() << "Image inserted successfully!";
    }
}
