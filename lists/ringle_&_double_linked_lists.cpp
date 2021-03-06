// ListTestsLabs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

typedef int s32;
typedef unsigned int u32;

template<typename T>
struct node {
	T data;
	node *next;
};

template<typename T>
node<T> *make_list(const s32 size) {
	node<T> *list = nullptr;

	for (s32 i = size - 1; i >= 0; --i)
		list = new node<T>{(T)i, list};

	return list;
}

template<typename T>
void delete_list(node<T> **list) {
	node<T> *del_list = *list;

	while (del_list) {
		node<T> *cashe = del_list->next;
		delete del_list;

		del_list = cashe;
	}

	*list = nullptr;
}

template<typename T>
void print_list(node<T> **list) {
	std::cout << "print list" << std::endl;

	node<T> *pr_list = *list;
	while (pr_list) {
		std::cout << pr_list->data << " ";
		pr_list = pr_list->next;
	}

	std::cout << std::endl;
}

template<typename T>
node<T> *make_rounded_list(const s32 size) {
	if (size <= 1) return nullptr;

	node<T> *head = nullptr;
	node<T> *list = nullptr;
	node<T> *prev = nullptr;

	for (s32 i = 0; i < size; ++i) {
		list = new node<T>{(T)i, head};
		if (prev)
			prev->next = list;

		prev = list;

		if (i == 0)
			head = list;
	}

	return list;
}

template<typename T>
void delete_rounded_list(node<T> **list) {
	node<T> *cur = *list;
	node<T> *head = *list;

	if (!cur) return;
	do {
		node<T> *cashe = cur->next;

		delete cur;
		cur = cashe;
	} while (cur != head);

	*list = nullptr;
}

template<typename T>
void print_rounded_list(node<T> **list) {
	std::cout << "print rounded list" << std::endl;
	node<T> *head = *list;
	node<T> *cur = *list;

	if (!head) return;

	do {
		std::cout << cur->data << " ";
		cur = cur->next;
	} while (cur != head);

	std::cout << std::endl;
}

template<typename T>
void delete_first_element_from_ringle_list(node<T> **list) {
	node<T> *head = *list;
	node<T> *cur = *list;
	node<T> *prev = *list;

	node<T> *cashe = cur->next;
		
	 do {
		 prev = cur;
		 cur = cur->next;
	} while (cur != head);

	head = cashe;
	prev->next = head;

	delete cur;
	*list = head;
}

template<typename T>
void add_node_to_ringle_list(node<T> **list, node<T> *new_node) {
	node<T> *add = new node<T>{ new_node->data, nullptr };
	if (!*list) {
		add->next = add;
		*list = add;
		return;
	}

	node<T> *prev = nullptr;
	node<T> *cur = *list;
	node<T> *head = *list;

	do {
		prev = cur;
		cur = cur->next;
	} while (cur != head);

	prev->next = add;
	add->next = head;
}

template<typename T>
node<T> *delete_elements_and_create_new_list(node<T> **list, const u32 count) {
	node <T> *head = *list;
	node <T> *last = *list;
	node <T> *prev = nullptr;

	node<T> *new_rounded_list = nullptr;

	u32 list_size = 0;
	do {
		++list_size;
		last = last->next;
	} while (last != head);

	for (u32 i = 0; i < count && i < list_size; ++i) {
		last = *list;
		do {
			prev = last;
			last = last->next;
		} while (last != head);

		head = head->next;

		if (prev)
			prev->next = head;

		add_node_to_ringle_list(&new_rounded_list, last);
		delete last;

		*list = head;
	}

	if (count > list_size)
		*list = nullptr;
	
	return new_rounded_list;
}

template<typename T>
T find_max_value(node<T> **list) {
	node<T> *cashe_list = *list;
	if (!cashe_list) return -1;

	T max = cashe_list->data;

	while (cashe_list) {
		if (cashe_list->data > max)
			max = cashe_list->data;

		cashe_list = cashe_list->next;
	}

	return max;
}


template<typename T>
void insert_max_after_greater_value(node<T> **list, const T &value) {
	node<T> *cashe_list = *list;

	if (!cashe_list) return;

	node<T> *prev = nullptr;

	while (cashe_list) {
		if (cashe_list->data > value) {
			T max = find_max_value(list);

			node <T> *new_node = new node<T>{ max, cashe_list->next };
			cashe_list->next = new_node;
			break;
		}

		prev = cashe_list;
		cashe_list = cashe_list->next;
	}
}

