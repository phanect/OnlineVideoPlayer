#ifndef VIDEO_H
#define VIDEO_H

#include <qdjango/db/QDjangoModel.h>

#include <QObject>
#include <QString>
#include <QUrl>

/** Enumulation of web services */
enum Service {
	Youtube, Nicovideo, Vimeo
};

class Video : public QDjangoModel {
	Q_OBJECT

	Q_PROPERTY(QString videoId READ videoId WRITE setVideoId)
	Q_CLASSINFO("videoId", "max_length=255")

	Q_PROPERTY(Service service READ service WRITE setService)
	Q_CLASSINFO("service", "max_length=128")

	Q_PROPERTY(QString composer READ composer WRITE setComposer)
	Q_CLASSINFO("composer", "max_length=128")

	Q_PROPERTY(QString singer READ singer WRITE setSinger)
	Q_CLASSINFO("singer", "max_length=128")

public:
	//explicit Video();
	explicit Video(const Video &video);

	static Video* createFromUrl(QString urlstr);
	static Video* createFromUrl(QUrl url);

	QString videoId();
	void setVideoId(const QString videoId);
	Service service();
	void setService(const Service service);
	QString composer();
	void setComposer(const QString composer);
	QString singer();
	void setSinger(const QString singer);

private:
	QString m_videoId;
	Service m_service;
};

#endif // VIDEO_H
