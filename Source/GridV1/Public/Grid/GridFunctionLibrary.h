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

	FORCEINLINE bool operator == (const FHex& Other) const
	{
		return q == Other.q && r == Other.r && s == Other.s;
	}

	FORCEINLINE bool operator != (const FHex& Other) const
	{
		return !(*this == Other);
	}

};

FORCEINLINE uint32 GetTypeHash(const FHex& Hex)
{
	uint32 HashQ = ::GetTypeHash(Hex.q);
	uint32 HashR = ::GetTypeHash(Hex.r);

	return HashCombine(HashQ, HashR);
}

USTRUCT()
struct FOrientation {
	GENERATED_BODY();

	double f0, f1, f2, f3;
	double b0, b1, b2, b3;
	double start_angle; // in multiples of 60°
	FOrientation(double f0_, double f1_, double f2_, double f3_,
		double b0_, double b1_, double b2_, double b3_,
		double start_angle_)
		: f0(f0_), f1(f1_), f2(f2_), f3(f3_),
		b0(b0_), b1(b1_), b2(b2_), b3(b3_),
		start_angle(start_angle_) {
	}

	FOrientation()
		: f0(0), f1(0), f2(0), f3(0),
		b0(0), b1(0), b2(0), b3(0),
		start_angle(0) {
	}
};

USTRUCT()
struct FLayout {
	GENERATED_BODY();

	FOrientation orientation;
	FVector2D size;
	FVector2D origin;
	FLayout(FOrientation orientation_, FVector2D size_, FVector2D origin_)
		: orientation(orientation_), size(size_), origin(origin_) {
	}

	FLayout()
		: orientation(FOrientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
			2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
			0.0)), size(FVector2D(1, 1)), origin(FVector2D::ZeroVector) {
	}
};

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

	static const FOrientation layout_flat;

	static FVector2D hex_to_pixel(FLayout layout, FHex h) {
		const FOrientation& M = layout.orientation;
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

	static FractionalHex pixel_to_hex_fractional(FLayout layout, FVector2D p) {
		const FOrientation& M = layout.orientation;
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

	static float lerp(double a, double b, double t) {
		return a * (1 - t) + b * t;
		/* better for floating point precision than
		   a + (b - a) * t, which is what I usually write */
	}

	static FractionalHex hex_lerp(FHex a, FHex b, double t) {
		return FractionalHex(lerp(a.q, b.q, t),
			lerp(a.r, b.r, t),
			lerp(a.s, b.s, t));
	}

	static FHex pixel_to_hex_rounded(FLayout layout, FVector2D p) {
		return hex_round(pixel_to_hex_fractional(layout, p));
	}

	TArray<FHex> hex_linedraw(FHex a, FHex b) {
		int N = hex_distance(a, b);
		FractionalHex a_nudge(a.q + 1e-6, a.r + 1e-6, a.s - 2e-6);
		FractionalHex b_nudge(b.q + 1e-6, b.r + 1e-6, b.s - 2e-6);
		TArray<FHex> results = {};
		double step = 1.0 / FMath::Max(N, 1);
		for (int i = 0; i <= N; i++) {
			results.Add(
				hex_round(hex_lerp(hex_round(a_nudge), hex_round(b_nudge), step * i)));
		}
		return results;
	}
	
	static void CreateRectangularGrid(TSet<FHex>& MapContainer, int32 Width, int32 Height)
	{
		int32 left = -Width;
		int32 top = -Height;
		int32 right = Width;
		int32 bottom = Height;

		for (int q = left; q <= right; q++) { // flat top
			int q_offset = floor(q / 2.0); // or q>>1
			for (int r = top - q_offset; r <= bottom - q_offset; r++) {
				MapContainer.Emplace(FHex(q, r, -q - r));
			}
		}
	}

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static AActor* GetGridManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector SnapVectorToVector(FVector V1, FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction);
};
