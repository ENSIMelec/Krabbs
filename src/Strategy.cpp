//
// Created by Tom on 23/02/2022.
//

#include "Strategy.h"

Strategy::Strategy(Point * startingPoint) {
//    cout << "Starting position : " << startingPoint << endl;
//    addPoint(startingPoint);
//
//    m_currentPoint = startingPoint;
}

Point * Strategy::getCurrentPoint() {
    return this->m_currentPoint;
}

bool Strategy::isDone() {
    return this->m_isDone;
}

void Strategy::addPoint(Point * point) {
    m_points.push_back(point);
}

void Strategy::setNextPoint(Controller *controller) {
    m_currentPointIndex++;
    if(m_currentPointIndex >= m_points.size()) {
        cout << "Strategy is done !" << endl;
        m_isDone = true;
        return;
    }

    cout << "Setting next point : (" << m_currentPoint->getX() << ", " << m_currentPoint->getY() << ", " <<
        m_currentPoint->getTheta() << ")" << endl;

    controller->set_point(m_currentPoint->getX(), m_currentPoint->getY(), m_currentPoint->getTheta());
    controller->set_trajectory(m_currentPoint->getTrajectory());
}

void Strategy::initController(Controller *controller) {
    cout << "==========================" << endl;
    //cout << "Strategy points : " << endl;
    int i = 1;
    for(Point * point : m_points) {
        cout << "\tP" << i++ << point << endl;
    }

    setNextPoint(controller);
}