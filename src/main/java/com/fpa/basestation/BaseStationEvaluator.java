package com.fpa.basestation;

import com.fpa.pollination.Flower;
import com.fpa.pollination.IFlowerFitnessEvaluator;
import com.vividsolutions.jts.awt.ShapeWriter;
import com.vividsolutions.jts.geom.Coordinate;
import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.geom.GeometryFactory;
import com.vividsolutions.jts.geom.Polygon;
import com.vividsolutions.jts.util.GeometricShapeFactory;
import org.la4j.Vector;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class BaseStationEvaluator extends JPanel implements IFlowerFitnessEvaluator {

    Geometry city;
    int K, R, iteration;
    GeometryFactory geoFactory;
    Polygon container;
    Flower bestFlower;

    public BaseStationEvaluator(Geometry city, int K, GeometryFactory geoFactory, int R) {
        this.city = city;
        this.K = K;
        this.geoFactory = geoFactory;
        this.R = R;
        container = geoFactory.createPolygon(new Coordinate[]{new Coordinate(0, 0), new Coordinate(625, 0), new Coordinate(625, 625), new Coordinate(0, 625), new Coordinate(0, 0)});
    }

    @Override
    public double fitness(Vector x) {
        if (x.length() != K * 2)
            throw new RuntimeException("Não existem coordenadas suficientes no vetor-solução");
        Geometry tot = asGeometry(x);
        if (tot == null)
            return 0;
        return tot.intersection(city).getArea() / city.getArea();
    }

    private Geometry asGeometry(Vector x) {
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
        return tot;
    }

    private Geometry createCircle(Coordinate coordinate, int radius) {
        GeometricShapeFactory shape = new GeometricShapeFactory(geoFactory);
        shape.setCentre(coordinate);
        shape.setSize(2 * radius);
        shape.setNumPoints(32);
        return shape.createCircle();
    }

    public void setBestFlower(Flower f) {
        bestFlower = f;
    }
    public void setIteration(int i) { iteration = i; }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2d = (Graphics2D) g;
        if (bestFlower == null)
            return;
        Geometry lastTot = asGeometry(bestFlower.x);
        if (lastTot == null)
            return;
        ShapeWriter sw = new ShapeWriter();
        Shape linShape = sw.toShape(container.difference(city));
        g2d.setPaint(new Color(126, 200, 80));
        g2d.fill(linShape);
        linShape = sw.toShape(city);
        g2d.setPaint(new Color(255, 0, 255));
        g2d.fill(linShape);
        g2d.setPaint(Color.cyan);
        linShape = sw.toShape(lastTot);
        g2d.fill(linShape);

        g2d.setPaint(Color.black);
        for (int i = 0, j = 0; i < bestFlower.x.length(); i+=2, j++)
            g2d.drawString(Integer.toString(j), (int) bestFlower.x.get(i), (int) bestFlower.x.get(i + 1));

        g2d.drawString("Iteration: " + iteration, 20, 20);
        g2d.drawString("Fitness: " + bestFlower.getFitness(), 20, 40);
    }

}
