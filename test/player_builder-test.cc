#include "gtest/gtest.h"
#include <vector>

#include "player/player_builder.h"

TEST(PlayerBuilderTest, ShouldCreateShipAndExhaust) {
	PlayerBuilder pb;
	auto objects = pb.Build();
	EXPECT_EQ(objects.size(), 2);
}