template<typename T>
void delete_key_and_revert_two_next(node<T> **list, const T &key) {
	node <T> *value = *list;
	node <T> *prev = nullptr;

	while (value) {
		node <T> *cashe = value->next;
		if (value->data == key) {
			node <T> *replace_value_first = cashe;
			if (!replace_value_first)
				break;

			node <T> *replace_value_second = cashe->next;
			if (!replace_value_second)
				break;

			replace_value_first->next = replace_value_second->next;
			replace_value_second->next = replace_value_first;

			if (prev)
				prev->next = replace_value_second;
			else
				*list = replace_value_second;

			delete value;
		} else {
			prev = value;
		}

		value = cashe;
	}
}

int need_print_node = 0;

template <typename T>
void print_reverse(node<T> **list, const T &value) {
	node<T> *pr_node = *list;

	if (!pr_node) return;

	if (pr_node->data == value) ++need_print_node;

	print_reverse(&pr_node->next, value);

	if (need_print_node == 0) return;

	if (pr_node->data == value)
		--need_print_node;
	//else
		std::cout << pr_node->data << " ";
}

template <typename T>
int count_values(node<T> **list, const T &value) {
	node<T> *pr_node = *list;

	if (!pr_node) return 0;
	int value_num = 0;

	while (pr_node) {
		if (pr_node->data == value)
			++value_num;

		pr_node = pr_node->next;
	}

	return value_num;
}

template <typename T>
void double_values(node<T> **list, const T &value) {
	node<T> *cur = *list;

	while (cur) {
		node <T> *cashe = cur->next;
		if (cur->data == value) {
			node <T> *new_node = new node<T>{value, cur->next};

			cur->next = new_node;
		}

		cur = cashe;
	}
}

template<typename T>
void add_reverted_list_to_end(node<T> **list) {
	node<T> *cur = *list;
	if (!cur) return;

	add_reverted_list_to_end(&cur->next);

	node<T> *new_node = new node<T>{ cur->data, nullptr };

	while (cur) {
		node<T> *cashe = cur->next;
		if (!cashe) {
			cur->next = new_node;
			break;
		} else {
			cur = cashe;
		}
	}
}

template <typename T>
void print_reverted_from_first_to_last(node<T> **list) {
	node<T> *cur = *list;
	if (!cur) return;

	static int el_num, rec_depth;
	++el_num; ++rec_depth;

	print_reverted_from_first_to_last(&cur->next);

	if (rec_depth > 5 && --el_num && cur->next)
		std::cout << cur->data << " ";
}

template<typename T>
void find_average_value(node<T> **list) {
	node<T> *cur = *list;

	int sum = 0;
	int el_num = 0;

	while (cur) {
		sum += cur->data;
		++el_num;
		cur = cur->next;
	}

	std::cout << std::endl << "average value " << (double)sum / el_num << " " << std::endl;
}

template<typename T>
void delete_value_from_first_max(node<T> **list) {
	node<T> *cur = *list;
	node<T> *prev = nullptr;

	T max = find_max_value(list);

	bool need_delete_value = false;
	while (cur) {
		if (need_delete_value) {
			node<T> *cashe = cur->next;
			delete cur;

			prev->next = cashe;
			break;
		}

		if (cur->data == max) {
			need_delete_value = true;
		}

		prev = cur;
		cur = cur->next;
	}
}

template<typename T>
T find_min_value(node<T> **list) {
	node<T> *cur = *list;

	T min = INT32_MAX;
	while(cur) {
		if (cur->data < min)
			min = cur->data;

		cur = cur->next;
	}

	return min;
}


template<typename T>
void find_first_min_and_last_max_and_reverse(node<T> **list, const T &min, const T &max) {
	node<T> *cur_min = *list, *cur_max = *list, *last_max_value = *list;
	node<T> *prev_min = nullptr, *prev_max = nullptr;

	while (cur_min) {
		if (cur_min->data == min)
			break;

		prev_min = cur_min;
		cur_min = cur_min->next;
	}

	node<T> *pr = nullptr;
	while (cur_max) {
		if (cur_max->data == max) {
			last_max_value = cur_max;
			prev_max = pr;
		}

		pr = cur_max;
		cur_max = cur_max->next;
	}

	if (prev_min)
		prev_min->next = last_max_value;

	if (prev_max)
		prev_max->next = cur_min;

	node<T> *cashe = cur_min->next;
	node<T> *cashe_1 = last_max_value->next;

	last_max_value->next = cashe;
	cur_min->next = cashe_1;
}


