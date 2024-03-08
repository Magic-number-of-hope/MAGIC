#pragma once
struct HEAD {
	char type[4];
	int length;
	int weight[256];
};