package com.fpa.pollination;

import org.la4j.Vector;
import org.la4j.vector.DenseVector;

public interface IFlowerFitnessEvaluator {
    double fitness(Vector x);
}
