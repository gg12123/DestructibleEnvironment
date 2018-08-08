// Fill out your copyright notice in the Description page of Project Settings.

#include "ShapeEdge.h"
#include "Point.h"
#include "Shape.h"
#include "NewPointsGetter.h"

ShapeEdge::ShapeEdge()
{
}

ShapeEdge::~ShapeEdge()
{
}

void ShapeEdge::Cache(std::vector<FVector>& edgePoints)
{
	edgePoints.push_back(m_EdgeP1->GetPoint());
	edgePoints.push_back(m_EdgeP2->GetPoint());
}

void ShapeEdge::SplitAtEnd(NewPointsGetter& newPoints, UShape& shapeAbove, UShape& shapeBelow)
{
	if (m_EdgeP1->GetPlaneRelationship() == PointPlaneRelationship::Inside)
	{
		if (m_EdgeP2->GetPlaneRelationship() == PointPlaneRelationship::Above)
		{
			m_EdgeP1 = &newPoints.GetPointAbove(*m_EdgeP1);
			//shapeAbove.Edges.Add(this);
		}
		else
		{
			m_EdgeP1 = &newPoints.GetPointBelow(*m_EdgeP1);
			//shapeBelow.Edges.Add(this);
		}
	}
	else if (m_EdgeP2->GetPlaneRelationship() == PointPlaneRelationship::Inside)
	{
		if (m_EdgeP1->GetPlaneRelationship() == PointPlaneRelationship::Above)
		{
			m_EdgeP2 = &newPoints.GetPointAbove(*m_EdgeP2);
			//shapeAbove.Edges.Add(this);
		}
		else
		{
			m_EdgeP2 = &newPoints.GetPointBelow(*m_EdgeP2);
			//shapeBelow.Edges.Add(this);
		}
	}
	else
	{
		assert(false);
	}
}

void ShapeEdge::SplitInHalf(NewPointsGetter& newPoints, const FVector& x, UShape& shapeAbove, UShape& shapeBelow)
{
	auto a = new Point(x);
	auto b = new Point(x);

	newPoints.AddPoints(*m_EdgeP1, *m_EdgeP2, *a, *b);

	//shapeAbove.AddPoint(a);
	//shapeBelow.AddPoint(b);

	if (m_EdgeP1->GetPlaneRelationship() == PointPlaneRelationship::Above)
	{
		auto newForBelow = new ShapeEdge(*m_EdgeP2, *b);
		m_EdgeP2 = a;

		//shapeAbove.Edges.Add(this);
		//shapeBelow.Edges.Add(newForBelow);
	}
	else
	{
		auto newForAbove = new ShapeEdge(*m_EdgeP2, *a);

		m_EdgeP2 = b;

		//shapeAbove.Edges.Add(newForAbove);
		//shapeBelow.Edges.Add(this);
	}
}

void ShapeEdge::Split(const FVector& P0, const FVector& n, NewPointsGetter& newPoints, UShape& shapeAbove, UShape& shapeBelow)
{
	if (Point::PointsBridgePlane(*m_EdgeP1, *m_EdgeP2))
	{
		FVector x;
		//Utils.LinePlaneIntersect(n, P0, EdgeP1.Point, EdgeP2.Point, out x);

		SplitInHalf(newPoints, x, shapeAbove, shapeBelow);
	}
	else if (Point::BothAbove(*m_EdgeP1, *m_EdgeP2))
	{
		//shapeAbove.Edges.Add(this);
	}
	else if (Point::BothBelow(*m_EdgeP1, *m_EdgeP2))
	{
		//shapeBelow.Edges.Add(this);
	}
	else if (Point::BothInside(*m_EdgeP1, *m_EdgeP2))
	{
		// do nothing - new edges for each shape will be created by the face split
	}
	else
	{
		SplitAtEnd(newPoints, shapeAbove, shapeBelow);
	}
}