template<typename T>
bool is_sorted(node<T> **list, const bool ascending) {
	node<T> *cur = *list;

	T data = cur->data;
	while (cur) {
		if ((ascending && cur->data < data) || (!ascending && cur->data > data))
			return false;

		data = cur->data;
		cur = cur->next;
	}

	return true;
}

template<typename T>
void swap(node<T> *value_1, node<T> *value_2) {
	T temp = value_1->data;
	value_1->data = value_2->data;
	value_2->data = temp;
}

template<typename T>
void bubble_sort_for_list(node<T> **list) {
	node<T> *cur = *list;
	bool swapped = false;

	node<T> *start_node = *list;
	do {
		swapped = false;
		while (cur) {
			node<T> *next = cur->next;

			if (next && cur->data < next->data) {
				swap(cur, next);
				swapped = true;
			}
			cur = cur->next;
		}
		cur = start_node;
	} while (swapped);
}

template<typename T>
void find_first_max_and_min_and_exchange_it(node<T> **list) {
	node<T> *cur = *list;
	T min = find_min_value(list);
	T max = find_max_value(list);

	bool find_min = false;

	node<T> *cashe_node_min = nullptr;
	node<T> *cashe_node_max = nullptr;
	while (cur) {
		if (!find_min && cur->data == min) {
			cashe_node_min = cur;
			find_min = true;
		}

		if (cur->data == max)
			cashe_node_max = cur;

		cur = cur->next;
	}

	if (cashe_node_min && cashe_node_max)
		swap(cashe_node_min, cashe_node_max);
}

template<typename T>
struct d_node {
	T data;
	d_node *prev;
	d_node *next;
};

template<typename T>
d_node<T> *make_d_node_list(const s32 size) {
	d_node<T> *list = nullptr;

	for (s32 i = size - 1; i >=0  ; --i) {
		list = new d_node<T>{ (T)i, nullptr, list };
		if (list->next)
			list->next->prev = list;
	}

	return list;
}

template<typename T>
void delete_d_node_list(d_node<T> **list) {
	d_node<T> *cur = *list;

	while (cur) {
		d_node<T> *cashe = cur->next;
		delete cur;

		cur = cashe;
	}

	*list = nullptr;
}

template<typename T>
void print_d_node(d_node<T> **list) {
	d_node<T> *cur = *list;
	
	while (cur) {
		std::cout << cur->data << " ";
		cur = cur->next;
	}

	std::cout << std::endl;
}

template<typename T>
void delete_key_d_node(d_node<T> **list, T key) {
	d_node<T> *cur = *list;

	while (cur) {
		if (cur->data == key) {
			d_node<T> *next = cur->next;
			d_node<T> *prev = cur->prev;
			
			prev->next = next;
			next->prev = prev;
		}
		cur = cur->next;
	}
}

int main()
{
	const s32 size = 10;
	/*
	node<int> *list = make_list<int>(size);
	print_list(&list);

	delete_key_and_revert_two_next(&list, 0);
	print_list(&list);

	insert_max_after_greater_value(&list, 4);
	print_list(&list);

	const int value = 9;
	if (count_values(&list, value) == 2)
		print_reverse(&list, value);

	double_values(&list, 9);
	print_list(&list);

	add_reverted_list_to_end(&list);
	print_list(&list);

	print_reverted_from_first_to_last(&list);
	find_average_value(&list);

	delete_value_from_first_max(&list);
	print_list(&list);

	//find_first_min_and_last_max_and_reverse(&list, find_min_value(&list), find_max_value(&list));
	//print_list(&list);

	find_first_max_and_min_and_exchange_it(&list);
	print_list(&list);

	if (!is_sorted(&list, true))
		bubble_sort_for_list(&list);

	print_list(&list);

	delete_list(&list);
	//print_list(&list);*/

	//node<int> *list = make_rounded_list<int>(size);
	//print_rounded_list(&list);

	//delete_first_element_from_ringle_list(&list);
	//print_rounded_list(&list);
	
	//node<int> *new_rounded_list = delete_elements_and_create_new_list<int>(&list, 11);
	//print_rounded_list(&list);
	//print_rounded_list(&new_rounded_list);
	//
	//delete_rounded_list(&list);
	//print_rounded_list(&list);
	//
	//delete_rounded_list(&new_rounded_list);
	//print_rounded_list(&list);

	d_node<int> *d_linked_list = make_d_node_list<int>(size);
	print_d_node(&d_linked_list);

	delete_key_d_node(&d_linked_list, 3);
	print_d_node(&d_linked_list);

	delete_d_node_list(&d_linked_list);
	print_d_node(&d_linked_list);

	system("pause");
	 
    return 0;
}

