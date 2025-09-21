// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/Data/GridTypes.h"
#include <vector>
#include "GridFunctionLibrary.generated.h"

USTRUCT()
struct FHex
{
	GENERATED_BODY();

	int32 q;
	int32 r;
	int32 s;

	FHex(int32 Inq, int32 Inr, int32 Ins)
		: q(Inq), r(Inr), s(Ins)
	{
		check(q + r + s == 0);
	}

	FHex()
		: q(0), r(0), s(0)
	{
	}
};

FORCEINLINE bool operator == (const FHex& a, const FHex& b)
{
	return a.q == b.q && a.r == b.r && a.s == b.s;
}

FORCEINLINE bool operator != (const FHex& a, const FHex& b)
{
	return !(a == b);
}



//struct FHex
//{
//	int32 q;
//	int32 r;
//	int32 s;
//
//	FHex(int32 Inq, int32 Inr, int32 Ins)
//		: q(Inq), r(Inr), s(Ins)
//	{
//		check(q + r + s == 0);
//	}
//
//	FHex()
//		: q(0), r(0), s(0)
//	{
//	}
//};
//
///* Grid Math */
//FORCEINLINE bool operator == (const FHex& a, const FHex& b)
//{
//	return a.q == b.q && a.r == b.r && a.s == b.s;
//}
//
//FORCEINLINE bool operator != (const FHex& a, const FHex& b)
//{
//	return !(a == b);
//}
//
//FHex hex_add(FHex a, FHex b) {
//	return FHex(a.q + b.q, a.r + b.r, a.s + b.s);
//}
//
//FHex hex_subtract(FHex a, FHex b) {
//	return FHex(a.q - b.q, a.r - b.r, a.s - b.s);
//}
//
//FHex hex_multiply(FHex a, int k) {
//	return FHex(a.q * k, a.r * k, a.s * k);
//}
//
//int hex_length(FHex hex) {
//	return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
//}
//
//int hex_distance(FHex a, FHex b) {
//	return hex_length(hex_subtract(a, b));
//}
//
//static const TArray<FHex> hex_directions = {
//	FHex(1, 0, -1), FHex(1, -1, 0), FHex(0, -1, 1),
//	FHex(-1, 0, 1), FHex(-1, 1, 0), FHex(0, 1, -1)
//};
//
//FHex hex_direction(int direction /* 0 to 5 */) {
//	check(0 <= direction && direction < 6);
//	return hex_directions[direction];
//}
//
//FHex hex_neighbor(FHex hex, int direction) {
//	return hex_add(hex, hex_direction(direction));
//}
//
//struct Orientation {
//	const double f0, f1, f2, f3;
//	const double b0, b1, b2, b3;
//	const double start_angle; // in multiples of 60°
//	Orientation(double f0_, double f1_, double f2_, double f3_,
//		double b0_, double b1_, double b2_, double b3_,
//		double start_angle_)
//		: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
//		b0(b0_), b1(b1_), b2(b2_), b3(b3_),
//		start_angle(start_angle_) {
//	}
//};
//
//const Orientation layout_pointy
//= Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
//	sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
//	0.5);
//
//const Orientation layout_flat
//= Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
//	2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
//	0.0);
//
//struct Layout {
//	const Orientation orientation;
//	const FVector2D size;
//	const FVector2D origin;
//	Layout(Orientation orientation_, FVector2D size_, FVector2D origin_)
//		: orientation(orientation_), size(size_), origin(origin_) {
//	}
//};
//
//FVector2D hex_to_pixel(Layout layout, FHex h) {
//	const Orientation& M = layout.orientation;
//	double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.X;
//	double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.Y;
//	return FVector2D(x + layout.origin.X, y + layout.origin.Y);
//}
//
//struct FractionalHex {
//	const double q, r, s;
//	FractionalHex(double q_, double r_, double s_)
//		: q(q_), r(r_), s(s_) {
//	}
//};
//
//FractionalHex pixel_to_hex_fractional(Layout layout, FVector2D p) {
//	const Orientation& M = layout.orientation;
//	FVector2D pt = FVector2D((p.X - layout.origin.X) / layout.size.X,
//		(p.Y - layout.origin.Y) / layout.size.Y);
//	double q = M.b0 * pt.X + M.b1 * pt.Y;
//	double r = M.b2 * pt.X + M.b3 * pt.Y;
//	return FractionalHex(q, r, -q - r);
//}
//
//FHex hex_round(FractionalHex h) {
//	int q = int(round(h.q));
//	int r = int(round(h.r));
//	int s = int(round(h.s));
//	double q_diff = abs(q - h.q);
//	double r_diff = abs(r - h.r);
//	double s_diff = abs(s - h.s);
//	if (q_diff > r_diff and q_diff > s_diff) {
//		q = -r - s;
//	}
//	else if (r_diff > s_diff) {
//		r = -q - s;
//	}
//	else {
//		s = -q - r;
//	}
//	return FHex(q, r, s);
//}
//
//FHex pixel_to_hex_rounded(Layout layout, FVector2D p) {
//	return hex_round(pixel_to_hex_fractional(layout, p));
//}

