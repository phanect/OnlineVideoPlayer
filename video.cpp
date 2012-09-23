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

/** Video Model */
Video::Video(QObject *parent) : QDjangoModel(parent) {
	// TODO extract title and urltxt to local variables
}

/**	Create Video object from video URL string. */
Video Video::createFromUrl(QString urlstr) {
	return createFromUrl(QUrl(urlstr));
}

/**	Create Video object from video URL object. */
Video Video::createFromUrl(QUrl url) {
	Video newVideo;

	// Note: URL Styles
	// http://www.youtube.com/watch?v=pc1BRfuzgpI&feature=related
	// http://www.nicovideo.jp/watch/sm13416410
	// http://vimeo.com/17202067

	// decide which web service the video is.
	if (url.host().contains("youtube.com")) {
		newVideo.setService(Service.Youtube);
		newVideo.setVideoId(url.queryItemValue("v"));
	} else if (url.host().contains("nicovideo.jp")) {
		newVideo.setService(Service.Nicovideo);

		QStringList splitted = url.path().split("/"); // split URL by "/"
		newVideo.setVideoId(splitted[1]);

	} else if (url.host().contains("vimeo.com")) {
		newVideo.setService(Service.Vimeo);

		newVideo.setVideoId(url.path().remove("/"));
	} else {
		return NULL;
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
