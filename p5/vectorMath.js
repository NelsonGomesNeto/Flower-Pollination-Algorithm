function dot(aVector, bVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i] * bVector[i];
  return(temp);
}

function divDot(aVector, bVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i] / bVector[i];
  return(temp);
}

function powDot(aVector, bVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = pow(aVector[i], bVector[i]);
  return(temp);
}

function add(aVector, bVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i] + bVector[i];
  return(temp);
}

function sub(aVector, bVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i] - bVector[i];
  return(temp);
}

function mult(aVector, c) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i] * c;
  return(temp);
}

function absVector(aVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = abs(aVector[i]);
  return(temp);
}

function randomVector() {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = random(0, 1);
  return(temp);
}

function copyVector(aVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = aVector[i];
  return(temp);
}

function copyMatrix(aVector) {
  var temp = new Array(n);
  for (var i = 0; i < n; i ++)
    temp[i] = copyVector(aVector[i]);
  return(temp);
}

function limit(aVector) {
  var temp = new Array(d);
  for (var i = 0; i < d; i ++)
    temp[i] = max(min(aVector[i], UpperBound[i]), LowerBound[i]);
  return(temp);
}