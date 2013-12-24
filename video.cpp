/****************************************************************************
 **
 ** Copyright (C) 2012 Jumpei Ogawa <phanective@gmail.com>
 **
 ** This file is licensed under ZLib license.
 ** http://www.opensource.org/licenses/Zlib
 **
 ** This software is provided 'as-is', without any express or implied warranty.
 ** In no event will the authors be held liable for any damages arising from
 ** the use of this software.
 **
 ** Permission is granted to anyone to use this software for any purpose,
 ** including commercial applications, and to alter it and redistribute it freely,
 ** subject to the following restrictions:
 **
 **   1. The origin of this software must not be misrepresented;
 **      you must not claim that you wrote the original software. If you use
 **      this software in a product, an acknowledgment in the product
 **      documentation would be appreciated but is not required.
 **
 **   2. Altered source versions must be plainly marked as such, and must not
 **      be misrepresented as being the original software.
 **
 **   3. This notice may not be removed or altered from any source distribution.
 **
 ****************************************************************************/

#include "video.h"
#include <QString>
#include <QStringList>
#include <QUrlQuery>

/** Video Model */
//Video::Video() {
	// TODO extract title and urltxt to local variables
//}

/** Video Model */
Video::Video(QDjangoModel *parent) : QDjangoModel(parent) {
	// TODO extract title and urltxt to local variables
}

/**	Create Video object from video URL string. */
Video* Video::createFromUrl(QString urlstr) {
	QUrl url(urlstr);
	return Video::createFromUrl(url);
}

/**	Create Video object from video URL object. */
Video* Video::createFromUrl(QUrl url) {
    Video *newVideo = new Video();
    QUrlQuery *query = new QUrlQuery(url);

	// Note: URL Styles
	// http://www.youtube.com/watch?v=pc1BRfuzgpI&feature=related
	// http://www.nicovideo.jp/watch/sm13416410
	// http://vimeo.com/17202067

	// decide which web service the video is.
	if (url.host().contains("youtube.com")) {
		newVideo->setService(Youtube);
        newVideo->setVideoId(query->queryItemValue("v"));
	} else if (url.host().contains("nicovideo.jp")) {
		newVideo->setService(Nicovideo);

		QStringList splitted = url.path().split("/"); // split URL by "/"
		newVideo->setVideoId(splitted[1]);

	} else if (url.host().contains("vimeo.com")) {
		newVideo->setService(Vimeo);

		newVideo->setVideoId(url.path().remove("/"));
	} else {
		throw "Given URL is not correct URL!"; // TODO Replace to something
	}

	return newVideo;
}

QString Video::videoId() {
	return m_videoId;
}

void Video::setVideoId(const QString videoId) {
	m_videoId = videoId;
}

Service Video::service() {
	return m_service;
}

void Video::setService(const Service service) {
	m_service = service;
}
