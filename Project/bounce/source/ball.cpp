#include <GL/gl.h>
#include <LinearMath/btDefaultMotionState.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include "../headers/ball.h"

Ball::Ball(btScalar mass,
           btMotionState *motionState,
           btCollisionShape *collisionShape,
           const btVector3 &localInertia)
        : SceneObject(mass, motionState, collisionShape, localInertia) {
    this->ballSize = 10;
}

void Ball::draw() {
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    ((btRigidBody *) this)->getMotionState()->getWorldTransform(transform);
    transform.getOpenGLMatrix(matrix);
    glMultMatrixf(matrix);
    drawer.drawSphere(0.5, 30, 30);
    glPopMatrix();
}

void Ball::setPosition(double x, double y) {}

SceneObject *Ball::getDefault(btVector3 origin, btVector3 boxShape, int size, bool gravity) {
    btQuaternion qtn;
    btCollisionShape *shape;
    btDefaultMotionState *motionState;
    btTransform trans;

    // The ball is considered as a box for simplification
    shape = new btBoxShape(boxShape);

    trans.setIdentity();
    trans.setOrigin(origin);

    motionState = new btDefaultMotionState(trans);

    btScalar mass = gravity ? btScalar(1.0) : btScalar(0.0);
    btVector3 inertia = gravity ? btVector3(1, 1, 1) : btVector3(0, 0, 0);

    auto ball = new Ball(mass, motionState, shape, inertia);

    ball->transform = trans;
    ball->quaternion = qtn;
    ball->ballSize = size;

    return ball;
}

Type Ball::getType() {
    return BALL;
}