// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <assert.h>

enum class PointPlaneRelationship
{
	Above,
	Below,
	Inside
};

class UShape;

/**
 * 
 */
class DESTRUCTABLEENV_API Point
{
public:
	static constexpr float PointInPlaneTol = 0.0001f;

	Point(FVector point)
	{
		m_Point = point;
	}

	~Point()
	{
	}

	PointPlaneRelationship GetPlaneRelationship() const
	{
		return m_PlaneRelationship;
	}

	void SetPlaneRelationship(PointPlaneRelationship relationship)
	{
		m_PlaneRelationship = relationship;
	}

	int GetId() const
	{
		return m_Id;
	}

	void SetId(int id)
	{
		m_Id = id;
	}

	void CentreAndCache(FVector centre, std::vector<FVector> points)
	{
		m_Point -= centre;
		points.push_back(centre);
	}

	Point* NextLinkedPoint(Point &prev)
	{
		if (m_LinkedPoint1 == &prev)
		{
			return m_LinkedPoint2;
		}

		else if (m_LinkedPoint2 == &prev)
		{
			return m_LinkedPoint1;
		}

		assert(false);
		return nullptr;
	}

	void AddLink(Point& linkedPoint)
	{
		if (m_LinkedPoint1 == nullptr)
		{
			m_LinkedPoint1 = &linkedPoint;
			return;
		}

		else if (m_LinkedPoint2 == nullptr)
		{
			m_LinkedPoint2 = &linkedPoint;
			return;
		}

		assert(false);
		return;
	}

	void Split(FVector P0, FVector n, UShape* shapeAbove, UShape* shapeBelow, int& numInside);

	static bool PointsBridgePlane(Point &p1, Point& p2)
	{
		if (p1.GetPlaneRelationship() == PointPlaneRelationship::Above && p2.GetPlaneRelationship() == PointPlaneRelationship::Below)
			return true;

		if (p2.GetPlaneRelationship() == PointPlaneRelationship::Above && p1.GetPlaneRelationship() == PointPlaneRelationship::Below)
			return true;

		return false;
	}

	static bool BothAbove(Point& p1, Point& p2)
	{
		return p1.GetPlaneRelationship() == PointPlaneRelationship::Above && p2.GetPlaneRelationship() == PointPlaneRelationship::Above;
	}

	static bool BothBelow(Point& p1, Point& p2)
	{
		return p1.GetPlaneRelationship() == PointPlaneRelationship::Below && p2.GetPlaneRelationship() == PointPlaneRelationship::Below;
	}

	static bool BothInside(Point& p1, Point& p2)
	{
		return p1.GetPlaneRelationship() == PointPlaneRelationship::Inside && p2.GetPlaneRelationship() == PointPlaneRelationship::Inside;
	}

private:
	Point * m_LinkedPoint1 = nullptr;
	Point * m_LinkedPoint2 = nullptr;

	FVector m_Point;

	int m_Id;

	PointPlaneRelationship m_PlaneRelationship;
};
