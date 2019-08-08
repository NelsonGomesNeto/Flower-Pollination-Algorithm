package com.fpa.pollination;

import org.la4j.Vector;
import org.la4j.vector.DenseVector;
import org.la4j.vector.dense.BasicVector;

import java.util.ArrayList;
import java.util.Random;

public class FPASolver {

    private int n, iterations, dimensions;
    float p;
    boolean limit;
    ArrayList<Flower> flowers;
    Flower bestFlower;
    float[] lower, upper;

    public FPASolver(int n, int dimensions, int iterations, float p, boolean limit, IFlowerFitnessEvaluator evaluator) {
        this.n = n;
        this.iterations = iterations;
        this.dimensions = dimensions;
        this.p = p;
        this.limit = limit;
        lower = new float[dimensions];
        upper = new float[dimensions];
        for (int i = 0; i < dimensions; i ++) {
            lower[i] = 0;
            upper[i] = 625;
        }
        flowers = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (limit)
                flowers.add(new Flower(dimensions, lower, upper, evaluator));
            else
                flowers.add(new Flower(dimensions, evaluator));
            if (i == 0 || flowers.get(i).getFitness() > bestFlower.getFitness()) {
                bestFlower = flowers.get(i);
            }
        }

    }

    private void limit(Vector vector) {
        if (!limit)
            return;
        for (int i = 0; i < dimensions; i++) {
            vector.set(i, Math.min(vector.get(i), upper[i]));
            vector.set(i, Math.max(vector.get(i), lower[i]));
        }
    }

    public Vector dot(Vector a, Vector b) {
        Vector temp = new BasicVector(a.length());
        for (int i = 0; i < a.length(); i ++)
            temp.set(i, a.get(i) * b.get(i));
        return(temp);
    }

    public void nextIteration() {
        for (int i = 0; i < n; i++) {
            Flower current = flowers.get(i);
            if (Math.random() > p) {
                Levy levy = new Levy(dimensions);
                Vector ds = dot(levy.levy(), (current.x.subtract(bestFlower.x)));
                current.x = current.x.add(ds);
		//System.out.println("Global: " + current.x);
                limit(current.x);
            } else {
                double epsilon = new Random().nextGaussian();
                int j = (int)(Math.random() * n), k = (int)(Math.random() * n);
                while (j == k)
                    k = (int)(Math.random() * n);
                current.x = current.x.add(flowers.get(j).x.subtract(flowers.get(k).x).multiply(0.05));
		//System.out.println("Local : " + current.x);
                limit(current.x);
            }
            current.evaluate();
            if (current.getFitness() >= flowers.get(i).getFitness())
                flowers.set(i, current.copy());
            if (current.getFitness() >= bestFlower.getFitness())
                bestFlower = current.copy();
        }
    }

    public Flower getBestFlower() {
        return bestFlower;
    }






}
