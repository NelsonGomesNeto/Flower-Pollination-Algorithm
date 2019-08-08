package com.fpa.basestation;

import com.fpa.pollination.IFlowerFitnessEvaluator;
import com.vividsolutions.jts.geom.Coordinate;
import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.geom.GeometryFactory;
import com.vividsolutions.jts.util.GeometricShapeFactory;
import javafx.util.Pair;
import org.la4j.Vector;

import java.util.ArrayList;

public class BaseStationEvaluator implements IFlowerFitnessEvaluator {

    Geometry city;
    int K, R;
    GeometryFactory geoFactory;

    public BaseStationEvaluator(Geometry city, int K, GeometryFactory geoFactory, int R) {
        this.city = city;
        this.K = K;
        this.geoFactory = geoFactory;
        this.R = R;
    }

    @Override
    public double fitness(Vector x) {
        if (x.length() != K * 2)
            throw new RuntimeException("Não existem coordenadas suficientes no vetor-solução");
        ArrayList<Coordinate> bsts = new ArrayList<>();
        for (int i = 0; i < x.length(); i += 2) {
            bsts.add(new Coordinate((int)x.get(i), (int)x.get(i + 1)));
        }
        Geometry tot = null;
        for (Coordinate bs : bsts) {
            Geometry newStation = createCircle(bs, R);
            if (tot == null)
                tot = geoFactory.createGeometry(newStation);
            else
                tot = tot.union(newStation);
        }
        if (tot == null)
            return 0;
        return tot.intersection(city).getArea() / city.getArea();
    }

    private Geometry createCircle(Coordinate coordinate, int radius) {
        GeometricShapeFactory shape = new GeometricShapeFactory(geoFactory);
        shape.setCentre(coordinate);
        shape.setSize(2 * radius);
        shape.setNumPoints(32);
        return shape.createCircle();
    }
}
