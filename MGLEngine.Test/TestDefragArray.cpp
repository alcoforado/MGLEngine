#include "catch.hpp"
#include <MGLEngine.Shared/Utils/DefragArray/ArrayRegion.h>
#include "MGLEngine.Shared/Utils/DefragArray/CopyRegion.h"
#include "MGLEngine.Shared/Utils/DefragArray/DefragArray.h"

TEST_CASE("Adjacent Regions Can Be  Merged")
{
	ArrayRegion r1 = { 0,4 };
	ArrayRegion r2 = { 5,2 };
	ArrayRegion r3 = { 2,1 };
	ArrayRegion r4 = { 4,3 };
	ArrayRegion r5 = { 3,10 };
	SECTION("Detect Intersections")
	{
		REQUIRE(!r1.Intersects(r2));
		REQUIRE(!r2.Intersects(r1));
		REQUIRE(r1.Intersects(r3));
		REQUIRE(!r1.Intersects(r4));
		REQUIRE(r1.Intersects(r5));
		REQUIRE(r5.Intersects(r1));
		REQUIRE(!r2.Intersects(r3));
	}
	SECTION("Continuously Follow")
	{
		REQUIRE(!r1.ContinuouslyFollows(r2));
		REQUIRE(!r2.ContinuouslyFollows(r1));
		REQUIRE(!r1.ContinuouslyFollows(r3));
		REQUIRE(!r1.ContinuouslyFollows(r4));
		REQUIRE(r4.ContinuouslyFollows(r1));
		REQUIRE(!r1.ContinuouslyFollows(r5));
		REQUIRE(!r5.ContinuouslyFollows(r1));
		REQUIRE(!r2.ContinuouslyFollows(r3));
		REQUIRE(!r3.ContinuouslyFollows(r5));
	}
	

}



TEST_CASE("Array Defragmentation")
{
	//0 1 | 2 3 | 4 5 6 | 7 8 => 0 1 | 4 5 6 | 7 8
	std::vector<int> s = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };
	std::vector<int> r = { 0,1,4,5,6,7,8 };

	SECTION("One Block Insertion Followed by Deletion")
	{
		//0 1 | 2 3 | 4 5 6 | 7 8 => 0 1 | x x x x | 2 3 |  7 8
		std::vector<CopyRegion> vInsertion;
		vInsertion.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(2, 2), ArrayRegion(6, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(8, 2)));

		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vInsertion);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[6] == 2);
		REQUIRE(s[7] == 3);
		REQUIRE(s[8] == 7);
		REQUIRE(s[9] == 8);


	}

	SECTION("One Block Deletion Followed by Insertion")
	{
		//0 1 | 2 3 | 4 5 6 | 7 8 => 0 1 | 4 5 6 | x |  7 8
		std::vector<CopyRegion> vInsertion;
		vInsertion.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(4, 3), ArrayRegion(2, 3)));
		vInsertion.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(6, 2)));

		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vInsertion);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[2] == 4);
		REQUIRE(s[3] == 5);
		REQUIRE(s[4] == 6);
		REQUIRE(s[6] == 7);
		REQUIRE(s[7] == 8);


	}




	SECTION ("One Block Insertion")
	{
		//0 1 | 2 3 | 4 5 6 | 7 8 => 0 1 | x x x | 2 3 | 4 5 6 | 7 8

		std::vector<CopyRegion> vInsertion;
		vInsertion.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(2, 2), ArrayRegion(5, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(4, 3), ArrayRegion(7, 3)));
		vInsertion.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(10, 2)));

		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vInsertion);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[5] == 2);
		REQUIRE(s[6] == 3);
		REQUIRE(s[7] == 4);
		REQUIRE(s[8] == 5);
		REQUIRE(s[9] == 6);
		REQUIRE(s[10] == 7);
		REQUIRE(s[11] == 8);

	}
	
	SECTION("2 Block Insertion")
	{
		//0 1 | 2 3 | 4 5 6 | 7 8 => 0 1 | x x x | 2 3 | x x | 4 5 6 | 7 8

		std::vector<CopyRegion> vInsertion;
		vInsertion.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(2, 2), ArrayRegion(5, 2)));
		vInsertion.push_back(CopyRegion(ArrayRegion(4, 3), ArrayRegion(9, 3)));
		vInsertion.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(12, 2)));

		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vInsertion);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[5] == 2);
		REQUIRE(s[6] == 3);
		REQUIRE(s[9] == 4);
		REQUIRE(s[10] == 5);
		REQUIRE(s[11] == 6);
		REQUIRE(s[12] == 7);
		REQUIRE(s[13] == 8);

	}


	
	SECTION("Block  Deletion") {
		std::vector<CopyRegion> vDeletion;
		vDeletion.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vDeletion.push_back(CopyRegion(ArrayRegion(4, 3), ArrayRegion(2, 3)));
		vDeletion.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(5, 2)));


		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vDeletion);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[2] == 4);
		REQUIRE(s[3] == 5);
		REQUIRE(s[4] == 6);
		REQUIRE(s[5] == 7);
		REQUIRE(s[6] == 8);
	}

	SECTION("Two block deletions") {
		//0 1 | 2 3 | 4 5 6 | 7 8 | 9 | 10 11| 12 => 0 1 | 4 5 6 | 7 8
		std::vector<CopyRegion> vDeletion2;
		vDeletion2.push_back(CopyRegion(ArrayRegion(0, 2), ArrayRegion(0, 2)));
		vDeletion2.push_back(CopyRegion(ArrayRegion(4, 3), ArrayRegion(2, 3)));
		vDeletion2.push_back(CopyRegion(ArrayRegion(7, 2), ArrayRegion(5, 2)));
		vDeletion2.push_back(CopyRegion(ArrayRegion(10, 2), ArrayRegion(7, 2)));
		vDeletion2.push_back(CopyRegion(ArrayRegion(12, 1), ArrayRegion(9, 1)));

		DefragArray<int> defrag;
		defrag.ReorganizeArray(s, vDeletion2);
		REQUIRE(s[0] == 0);
		REQUIRE(s[1] == 1);
		REQUIRE(s[2] == 4);
		REQUIRE(s[3] == 5);
		REQUIRE(s[4] == 6);
		REQUIRE(s[5] == 7);
		REQUIRE(s[6] == 8);
		REQUIRE(s[7] == 10);
		REQUIRE(s[8] == 11);
		REQUIRE(s[9] == 12);

	}


}
