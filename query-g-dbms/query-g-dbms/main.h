#pragma once
#include "query-g-libraray-headers\query-g-libraray.h"
#include "query-g-libraray-headers\book.h"

using namespace std;
namespace qgl {
	void demo_increse_book_id();
	void termianate_program();

	void demo_increse_book_id() {
		QGLibraray qgl;
		Book *b = new Book();

		b->print_details();

		qgl.increse_book_id(b, 3);
		b->print_details();

		free(b);
	}

	void termianate_program() {
		char dammy;

		cout << "Press ENTER to close terminal window" << endl;
		scanf("%c", &dammy);
	}
}
