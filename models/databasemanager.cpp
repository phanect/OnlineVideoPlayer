#include "databasemanager.h"
#include "video.h"

#include <QSqlDatabase>
#include <qdjango/db/QDjango.h>
#include <qdjango/db/QDjangoModel.h>


DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
	//
	// Connect to the Database
	//
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(":memory:");
	db.open();
	QDjango::setDatabase(db);

	//
	// Model object registration
	//
	QDjango::registerModel<Video>();
}

void DatabaseManager::initDB() {
	QDjango::createTables();
}

// TODO create destructor to destroy database connection
