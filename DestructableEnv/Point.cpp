// Fill out your copyright notice in the Description page of Project Settings.

#include "Point.h"
#include "Shape.h"

void Point::Split(FVector P0, FVector n, UShape* shapeAbove, UShape* shapeBelow, int& numInside)
{
	m_LinkedPoint1 = nullptr;
	m_LinkedPoint2 = nullptr;

	auto comp = FVector::DotProduct(m_Point - P0, n);

	if (fabs(comp) <= PointInPlaneTol)
	{
		auto newAbove = this;
		auto newBelow = new Point(m_Point);

		//newPoints.AddPoints(this, newAbove, newBelow);

		//shapeAbove.AddPoint(newAbove);
		//shapeBelow.AddPoint(newBelow);

		m_PlaneRelationship = PointPlaneRelationship::Inside;
		numInside++;
	}
	else if (comp > 0.0f)
	{
		//shapeAbove.AddPoint(this);
		m_PlaneRelationship = PointPlaneRelationship::Above;
	}
	else
	{
		//shapeBelow.AddPoint(this);
		m_PlaneRelationship = PointPlaneRelationship::Below;
	}
}
