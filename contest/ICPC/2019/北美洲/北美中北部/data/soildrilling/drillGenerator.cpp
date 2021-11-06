#include <algorithm>
#include <iostream>
#include <random>
#include <string>

using namespace std;

const double PI = 3.141592653589793;
const double PI2 = 2.0*PI;


struct Point {
    double x;
    double y;
    double z;

    Point(double x0=0.0, double y0=0.0, double z0=0.0) : x(x0), y(y0), z(z0) {}
};


void generate (int nPoints, double radius, int orientation)
{
    std::default_random_engine generator(time(NULL) + nPoints + orientation);

    bool radiusWasNegative = (radius < 0.0);
    if (radiusWasNegative)
        radius = -radius;

    std::uniform_real_distribution<double> randomCenter(-1000.0 + 1.1*radius,1000.0-1.1*radius);
    double xc = randomCenter(generator);
    double yc = randomCenter(generator);
    double zc = randomCenter(generator);
    cerr << "center is " << xc << "," << yc << "," << zc << endl;
    // Generate the first three points  on the circle (special case, if radius was negative, choose
    //   two points on a diameter and third slightly inside.
    std::uniform_real_distribution<double> randomAngle(0.0, PI2);
    std::uniform_real_distribution<double> reducedRadius(0.0, 0.95*radius);

    Point* pts = new Point[nPoints];
    if (radiusWasNegative) {
        double theta1 = randomAngle(generator);
        double theta2 = theta1 + PI;
        double theta3 = randomAngle(generator);
        pts[0] = Point(xc + radius*cos(theta1), yc+radius*sin(theta1), zc+reducedRadius(generator));
        pts[1] = Point(xc + radius*cos(theta2), yc+radius*sin(theta2), zc+reducedRadius(generator));
        pts[2] = Point(xc + 0.99*radius*cos(theta3), yc+0.99*radius*sin(theta3), zc+reducedRadius(generator));
    } else {
        double theta1 = randomAngle(generator);
        double theta2 = theta1 + randomAngle(generator)/4.0;
		std::uniform_real_distribution<double> constrainedAngle(theta1+PI+0.01,
															   theta2+PI-0.01);
        double theta3 = constrainedAngle(generator);
		cerr << "Thetas: " << theta1 << " " << theta2 << " " << theta3 << endl;
        pts[0] = Point(xc + radius*cos(theta1), yc+radius*sin(theta1), zc+reducedRadius(generator));
        pts[1] = Point(xc + radius*cos(theta2), yc+radius*sin(theta2), zc+reducedRadius(generator));
        pts[2] = Point(xc + radius*cos(theta3), yc+radius*sin(theta3), zc+reducedRadius(generator));
    }

    // Now generate the remaining points using smaller or equal radius
    std::uniform_real_distribution<double> randomRadius(0.0, radius);
    for (int i = 3; i < nPoints; ++i)
    {
        double r = randomRadius(generator);
        double theta = randomAngle(generator);
        pts[i] = Point(xc + r*cos(theta), yc + sin(theta), zc+reducedRadius(generator));
    }

	// Force the z dimension to be irrelevant
	int k = nPoints/2;
	pts[k].z = zc + 1.1 * radius;
	pts[k+1].z = zc - 1.1 * radius;

    // Change orientation if necessary
    if (orientation == 1) {
        for (int i = 0; i < nPoints; ++i) {
            swap(pts[i].y, pts[i].z);
        }
    } else if (orientation == 2) {
        for (int i = 0; i < nPoints; ++i) {
            swap(pts[i].x, pts[i].z);
        }
    }
    // Permute
    random_shuffle(pts, pts+nPoints);

    // Print
    cout << nPoints << endl;
    for (int i = 0; i < nPoints; ++i)
    {
	  //cerr << i << ' ' << pts[i].x << ' ' << pts[i].y << ' ' << pts[i].z << endl;
        cout << pts[i].x << ' ' << pts[i].y << ' ' << pts[i].z << endl;
    }
}


/**
 * Generator for Drilling Clear Through
 * Params: numberofPoints desiredRadius orientation
 *
 * orientation = 0 for x,y, 1 for x,z, 2 for y,z
 */
int main(int argc, char** argv) {

    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " numberofPoints desiredRadius orientation" << endl;
        return -1;
    }

    int nPoints = atoi(argv[1]);
    nPoints = max(nPoints, 3);

    double radius = atof(argv[2]);

    int orientation = atoi(argv[3]);

    generate(nPoints, radius, orientation);

    return 0;
}
