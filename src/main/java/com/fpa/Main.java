package com.fpa;

import com.fpa.basestation.BaseStationEvaluator;
import com.fpa.basestation.City;
import com.fpa.pollination.FPASolver;
import com.vividsolutions.jts.geom.Geometry;
import com.vividsolutions.jts.geom.GeometryFactory;

import javax.swing.*;

public class Main {

    public static void main(String[] args) {
        GeometryFactory geoFactory = new GeometryFactory();
        int iter = 10000;
        int K = 7, R = 63;
        Geometry city = City.getCity1();
        BaseStationEvaluator bsEvaluator = new BaseStationEvaluator(city, K, geoFactory, R);
        FPASolver solver = new FPASolver(20, K * 2, iter, 0.8f, true, bsEvaluator);
        int i = 0;

        JFrame frame = new JFrame("ERBs") ;
        frame.getContentPane().add(bsEvaluator);
        frame.setSize(625, 625);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setVisible(true);
        while (true) {
            solver.nextIteration();
            //solver.getBestFlower().print();
            if (++i % 50 == 0) {
                bsEvaluator.setBestFlower(solver.getBestFlower());
                frame.repaint();
            }
        }
//        System.out.println("Finished. Best Flower:");
//        solver.getBestFlower().print();
    }
}
