#include <iostream>
#include <fstream>
#include <sstream> 

#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "main.h"


//#define DEBUG

using namespace std;
using namespace qgl;


void print_cartesian_cpu(AuthorBook *cartesian, int num_authors, int num_books) {
	int i, j;
	int current = 0;

	for (i = 0; i < num_authors; i++)
	{
		for (j = 0; j < num_books; j++)
		{
			current++;

			printf("%d\n", current);
			cartesian[i + j].print_details();
			printf("\n");
		}
	}
}

void benchmark_cartesian_product_gpu(Author *author_list, const int num_authors, Book *books_list, const int num_books) {
	cout << "cartesion product on GPU" << endl;

	cout << endl;
	cout << "Authors: " << num_authors << endl;
	cout << "Books:   " << num_books << endl;

	cout << endl;
	cout << "Cartesian product: " << num_authors * num_books << " elements" << endl;

	QGLibraray qgl;

	// on windows this is wall time
	// on linux this is cpu time
	clock_t begin = clock();

	qgl.cartesian_product(author_list, num_authors, books_list, num_books);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %.2f\n\n", time_spent);
}

void benchmark_cartesian_product_cpu(Author *author_list, int num_authors, Book *books_list, int num_books) {
	cout << "cartesion product on CPU" << endl;

	cout << endl;
	cout << "Authors: " << num_authors << endl;
	cout << "Books:   " << num_books << endl;

	cout << endl;
	cout << "Cartesian product: " << num_authors * num_books << " elements" << endl << endl;
	
	QGLibraray qgl;

	// on windows this is wall time
	// on linux this is cpu time
	clock_t begin = clock();

	qgl.cartesian_product_cpu(author_list, num_authors, books_list, num_books);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Total time: %.2f\n\n", time_spent);
}

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

	while (!books_file.eof() && current_book_position < *num_books_ptr)
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

void read_authors(Author *authors_ptr, const int *num_authors_ptr) {
	ifstream authors_file("D:\\Downloads_WD\\UnstructuredDB_v2\\UnstructuredDB\\bin\\authors.xml");

	string line_1;
	string line_2;
	string line_3;
	string line_4;
	string line_5;
	string line_6;

	string::size_type st;

	string first_name;
	string last_name;
	int author_id;

	int num_authors = 0;
	int current_author_position = 0;

	while (!authors_file.eof() && current_author_position < *num_authors_ptr)
	{
		if (num_authors == 0) {
			// read the xml header, then
			// override content later
			getline(authors_file, line_1);
			getline(authors_file, line_1);
		}

		getline(authors_file, line_1);
		getline(authors_file, line_2);
		getline(authors_file, line_3);
		getline(authors_file, line_4);
		getline(authors_file, line_5);
		getline(authors_file, line_6);

		if (line_1 == "</AVTORI>") {
			break;
		}

#ifdef DEBUG
		cout << endl << "Line 1: " << line_1 << endl;
		cout << "Line 2: " << line_2 << endl;
		cout << "Line 3: " << line_3 << endl;
		cout << "Line 4: " << line_4 << endl;
		cout << "Line 5: " << line_4 << endl;
		cout << "Line 6: " << line_4 << endl;
#endif // DEBUG

		// author id
		//author_id = stoi(line_1.substr(11, line_3.length() - 11 - 8), &st, 10);
		author_id = stoi(line_1.substr(13, line_1.length() - 13 - 1), &st, 10);
		//cout << "Author ID: " << author_id << endl;

		// fist name
		first_name = line_3.substr(11, (line_3.length() - 11 - 6));
		//cout << "First Name: " << first_name << endl;

		last_name = line_4.substr(15, (line_4.length() - 15 - 10));
		//cout << "Last Name: " << last_name << endl;

		// add to the list of book
		authors_ptr[current_author_position].author_id = author_id;
		strcpy(authors_ptr[current_author_position].first_name, first_name.c_str());
		strcpy(authors_ptr[current_author_position].last_name, last_name.c_str());

		num_authors++;
		current_author_position++;
	}

#ifdef DEBUG
	cout << "Books: " << num_books << endl;
#endif // DEBUG

	authors_file.close();

}

void print_books(Book *books_list, const int *num_books) {
	int i;
	for (i = 0; i < *num_books; i++) {
		//cout << "book_list[" << i << "]:" << endl;
		cout << i << endl;
		books_list[i].print_details();
		cout << endl;
	}
}

void print_authors(Author *author_list, const int *num_authors) {
	int i;
	for (i = 0; i < *num_authors; i++) {
		cout << i << endl;
		author_list[i].print_details();
		cout << endl;
	}
}

void benchmark_increse_books_outhor_id(Book *books_list, int num_books, int ammount) {
	QGLibraray qgl;

	unsigned long time_cpu;
	unsigned long time_gpu;

	qgl.increse_books_outhor_id(books_list, num_books, ammount);
}

void benchmark_agregate_function(Book *books_list, int num_books, int ammount) {
	benchmark_increse_books_outhor_id(books_list, num_books, ammount);
}



void termianate_program() {
	char dammy;

	cout << "Press ENTER to exit" << endl;
	scanf("%c", &dammy);
}

int main() {

	//const int num_books = 123;
	//const int num_books = 460;
	const int num_books = 2000;		// <-- good for GPU
	//const int num_books = 4000;
	//const int num_books = 5;

	//const int num_authors = 123;
	//const int num_authors = 12;
	//const int num_authors = 462;
	const int num_authors = 4000;	// <-- good for GPU
	//const int num_authors = 5;

	int ammount = 5;

	Book books_list[num_books];
	Author author_list[num_authors];

	// books
	read_books(books_list, &num_books);		// pass pointer to the memory address alocated for the list of books
											// pass pointer to the memory address used to store number of books

	//cout << "Original: " << endl;
	//print_books(books_list, &num_books);

	//benchmark_agregate_function(books_list, num_books, ammount);
	
	//cout << endl <<"Incressed: " << endl;
	//print_books(books_list, &num_books);

	// authors
	read_authors(author_list, &num_authors);
	
	//cout << "Original: " << endl;
	//print_authors(author_list, &num_authors);
	benchmark_cartesian_product_cpu(author_list, num_authors, books_list, num_books);
	benchmark_cartesian_product_gpu(author_list, num_authors, books_list, num_books);

	termianate_program();

	return 0;
}