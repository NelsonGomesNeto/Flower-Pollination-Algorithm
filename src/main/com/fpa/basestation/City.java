package com.fpa.basestation;

import com.vividsolutions.jts.geom.Coordinate;
import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.geom.GeometryFactory;
import com.vividsolutions.jts.geom.Polygon;

import java.awt.Point;
import java.util.ArrayList;

public class City {

    private final static double TWO_PI = 2 * 3.14159265359;

    private static GeometryFactory geoFactory = new GeometryFactory();

    public static Geometry getCity1() {
        Point[] hexagons = {
                new Point(220, 286), new Point(220, 394),
                new Point(312, 231), new Point(312, 340), new Point(312, 448),
                new Point(406, 286), new Point(406, 394)
        };
        return buildGeometry(hexagons);
    }

    public static Geometry getCity2() {
        Point[] hexagons = {
                new Point(127, 124), new Point(127, 231), new Point(127, 340), new Point(127, 448),
                new Point(220, 178), new Point(220, 286), new Point(220, 394), new Point(220, 502),
                new Point(312, 124), new Point(312, 231), new Point(312, 340), new Point(312, 448),
                new Point(406, 178), new Point(406, 286), new Point(406, 394), new Point(406, 502),
                new Point(499, 124), new Point(499, 231), new Point(499, 340), new Point(499, 448)
        };
        return buildGeometry(hexagons);
    }

    public static Geometry getCity3() {
        Point[] hexagons = {
                new Point(127, 231), new Point(127, 340), new Point(127, 448),
                new Point(220, 178), new Point(220, 286), new Point(220, 394),
                new Point(312, 124), new Point(312, 231),
                new Point(406, 178), new Point(406, 286), new Point(406, 394),
                new Point(499, 231), new Point(499, 340), new Point(499, 448)
        };
        return buildGeometry(hexagons);
    }

    private static Geometry buildGeometry(Point[] hexagonsCenters) {
        ArrayList<Polygon> hexagons = new ArrayList<>();
        for (Point p : hexagonsCenters) {
            Coordinate[] cors = polygonVertices(p.x, p.y, 63, 6);
            hexagons.add(geoFactory.createPolygon(cors));
        }
        Geometry city = hexagons.get(0);
        for (int i = 1; i < hexagons.size(); i++)
            city = city.union(hexagons.get(i));
        return city;
    }

    private static Coordinate[] polygonVertices(int x, int y, double rad, int npoints) {
        ArrayList<Coordinate> coordinates = new ArrayList<>();
        double angle = TWO_PI / npoints;
        double a = 0;
        while (a < TWO_PI) {
            double sx = (x + Math.cos(a) * rad);
            double sy = (y + Math.sin(a) * rad);
            a += angle;
            coordinates.add(new Coordinate(Math.floor(sx), Math.floor(sy)));
        }
        coordinates.add(coordinates.get(0));
        return coordinates.toArray(new Coordinate[0]);
    }
}
