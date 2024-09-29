#include <iostream>
#include <vector>
#include <cmath>


struct Point {
    double x;
    double y;
};

struct Line {
    double A;
    double B;
    double C;
};

Line findPerpendicularLine(Line l, Point p) {
    Line perpendicularLine;
    perpendicularLine.A = l.B;
    perpendicularLine.B = -l.A;
    perpendicularLine.C = 0;
    return perpendicularLine;
}

Point findIntersectionPoint(Line l1, Line l2) {
    Point intersectionPoint;
    intersectionPoint.x = (l1.C * l2.B - l1.B * l2.C) / (l1.A * l2.B - l1.B * l2.A);
    intersectionPoint.y = (l1.A * l2.C - l1.C * l2.A) / (l1.A * l2.B - l1.B * l2.A);
    return intersectionPoint;
}

Point findSymmetricPoint(Point originalPoint, Point reflectionPoint) {
    Point symmetricPoint;
    symmetricPoint.x = 2 * reflectionPoint.x - originalPoint.x;
    symmetricPoint.y = 2 * reflectionPoint.y - originalPoint.y;
    return symmetricPoint;
}


int main() {
    std::cout << ("\e[1;1H\e[2J");
    int numPoints;
    std::cout << "Введите количество точек: ";
    std::cin >> numPoints;

    std::vector<Point> points;
    for (int i = 0; i < numPoints; i++) {
        Point p;
        std::cout << "Введите координату x для точки " << i+1 << ": ";
        std::cin >> p.x;
        std::cout << "Введите координату y для точки " << i+1 << ": ";
        std::cin >> p.y;
        std::cout << "\n";
        points.push_back(p);
    }

    Line originalLine;
    std::cout << "Введите коэффициенты для прямой (A, B, C): \n";
    std::cout << "A: "; std::cin >> originalLine.A;
    std::cout << "B: "; std::cin >> originalLine.B;
    std::cout << "C: "; std::cin >> originalLine.C; std::cout << "\n";

    Line perpendicularLine = findPerpendicularLine(originalLine, {0, 0});
    Point intersection = findIntersectionPoint(originalLine, perpendicularLine);

    for (const auto &point : points) {
        Point symmetricPoint = findSymmetricPoint(point, intersection);
        std::cout << "Исходная точка: (" << point.x << ", " << point.y << ") | ";
        std::cout << "Симметричная точка: (" << symmetricPoint.x << ", " << symmetricPoint.y << ")\n\n";
    }

    return 0;
}
