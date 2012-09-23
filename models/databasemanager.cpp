#include "databasemanager.h"

#include <QSqlDatabase>
#include "video.h"

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

DatabaseManager::initDB() {
	QDjango::createTables();
}

// TODO create destructor to destroy database connection
