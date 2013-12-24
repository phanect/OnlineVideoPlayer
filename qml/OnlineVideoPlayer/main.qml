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

import QtQuick 2.0
import QtWebKit 1.0
import QtQuick.Controls 1.0

Rectangle {
	width: 600
	height: 400

	// Movie List
	ListView {
		id: videolist

		model: ytlist
		delegate: Column{
			Image {
				source: thumbnail

				MouseArea {
					anchors.fill: parent
					onClicked: {
						videoplayer.url = "http://www.youtube.com/embed/" + videoId // + "?html5=1"
					}
				}
			}

			Text {text: title}
		}

		anchors.top: in_keyword.bottom
		anchors.margins: 10
		width: parent.width / 3
		height: parent.height
	}

	// Player
	WebView {
		id: videoplayer

		url: ""
		settings.pluginsEnabled: true

		anchors.top: in_keyword.bottom
		anchors.left: videolist.right
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.margins: 10
	}

	// Label
	Text {
		id: text1
		x: 14
		y: 15
		text: "Search Keywords:"
		font.pixelSize: 12
	}

	// Search Keyword Textbox
	TextInput {
		id: in_keyword

		anchors.left: text1.right
		anchors.verticalCenter: text1.verticalCenter
		anchors.margins: 10

		width: 137
		height: 20
		text: "Input keywords here"
		font.pixelSize: 12
	}

	// Search Button
	Rectangle {
		id: button
		anchors.left: in_keyword.right
		anchors.verticalCenter: in_keyword.verticalCenter
		anchors.margins: 10

		width: 72
		height: 20
		color: "#ffffff"

		Text {
			id: buttontext
			anchors.centerIn: parent
			text: "Search"
			font.pixelSize: 12
		}

		MouseArea {
			anchors.fill: parent
			onClicked: {
				// Change XML URL of XmlListModel (ytlist)
				ytlist.source = "http://gdata.youtube.com/feeds/api/videos?v=2&q=" + in_keyword.text
			}
		}
	}

	XmlListModel {
		id: ytlist

		source: ""
		query: "/feed/entry" // Load <entry> tag

		namespaceDeclarations: "declare default element namespace 'http://www.w3.org/2005/Atom'; declare namespace media='http://search.yahoo.com/mrss/'; declare namespace yt='http://gdata.youtube.com/schemas/2007';"

		XmlRole { name: "title"; query: "title/string()" }
		XmlRole {
			name: "thumbnail"
			query: "media:group/media:thumbnail[1]/@url/string()"
		}
		XmlRole {
			name: "videoId"
			query: "media:group/yt:videoid/string()"
		}
	}
}