/**
 * 
 */
UCLASS()
class GRIDV1_API UGridFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:



	/* Grid Math */
	
	static FHex hex_add(FHex a, FHex b) {
		return FHex(a.q + b.q, a.r + b.r, a.s + b.s);
	}

	static FHex hex_subtract(FHex a, FHex b) {
		return FHex(a.q - b.q, a.r - b.r, a.s - b.s);
	}

	static FHex hex_multiply(FHex a, int k) {
		return FHex(a.q * k, a.r * k, a.s * k);
	}

	static int hex_length(FHex hex) {
		return int((abs(hex.q) + abs(hex.r) + abs(hex.s)) / 2);
	}

	static int hex_distance(FHex a, FHex b) {
		return hex_length(hex_subtract(a, b));
	}

	static const TArray<FHex> hex_directions;

	static FHex hex_direction(int direction /* 0 to 5 */) {
		check(0 <= direction && direction < 6);
		return hex_directions[direction];
	}

	static FHex hex_neighbor(FHex hex, int direction) {
		return hex_add(hex, hex_direction(direction));
	}

	struct Orientation {
		const double f0, f1, f2, f3;
		const double b0, b1, b2, b3;
		const double start_angle; // in multiples of 60°
		Orientation(double f0_, double f1_, double f2_, double f3_,
			double b0_, double b1_, double b2_, double b3_,
			double start_angle_)
			: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
			b0(b0_), b1(b1_), b2(b2_), b3(b3_),
			start_angle(start_angle_) {
		}
	};

	const Orientation layout_pointy
		= Orientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
			sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
			0.5);

	const Orientation layout_flat
		= Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
			2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
			0.0);

	struct Layout {
		const Orientation orientation;
		const FVector2D size;
		const FVector2D origin;
		Layout(Orientation orientation_, FVector2D size_, FVector2D origin_)
			: orientation(orientation_), size(size_), origin(origin_) {
		}
	};

	static FVector2D hex_to_pixel(Layout layout, FHex h) {
		const Orientation& M = layout.orientation;
		double x = (M.f0 * h.q + M.f1 * h.r) * layout.size.X;
		double y = (M.f2 * h.q + M.f3 * h.r) * layout.size.Y;
		return FVector2D(x + layout.origin.X, y + layout.origin.Y);
	}

	struct FractionalHex {
		const double q, r, s;
		FractionalHex(double q_, double r_, double s_)
			: q(q_), r(r_), s(s_) {
		}
	};

	static FractionalHex pixel_to_hex_fractional(Layout layout, FVector2D p) {
		const Orientation& M = layout.orientation;
		FVector2D pt = FVector2D((p.X - layout.origin.X) / layout.size.X,
			(p.Y - layout.origin.Y) / layout.size.Y);
		double q = M.b0 * pt.X + M.b1 * pt.Y;
		double r = M.b2 * pt.X + M.b3 * pt.Y;
		return FractionalHex(q, r, -q - r);
	}

	static FHex hex_round(FractionalHex h) {
		int q = int(round(h.q));
		int r = int(round(h.r));
		int s = int(round(h.s));
		double q_diff = abs(q - h.q);
		double r_diff = abs(r - h.r);
		double s_diff = abs(s - h.s);
		if (q_diff > r_diff and q_diff > s_diff) {
			q = -r - s;
		}
		else if (r_diff > s_diff) {
			r = -q - s;
		}
		else {
			s = -q - r;
		}
		return FHex(q, r, s);
	}

	static FHex pixel_to_hex_rounded(Layout layout, FVector2D p) {
		return hex_round(pixel_to_hex_fractional(layout, p));
	}

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector SnapVectorToVector(FVector V1, FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction);
};
