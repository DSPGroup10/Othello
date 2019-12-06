#include "node.h"
#include <iostream>

node::node() {
	data = 0;
	up = NULL;
	down = NULL;
	right = NULL;
	left = NULL;
	urcross = NULL;
	ulcross = NULL;
	drcross = NULL;
	dlcross = NULL;
}

void node::setData(int data) {
	this.data = data;
}

void node::setUp(node up) {
	this.up = up;
}

void node::setDown(node down) {
	this.down = down;
}

void node::setRight(node right) {
	this.right = right;
}

void node::setLeft(node left) {
	this.left = left;
}

void node::setUrc(node urc) {
	urcross = urc;
}

void node::setUlc(node ulc) {
	ulcross = ulc;
}

void node::setDrc(node drc) {
	drcross = drc;
}

void node::setDlc(node dlc) {
	dlcross = dlc;
}

int node::getData() {
	return data;
}
node * node::getUp() {
	return up;
}
node * node::getDown() {
	return down;
}
node * node::getRight() {
	return right;
}
node * node::getLeft() {
	return left;
}
node * node::getUrc() {
	return urcross;
}
node * node::getUlc() {
	return ulcross;
}
node * node::getDrc() {
	return drcross;
}
node * node::getDlc() {
	return dlcross;
}