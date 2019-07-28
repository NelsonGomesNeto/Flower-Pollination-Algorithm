var ended = false, baseX, baseY, centerX = 0, centerY = 0, zooming = false, zoom = 1.2;
let d = 2, n = 20, p = 0.8, beta = 1.5, ir = 0, iterationRate = 5;
let numberOfIterations = 100;
var LowerBound = [], UpperBound = [], t = 0;
var Solution = [], Fitness = [], bestSolution, bestFitness = 1e9;
var bestHistory = [];

function evaluate(aVector) {
  return(abs(5 * aVector[0] + 2 * aVector[1] - 185));
}

function mouseWheel() {
  zoom -= event.delta / 1000;
  centerX += (mouseX - centerX) / zoom, centerY += (mouseY - centerY) / zoom;
  // print(zoom);
}

function keyReleased() {
  if (key == 'z' || key == 'Z') {
    zooming = !zooming;
    if (zooming) centerX = mouseX, centerY = mouseY;
    else centerX = baseX, centerY = baseY;
  }
}

function setup() {
  createCanvas(400, 400);
  baseX = 200, baseY = 200, centerX = 0, centerY = 0;
  frameRate(5);

  for (var i = 0; i < d; i ++)
    LowerBound.push(-1000), UpperBound.push(1000);

  for (var i = 0; i < n; i ++) {
    Solution.push(dot(add(LowerBound, sub(UpperBound, LowerBound)), randomVector()));
    Fitness.push(evaluate(Solution[i]));
  }
  for (var i = 0; i < n; i ++)
    if (Fitness[i] < bestFitness)
      bestFitness = Fitness[i], bestSolution = copyVector(Solution[i]);
  bestHistory.push(bestSolution);
}

function drawPoint(aVector) {
  var x = (aVector[0] + 1000) / 2000 * width; //* (zooming ? zoom : 1);
  var y = (aVector[1] + 1000) / 2000 * height; //* (zooming ? zoom : 1);
  stroke(random(0, 255), random(0, 255), random(0, 255));
  point(x, y);
}

function drawSolutions() {
  strokeWeight(5);
  // translate(centerX, centerY);
  // scale(zoom, zoom);
  // for (var i = 0; i < n; i ++) {
  //   drawPoint(Solution[i]);
  // }
  drawPoint(bestSolution);
}

function drawBestHistory() {
  strokeWeight(5);
  stroke(0, 0, 255);
  translate(centerX, centerY);
  // translate(centerX - baseX, baseY - centerY);
  scale(zooming ? zoom : 1, zooming ? zoom : 1);
  translate(-centerX, -centerY);
  for (var i = 0; i < bestHistory.length; i ++) {
    drawPoint(bestHistory[i]);
  }
}

function draw() {
  background(10, 10, 10);
  // drawSolutions();
  drawBestHistory();

  if (t < numberOfIterations && (++ ir) % iterationRate == 0)
    nextIteration();
  else if (!ended) {
    ended = true;
    print(bestSolution);
  }

  if (zooming) fill(0, 255, 0);
  else fill(255, 0, 0);
  noStroke();
  rect(width - 10, height - 10, 10, 10);
}

function Levy() {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++) {
  let sigma = pow((gamma(1+beta)*sin(PI*beta/2)/(gamma((1+beta)/2)*beta*pow(2,((beta-1)/2)))), (1/beta));
    let u = mult(randomVector(), sigma);
    let v = randomVector();
    let step = powDot(divDot(u, absVector(v)), 1/beta);
    temp[i] = 0.01*step;
  }
  return(temp);
}

function nextIteration() {
  t ++;
  var updated = false;
  var current = copyMatrix(Solution);

  for (var i = 0; i < n; i ++) {
    if (random() > p) { // Biotic
      let dS = dot(Levy(), sub(Solution[i], bestSolution));
      current[i] = limit(add(Solution[i], dS));
    } else { // Abiotic
      let epsilon = random();
      var JK = [floor(random(0, n)), floor(random(0, n))];
      while (JK[0] == JK[1]) JK[1] = floor(random(0, n));
      current[i] = limit(add(current[i], mult(sub(Solution[JK[0]], Solution[JK[1]]), epsilon)));
    }
    
    let Fnew = evaluate(current[i]);
    if (Fnew <= Fitness[i])
      Solution[i] = copyVector(current[i]), Fitness[i] = Fnew;
    if (Fnew <= bestFitness)
      bestSolution = copyVector(current[i]), bestFitness = Fnew, updated = true,
      bestHistory.push(bestSolution);
  }
}