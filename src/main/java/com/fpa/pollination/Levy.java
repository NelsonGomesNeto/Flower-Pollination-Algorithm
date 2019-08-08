package com.fpa.pollination;

import org.apache.commons.math3.special.Gamma;
import org.la4j.Vector;
import org.la4j.vector.dense.BasicVector;

import java.util.Random;

import static java.lang.Math.PI;

public class Levy {
    private final static float BETA = 3f/2f, INV_BETA = 2f/3f, alpha = 0.05f;
    private static final double sigma = Math.pow(Gamma.gamma(1 + BETA) * Math.sin(PI * BETA / 2f) / (Gamma.gamma((1 + BETA) / 2f) * BETA * Math.pow(2, (BETA - 1) / 2F)), INV_BETA);

    private int dimensions;

    public Levy(int dimensions) {
        this.dimensions = dimensions;
    }

    public Vector levy() {
        Random random = new Random();
        double[] vals = new double[dimensions];
        for (int i = 0; i < dimensions; i++)
            vals[i] = random.nextGaussian() * sigma / Math.pow(Math.abs(random.nextGaussian()), INV_BETA) * alpha;
        return BasicVector.fromArray(vals);
    }
}
