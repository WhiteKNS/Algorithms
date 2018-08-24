#include <iostream>

template<typename T>
struct node {
	T data;
	node *next;
};

template<typename T>
node<T> *reverse(node<T> *list)
{
	node<T> *prev = nullptr;

	while (list)
	{
		node<T> *next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}

	return prev;
}

template<typename T>
void print_list(node<T> *&list) {
	node<T> *head = list;
	while (list != NULL) {
		std::cout << list->data << " ";
		list = list->next;
	}

	list = head;

	std::cout << std::endl;
}

template<typename T>
node<T> *make_list(const unsigned int L)
{
	node<T> *list = nullptr;

	for (unsigned int i = 0; i < L; ++i)
		list = new node<T>{ T(i), list };

	return list;
}

template<typename T >
void delete_list(node<T> *list)
{
	while (list)
	{
		node<T> *next = list->next;
		delete list;
		list = next;
	}
}

int main() {
	auto list = make_list<int>(10);
	std::cout << "List: " << std::endl;
	print_list(list);
	list = reverse(list);
	std::cout << "Reversed list: " << std::endl;
	print_list(list);

	delete_list(list);

	getchar();

	return 0;
}


есть список 1->2->3->4->5
1 элемент хранит в себе указатель на 2, 2 на 3 и тд
главное правило в алгоритмах для всех списков - их нужно разделить на две части. и просто поменять связи местами.
после переворота должно получиться
1<-2<-3<-4<-5
т.е. меняем только связи!!!
