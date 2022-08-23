#include <stdio.h>
#include <string.h>
#include "sorter.h"
#include <functional>

using namespace sorter;

class Person {
public:
	enum Gender { UNKNOWN, MALE, FEMALE };
	Person(const char *name, int age, Gender gender) :
		name(name), age(age), gender(gender) {}

	Person() {}

	void print() { printf("<%s,%d,%d>", name, age, gender); }

	static bool age_cmp(Person &a, Person &b) { return a.age <= b.age; }

	static bool name_cmp(Person &a, Person &b)
		{ return strcmp(a.name, b.name) <= 0; }

private:
	const char *name;
	int age;
	Gender gender;
};

void sort_test(std::function<void (Person arr[], int size,
			std::function<bool (Person &, Person &)> cmp)> fn,
		const char *prefix)
{
	const int SAMPLE_DATA_SIZE = 7;

	Person *testdata = new Person[SAMPLE_DATA_SIZE]{
		Person{"Harry", 10, Person::MALE},
		Person{"Ron", 10, Person::MALE},
		Person{"Hermione", 10, Person::FEMALE},
		Person{"Albus", 120, Person::MALE},
		Person{"Severus", 32, Person::MALE},
		Person{"Tom", 50, Person::MALE},
		Person{"Malfoy", 10, Person::MALE},
	};

	std::function<void ()> testdata_print = [testdata]() {
		printf("\t");
		for (int i = 0; i < SAMPLE_DATA_SIZE; i++)
			testdata[i].print();
		printf("\n");
	};

	printf("%s:\n", prefix);
	fn(testdata, SAMPLE_DATA_SIZE, &Person::name_cmp);
	testdata_print();

	fn(testdata, SAMPLE_DATA_SIZE, &Person::age_cmp);
	testdata_print();

	delete[] testdata;
}

int main(int argc, const char **argv) {
	sort_test(bubble_sort<Person>, "bubble sort");
	sort_test(selection_sort<Person>, "selection sort");
	sort_test(insertion_sort<Person>, "insertion sort");
	sort_test(shell_sort<Person>, "shell sort");
	sort_test(merge_sort_recur<Person>, "recursive merge sort");
	sort_test(merge_sort<Person>, "merge sort");
	sort_test(quick_sort_recur<Person>, "recursive quick sort");
	sort_test(quick_sort<Person>, "quick sort");
	sort_test(heap_sort<Person>, "heap sort");
	return 0;
}

