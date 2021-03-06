#pragma once

#ifndef QUERY_G_LIBRARAY
#define QUERY_G_LIBRARAY
#include <iostream>
#include "book.h"
#include "author.h"

using namespace std;
namespace qgl {

	// All declarations are within the namespace scope.
	// Notice the lack of indentation.
	class QGLibraray {
	public:
		QGLibraray();
		~QGLibraray();

		Book *find_book_by_id(int id);

		void increse_books_outhor_id    (Book *book, unsigned long num_books, int amount);
		void increse_books_outhor_id_cpu(Book *book, unsigned long num_books, int amount);

		void agregate_sum_cpu(Book* books, unsigned long num_books);
		void agregate_sum(Book* books, unsigned long num_books);

		void cartesian_product	  (Author *authors, unsigned long num_authors, Book *books, unsigned long num_books);
		void cartesian_product_cpu(Author *authors, unsigned long num_authors, Book *books, unsigned long num_books);

	private:

	};

}  // namespace qgl

#endif  // QUERY_G_LIBRARAY