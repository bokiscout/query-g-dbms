#include <iostream>
#include "query-g-libraray-headers\query-g-libraray.h"
#include "query-g-libraray-headers\book.h"

using namespace std;
using namespace qgl;

int main() {

	QGLibraray qgl;
	Book *b = new Book();

	b->print_details();

	qgl.increse_book_id(b, 3);
	b->print_details();

	char dammy;
	scanf("%c", &dammy);

	free(b);
	return 0;
}