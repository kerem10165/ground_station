import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15

Map {
    signal locationChangeSignal(coordinate: variant)
    id: map
    plugin: Plugin {name: "osm"}
    zoomLevel: 12
    center {
        latitude: 41.024470
        longitude: 28.946281
    }

    MapQuickItem {
        id:marker
        sourceItem: Rectangle
        {
            id: waypointMarker
            width: 20
            height: 20
            radius: 20
            border.width: 1
            border.color: mouseArea.containsMouse ? "red" : "black"
            color: markerItem.selected ? "red" : "gray"
        }
        coordinate: {0.0; 0.0}
        anchorPoint.x: image.width / 2
        anchorPoint.y: image.height / 2
    }

    MouseArea
    {
        Item {
            id: check
            clip: false
        }
        anchors.fill: parent
        onDoubleClicked:
        {
            marker.coordinate = map.toCoordinate(Qt.point(mouse.x,mouse.y))
            parent.locationChangeSignal(marker.coordinate)
        }
    }
}
