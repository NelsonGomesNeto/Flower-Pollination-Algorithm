package com.fpa.pollination;

import com.vividsolutions.jts.geom.Coordinate;
import com.vividsolutions.jts.geom.Geometry;
import org.la4j.Vector;
import org.la4j.vector.DenseVector;
import org.la4j.vector.dense.BasicVector;

import javax.swing.plaf.basic.BasicBorders;
import java.util.ArrayList;
import java.util.Random;

public class Flower {

    public Vector x;
    private Double fitness;
    IFlowerFitnessEvaluator evaluator;

    public Flower(int dimensions, float[] lower, float[] upper, IFlowerFitnessEvaluator evaluator) {
        this.evaluator = evaluator;
        x = new BasicVector(dimensions);
        Random random = new Random(System.currentTimeMillis());
        for (int i = 0; i < dimensions; i++) {
            double value = Math.abs(random.nextInt((int)upper[i]));
//            double value = random.nextInt((int) (upper[i] + lower[i]) / 2) + lower[i] + (upper[i] + lower[i]) / 3.0;
            x.set(i,  value);
        }
        evaluate();
    }

    public Flower(int dimensions, IFlowerFitnessEvaluator evaluator) {
        this.evaluator = evaluator;
        x = new BasicVector(dimensions);
        for (int i = 0; i < dimensions; i++) {
            double value = -0.5 + Math.random();
            x.set(i, value);
        }
        evaluate();
    }

    protected void evaluate() {
        this.fitness = evaluator.fitness(x);
    }

    public double getFitness() {
        if (fitness == null)
            throw new RuntimeException("Chame o evaluate para obter um valor de fitness.");
        return fitness;
    }

    public Flower copy() {
        Flower flower = new Flower(x.length(), evaluator);
        flower.x = this.x.copy();
        flower.fitness = this.fitness;
        return flower;
    }

    public void print() {
        System.out.print("[");
        for (int i = 0; i < x.length(); i++)
            System.out.printf("%5.3f%c", x.get(i), i < x.length() - 1 ? ' ' : ']');
        System.out.printf(" - %8.5f\n", fitness);
    }

    private void limit(Vector vector, float[] upper, float[] lower) {
        for (int i = 0; i < x.length(); i++) {
            vector.set(i, Math.min(vector.get(i), upper[i]));
            vector.set(i, Math.max(vector.get(i), lower[i]));
        }
    }
}
