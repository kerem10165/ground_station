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
        latitude: 41
        longitude: 29
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

    function changeMarkerLocation(lat, lng)
    {
        mapMarker.coordinate = QtPositioning.coordinate(lat, lng)
    }

    MapQuickItem {
        id:mapMarker
        sourceItem: Rectangle
        {
            id: mapWaypointMarker
            width: 15
            height: 15
            radius: 15
            border.width: 1
            color: "red"
            border.color: "gray"
        }
        coordinate: {0.0; 0.0}
        anchorPoint.x: image.width / 2
        anchorPoint.y: image.height / 2
    }

}
