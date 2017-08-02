#include <iostream>
#include <fstream>
#include <sstream> 

#include "main.h"

//#define DEBUG

using namespace std;
using namespace qgl;

void read_books(Book *books_ptr, const int *num_books_ptr) {
	ifstream books_file("D:\\Downloads_WD\\UnstructuredDB_v2\\UnstructuredDB\\bin\\books.xml");

	string line_1;
	string line_2;
	string line_3;
	string line_4;

	string::size_type st;

	string title;
	int invenatr_id;
	int author_id;

	int num_books = 0;
	int current_book_position = 0;

	while (!books_file.eof() || current_book_position <= *num_books_ptr)
	{
		if (num_books == 0) {
			// read the xml header, then
			// override content later
			getline(books_file, line_1);
			getline(books_file, line_1);
		}

		getline(books_file, line_1);
		getline(books_file, line_2);
		getline(books_file, line_3);
		getline(books_file, line_4);

		if (line_1 == "</KNIGI>") {
			break;
		}

#ifdef DEBUG
	cout << endl << "Line 1: " << line_1 << endl;
	cout << "Line 2: " << line_2 << endl;
	cout << "Line 3: " << line_3 << endl;
	cout << "Line 4: " << line_4 << endl;
#endif // DEBUG

		// inventar
		invenatr_id = stoi(line_1.substr(16, (line_1.length() - 16 - 2)), &st, 10);
		//cout << "inventar_br: " << invenatr_id << endl;

		// title
		title = line_2.substr(12, (line_2.length() - 12 - 9));
		//cout << "title: " << title << endl;

		// author id
		author_id = stoi(line_3.substr(11, line_3.length() - 11 - 8), &st, 10);
		//cout << "author_id: " << author_id << endl;

		// add to the list of book
		books_ptr[current_book_position].set_author_id(author_id);
		books_ptr[current_book_position].set_invertar_id(invenatr_id);
		books_ptr[current_book_position].set_title(title);

		num_books++;
		current_book_position++;
	}

#ifdef DEBUG
	cout << "Books: " << num_books << endl;
#endif // DEBUG

	books_file.close();
}

void print_books(Book *books_list, const int *num_books) {
	int i;
	for (i = 0; i < *num_books; i++) {
		//cout << "book_list[" << i << "]:" << endl;
		books_list[i].print_details();
		cout << endl;
	}
}

void benchmark_increse_books_outhor_id(Book *books_list, int num_books, int ammount) {
	QGLibraray qgl;

	unsigned long time_cpu;
	unsigned long time_gpu;

	qgl.increse_books_outhor_id(books_list, num_books, ammount);
}

void termianate_program() {
	char dammy;

	cout << "Press ENTER to exit" << endl;
	scanf("%c", &dammy);
}

int main() {

	const int num_books = 123;
	int ammount = 5;

	Book books_list[num_books];
	read_books(books_list, &num_books);		// pass pointer to the memory address alocated for the list of books
											// pass pointer to the memory address used to store number of books

	cout << "Original: " << endl;
	print_books(books_list, &num_books);

	benchmark_increse_books_outhor_id(books_list, num_books, ammount);

	cout << endl <<"Incressed: " << endl;
	print_books(books_list, &num_books);

	termianate_program();

	return 0;
}