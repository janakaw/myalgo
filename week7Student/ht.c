#define SIZE 36739
#define MULT 27541

//275412754127541275412754127541

int table[SIZE];

int
hash(int x)
{
	return ((x % SIZE) * MULT) % SIZE;
}
