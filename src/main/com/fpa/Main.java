package com.fpa;

import com.fpa.basestation.BaseStationEvaluator;
import com.fpa.basestation.City;
import com.fpa.pollination.FPASolver;
import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.geom.GeometryFactory;

public class Main {

    public static void main(String[] args) {
        GeometryFactory geoFactory = new GeometryFactory();
        int iter = 10000;
        int K = 7, R = 63;
        Geometry city = City.getCity1();
        BaseStationEvaluator bsEvaluator = new BaseStationEvaluator(city, K, geoFactory, R);
        FPASolver solver = new FPASolver(100, K * 2, iter, 0.6f, true, bsEvaluator);
        while (true) {
            solver.nextIteration();
            solver.getBestFlower().print();
        }
//        System.out.println("Finished. Best Flower:");
//        solver.getBestFlower().print();
    }
}
