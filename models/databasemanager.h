#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>

class DatabaseManager : public QObject {
	Q_OBJECT
public:
	explicit DatabaseManager(QObject *parent = 0);

signals:

private:
	void initDB();

};

#endif // DATABASEMANAGER_H
