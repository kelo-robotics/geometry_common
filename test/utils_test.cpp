#include <gtest/gtest.h>

#include <vector>

#include <geometry_common/Point.h>
#include <geometry_common/Utils.h>

TEST(UtilsTest, getAngleBetweenPoints)
{
    kelo::geometry_common::Point a(0.0f, 0.0f);
    kelo::geometry_common::Point b(1.0f, 0.0f);
    kelo::geometry_common::Point c(2.0f, 1.0f);
    kelo::geometry_common::Point d(0.0f, 1.0f);
    kelo::geometry_common::Point e(2.0f, -1.0f);
    EXPECT_FLOAT_EQ(kelo::geometry_common::Utils::getAngleBetweenPoints(a, b, c), -3*M_PI/4)
        << "Angle should be -3pi/4.";
    EXPECT_FLOAT_EQ(kelo::geometry_common::Utils::getAngleBetweenPoints(d, b, a), M_PI/4)
        << "Angle should be pi/4.";
    EXPECT_FLOAT_EQ(kelo::geometry_common::Utils::getAngleBetweenPoints(e, b, a), -3*M_PI/4)
        << "Angle should be -3pi/4.";
}

TEST(UtilsTest, isPolygonConvex)
{
    std::vector<kelo::geometry_common::Point> convex_polygon(
    {
        kelo::geometry_common::Point(0.0f, 0.0f),
        kelo::geometry_common::Point(5.0f, 0.0f),
        kelo::geometry_common::Point(4.0f, 4.0f),
        kelo::geometry_common::Point(0.0f, 3.0f)
    });
    EXPECT_EQ(kelo::geometry_common::Utils::isPolygonConvex(convex_polygon), true)
        << "Convex polygon is not found to be convex.";

    std::vector<kelo::geometry_common::Point> concave_polygon(
    {
        kelo::geometry_common::Point(0.0f, 0.0f),
        kelo::geometry_common::Point(5.0f, 0.0f),
        kelo::geometry_common::Point(1.0f, 1.0f),
        kelo::geometry_common::Point(0.0f, 5.0f)
    });
    EXPECT_EQ(kelo::geometry_common::Utils::isPolygonConvex(concave_polygon), false)
        << "Concave polygon is not found to be concave.";

    std::vector<kelo::geometry_common::Point> star_polygon(
    {
        kelo::geometry_common::Point(0.0f, 0.0f),
        kelo::geometry_common::Point(2.0f, 5.0f),
        kelo::geometry_common::Point(4.0f, 0.0f),
        kelo::geometry_common::Point(0.0f, 3.0f),
        kelo::geometry_common::Point(4.0f, 3.0f),
    });
    EXPECT_EQ(kelo::geometry_common::Utils::isPolygonConvex(star_polygon), false)
        << "Star polygon is not found to be concave.";
}

TEST(UtilsTest, calcConvexHullOfPolygons)
{
    std::vector<kelo::geometry_common::Point> polygon_a(
    {
        kelo::geometry_common::Point(0.0f, 0.0f),
        kelo::geometry_common::Point(5.0f, 0.0f),
        kelo::geometry_common::Point(5.0f, 4.0f),
        kelo::geometry_common::Point(0.0f, 4.0f)
    });
    std::vector<kelo::geometry_common::Point> polygon_b(
    {
        kelo::geometry_common::Point(3.0f, 2.0f),
        kelo::geometry_common::Point(9.0f, 1.0f),
        kelo::geometry_common::Point(9.0f, 3.0f)
    });
    std::vector<kelo::geometry_common::Point> convex_hull = kelo::geometry_common::Utils::calcConvexHullOfPolygons(
            polygon_a, polygon_b);

    EXPECT_EQ(convex_hull.size(), 6u);
    EXPECT_EQ(convex_hull[0], polygon_a[0]);
    EXPECT_EQ(convex_hull[1], polygon_a[1]);
    EXPECT_EQ(convex_hull[2], polygon_b[1]);
    EXPECT_EQ(convex_hull[3], polygon_b[2]);
    EXPECT_EQ(convex_hull[4], polygon_a[2]);
    EXPECT_EQ(convex_hull[5], polygon_a[3]);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
