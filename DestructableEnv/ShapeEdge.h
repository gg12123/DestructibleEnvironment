// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <assert.h>
#include <vector>

class Point;
class UShape;
class NewPointsGetter;

/**
 * 
 */
class DESTRUCTABLEENV_API ShapeEdge
{
public:
	ShapeEdge();

	ShapeEdge(Point& p1, Point& p2)
	{
		m_EdgeP1 = &p1;
		m_EdgeP2 = &p2;
	}

	~ShapeEdge();

	void AddPoint(Point &p)
	{
		if (m_EdgeP1 == nullptr)
		{
			m_EdgeP1 = &p;
		}
		else if (m_EdgeP2 == nullptr)
		{
			m_EdgeP2 = &p;
		}
		else
		{
			assert(false);
		}
	}

	void Cache(std::vector<FVector>& edgePoints);

	void Split(const FVector& P0, const FVector& n, NewPointsGetter& newPoints, UShape& shapeAbove, UShape& shapeBelow);

private:
	void SplitInHalf(NewPointsGetter& newPoints, const FVector& x, UShape& shapeAbove, UShape& shapeBelow);
	void SplitAtEnd(NewPointsGetter& newPoints, UShape& shapeAbove, UShape& shapeBelow);

	Point* m_EdgeP1;
	Point* m_EdgeP2;
};
