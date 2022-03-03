/******************************************************************************
 * Copyright (c) 2022
 * KELO Robotics GmbH
 *
 * Author:
 * Dharmin Bakaraniya
 * Sushant Chavan
 *
 *
 * This software is published under a dual-license: GNU Lesser General Public
 * License LGPL 2.1 and BSD license. The dual-license implies that users of this
 * code may choose which terms they prefer.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * * Neither the name of Locomotec nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version or the BSD license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License LGPL and the BSD license for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL and BSD license along with this program.
 *
 ******************************************************************************/

#ifndef KELO_GEOMETRY_COMMON_POINT_3D_H
#define KELO_GEOMETRY_COMMON_POINT_3D_H

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point32.h>
#include <geometry_msgs/Point.h>

#include <geometry_common/Point2D.h>

namespace kelo::geometry_common
{

/**
 * @brief 
 * 
 */
class Point3D
{
    public:
        float x{0.0f}, y{0.0f}, z{0.0f};

        using Ptr = std::shared_ptr<Point3D>;
        using ConstPtr = std::shared_ptr<const Point3D>;

        /**
         * @brief
         * 
         * @param _x 
         * @param _y 
         * @param _z 
         */
        Point3D(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f):
            x(_x),
            y(_y),
            z(_z) {}

        /**
         * @brief
         * 
         * @param point 
         * @param _z 
         */
        Point3D(const Point2D& point, float _z = 0.0f):
            Point3D(point.x, point.y, _z) {}

        /**
         * @brief
         * 
         * @param point 
         */
        Point3D(const Point3D& point):
            Point3D(point.x, point.y, point.z) {}

        /**
         * @brief
         * 
         * @param point 
         */
        Point3D(const geometry_msgs::PointStamped& point):
            Point3D(point.point) {}

        /**
         * @brief
         * 
         * @param point 
         */
        Point3D(const geometry_msgs::Point& point):
            Point3D(point.x, point.y, point.z) {}

        /**
         * @brief
         * 
         * @param point 
         */
        Point3D(const geometry_msgs::Point32& point):
            Point3D(point.x, point.y, point.z) {}

        /**
         * @brief
         * 
         */
        virtual ~Point3D() {}

        /**
         * @brief
         * 
         * @return geometry_msgs::Point 
         */
        geometry_msgs::Point getPoint() const;

        /**
         * @brief
         * 
         * @return geometry_msgs::Point32 
         */
        geometry_msgs::Point32 getPoint32() const;

        /**
         * @brief
         * 
         * @param frame 
         * @return geometry_msgs::PointStamped 
         */
        geometry_msgs::PointStamped getPointStamped(const std::string& frame = "map") const;

        /**
         * @brief
         * 
         * @param p 
         * @return float 
         */
        inline float getCartDist(const Point3D& p) const
        {
            return std::sqrt(getCartDistSquared(p));
        };

        /**
         * @brief
         * 
         * @param p 
         * @return float 
         */
        inline float getCartDistSquared(const Point3D& p) const
        {
            return std::pow(x - p.x, 2) + std::pow(y - p.y, 2) + std::pow(z - p.z, 2);
        };

        /**
         * @brief 
         * 
         * @return float 
         */
        inline float magnitude() const
        {
            return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
        };

        /**
         * @brief 
         * 
         * @return Point3D 
         */
        Point3D normalise() const;

        /**
         * @brief 
         * 
         * @param tf_mat 
         */
        void transform(const std::vector<float>& tf_mat);

        /**
         * @brief
         * 
         * @param tf_mat 
         * @return Point3D 
         */
        Point3D getTransformedPoint(const std::vector<float>& tf_mat) const;

        /**
         * @brief
         * 
         * @param frame 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         * @param diameter 
         * @return visualization_msgs::Marker 
         */
        visualization_msgs::Marker getMarker(
                const std::string& frame = "base_link",
                float red = 1.0f,
                float green = 0.0f,
                float blue = 0.0f,
                float alpha = 1.0f,
                float diameter = 0.2f) const;

        /**
         * @brief 
         * 
         * @param p1 
         * @param p2 
         * @return Point3D 
         */
        friend Point3D operator - (const Point3D& p1, const Point3D& p2);

        /**
         * @brief 
         * 
         * @param p1 
         * @param p2 
         * @return Point3D 
         */
        friend Point3D operator + (const Point3D& p1, const Point3D& p2);

        /**
         * @brief 
         * 
         * @param p1 
         * @param scalar 
         * @return Point3D 
         */
        friend Point3D operator * (const Point3D& p1, float scalar);

        /**
         * @brief 
         * 
         * @param out 
         * @param point 
         * @return std::ostream& 
         */
        friend std::ostream& operator << (std::ostream& out, const Point3D& point);

        /**
         * @brief 
         * 
         * @param p1 
         * @param p2 
         * @return bool 
         */
        friend bool operator == (const Point3D& p1, const Point3D& p2);
};

/**
 * @brief 
 * 
 */
using Vec3D = Point3D;

/**
 * @brief 
 * 
 */
using PointVec3D = std::vector<Point3D>;

/**
 * @brief 
 * 
 */
using PointCloud3D = std::vector<Point3D>;

}; // namespace kelo::geometry_common
#endif // KELO_GEOMETRY_COMMON_POINT_3D_H